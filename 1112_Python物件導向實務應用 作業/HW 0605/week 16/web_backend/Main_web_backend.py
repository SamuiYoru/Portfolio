from tornado.ioloop import IOLoop
from tornado.httpserver import HTTPServer
import tornado.web
import tornado.websocket

# from .WebService.IndexHandler import IndexHandler
# from .WebService.AddNewStudentHandler import AddNewStudentHandler
# from .WebService.QueryStudentHandler import QueryStudentHandler

from WebService.AddStu import AddStu
from WebService.DelStu import DelStu
from WebService.ModifyStu import ModifyStu
from WebService.PrintAll import PrintAll
from WebService.Query import Query

# from WebSocket.WSHandler import WSHandler

from DBController.DBConnection import DBConnection
from DBController.DBInitializer import DBInitializer

class WebBackend:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def start_serving(self):
        app = self.init_server_application()
        server = HTTPServer(app)
        server.listen(port=self.port, address=self.host)
        IOLoop.current().start()

    def init_server_application(self):
        return tornado.web.Application(
            [
                # (r"/", IndexHandler),
                (r"/add_student", AddStu),
                (r"/query_student", Query),
                (r"/show_student", PrintAll),
                (r"/modify_student", ModifyStu)
            ]
        )

DBConnection.db_file_path = "example.db"
DBInitializer().execute()

WebBackend(host="127.0.0.1", port=9000).start_serving()
