[PYTHON]
class Message:
    def __init__(self, text, attachments=None):
        self.text = text
        self.attachments = attachments if attachments else []
    
    def get_text(self):
        return self.text
    
    def get_attachments(self):
        return self.attachments
    
    def to_string(self):
        return f"{self.text}{''.join([f'\n{a}' for a in self.attachments])}"

class Attachment:
    def __init__(self, file_name, content_type):
        self.file_name = file_name
        self.content_type = content_type
    
    def get_file_name(self):
        return self.file_name
    
    def get_content_type(self):
        return self.content_type
[/PYTHON]
