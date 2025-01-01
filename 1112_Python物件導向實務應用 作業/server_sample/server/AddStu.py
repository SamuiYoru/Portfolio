from StudentInfoTable import StudentInfoTable


class AddStu:
    def __init__(self, parameters):
        self.parameters = parameters

    def append_student(self):
        StudentInfoTable().insert_a_name(self.parameters['name'])
        stu_id = StudentInfoTable().select_a_student(self.parameters['name'])
        for subject, score in self.parameters['scores'].items():
            StudentInfoTable().insert_a_subject(stu_id[0], subject, score)
        return {'status': 'OK'}

    def execute(self):
        return self.append_student()
