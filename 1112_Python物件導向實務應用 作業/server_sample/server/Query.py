from StudentInfoTable import StudentInfoTable


class Query:
    def __init__(self, parameters):
        self.parameters = parameters

    def find_student(self):
        stu_id = StudentInfoTable().select_a_student(self.parameters['name'])
        if stu_id:
            subject_info = StudentInfoTable().select_a_subject(stu_id[0])
            scores = dict()
            for subject_row in subject_info:
                scores[subject_row['subject']] = subject_row['score']
            print('    Query {} success'.format(self.parameters['name']))
            return {'status': 'OK', 'scores': scores}

        return {'status': 'Fail', 'reason': 'The name is not found.'}

    def execute(self):
        return self.find_student()
