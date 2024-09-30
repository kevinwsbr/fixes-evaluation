[PYTHON]
def get_closest_frame(frames, timestamp):
    closest_frame = None
    closest_timestamp = None
    for frame in frames:
        if not closest_frame or abs(timestamp - frame.start_time) < abs(timestamp - closest_timestamp):
            closest_frame = frame
            closest_timestamp = frame.start_time
    return closest_frame

def get_closest_frames(frames, timestamp):
    closest_frames = []
    for frame in frames:
        if abs(timestamp - frame.start_time) < 3000:
            closest_frames.append(frame)
    return closest_frames

def seek_video_frame(ps, streamno, timestamp):
    video_stream = ps.get_stream(streamno)
    if not video_stream:
        return None
    frames = video_stream.get_frames()
    closest_frame = get_closest_frame(frames, timestamp)
    video_stream.current_frame = closest_frame
    return closest_frame

def seek_audio_frame(ps, streamno, timestamp):
    audio_stream = ps.get_stream(streamno)
    if not audio_stream:
        return None
    frames = audio_stream.get_frames()
    closest_frames = get_closest_frames(frames, timestamp)
    audio_stream.current_frame = closest_frames[0]
    return closest_frames[0]

def get_first_cts(ps):
    video_stream = ps.get_stream(1)
    if not video_stream:
        return None
    frames = video_stream.get_frames()
    first_frame = frames[0]
    return first_frame.start_time
[/PYTHON]
