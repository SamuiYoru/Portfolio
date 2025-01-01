import socket
import json

BUFFER_SIZE = 1940


class SocketClient:
    def __init__(self, host, port):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((host, port))

    def send_command(self, command, parameters):
        send_data = {'command': command, 'parameters': parameters}
        print("    The client sent data => {}".format(send_data))
        self.client_socket.send(json.dumps(send_data).encode())

    def wait_response(self):
        data = self.client_socket.recv(BUFFER_SIZE)
        raw_data = data.decode()
        dict_temp = eval(raw_data)
        print("    The client received data => {}".format(dict_temp))
        
        if dict_temp['status'] == 'Fail':
            return False
        return dict_temp
