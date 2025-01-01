from StudentInfoTable import StudentInfoTable

class PrintAll:
    def __init__(self,student_data):
        self.student_data = student_data

    def execute(self):
        student_list = StudentInfoTable().get_all_student()
        return_message = {'status':'OK','parameters':student_list}
        return return_message
    

