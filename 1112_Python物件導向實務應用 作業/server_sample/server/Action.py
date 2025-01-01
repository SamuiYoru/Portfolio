from AddStu import AddStu
from DelStu import DelStu
from ModifyStu import ModifyStu
from PrintAll import PrintAll
from Query import Query

action_list = {
    "add": AddStu,
    "delete": DelStu,
    "modify": ModifyStu,
    "show": PrintAll,
    "query": Query,
}


class Action:
    def __init__(self, message):
        self.message = message

    def execute(self):
        try:
            reply_msg = action_list[self.message['command']](self.message['parameters']).execute()
        except Exception:
            reply_msg = {'status': 'Fail', 'reason': 'The command error.'}
            print("The command error.")
        return reply_msg
