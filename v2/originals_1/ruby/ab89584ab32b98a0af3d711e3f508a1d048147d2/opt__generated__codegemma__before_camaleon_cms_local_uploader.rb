class CamaleonCmsLocalUploader < CamaleonCmsUploader
  def after_initialize
    @root_folder = @args[:root_folder] || @current_site.upload_directory

    FileUtils.mkdir_p(@root_folder)
  rescue Exception => e
    # Log the exception or handle it appropriately
    Rails.logger.error("Exception in after_initialize: #{e}")
  end

  # ... remaining code
end
