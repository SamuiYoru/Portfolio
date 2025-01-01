class DelClient:
    def __init__(self,client):
        self.client = client

    def delete_or_not(self,name,count):
        if(count == 0):
            do_or_not = input("  Confirm to delete (y/n):")
        else:
            do_or_not = input("  Please reconfirm to delete (y/n):")
        
        if(do_or_not=='y'):
            self.client.send_command("delete", {'name': name})
            return_data = self.client.wait_response()
            if(return_data['status']=='OK'):
                print("    Delete success\n")
            Flag = False
        elif(do_or_not=='n'):
            print("  delete discard\n")
            Flag = False
        else:
            Flag = True

        return Flag

    def execute(self):
        name = input("  Please input a student's name:")
        if(name!="exit"):
            self.client.send_command("query", {'name': name})
            return_data = self.client.wait_response()
            if(return_data['status']=='OK'):
                Flag = True
                count = 0
                while(Flag == True):
                    Flag = self.delete_or_not(name,count)
                    count=count+1
            else:
                print(return_data['reason'],"\n")
        else:
            pass

# if __name__ == '__main__':
#     DelClient.execute()