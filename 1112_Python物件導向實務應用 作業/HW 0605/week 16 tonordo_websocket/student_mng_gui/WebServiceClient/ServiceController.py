from PyQt5 import QtCore
from PyQt5.QtCore import pyqtSignal
import requests
import json

url_dict = {
    "query": "http://127.0.0.1:9000/query_student",
    "add": "http://127.0.0.1:9000/add_student",
    "show": "http://127.0.0.1:9000/show_student",
    "modify": "http://127.0.0.1:9000/modify_student"
}

class ServiceController:
    def command_sender(self, command, data):
        response = requests.post(
            url=url_dict[command],
            data=data,
            verify=False
        )

        if (response.status_code == requests.codes.ok):
            response_json = json.loads(response.text)
            print ("  Client received data  ==> {}".format(response_json))
            return response_json
        else:
            return {"status": "ERROR"}


class ExecuteCommand(QtCore.QThread):
    return_sig = pyqtSignal(str)

    def __init__(self, command, data):
        super().__init__()
        self.data = data
        self.command = command

    def run(self):
        result = ServiceController().command_sender(self.command, self.data)
        self.return_sig.emit(json.dumps(result))

