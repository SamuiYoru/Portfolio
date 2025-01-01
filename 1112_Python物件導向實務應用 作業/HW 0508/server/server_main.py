
from SocketServer import SocketServer
from DBConnection import DBConnection
from DBInitializer import DBInitializer

host = "127.0.0.1"
port = 20001
DBConnection.db_file_path = "example.db"

def server_main():
    
    DBInitializer().execute()
    server = SocketServer(host, port)
    server.setDaemon(True)
    server.serve()
    
    # because we set daemon is true, so the main thread has to keep alive
    while True:
        command = input()
        if command == "finish":
            break
    
    server.server_socket.close()
    print("leaving ....... ")

server_main()
