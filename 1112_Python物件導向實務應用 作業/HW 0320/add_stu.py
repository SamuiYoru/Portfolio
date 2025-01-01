def main(student_list):
    #要做保護措施(分數輸入非數字的話)#這邊還沒寫完有BUG
    new_std = {}
    new_score ={}
    name_input = input("  Please input a student's name or exit: ")
    while name_input != "exit":
        new_score.clear()
        new_std.clear()
        flag = False
        for student_name in student_list:
            if name_input == student_name.get("name"):
                flag = True
        if flag == False:#學生名字不在清單中
            subject = input("  Please input a subject name or exit for ending: ")
            while subject !="exit":
                s = input("  Please input {}'s {} score or < 0 for discarding the subject: ".format(name_input,subject))
                try:  
                    s_ = float(s)
                    if (s_<0):#取消操作
                        pass
                    else:#增加資料
                        new_score[subject]=s_
                    subject = input("  Please input a subject name or exit for ending: ")
                except:
                    print("  Wrong format with reason could not convert string to float: '{}', try again".format(s))
            new_std["name"] = name_input  
            new_std["scores"] = new_score.copy()
            student_list.append(new_std.copy())
            print("    Add {}'s score successfully".format(name_input))
            name_input = "exit"
        else:#如果名字存在
            print("    {} is already exists".format(name_input))
            name_input = input("  Please input a student's name or exit: ")
    















