def main(student_list):
    name_input = input("  Please input a student's name or exit: ")
    stu ={}
    if name_input != "exit":
        flag = False
        for student_name in student_list:
            if name_input == student_name.get("name"):
                stu = student_name
                flag = True
        if flag == True:
            student_list.remove(stu)
            print("    Del {} success".format(name_input))
        else:
            print("    The name {} is not found".format(name_input))
        #name_input = input("Please input a student's name or exit: ")









