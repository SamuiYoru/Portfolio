def main(student_list):
    print ("\n==== student list ====\n")
    for student_name in student_list:
        print('Name : {}'.format(student_name.get("name")))
        for key,value in student_name.get("scores").items():
            print("  subject: {}, score: {}".format(key,value))

        print(" ")
    print ("======================")
