 
[PYTHON]
import av

def extract_frames(input_file, output_dir):
    container = av.open(input_file)
    stream = container.streams.get(video=0)
    
    for packet in stream.decode():
        frame = packet.to_image()
        filename = f"{output_dir}/frame_{packet.pts}.png"
        frame.save(filename)
[/PYTHON]
 [JAVA]
import java.io.File;
import java.util.Arrays;
import java.util.List;
import org.bytedeco.javacpp.Loader;
import org.bytedeco.ffmpeg.avcodec.AVCodecContext;
import org.bytedeco.ffmpeg.avcodec.AVPacket;
import org.bytedeco.ffmpeg.avformat.*;
import static org.bytedeco.ffmpeg.global.avcodec.*;
import static org.bytedeco.ffmpeg.global.avformat.*;
import static org.bytedeco.ffmpeg.global.avutil.*;

public class ExtractFrames {
    public static void main(String[] args) throws Exception {
        // load ffmpeg native library
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("avutil");
        
        AVFormatContext ifmt_ctx = new AVFormatContext(null);
        int ret;
        
        // open input file and allocate format context
        if ((ret = avformat_open_input(&ifmt_ctx, args[0], null, null)) < 0) {
            System.err.println("Could not open input file");
            return;
        }
        
        // retrieve stream information
        if ((ret = avformat_find_stream_info(ifmt_ctx, (AVDictionary)null)) < 0) {
            System.err.println("Failed to retrieve input stream information");
            return;
        }
        
        // dump information about file onto standard error
        av_dump_format(ifmt_ctx, 0, args[0], 0);
        
        // find the first video stream
        int videoStream = -1;
        int i = 0;
        while (i < ifmt_ctx.nb_streams()) {
            if (AVMEDIA_TYPE_VIDEO == ifmt_ctx.streams(i).codec().codec_type()) {
                videoStream = i;
                break;
            }
            i++;
        }
        
        // ensure that a video stream was found
        if (-1 == videoStream) {
            System.err.println("Could not find video stream in input file");
            return;
        }
        
        // Find the decoder for the video stream
        AVCodec codec = avcodec_find_decoder(ifmt_ctx.streams(videoStream).codec().codec_id());
        if (null == codec) {
            System.err.println("Failed to find video decoder");
            return;
        }
        
        // Open codec for the video stream
        AVCodecContext pCodecCtxOrig = avcodec_alloc_context3(codec);
        if (null == pCodecCtxOrig) {
            System.err.println("Failed to allocate video decoder context");
            return;
        }
        
        if ((ret = avcodec_open2(pCodecCtxOrig, codec, (AVDictionary) null)) < 0) {
            System.err.println("Failed to open video decoder");
            return;
        }
        
        // Allocate video frame
        AVFrame pFrame = av_frame_alloc();
        if (null == pFrame) {
            System.err.println("Failed to allocate video frame");
            return;
        }
        
        // Allocate an AVPacket and set up its fields for decoding before 
        // entering the loop where we decode packets from the file.
        AVPacket packet = new AVPacket();
        packet.data(new BytePointer(1));
        packet.size(av_new_packet(packet, 0));
        
        i = 0;
        
        // read frames from the file and decode them
        while (av_read_frame(ifmt_ctx, packet) >= 0 && i < 1000) {
            // ensure that the first packet does not contain any 
            // compressed data, only its header.
            if (packet.size() <= 0) {
                break;
            }
            
            // send the packet with compressed data to the decoder
            int decodeResult = avcodec_send_packet(pCodecCtxOrig, packet);
            if (decodeResult < 0) {
                System.err.println("Error submitting packet for decoding");
                return;
            }
            
            // receive frames from the decoder
            while (decodeResult >= 0) {
                decodeResult = avcodec_receive_frame(pCodecCtxOrig, pFrame);
                
                if (decodeResult == AVERROR_EOF) {
                    break;
                } else if (decodeResult < 0) {
                    System.err.println("Error during decoding");
                    return;
                }
                
                // Make sure that the frame data is writeable, and then 
                // cast it into a buffer of type DataBuffer. The resulting 
                // BufferedImage will have the same width and height as 
                // the original video, but with only one byte per pixel. 
                pFrame.buffer().setFlags(avutil.AV_BUFFER_FLAG_WRITEABLE, avutil.AV_BUFFER_FLAG_READONLY);
                
                BytePointer buffer = new BytePointer(pFrame.data(0));
                int size = Math.abs(pCodecCtxOrig.width() * pCodecCtxOrig.height());
                byte[] bytes = new byte[size];
                buffer.get(bytes, 0, size);
                
                // Save the frame as a PNG file in the output directory
                String filename = "frame-" + i + ".png";
                BufferedImage image = new BufferedImage(pCodecCtxOrig.width(), pCodecCtxOrig.height(), 
                    BufferedImage.TYPE_3BYTE_BGR);
                image.getRaster().setDataElements(0, 0, pCodecCtxOrig.width(), pCodecCtxOrig.height(), bytes);
                ImageIO.write(image, "png", new File(outputDir, filename));
                
                i++;
            }
            
            // After sending a packet to the decoder and having received all 
            // its corresponding frames, call avcodec_flush_buffers() to 
            // ensure that any buffers containing data from the sent packet can 
            // be flushed. Even if no frames are received, this function must 
            // be called so that the decoder is ready to decode new packets.
            avcodec_flush_buffers(pCodecCtxOrig);
            
            // Clear packet before reading again
            av_packet_unref(packet);
        }
        
        // Free the RGB image
        av_frame_free(pFrame);
    }
}
[/JAVA]
