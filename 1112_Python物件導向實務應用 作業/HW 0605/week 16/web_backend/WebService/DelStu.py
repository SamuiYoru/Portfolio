from .StudentInfoTable import StudentInfoTable
import tornado.web
import json


class DelStu(tornado.web.RequestHandler):
    def post(self):
        std_data = self.request.body
        self.student_data = json.loads(std_data)
        return_message = self.execute()
        self.write(return_message)

    def execute(self):
        student_id = StudentInfoTable().select_a_student(self.student_data['name'])
        StudentInfoTable().delete_a_student(student_id[0])
        return_message = {'status':'OK'}

        return return_message