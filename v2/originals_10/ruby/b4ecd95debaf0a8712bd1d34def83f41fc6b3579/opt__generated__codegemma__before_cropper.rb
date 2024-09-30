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
        w = target.send :"#{@attachment.name}_crop_w".to_i
        h = target.send :"#{@attachment.name}_crop_h".to_i
        x = target.send :"#{@attachment.name}_crop_x".to_i
        y = target.send :"#{@attachment.name}_crop_y".to_i
        ["-crop", "#{w}x#{h}+#{x}+#{y}"]
      end
    end

  end
end
