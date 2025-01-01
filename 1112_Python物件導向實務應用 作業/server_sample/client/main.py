from AddStu import AddStu
from DelStu import DelStu
from ModifyStu import ModifyStu
from PrintAll import PrintAll
from SocketClient import SocketClient

host = "127.0.0.1"
port = 20001

action_list = {
    "add": AddStu,
    "del": DelStu,
    "modify": ModifyStu,
    "show": PrintAll
}


def main():
    select_result = "initial"
    client = SocketClient(host, port)

    while select_result != "exit":
        select_result = print_menu()
        try:
            action_list[select_result](client).execute()
        except:
            pass


def print_menu():
    print()
    print("add: Add a student's name and score")
    print("del: Delete a student")
    print("modify: Modify a student's score")
    print("show: Print all")
    print("exit: Exit")
    selection = input("Please select: ")

    return selection


main()
