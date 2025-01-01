from PyQt5 import QtWidgets, QtGui, QtCore
from WidgetComponents import LabelComponent, LineEditComponent, ButtonComponent
from func import Func

class AddStuWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("add_stu_widget")
        layout = QtWidgets.QGridLayout()
        self.student_data_save = Func()

        self.header_label = LabelComponent(20, "Add Student")
        self.label = LabelComponent(15, "")
        self.label.setStyleSheet("color:red")
        self.label.setWordWrap(True)

        self.label_warn = LabelComponent(12, "")
        self.label_warn.setStyleSheet("color:red")
        self.label_warn.setWordWrap(True)

        content_label = LabelComponent(16, "Name: ")
        self.editor_label_1 = LineEditComponent("Name")
        self.editor_label_1.mousePressEvent = self.name_editor_content
        content_label_2 = LabelComponent(16, "Subject: ")
        self.editor_label_2 = LineEditComponent("Subject")
        self.editor_label_2.mousePressEvent = self.subject_editor_content
        content_label_3 = LabelComponent(16, "Score: ")
        self.editor_label_3 = LineEditComponent("")
        self.editor_label_3.setValidator(QtGui.QIntValidator(0,100))
        self.editor_label_3.mousePressEvent = self.score_editor_content


        self.button = ButtonComponent("Query")
        self.button.clicked.connect(self.confirm_action)
        self.button_2 = ButtonComponent("Add")
        self.button_2.clicked.connect(self.add_action)
        self.button_3 = ButtonComponent("Send")
        self.button_3.clicked.connect(self.send_action)

        layout.addWidget(self.header_label, 0, 0, 1, 4)
        layout.addWidget(self.label, 1, 5, 3, 3)
        layout.addWidget(self.label_warn, 4, 6, 2, 3)

        layout.addWidget(content_label, 1, 0, 1, 1)
        layout.addWidget(self.editor_label_1, 1, 1, 1, 3)
        layout.addWidget(self.button, 1, 4, 1, 1)
        self.button.setEnabled(False)
        
        layout.addWidget(content_label_2, 2, 0, 1, 1)
        layout.addWidget(self.editor_label_2, 2, 1, 1, 3)
        self.editor_label_2.setEnabled(False)

        layout.addWidget(content_label_3, 3, 0, 1, 1)
        layout.addWidget(self.editor_label_3, 3, 1, 1, 3)
        layout.addWidget(self.button_2, 3, 4, 1, 1)
        self.button_2.setEnabled(False)

        layout.addWidget(self.button_3, 5, 5, 1, 2)
        self.button_3.setEnabled(False)

        layout.setColumnStretch(0, 1)
        layout.setColumnStretch(1, 3)
        layout.setColumnStretch(3, 4)
        layout.setColumnStretch(4, 5)
        layout.setColumnStretch(5, 6)
        layout.setColumnStretch(5, 7)
        layout.setColumnStretch(7, 9)#橫向切
        layout.setRowStretch(0, 1)
        layout.setRowStretch(1, 2)
        layout.setRowStretch(2, 3)
        layout.setRowStretch(3, 4)
        layout.setRowStretch(4, 5)
        layout.setRowStretch(5, 6)

        self.setLayout(layout)

    def original_setting(self):
        self.editor_label_1.clear()
        self.editor_label_2.clear()
        self.editor_label_3.clear()
        self.student_data_save = Func()
        self.editor_label_1.setEnabled(True)
        self.button.setEnabled(False)
        self.editor_label_2.setEnabled(False)
        self.button_2.setEnabled(False)
        self.button_3.setEnabled(False)

    def name_editor_content(self,event):
        self.editor_label_1.clear()
        self.button.setEnabled(True)

    def subject_editor_content(self,event):
        self.editor_label_2.clear()

    def score_editor_content(self,event):
        self.editor_label_3.clear()

    def confirm_action(self):
        if(self.editor_label_1.text()!=""):
            self.label.setText("Please enter subject for student '{}'".format(self.editor_label_1.text()))
            self.student_data_save.add_student({'name':self.editor_label_1.text(),'scores':{}})
            self.editor_label_2.setEnabled(True)
            self.button_2.setEnabled(True)
            self.editor_label_1.setEnabled(False)
            self.button_3.setEnabled(True)
        else:
            self.label_warn.setText("warning:\nPlease enter a student's name.")

    def add_action(self):
        if(self.editor_label_2.text()!="" and self.editor_label_3.text()!=""):
            score_data = {self.editor_label_2.text():self.editor_label_3.text()}
            self.student_data_save.add_subject(self.editor_label_1.text(),score_data)
            self.label.setText("Student {}'s subject '{}'with score '{}' added".format(self.editor_label_1.text(),self.editor_label_2.text(),self.editor_label_3.text()))
        else:
            self.label_warn.setText('warning:\nplease enter the correct subject and the score.')
    

    def send_action(self):
        if(self.editor_label_1.text()!=""and len(self.student_data_save.get_subject())!=0):
            save_data = {'name':self.editor_label_1.text(),'scores':self.student_data_save.get_subject()}
            return_data = self.student_data_save.send_data(save_data)
            self.label.setText('The information {}is sent.'.format(return_data))
            self.original_setting()
        else:
            self.label_warn.setText('warning:\nPlease add the score.')
