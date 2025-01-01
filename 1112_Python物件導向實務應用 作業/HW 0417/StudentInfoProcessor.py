import pickle
class StudentInfoProcessor:
    def __init__(self):
        self.student_list = list()
    
    def read_student_file(self):
        #print("read_student_file")
        try:
            with open("student_list.db", "rb") as fp:
                self.student_list = pickle.load(fp)
        except:
            pass
        
        return self.student_list

    def restore_student_file(self,student_list):
        #print("restore_student_file")
        with open("student_list.db", "wb") as fp:
            pickle.dump(student_list, fp)