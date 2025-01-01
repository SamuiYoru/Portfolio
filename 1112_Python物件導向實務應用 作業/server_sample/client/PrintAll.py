class PrintAll:
    def __init__(self, client):
        self.client = client

    def execute(self):
        self.client.send_command('show', {})
        student_list = self.client.wait_response()['parameters']
        print("\n==== student list ====\n")
        for student in student_list:
            for key, value in student.items():
                if key == 'name':
                    print("Name: {}".format(value))
                else:
                    for subject, score in value.items():
                        print("  subject: {}, score: {}".format(subject, score))
        print("======================")
