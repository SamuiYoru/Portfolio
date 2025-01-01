class PrintAll:
    def __init__(self,student_list):
        self.student_list = student_list

    def execute(self):
        return_message = {'status':'OK','parameters':self.student_list}
        return return_message