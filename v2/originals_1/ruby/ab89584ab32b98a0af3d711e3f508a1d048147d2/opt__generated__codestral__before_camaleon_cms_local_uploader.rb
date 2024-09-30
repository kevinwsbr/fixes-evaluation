class CamaleonCmsLocalUploader < CamaleonCmsUploader
  # ... rest of the code remains unchanged ...

  def browser_files(prefix = '/', objects = {})
    path = File.join(@root_folder, prefix)

    begin
      Dir.entries(path).each do |f_name|
        next if f_name == '..' || f_name == '.' || f_name == 'thumb'

        obj = file_parse(File.join(path, f_name).sub(@root_folder, '').cama_fix_media_key)
        cache_item(obj)

        if obj['is_folder']
          browser_files(File.join(prefix, obj['name']))
        end
      end
    rescue StandardError => e
      # handle exception here or log the error message:
      puts "An error occurred while iterating over directory entries: #{e.message}"
    end
  end

  # ... rest of the code remains unchanged ...
end
