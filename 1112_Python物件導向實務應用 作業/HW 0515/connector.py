from PyQt5 import QtCore
from PyQt5.QtCore import pyqtSignal
import json

class Connector(QtCore.QThread):
    return_sig = pyqtSignal(str)

    def __init__(self, message, client):
        super().__init__()
        self.message = message
        self.client = client
    
    def run(self):
        try:
            self.client.send_command(self.message['command'],self.message['parameters'])
            reply_msg = self.client.wait_response()
        except Exception:
            reply_msg = {'status': 'Fail', 'reason': 'The command error.'}
            print("The command error.")
        self.return_sig.emit(json.dumps(reply_msg))

