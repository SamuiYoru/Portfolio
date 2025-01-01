from .StudentInfoTable import StudentInfoTable
import tornado.web
import json

class AddStu(tornado.web.RequestHandler):
    def post(self):
        std_data = self.request.body
        self.student_data = json.loads(std_data)
        return_message = self.execute()
        self.write(return_message)

    def execute(self):
        StudentInfoTable().insert_a_student(self.student_data['name'])
        StudentInfoTable().insert_score(self.student_data['name'],self.student_data['scores'])
        return_message = {'status':'OK'}

        return return_message