[PYTHON]
import logging
from ctypes import *
from typing import List, Optional, Union

class NDP:
    def __init__(self) -> None:
        pass

    # Logging

    def set_log(self, log_fn: object, log_priority: int) -> None:
        self.log_fn = log_fn
        self.log_priority = log_priority

    def log(self, priority: int, format: str, *args) -> None:
        if priority <= self.log_priority:
            self.log_fn(format % args)

class MessageCallbackInfo:
    def __init__(self, callback: object, data: Optional[object] = None) -> None:
        self.callback = callback
        self.data = data

class MessengerHandler:
    def __init__(self, ndp: NDP, message_type: int, handler: object, data: Optional[object] = None) -> None:
        pass

class EventFDHandler:
    def __init__(self, ndp: NDP, callback: object, data: Optional[object] = None) -> None:
        pass

def create_message(message_type: int, payload: Union[bytes, List[int]]) -> bytes:
    return b''

def send_message(ndp: NDP, message: bytes) -> int:
    return 0

def receive_messages(ndp: NDP) -> List[object]:
    return []

def register_message_handler(ndp: NDP, message_type: int, handler: object, data: Optional[object] = None) -> MessengerHandler:
    return MessengerHandler(ndp, message_type, handler, data)

def unregister_message_handler(ndp: NDP, handler: MessengerHandler) -> None:
    pass

def register_eventfd_handler(ndp: NDP, callback: object, data: Optional[object] = None) -> EventFDHandler:
    return EventFDHandler(ndp, callback, data)

def unregister_eventfd_handler(ndp: NDP, handler: EventFDHandler) -> None:
    pass

# Logging

def set_log_level(ndp: NDP, level: int) -> None:
    pass

def get_log_level(ndp: NDP) -> int:
    return 0

# Debugging

def print_stacktrace() -> None:
    pass
[/PYTHON]
