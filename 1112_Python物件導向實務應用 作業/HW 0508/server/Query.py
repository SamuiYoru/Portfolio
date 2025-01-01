from StudentInfoTable import StudentInfoTable

class Query:
    def __init__(self,student_data):
        self.student_data = student_data

    def execute(self):
        student_id = StudentInfoTable().select_a_student(self.student_data['name'])
        if (len(student_id)==0):
            return_message = {'status': 'Fail', 'reason': 'The name is not found.'}
        else:
            score_list = StudentInfoTable().get_student_score(student_id[0])
            return_message =  {'status': 'OK', 'scores': score_list}
        
        return return_message