from threading import Thread
import socket
import json

from PrintAll import PrintAll
from AddStu import AddStu
from Query import Query
from DelStu import DelStu
from ModifyStu import ModifyStu

function_list={
    "add":AddStu,
    "show":PrintAll,
    "query":Query,
    "delete":DelStu,
    "modify":ModifyStu
}

class SocketServer(Thread):
    def __init__(self, host, port):
        super().__init__()
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # The following setting is to avoid the server crash. So, the binded address can be reused
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind((host, port))
        self.server_socket.listen(5)

    def serve(self):
        self.start()

    def run(self):
        while True:
            try:
                connection, address = self.server_socket.accept()
                print("{} connected".format(address))
                self.new_connection(connection=connection,
                                    address=address)
            except:
                pass

    def new_connection(self, connection, address):
        Thread(target=self.receive_message_from_client,
               kwargs={
                   "connection": connection,
                   "address": address}, daemon=True).start()
    
    def return_message(self,message): 
        print("message = ",message)      
        try:
            if(function_list.get(message['command'])!=None):
                return_msg = function_list.get(message['command'])(message['parameters']).execute()
            else:
                return_msg = {'status': 'Fail', 'reason': 'The command does not exit.'}
        except Exception as e:
            print("Exeption happened {}".format(e))
            return_msg = {'status': 'Fail', 'reason': 'Command is error.'}
        
        return return_msg

    def receive_message_from_client(self, connection, address):
        keep_going = True
        while keep_going:
            try:
                message = connection.recv(1024).strip().decode()
                message = json.loads(message)
                print(message)
                print("    server received: {} from {}".format(message, address))
                if message['command'] == "close":
                    connection.send("closing".encode())
                    keep_going = False
                else:
                    return_msg = self.return_message(message)
                    connection.send(json.dumps(return_msg).encode())

            except Exception as e:
                #print("Exeption happened {}, {}".format(e, address))
                keep_going = False

        connection.close()
        print("{} close connection".format(address))