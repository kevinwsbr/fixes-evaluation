```ruby
module Kaminari
  module Helpers
    PARAM_KEY_EXCEPT_LIST = [:authenticity_token, :commit, :utf8, :_method, :script_name].freeze

    # A tag stands for an HTML tag inside the paginator.
    # Basically, a tag has its own partial template file, so every tag can be
    # rendered into String using its partial template.
    #
    # The template file should be placed in your app/views/kaminari/ directory
    # with underscored class name (besides the "Tag" class. Tag is an abstract
    # class, so _tag partial is not needed).
    #   e.g.)  PrevLink  ->  app/views/kaminari/_prev_link.html.erb
    #
    # When no matching template were found in your app, the engine's pre
    # installed template will be used.
    #   e.g.)  Paginator  ->  $GEM_HOME/kaminari-x.x.x/app/views/kaminari/_paginator.html.erb
    class Tag
      def initialize(template, params: {}, param_name: nil, theme: nil, views_prefix: nil, **options) #:nodoc:
        @template, @theme, @views_prefix, @options = template, theme, views_prefix, options
        @param_name = param_name || Kaminari.config.param_name
        @params = template.params
        # @params in Rails 5 no longer needs to be converted to a Hash
        @params = @params.with_indifferent_access if @params.respond_to?(:with_indifferent_access)
        @params = @params.merge(params) if params

        ActiveSupport::Deprecation.warn 'Explicitly passing params to helpers is deprecated. Please use the :params option instead.' if params
      end

      def to_s(locals = {}) #:nodoc:
        locals[:params] = @params
        locals[:param_name] = @param_name
        locals[:theme] = @theme
        locals[:views_prefix] = @views_prefix

        @template.render partial: self.class.to_s.underscore, locals: locals
      end
    end

    # A page
    class Page < Tag
      # target page number
      def page
        @options[:page]
      end
    end

    # Link with page number that appears at the leftmost
    class FirstPage < Tag
      # target page number
      def page #:nodoc:
        1
      end
    end

    # Link with page number that appears at the rightmost
    class LastPage < Tag
      # target page number
      def page #:nodoc:
        @options[:total_pages]
      end
    end

    # The "previous" page of the current page
    class PrevPage < Tag
      # TODO: Remove this initializer before 1.3.0.
      def initialize(template, params: {}, param_name: nil, theme: nil, views_prefix: nil, **options) #:nodoc:
        super(template, params: params, param_name: param_name, theme: theme, views_prefix: views_prefix, **options)
      end

      def page #:nodoc:
        @options[:current_page] - 1
      end
    end

    # The "next" page of the current page
    class NextPage < Tag
      # TODO: Remove this initializer before 1.3.0.
      def initialize(template, params: {}, param_name: nil, theme: nil, views_prefix: nil, **options) #:nodoc:
        super(template, params: params, param_name: param_name, theme: theme, views_prefix: views_prefix, **options)
      end

      def page #:nodoc:
        @options[:current_page] + 1
      end
    end

    # Non-link tag that stands for skipped pages...
    class Gap < Tag
    end
  end
end
