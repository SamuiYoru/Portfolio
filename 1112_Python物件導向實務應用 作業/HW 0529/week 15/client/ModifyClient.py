class ModifyClient:
    def __init__(self,client):
        self.client = client

    def output_print(self,return_data,change_sub,scores,name,new_score):
        if(return_data['status']=='OK'):
            if change_sub in scores:
                print("    Modify [{}, {}, {}] success\n".format(name,change_sub,new_score))
            else:
                print("    Add [{}, {}, {}] success\n".format(name,change_sub,new_score))

    def input_score(self,Flag,scores_dict,change_sub,name,scores):
        new_score = input("  Add a new subject for {} please input {} score or < 0 for discarding the subject:".format(name,change_sub))
        try:
            new_score = int(new_score)
            if(new_score >=0):
                scores_dict[change_sub]=new_score
                self.client.send_command("modify", {'name': name,'scores_dict':scores_dict})
                return_data = self.client.wait_response()
                self.output_print(return_data,change_sub,scores,name,new_score)
            else:
                print("  discard modifying subject {} for {}\n".format(change_sub,name))
            Flag = False
        except:
            print("  The format of score is not correct, please enter again.")
        
        return Flag
    
    def execute(self):        
        name = input("  Please input a student's name:")
        self.client.send_command("query", {'name': name})
        return_data = self.client.wait_response()
        if(return_data['status']=='OK'):
            scores_dict = return_data['scores']
            scores = []
            print("  current subjects are ",end = "")
            for key in return_data['scores']:
                print(key,end = " ")
                scores.append(key)
            print(" \n")
            change_sub = input("  Please input a subject you want to change:")
            if(change_sub!='exit'):
                Flag = True
                while(Flag == True):
                    Flag = self.input_score(Flag,scores_dict,change_sub,name,scores)
            else:
                print("exit modify\n")
        else:
            print("    The name {} is not found\n".format(name))
        
if __name__ == '__main__':
    ModifyClient.execute()