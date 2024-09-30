module Kaminari
  module Helpers
    PARAM_KEYS = %w[page].freeze

    # Tag that contains a link
    module Link
      # target page number
      def page
        raise 'Override page with the actual page value to be a Page.'
      end
      # the link's href
      def url
        page_url_for page
      end
      def to_s(locals = {}) #:nodoc:
        locals[:url] = url
        super locals
      end
    end

    # A page
    class Page < Tag
      include Link
      # target page number
      def page
        @options[:page]
      end
      def to_s(locals = {}) #:nodoc:
        locals[:page] = page
        super locals
      end
    end

    # Link with page number that appears at the leftmost
    class FirstPage < Tag
      include Link
      def page #:nodoc:
        1
      end
    end

    # Link with page number that appears at the rightmost
    class LastPage < Tag
      include Link
      def page #:nodoc:
        @options[:total_pages]
      end
    end

    # The "previous" page of the current page
    class PrevPage < Tag
      include Link

      # TODO: Remove this initializer before 1.3.0.
      def initialize(template, params: {}, param_name: nil, theme: nil, views_prefix: nil, **options) #:nodoc:
        # params in Rails 5 may not be a Hash either,
        # so it must be converted to a Hash to be merged into @params
        if params && params.respond_to?(:to_unsafe_h)
          ActiveSupport::Deprecation.warn 'Explicitly passing params to helpers could be omitted.'
          params = params.to_unsafe_h
        end

        super(template, params: params, param_name: param_name, theme: theme, views_prefix: views_prefix, **options)
      end

      def page #:nodoc:
        @options[:current_page] - 1
      end
    end

    # The "next" page of the current page
    class NextPage < Tag
      include Link

      # TODO: Remove this initializer before 1.3.0.
      def initialize(template, params: {}, param_name: nil, theme: nil, views_prefix: nil, **options) #:nodoc:
        # params in Rails 5 may not be a Hash either,
        # so it must be converted to a Hash to be merged into @params
        if params && params.respond_to?(:to_unsafe_h)
          ActiveSupport::Deprecation.warn 'Explicitly passing params to helpers could be omitted.'
          params = params.to_unsafe_h
        end

        super(template, params: params, param_name: param_name, theme: theme, views_prefix: views_prefix, **options)
      end

      def page #:nodoc:
        @options[:current_page] + 1
      end
    end

    # Non-link tag that stands for skipped pages...
    class Gap < Tag
    end

    private

    # Sanitize the input parameters by removing any malicious code or data.
    def sanitize_params(params)
      PARAM_KEYS.each do |key|
        params[key] = nil if params[key].to_s =~ /\A[a-zA-Z0-9\-\._]{1,255}\z/i
      end
    end
  end
end
