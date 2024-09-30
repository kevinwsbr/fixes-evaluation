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

      if target.respond_to?(:cropping?) && target.respond_to?(:"#{@attachment.name}_crop_w") &&
         target.respond_to?(:"#{@attachment.name}_crop_h") && target.respond_to?(:"#{@attachment.name}_crop_x") &&
         target.respond_to?(:"#{@attachment.name}_crop_y")
        w = target.send :"#{@attachment.name}_crop_w"
        h = target.send :"#{@attachment.name}_crop_h"
        x = target.send :"#{@attachment.name}_crop_x"
        y = target.send :"#{@attachment.name}_crop_y"
        ["-crop", "#{w}x#{h}+#{x}+#{y}"] unless w.nil? || h.nil? || x.nil? || y.nil?
      end
    end
  end
end
