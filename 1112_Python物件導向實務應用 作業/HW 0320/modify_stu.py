def main(student_list):
    name_input = input("  Please input a student's name or exit: ")
    stu = {}
    if name_input!= "exit":
        flag = False
        for student_name in student_list:
            if name_input == student_name.get("name"):
                stu = student_name
                flag = True
        if flag==True:
            print("  current subjects are",end=" ")
            for a in stu.get("scores").keys():
                print (a,end=" ")
            print("\n")
            subject_input=input("  Please input a subject you want to change: ")
            if subject_input in stu.get("scores").keys():
                score = input("  Please input {}'s new score of {}: ".format(subject_input,name_input))
                try:
                    s = float(score)
                    stu.get("scores")[subject_input]=s
                    print("    Modify [{}, {}, {}] success".format(name_input,subject_input,s))
                except:
                    pass
            else:
                score2 = input("  Add a new subject for {} please input {} score or < 0 for discarding the subject: ".format(name_input,subject_input))
                try:
                    s1=float(score2)
                    if (s1>0):
                        stu.get("scores")[subject_input]=s1
                        print("  Add successfully")
                    else:
                        pass
                except:
                    pass
        else:
            print("{} isn't exit in the list".format(name_input))
        #name_input = input("Please input a student's name or exit: ")




































