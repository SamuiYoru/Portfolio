from .StudentInfoTable import StudentInfoTable
import tornado.web
import json

class PrintAll(tornado.web.RequestHandler):
    def post(self):
        std_data = self.request.body
        self.student_data = json.loads(std_data)
        return_message = self.execute()
        self.write(return_message)

    def execute(self):
        student_list = StudentInfoTable().get_all_student()
        return_message = {'status':'OK','parameters':student_list}
        return return_message
    

