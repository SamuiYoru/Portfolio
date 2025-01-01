from PyQt5 import QtWidgets, QtGui, QtCore
from .AddStuWidget import AddStuWidget
from .WidgetComponents import LabelComponent
from .WidgetComponents import LabelComponent
from .WidgetComponents import ButtonComponent
from .ShowStuWidget import ShowStuWidget
from .ModifyStuWidget import ModifyStuWidget
from client.client_socket import SocketClient
host = "127.0.0.1"
port = 20001
class MainWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("main_widget")

        layout = QtWidgets.QGridLayout()
        header_label = LabelComponent(24, "Student Management System")
        header_label.setAlignment(QtCore.Qt.AlignCenter)
        function_widget = FunctionWidget()
        menu_widget = MenuWidget(function_widget.update_widget)

        layout.addWidget(header_label, 0, 0, 1, 2)
        layout.addWidget(menu_widget, 1, 0, 1, 1)
        layout.addWidget(function_widget, 1, 1, 1, 1)

        layout.setColumnStretch(0, 1)
        layout.setColumnStretch(1, 6)
        layout.setRowStretch(0, 1)
        layout.setRowStretch(1, 6)

        self.setLayout(layout)


class MenuWidget(QtWidgets.QWidget):
    def __init__(self, update_widget_callback):
        super().__init__()
        self.setObjectName("menu_widget")
        self.update_widget_callback = update_widget_callback

        layout = QtWidgets.QVBoxLayout()
        add_button = ButtonComponent("Add student")
        show_button = ButtonComponent("Show all")
        modify_button = ButtonComponent("Modify")
        add_button.clicked.connect(lambda: self.update_widget_callback("add"))
        show_button.clicked.connect(lambda: self.update_widget_callback("show"))
        modify_button.clicked.connect(lambda: self.update_widget_callback("modify"))

        layout.addWidget(add_button, stretch=1)
        layout.addWidget(modify_button, stretch=1)
        layout.addWidget(show_button, stretch=1)

        self.setLayout(layout)


class FunctionWidget(QtWidgets.QStackedWidget):
    def __init__(self):
        super().__init__()
        self.client = SocketClient(host, port)
        self.widget_dict = {
            "add": self.addWidget(AddStuWidget(self.client)),
            "show": self.addWidget(ShowStuWidget(self.client)),
            "modify": self.addWidget(ModifyStuWidget(self.client))
        }
        self.update_widget("add")
    
    def update_widget(self, name):
        self.setCurrentIndex(self.widget_dict[name])
        current_widget = self.currentWidget()
        current_widget.load()
