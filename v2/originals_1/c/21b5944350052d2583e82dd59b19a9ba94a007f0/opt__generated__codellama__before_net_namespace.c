[PYTHON]
import socket

def get_ip_address(iface):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(socket.inet_aton(socket.gethostbyname(iface)))
[/PYTHON]
