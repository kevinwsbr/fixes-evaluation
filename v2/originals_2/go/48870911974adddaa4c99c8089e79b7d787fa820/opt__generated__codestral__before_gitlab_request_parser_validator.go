func (d *DefaultGitlabRequestParserValidator) ParseAndValidate(r *http.Request, secret []byte) (interface{}, error) {
    // ... (other code)

    headerSecret := r.Header.Get(secretHeader)
    if len(secret) != 0 && !hmac.Equal([]byte(headerSecret), secret) {
        return nil, fmt.Errorf("invalid credentials")
    }

    // ... (rest of the code)
}
