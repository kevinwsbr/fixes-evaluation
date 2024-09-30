   def page_url_for(page)
     params = params_for(page)
     params[:only_path] = true
     @template.url_for(params).html_safe
   end

   class Page < Tag
     include Link

     #...

     def to_s(locals = {})
       locals[:page] = page
       super locals.map { |key, value| [key, value.to_s.html_safe] }.to_h
     end
   end

   class FirstPage < Tag
     include Link

     #...

     def to_s(locals = {})
       super locals.merge(url: url.html_safe)
     end
   end

   class LastPage < Tag
     include Link

     #...

     def to_s(locals = {})
       super locals.merge(url: url.html_safe)
     end
   end

   class PrevPage < Tag
     include Link

     #...

     def to_s(locals = {})
       super locals.merge(url: url.html_safe)
     end
   end

   class NextPage < Tag
     include Link

     #...

     def to_s(locals = {})
       super locals.merge(url: url.html_safe)
     end
   end
   