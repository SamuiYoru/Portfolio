from .StudentInfoTable import StudentInfoTable
import tornado.web
import json


class ModifyStu(tornado.web.RequestHandler):
    def post(self):
        std_data = self.request.body
        self.student_data = json.loads(std_data)
        print("self.student_data = ",self.student_data)
        return_message = self.execute()
        self.write(return_message)

    def execute(self):
        student_id = StudentInfoTable().select_a_student(self.student_data['name'])
        old_score_list = StudentInfoTable().get_student_score(student_id[0])
        new_score_list = self.student_data['scores']
        for keys in new_score_list.keys():
            if keys in old_score_list.keys():
                StudentInfoTable().update_subject(student_id[0], keys,new_score_list[keys])
            else:
                StudentInfoTable().insert_score(self.student_data['name'], {keys:new_score_list[keys]})
        score_list = StudentInfoTable().get_student_score(student_id[0])
        return_message =  {'status': 'OK'}
        
        return return_message
    