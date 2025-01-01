from SocketServer import SocketServer
from DBConnection import DBConnection
from DBInitializer import DBInitializer

host = "127.0.0.1"
port = 20001


def main():
    DBConnection.db_file_path = "example.db"
    DBInitializer().execute()

    server = SocketServer(host, port)
    server.setDaemon(True)
    server.serve()

    while True:
        command = input()
        if command == "finish":
            break

    server.server_socket.close()
    print("leaving ....... ")


main()
