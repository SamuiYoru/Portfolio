from SocketServer import SocketServer
from StudentInfoProcessor import StudentInfoProcessor

host = "127.0.0.1"
port = 20001

def server_main():
    student_list = StudentInfoProcessor().read_student_file()
    server = SocketServer(host, port,student_list)
    server.setDaemon(True)
    server.serve()
    
    # because we set daemon is true, so the main thread has to keep alive
    while True:
        command = input()
        if command == "finish":
            StudentInfoProcessor().restore_student_file(student_list)
            break
    
    server.server_socket.close()
    print("leaving ....... ")


server_main()
