class PrintAll:
    def __init__(self,student_list):
        self.student_list = student_list

    def execute(self):
        print ("\n==== student list ====\n")
        for student_name in self.student_list:
            print('Name : {}'.format(student_name.get("name")))
            for key,value in student_name.get("scores").items():
                print("  subject: {}, score: {}".format(key,value))
            print(" ")
        print ("======================")
        return self.student_list