class DelStu:
    def __init__(self,student_list):
        self.student_list = student_list

    def in_the_list(self,name_input):
        stu={}
        for student_name in self.student_list:
            if name_input == student_name.get("name"):
                stu = student_name
                return True,stu
        return False,stu
    
    def remove(self,flag,stu,name_input):
        if flag == True:
            self.student_list.remove(stu)
            print("    Del {} success".format(name_input))
        else:
            print("    The name {} is not found".format(name_input))

    def execute(self):
        name_input = input("  Please input a student's name or exit: ")
        stu ={}
        if name_input != "exit":
            flag = False
            flag,stu = self.in_the_list(name_input)
            self.remove(flag,stu,name_input)
        return self.student_list