def main(student_list):
    name = input("  Please input a student's name: ")
    flag = 0
    for i in student_list:
        if (i[0]==name):
            score = float(input("  Please input {}'s new score: ".format(name)))
            i[1]=score
            print("    Modify [{}, {}] success".format(name,float(score)))
            flag = 1
        else:
            pass
    if(flag == 0):
        print("    The name {} is not found".format(name))