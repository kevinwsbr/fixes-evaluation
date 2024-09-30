 This is a Ruby on Rails helper module that provides functions for handling issue queries in Redmine. It includes methods for building and retrieving query objects, rendering query definitions as hidden field tags, and generating query links for the sidebar. Here are some of the key functions:

1. `build_query(klass = IssueQuery)`: This method builds a new query object based on parameters passed in the request. It initializes filters, columns, grouping, sorting criteria, and project information for the query. If an existing query is found in the session, it retrieves that query instead.

2. `retrieve_query_from_session(klass = IssueQuery)`: This method retrieves a query object from the user's session data. It checks if the session contains query data and creates a new query object based on that data if available.

3. `query_as_hidden_field_tags(query)`: This function generates hidden field tags for the given query object. These tags can be used to persist the query definition across requests.

4. `sidebar_queries(klass, project)`: This method returns an array of queries that are visible and either global or specific to a project, sorted by their default order.

5. `query_links(title, queries)`: This function generates HTML links for the given title and list of queries. It adds the "selected" class to the link corresponding to the current query being displayed.

6. `render_sidebar_queries(klass, project)`: This method renders the list of queries for the sidebar by calling the `query_links` function for private queries and public queries separately. It then concatenates the results and returns the HTML output.