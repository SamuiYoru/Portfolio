class ModifyStu:
    def __init__(self,student_list):
        self.student_list = student_list

    def in_list(self,name_input):
        stu={}
        for student_name in self.student_list:
            if name_input == student_name.get("name"):
                stu = student_name
                return True,stu
        return False,stu
    
    def print_current_subject(self,stu):
        print("  current subjects are",end=" ")
        for a in stu.get("scores").keys():
            print (a,end=" ")
        print("\n")

    def find_subject(self,subject_input,stu,name_input):#要處理一下BUG    
        while subject_input in stu.get("scores").keys(): 
            score = input("  Please input {}'s new score of {}: ".format(subject_input,name_input))   
            try:
                s = float(score)
                if(s>=0):
                    stu.get("scores")[subject_input]=s
                    print("    Modify [{}, {}, {}] success".format(name_input,subject_input,s))
                    return
                else:
                    print("  The score can't be negative, please enter the score again.")
            except:
                print("  Wrong format with reason could not convert string to float: '{}', try again".format(score))
        while subject_input not in stu.get("scores").keys(): 
            score2 = input("  Add a new subject for {} please input {} score or < 0 for discarding the subject: ".format(name_input,subject_input))
            try:
                s1=float(score2)
                if (s1>0):
                    stu.get("scores")[subject_input]=s1
                    print("  Add successfully")
                    return
                else:
                    print("  Discarding the subject")
                    return
            except:
                print("  Wrong format with reason could not convert string to float: '{}', try again".format(score2))

    def modify_subject(self,flag,stu,name_input):
        if flag==True:
            self.print_current_subject(stu)
            subject_input=input("  Please input a subject you want to change: ")
            self.find_subject(subject_input,stu,name_input)
        else:
            print("{} isn't exit in the list".format(name_input))
    
    def execute(self):
        name_input = input("  Please input a student's name or exit: ")
        stu = {}
        if name_input!= "exit":
            flag = False
            flag,stu = self.in_list(name_input)
            self.modify_subject(flag,stu,name_input)
        return self.student_list
