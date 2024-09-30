package events

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"

	gitlab "github.com/xanzy/go-gitlab"
)

const secretHeader = "X-Gitlab-Token" // #nosec

// GitlabRequestParserValidator parses and validates GitLab requests.
type GitlabRequestParserValidator interface {
	// ParseAndValidate validates that the request has a token header matching secret.
	// If the secret does not match it returns an error.
	// If secret is empty it does not check the token header.
	// It then parses the request as a GitLab object depending on the header
	// provided by GitLab identifying the webhook type. If the webhook type
	// is not recognized it will return nil but will not return an error.
	// Usage:
	//	event, err := GitlabRequestParserValidator.ParseAndValidate(r, secret)
	//	if err != nil {
	//		return
	//	}
	//	switch event := event.(type) {
	//	case gitlab.MergeCommentEvent:
	//		// handle
	//	case gitlab.MergeEvent:
	//		// handle
	//	default:
	//		// unsupported event
	//	}
	ParseAndValidate(r *http.Request, secret []byte) (interface{}, error)
}

// DefaultGitlabRequestParserValidator parses and validates GitLab requests.
type DefaultGitlabRequestParserValidator struct{}

// ParseAndValidate returns the JSON payload of the request.
// See GitlabRequestParserValidator.ParseAndValidate().
func (d *DefaultGitlabRequestParserValidator) ParseAndValidate(r *http.Request, secret []byte) (interface{}, error) {
	const mergeEventHeader = "Merge Request Hook"
	const noteEventHeader = "Note Hook"

	// Validate secret if specified.
	headerSecret := r.Header.Get(secretHeader)
	if len(secret) != 0 && headerSecret != string(secret) {
		return nil, fmt.Errorf("header %s=%s did not match expected secret", secretHeader, headerSecret)
	}

	// Parse request into a gitlab object based on the object type specified
	// in the gitlabHeader.
	bytes, err := io.ReadAll(r.Body)
	if err != nil {
		return nil, err
	}
	switch r.Header.Get("GitLab-Event") {
	case mergeEventHeader:
		var m gitlab.MergeEvent
		if err := json.Unmarshal(bytes, &m); err != nil {
			return nil, err
		}
		return m, nil
	case noteEventHeader:
		// First, parse a small part of the json to determine if this is a
		// comment on a merge request or a commit.
		var subset struct {
			ObjectAttributes struct {
				NoteableType string `json:"noteable_type"`
			} `json:"object_attributes"`
		}
		if err := json.Unmarshal(bytes, &subset); err != nil {
			return nil, err
		}

		// We then parse into the correct comment event type.
		switch subset.ObjectAttributes.NoteableType {
		case "Commit":
			var e gitlab.CommitCommentEvent
			err := json.Unmarshal(bytes, &e)
			if err != nil {
				return nil, err
			}
			return e, nil
		case "MergeRequest":
			var e gitlab.MergeCommentEvent
			err := json.Unmarshal(bytes, &e)
			if err != nil {
				return nil, err
			}
			return e, nil
		default:
			// Unsupported event type
			return nil, fmt.Errorf("unsupported noteable_type: %s", subset.ObjectAttributes.NoteableType)
		}
	}
	return nil, nil
}
