class AddStu:
    def __init__(self,student_list):
        self.student_list = student_list
        self.s = 0

    def find(self,name_input):
        for student_name in self.student_list:
            if name_input == student_name.get("name"):
                return True
        return False
            
    def check_if_negative(self,s,new_score,subject):
        s_ = float(s)
        if (s_<0):#取消操作
            pass
        else:#增加資料
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

    def add(self,new_score,new_std,name_input):
        self.subject_add(new_score,name_input)
        if len(new_score)!=0:
            new_std["name"] = name_input  
            new_std["scores"] = new_score.copy()
            self.student_list.append(new_std.copy())
            print("    Add {}'s score successfully".format(name_input))


    def execute(self):
        new_std = {}
        new_score ={}
        name_input = input("  Please input a student's name or exit: ")
        while name_input != "exit":
            flag = False
            flag = self.find(name_input)
            if flag == False:
                self.add(new_score,new_std,name_input)
                name_input = "exit"
            else:
                print("    {} is already exists".format(name_input))
                name_input = input("  Please input a student's name or exit: ")

        return self.student_list