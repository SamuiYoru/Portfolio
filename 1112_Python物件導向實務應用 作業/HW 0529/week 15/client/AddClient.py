#import client_socket 

class AddClient:
    def __init__(self,client):
        self.client = client
        self.student_list = {}
        self.s = 0
            
    def check_if_negative(self,s,new_score,subject):
        s_ = float(s)
        if (s_<0):
            pass
        else:
            new_score[subject]=s_

    def subject_add(self,new_score,name_input):
        subject = input("  Please input a subject name or exit for ending: ")
        while subject !="exit":
            self.s = input("  Please input {}'s {} score or < 0 for discarding the subject: ".format(name_input,subject))
            try:
                self.check_if_negative(self.s,new_score,subject)
                subject = input("  Please input a subject name or exit for ending: ")
            except:
                print("  Wrong format with reason could not convert string to float: '{}', try again".format(self.s))

    def add(self,new_score,name_input):
        self.client.send_command('query',{'name':name_input})
        return_data = self.client.wait_response()
        if(return_data['status']=='Fail'):
            self.subject_add(new_score,name_input)
            if len(new_score)!=0:
                self.student_list['name']=name_input
                self.student_list['scores']=new_score.copy()

    def execute(self):
        new_score ={}
        name_input = input("  Please input a student's name or exit: ")
        while name_input != "exit":
            self.add(new_score,name_input)
            name_input = "exit"
        if(bool(self.student_list)!=False):
            self.client.send_command("add",self.student_list)
            return_data = self.client.wait_response()
            if(return_data['status']=="OK"):
                print("    Add {} success\n".format(self.student_list))
            else:
                print("    Add {} fail\n".format(self.student_list))
        else:
            pass

        
