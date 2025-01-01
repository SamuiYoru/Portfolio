from StudentInfoTable import StudentInfoTable


class PrintAll:
    def __init__(self, parameters):
        self.parameters = parameters
        self.student_list = list()

    def get_student(self):
        student_info = StudentInfoTable().select_all_student()
        for student_row in student_info:
            subject_info = StudentInfoTable().select_a_subject(student_row['stu_id'])
            scores = dict()
            for subject_row in subject_info:
                scores[subject_row['subject']] = subject_row['score']
            student = {'name': student_row['name'], 'scores': scores}
            self.student_list.append(student)
        return {'status': 'OK', 'parameters': self.student_list}

    def execute(self):
        return self.get_student()
