def main(student_list):
    name = input("  Please input a student's name: ")
    flag = 0
    for i in student_list:
        if (i[0]==name):
            student_list.remove(i)
            print("    Del {} success".format(name))
            flag = 1
        else:
            pass

    if(flag == 0):
        print("    The name {} is not found".format(name))