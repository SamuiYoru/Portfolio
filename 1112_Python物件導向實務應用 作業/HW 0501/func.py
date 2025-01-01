class Func:
    def __init__(self):
        self.student_dict = {}
        self.student_dict_save = {}
        self.score_dict = {}

    def add_student(self,data):
        self.student_dict['name'] =  data.get('name')
        self.student_dict['scores'] = data.get('scores')

    def send_data(self,data):
        self.student_dict['name'] = data.get('name')
        self.student_dict['scores'] = data.get('scores')
        # print(self.student_dict)
        return self.student_dict
    
    def add_subject(self,name,data):
        for key in data.keys():
            self.score_dict[key]=data.get(key)
        if(self.student_dict['name']==name):
             self.student_dict['scores'] = self.score_dict
        print(self.student_dict)

    def get_subject(self):
        return self.score_dict
    