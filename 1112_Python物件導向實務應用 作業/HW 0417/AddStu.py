class AddStu:
    def __init__(self,student_list):
        self.student_list = student_list

    def find(self,name_input):
        for student_name in self.student_list:
            if name_input == student_name.get("name"):
                return True
        return False

    def execute(self,new_data):
        flag = False
        flag = self.find(new_data['name'])
        if flag == False:
            self.student_list.append(new_data)
            return_message = {'status':'OK'}
        else:
            return_message = {'status': 'Fail', 'reason': 'The name already exists.'}

        return return_message