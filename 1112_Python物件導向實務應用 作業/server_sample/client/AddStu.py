class AddStu:
    def __init__(self,client):
        self.student = dict()
        self.client = client
    
    def check_name_exit(self):
        while True:
            self.name = input("  Please input a student's name or exit: ")
            if self.name == 'exit':
                return
            self.client.send_command('query',{'name':self.name})
            status = self.client.wait_response()
            if not status:
                break
            print('    {} already exists'.format(self.name))
        self.get_scores()
        self.append_student()
    
    def get_scores(self):
        scores = dict()
        subject = input("  Please input a subject name or exit for ending: ")
        while subject != 'exit':
            try:
                score = float(input("  Please input {}'s {} score or < 0 for discarding the subject: ".format(self.name, subject)))
                if score < 0:
                    raise Exception
            except ValueError as e:
                print("    Wrong format with reason {}, try again".format(e))
                continue
            except:
                print("    Something wrong!")
            else:
                scores[subject] = score
                self.student = {'name': self.name, 'scores': scores}
            subject = input("  Please input a subject name or exit for ending: ")
    
    def append_student(self):
        if(self.student.get('name')):
            self.client.send_command('add',self.student)
            status = self.client.wait_response()
            if status is False:
                print("    Add {} fail".format(self.student))
            else:
                print("    Add {} success".format(self.student))

    def execute(self):
        self.check_name_exit()     
        
        
