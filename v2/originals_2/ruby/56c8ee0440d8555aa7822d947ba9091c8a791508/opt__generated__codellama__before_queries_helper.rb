[PYTHON]
class IssueQuerySelectHelper < Redmine::Helper
  include ActionView::Helpers::TagHelper
  include ActionView::Context
  include ActionView::Helpers::UrlHelper
  include ActionView::Helpers::FormTagHelper
  include ActionView::Helpers::FormOptionsHelper
  include Redmine::I18n

  def render_query(query, params = {})
    @project = query.project
    @query = query
    @filters = params[:filters] || {}
    @sort = params[:sort] || ''

    out = ''.html_safe
    out << '<h3>' + l(:label_my_queries) + '</h3><ul class="queries">'
    queries.each do |query|
      css = 'query'
      css << ' selected' if query == @query
      out << content_tag('li', link_to(query.name, url_for(:controller => 'issues', :action => 'index', :project_id => @project, :query_id => query), :class => css))
    end
    out << '</ul>'
  end

  def render_sidebar_queries(klass, project)
    queries = sidebar_queries(klass, project)

    out = ''.html_safe
    out << query_links(l(:label_my_queries), queries.select(&:is_private?))
    out << query_links(l(:label_query_plural), queries.reject(&:is_private?))
    out
  end

  private

  def sidebar_queries(klass, project)
    klass.visible.global_or_on_project(@project).sorted.to_a
  end

  def queries
    @query ||= retrieve_query_from_session
    if @query && !@query.is_a?(IssueQuery)
      raise ArgumentError, "Invalid query class: #{@query.class}"
    end

    @queries ||= sidebar_queries(IssueQuery, @project)
  end

  def retrieve_query_from_session(klass = IssueQuery)
    session_key = klass.name.underscore.to_sym
    session_data = session[session_key]

    if session_data
      if session_data[:id]
        @query = IssueQuery.find_by_id(session_data[:id])
        return unless @query
      else
        @query = IssueQuery.new(:name => "_", :filters => session_data[:filters], :group_by => session_data[:group_by], :column_names => session_data[:column_names], :totalable_names => session_data[:totalable_names], :sort_criteria => session[session_key][:sort])
      end
      if session_data.has_key?(:project_id)
        @query.project_id = session_data[:project_id]
      else
        @query.project = @project
      end
      @query
    end
  end
end
[/PYTHON]
