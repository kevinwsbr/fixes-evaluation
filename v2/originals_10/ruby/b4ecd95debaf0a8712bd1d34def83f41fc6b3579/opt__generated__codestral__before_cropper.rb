require "paperclip"

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
        w = target.send :"#{@attachment.name}_crop_w".to_i # convert to integer
        h = target.send :"#{@attachment.name}_crop_h".to_i # convert to integer
        x = target.send :"#{@attachment.name}_crop_x".to_i # convert to integer
        y = target.send :"#{@attachment.name}_crop_y".to_i # convert to integer

        if valid_dimensions?(w, h) && valid_coordinates?(x, y)
          ["-crop", "#{w}x#{h}+#{x}+#{y}"]
        else
          raise "Invalid crop dimensions or coordinates"
        end
      end
    end

    private

    def valid_dimensions?(width, height)
      width > 0 && height > 0 # check if both dimensions are positive integers
    end

    def valid_coordinates?(x, y)
      x >= 0 && y >= 0 # check if coordinates are non-negative integers
    end
  end
end
