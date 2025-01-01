from StudentInfoTable import StudentInfoTable


class DelStu:
    def __init__(self, parameters):
        self.parameters = parameters

    def del_student(self):
        stu_id = StudentInfoTable().select_a_student(self.parameters['name'])
        StudentInfoTable().delete_a_student(stu_id[0])
        StudentInfoTable().delete_a_subject(stu_id[0])
        print('    Del {} success'.format(self.parameters['name']))
        return {'status': 'OK'}

    def execute(self):
        return self.del_student()
