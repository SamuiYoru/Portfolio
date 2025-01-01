from StudentInfoTable import StudentInfoTable

class AddStu:
    def __init__(self,student_data):
        self.student_data = student_data

    def execute(self):
        StudentInfoTable().insert_a_student(self.student_data['name'])
        StudentInfoTable().insert_score(self.student_data['name'],self.student_data['scores'])
        return_message = {'status':'OK'}

        return return_message