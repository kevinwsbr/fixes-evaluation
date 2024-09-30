 
[PYTHON]
import contextlib

class Sequence:
    def __init__(self, name):
        self.name = name
        self.events = []
    
    def add_event(self, event):
        self.events.append(event)
    
    @contextlib.contextmanager
    def process_events(self):
        yield
        for event in self.events:
            if event['type'] == 'NoteOn':
                print(f"Processing NoteOn event for {self.name}")
            elif event['type'] == 'NoteOff':
                print(f"Processing NoteOff event for {self.name}")
    
    def set_volume(self, volume):
        self.volume = volume

class SequencePlayer:
    def __init__(self):
        self.sequences = {}
    
    def add_sequence(self, sequence):
        self.sequences[sequence.name] = sequence
    
    def remove_sequence(self, name):
        del self.sequences[name]
    
    def get_sequence(self, name):
        return self.sequences[name]
    
    def play(self, sequence_name, loop=False):
        sequence = self.get_sequence(sequence_name)
        with sequence.process_events():
            print("Playing sequence")

sp = SequencePlayer()
seq1 = Sequence("Sequence 1")
seq2 = Sequence("Sequence 2")
sp.add_sequence(seq1)
sp.add_sequence(seq2)

event1 = {'type': 'NoteOn', 'note': 60}
event2 = {'type': 'NoteOff', 'note': 60}
seq1.add_event(event1)
seq1.add_event(event2)

sp.play("Sequence 1")
[/PYTHON]
