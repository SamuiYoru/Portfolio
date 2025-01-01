def main(student_list):
    new = []
    name = input("  Please input a student's name: ")
    new.append(name)
    score = input("  Please input {}'s score: ".format(name))
    new.append(float(score))
    student_list.append(new)
    print("    Add [{}, {}] success".format(name,float(score)))








