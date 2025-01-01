#import client_socket 

class ShowClient:
    def __init__(self,client):
        self.client = client
        self.data = []

    def print_list(self,student_list):
        print ("\n==== student list ====\n")
        for student_name in student_list:
            print('Name : {}'.format(student_name.get("name")))
            for key,value in student_name.get("scores").items():
                print("  subject: {}, score: {}".format(key,value))
            print(" ")
        print ("======================\n\n")

    def execute(self):
        self.client.send_command("show",{})
        self.data=self.client.wait_response()
        self.data = self.data["parameters"]
        self.print_list(self.data)
