func (d *DefaultGitlabRequestParserValidator) ParseAndValidate(r *http.Request, secret []byte) (interface{}, error) {
    const mergeEventHeader = "Merge Request Hook"
    const noteEventHeader = "Note Hook"

    // Validate secret if specified.
    headerSecret := r.Header.Get(secretHeader)
    secretStr := string(secret)
    if len(secret) != 0 && headerSecret != secretStr {
        return nil, fmt.Errorf("header %s=%s did not match expected secret", secretHeader, headerSecret)
    }

    // Check that the request body is not empty and contains valid JSON.
    bytes, err := io.ReadAll(r.Body)
    if err != nil {
        return nil, err
    }
    if len(bytes) == 0 || !json.Valid(bytes) {
        return nil, fmt.Errorf("request body is empty or contains invalid JSON")
    }

    // Parse request into a gitlab object based on the object type specified
    // in the gitlabHeader.
    switch r.Header.Get(gitlabHeader) {
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
            return e, err
        case "MergeRequest":
            var e gitlab.MergeCommentEvent
            err := json.Unmarshal(bytes, &e)
            return e, err
        }
    }
    return nil, nil
}
