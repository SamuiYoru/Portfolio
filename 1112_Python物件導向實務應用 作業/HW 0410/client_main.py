import client_socket 
import client_add,client_show

host = "127.0.0.1"
port = 20001

def print_list():
    print("add: Add a student's name and score")
    print("Show: Print all")
    print("exit: Exit")

if __name__ == '__main__':
    client = client_socket.SocketClient(host, port)
    keep_going = True
    function_list={
        "add":client_add.AddClient,
        "show":client_show.ShowClient
    }
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
