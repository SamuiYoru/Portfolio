from PyQt5 import QtWidgets, QtGui, QtCore
from .WidgetComponents import LabelComponent, LineEditComponent, ButtonComponent
import json
from WebServiceClient.ServiceController import ExecuteCommand


class ShowStuWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("show_stu_widget")

        layout = QtWidgets.QVBoxLayout()
        self.setAttribute(QtCore.Qt.WA_StyledBackground, True)

        header_label = LabelComponent(20, "Show Student")
        header_label.setAlignment(QtCore.Qt.AlignCenter)
        header_label.setStyleSheet("background-color:  #e2eafc;border-bottom: 1px dotted #03045e;")
        self.show_scroll_area = QtWidgets.QScrollArea()
        self.show_scroll_area.setStyleSheet("background-color: transparent;border:none;")
        layout.addWidget(header_label, stretch=1)
        layout.addWidget(self.show_scroll_area , stretch=4)
        self.setLayout(layout)

    def load(self):
        # print("show widget")
        self.widget = QtWidgets.QWidget()
        self.widget.setFont(QtGui.QFont("微軟正黑體", 15, QtGui.QFont.Bold))  
        self.vbox = QtWidgets.QVBoxLayout()
        self.show_action()

    def print_list(self,student_list):
        object =  QtWidgets.QLabel("==== student list ====\n")
        self.vbox.addWidget(object)
        for student_name in student_list:
            object_std =  QtWidgets.QLabel('Name : {}'.format(student_name.get("name")))
            object_std .setAlignment(QtCore.Qt.AlignCenter)
            self.vbox.addWidget(object_std)
            for key,value in student_name.get("scores").items():
                object_subject =  QtWidgets.QLabel("subject: {}, score: {}".format(key,value))
                object_subject.setAlignment(QtCore.Qt.AlignCenter)
                self.vbox.addWidget(object_subject)
            object_line =  QtWidgets.QLabel("")
            self.vbox.addWidget(object_line)
        object =  QtWidgets.QLabel("================\n")
        self.vbox.addWidget(object)
        


    def show_action(self):
        self.send_command = ExecuteCommand(command="show", data={})
        self.send_command.start()
        self.send_command.return_sig.connect(self.show_result)

    def show_result(self, result):
        result = json.loads(result)

        if (result['status']=='OK'and len(result['parameters'])!=0 ):
            self.show_scroll_area.setVerticalScrollBarPolicy(2)
            self.print_list(result['parameters'])
        else:
            object_none =  QtWidgets.QLabel("nothing in the database")
            object_none.setAlignment(QtCore.Qt.AlignCenter)
            self.vbox.addWidget(object_none)

        self.widget.setLayout(self.vbox)
        self.show_scroll_area.setWidget(self.widget)
        self.show_scroll_area.setAlignment(QtCore.Qt.AlignHCenter)

