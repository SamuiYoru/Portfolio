from PyQt5 import QtWidgets, QtGui, QtCore
from .WidgetComponents import LabelComponent, LineEditComponent, ButtonComponent
# from func import Func#要改成按下去之後 send 或 add data ，資料存在connector裡面
from PyQt5.QtCore import pyqtSignal
import json
from client.client_socket import SocketClient
from connector import Connector

class AddStuWidget(QtWidgets.QWidget):
    def __init__(self,client):
        super().__init__()
        self.client = client
        self.setObjectName("add_stu_widget")
        layout = QtWidgets.QGridLayout()

        self.header_label = LabelComponent(20, "Add Student")
        self.header_label.setAlignment(QtCore.Qt.AlignCenter)
        self.label_show_message = LabelComponent(15, "")
        self.label_show_message.setStyleSheet("color:red")
        self.label_show_message.setWordWrap(True)

        self.label_warn = LabelComponent(12, "")
        self.label_warn.setStyleSheet("color:red")
        self.label_warn.setWordWrap(True)

        content_label_Name = LabelComponent(16, "Name: ")
        self.editor_label_Name = LineEditComponent("Name")
        self.editor_label_Name.mousePressEvent = self.name_editor_content
        content_label_Subject = LabelComponent(16, "Subject: ")
        self.editor_label_Subject = LineEditComponent("Subject")
        self.editor_label_Subject.mousePressEvent = self.subject_editor_content
        content_label_Score = LabelComponent(16, "Score: ")
        self.editor_label_Score = LineEditComponent("")
        self.editor_label_Score.setValidator(QtGui.QIntValidator(0,100))#只能輸入INT
        self.editor_label_Score.mousePressEvent = self.score_editor_content

        self.button_Query = ButtonComponent("Query")
        self.button_Query.clicked.connect(self.query_action)
        self.button_Add = ButtonComponent("Add")
        self.button_Add.clicked.connect(self.add_action)
        self.button_Send = ButtonComponent("Send")
        self.button_Send.clicked.connect(self.send_action)

        layout.addWidget(self.header_label, 0, 0, 1, 5)
        layout.addWidget(self.label_show_message, 1, 5, 3, 3)
        layout.addWidget(self.label_warn, 4, 5, 2, 3)

        layout.addWidget(content_label_Name, 1, 0, 1, 1)
        layout.addWidget(self.editor_label_Name, 1, 1, 1, 3)
        layout.addWidget(self.button_Query, 1, 4, 1, 1)
        self.button_Query.setEnabled(False)
        
        layout.addWidget(content_label_Subject, 2, 0, 1, 1)
        layout.addWidget(self.editor_label_Subject, 2, 1, 1, 3)
        self.editor_label_Subject.setEnabled(False)

        layout.addWidget(content_label_Score, 3, 0, 1, 1)
        layout.addWidget(self.editor_label_Score, 3, 1, 1, 3)
        layout.addWidget(self.button_Add, 3, 4, 1, 1)
        self.button_Add.setEnabled(False)

        layout.addWidget(self.button_Send, 5, 5, 1, 2)
        self.button_Send.setEnabled(False)

        layout.setColumnStretch(0, 1)
        layout.setColumnStretch(1, 3)
        layout.setColumnStretch(3, 4)
        layout.setColumnStretch(7, 9)#橫向切
        layout.setRowStretch(0, 1)
        layout.setRowStretch(3, 4)
        layout.setRowStretch(4, 5)

        self.setLayout(layout)

    def original_setting(self):
        self.editor_label_Name.clear()
        self.editor_label_Subject.clear()
        self.editor_label_Score.clear()

        self.editor_label_Name.setEnabled(True)
        self.button_Query.setEnabled(False)
        self.editor_label_Subject.setEnabled(False)
        self.button_Add.setEnabled(False)
        self.editor_label_Score.setEnabled(False)
        self.button_Send.setEnabled(False)

    def name_editor_content(self,event):
        self.editor_label_Name.clear()
        self.button_Query.setEnabled(True)

    def subject_editor_content(self,event):
        self.editor_label_Subject.clear()

    def score_editor_content(self,event):
        self.editor_label_Score.clear()

    def query_action(self):
        if(self.editor_label_Name.text()!=""):
            message = {'command': 'query', 'parameters': {'name': self.editor_label_Name.text()}}
            self.send_command = Connector(message, self.client)
            self.send_command.start()
            self.send_command.return_sig.connect(self.query_result)
        else:#未輸入學生姓名就按query
            self.label_warn.setText("warning:\nPlease enter a student's name.")

    def query_result(self, result):
        result = json.loads(result)
        if (result['status']=='Fail'):
            self.scores = dict()
            self.editor_label_Name.setEnabled(False)
            self.editor_label_Subject.setEnabled(True)
            self.button_Add.setEnabled(True)
            self.button_Send.setEnabled(True)
            self.editor_label_Score.setEnabled(True)
            self.label_show_message.setText("Please enter subject for student '{}'".format(self.editor_label_Name.text()))
        else:
            self.label_show_message.setText('{} already exists'.format(self.editor_label_Name.text()))
            self.original_setting()


    def add_action(self):
        score = self.editor_label_Score.text()
        subject = self.editor_label_Subject.text()
        if(subject!="" and score!=""):
            if(int(score) >= 0):
                self.scores[subject] = int(score)
                print({'name': self.editor_label_Name.text(), 'scores': self.scores})
                self.label_show_message.setText("Student {}'s subject '{}'with score '{}' added".format(self.editor_label_Name.text(),subject,score))
                self.label_warn.setText("")
        else:
            self.label_warn.setText('warning:\nplease enter the correct subject and the score.')
    

    def send_action(self):
        if self.scores:
            message = {'command': 'add', 'parameters': {'name': self.editor_label_Name.text(), 'scores': self.scores}}
            self.send_command = Connector(message, self.client)
            self.send_command.start()
            self.send_command.return_sig.connect(self.send_result)
        elif(len(self.scores)==0):
            self.label_warn.setText("Please add the score first.")
        else:
            self.label_warn.setText("Please enter the correct information.")

    def send_result(self, result):
        result = json.loads(result)
        if (result['status']=='OK'):
            self.label_show_message.setText("The information {} is send and save.".format({'name': self.editor_label_Name.text(), 'scores': self.scores}))
            self.original_setting()
            self.label_warn.setText("")
        else:
            self.label_show_message.setText("Fail to add {},{}".format({'name': self.editor_label_Name.text(), 'scores': self.scores}))

    def load(self):
        # print("add widget")
        self.original_setting()
        self.label_show_message.setText("")
        self.label_warn.setText("")
