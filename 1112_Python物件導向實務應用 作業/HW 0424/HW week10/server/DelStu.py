from StudentInfoTable import StudentInfoTable

class DelStu:
    def __init__(self,student_data):
        self.student_data = student_data

    def execute(self):
        student_id = StudentInfoTable().select_a_student(self.student_data['name'])
        StudentInfoTable().delete_a_student(student_id[0])
        return_message = {'status':'OK'}

        return return_message