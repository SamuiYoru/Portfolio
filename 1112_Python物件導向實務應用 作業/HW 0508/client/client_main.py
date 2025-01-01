from .client_socket import SocketClient
from .AddClient import AddClient
from .ShowClient import ShowClient
from .DelClient import DelClient
from .ModifyClient import ModifyClient

host = "127.0.0.1"
port = 20001

def print_list():
    print("add: Add a student's name and score")
    print("del: Delete a student")
    print("modify: Modify a student's score")
    print("Show: Print all")
    print("exit: Exit")
    
function_list={
    "add":AddClient,
    "del":DelClient,
    "modify":ModifyClient,
    "show":ShowClient
}

if __name__ == '__main__':
    client = SocketClient(host, port)
    keep_going = True

    while keep_going:
        print_list()
        command = input("Please select:")
        try:
            if(command == "exit"):
                keep_going = False
            else:
                function_list[command](client).execute()
        except:
            pass
