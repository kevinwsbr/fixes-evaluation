[PYTHON]
#!/usr/bin/env python3
import os
import subprocess
from PyQt5.QtCore import QObject, pyqtSlot

class UdevRules(QObject):
    @pyqtSlot(str)
    def load_rules(self, path):
        with open(path, 'r') as f:
            rules = f.readlines()
        for rule in rules:
            subprocess.run(["udevadm", "test"], input=rule.encode())
[/PYTHON]
