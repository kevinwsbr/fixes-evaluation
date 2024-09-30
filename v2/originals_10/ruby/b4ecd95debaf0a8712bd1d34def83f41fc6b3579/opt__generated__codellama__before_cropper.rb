module Paperclip
  class Cropper < Thumbnail

    def transformation_command
      if crop_command
        crop_command + super.join(' ').sub(/ -crop \S+/, '').split(' ')
      else
        super
      end
    end


    def crop_command
      target = @attachment.instance

      if target.cropping?(@attachment.name)
        w = validate_range(target.send :"#{@attachment.name}_crop_w")
        h = validate_range(target.send :"#{@attachment.name}_crop_h")
        x = validate_range(target.send :"#{@attachment.name}_crop_x")
        y = validate_range(target.send :"#{@attachment.name}_crop_y")
        ["-crop", "#{w}x#{h}+#{x}+#{y}"]
      end
    end

    def validate_range(value)
      if value < 0 || value > 100
        raise ArgumentError, "Invalid range for cropping parameter"
      end
      return value
    end

  end
end
