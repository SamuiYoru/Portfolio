from StudentInfoTable import StudentInfoTable


class ModifyStu:
    def __init__(self, parameters):
        self.parameters = parameters

    def find_scores(self, stu_id):
        subject_info = StudentInfoTable().select_a_subject(stu_id)
        scores = dict()
        for subject_row in subject_info:
            scores[subject_row['subject']] = subject_row['score']
        return scores

    def update_scores(self, stu_id, scores):
        for new_subject, new_score in self.parameters['scores'].items():
            if new_subject not in scores:
                StudentInfoTable().insert_a_subject(stu_id, new_subject, new_score)
            else:
                StudentInfoTable().update_a_subject(stu_id, new_subject, new_score)

    def execute(self):
        stu_id = StudentInfoTable().select_a_student(self.parameters['name'])
        scores = self.find_scores(stu_id[0])
        self.update_scores(stu_id[0], scores)
        print('    Modify {} success'.format(self.parameters['name']))
        return {'status': 'OK'}
