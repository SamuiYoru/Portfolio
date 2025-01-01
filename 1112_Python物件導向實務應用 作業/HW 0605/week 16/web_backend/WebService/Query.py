from .StudentInfoTable import StudentInfoTable
import tornado.web
import json


class Query(tornado.web.RequestHandler):
    def post(self):
        std_data = self.request.body
        self.student_data = json.loads(std_data)
        
        return_message = self.execute()
        self.write(return_message)

    def execute(self):
        student_id = StudentInfoTable().select_a_student(self.student_data['name'])
        if (len(student_id)==0):
            return_message = {'status': 'Fail', 'reason': 'The name is not found.'}
        else:
            score_list = StudentInfoTable().get_student_score(student_id[0])
            return_message =  {'status': 'OK', 'scores': score_list}
        
        return return_message