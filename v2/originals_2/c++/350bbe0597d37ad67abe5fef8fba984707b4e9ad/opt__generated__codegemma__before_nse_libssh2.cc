-- Establish an SSH session
ssh2.session_open(host, port, username, password)

-- Open an SSH channel
channel = ssh2.open_channel(session, command)

-- Read data from the channel
data = ssh2.channel_read(channel)

-- Close the channel
ssh2.channel_close(channel)

-- Close the SSH session
ssh2.session_close(session)
