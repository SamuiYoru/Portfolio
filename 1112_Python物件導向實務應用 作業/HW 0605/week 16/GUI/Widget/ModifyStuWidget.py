from PyQt5 import QtWidgets, QtGui, QtCore
from .WidgetComponents import LabelComponent, LineEditComponent, ButtonComponent
from PyQt5.QtCore import pyqtSignal
import json
from WebServiceClient.ServiceController import ExecuteCommand


class ModifyStuWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("modify_stu_widget")

        layout = QtWidgets.QVBoxLayout()

        header_label = LabelComponent(20, "Modify Student")
        modify_widget = ModifyWidget()

        layout.addWidget(header_label, stretch=1)
        layout.addWidget(modify_widget, stretch=8)
        self.setLayout(layout)
    
    def load(self):
        print("modify widget")

class ModifyWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("modify_stu_widget")
        layout = QtWidgets.QGridLayout()
        self.modify_widget = ModifyinfoWidget()

        self.setAttribute(QtCore.Qt.WA_StyledBackground, True)
        
        self.label_show_message = LabelComponent(15, "")
        self.label_show_message.setWordWrap(True)

        content_label_Name = LabelComponent(16, "Name: ")
        self.editor_label_Name = LineEditComponent("Name")
        self.editor_label_Name.mousePressEvent = self.name_editor_content
        self.button_Query = ButtonComponent("Query")
        self.button_Query.clicked.connect(self.query_action)
        
        self.modify_widget.combo_box_score.currentIndexChanged.connect(self.combo_box_select_changed)
        self.modify_widget.button_confirm.clicked.connect(self.confirm_action)

        layout.addWidget(self.label_show_message,0, 0, 1, 5)
        layout.addWidget(content_label_Name,1, 0, 1, 1)
        layout.addWidget(self.editor_label_Name,1, 1, 1, 1)
        layout.addWidget(self.button_Query,1, 2, 1, 1)
        layout.addWidget(self.modify_widget, 2, 0, 5, 5)

        self.setLayout(layout)
        self.original_state()

    def original_state(self):
        self.editor_label_Name.clear()
        self.modify_widget.editor_label_score.clear()
        self.modify_widget.editor_label_subject_add.clear()
        self.modify_widget.editor_label_score_add.clear()
        self.modify_widget.combo_box_score.clear()
        self.label_show_message.clear()

        self.editor_label_Name.setEnabled(True)
        self.button_Query.setEnabled(False)
        self.modify_widget.editor_label_score.setEnabled(False)
        self.modify_widget.editor_label_subject_add.setEnabled(False)
        self.modify_widget.editor_label_score_add.setEnabled(False)
        self.modify_widget.button_confirm.setEnabled(False)
        self.modify_widget.radio_button_change.setChecked(True)
        
    def name_editor_content(self,event):
        self.editor_label_Name.clear()
        self.button_Query.setEnabled(True)

    def query_action(self):
        self.modify_widget.combo_box_score.clear()
        if(self.editor_label_Name.text()!=""):
            self.send_command = ExecuteCommand(command="query", data={'name': self.editor_label_Name.text()})
            self.send_command.start()
            self.send_command.return_sig.connect(self.query_result)
        else:#未輸入學生姓名就按query
            self.label_show_message.setText("Warning:  Please enter a student's name.")

    def query_result(self, result):
        result = json.loads(result)
        if (result['status']=='OK'):
            self.editor_label_Name.setEnabled(False)
            self.modify_widget.editor_label_score.setEnabled(True)
            self.modify_widget.editor_label_subject_add.setEnabled(True)
            self.modify_widget.editor_label_score_add.setEnabled(True)
            self.modify_widget.button_confirm.setEnabled(True)
            self.scores_dict = result['scores']
            scores = []
            for key in result['scores']:
                scores.append(key)
                self.modify_widget.combo_box_score.addItems([key])
        else:
            self.label_show_message.setText('The name {} is not found'.format(self.editor_label_Name.text()))
            #print('{} already exists'.format(self.editor_label_Name.text()))

    def confirm_action(self):
        confirm_flag = 0
        if self.modify_widget.selected_button.isChecked() and self.modify_widget.selected_button is self.modify_widget.radio_button_change:
            self.subject = self.modify_widget.combo_box_score.currentText()
            self.score = self.modify_widget.editor_label_score.text()
            self.output_text = "Modify"
            confirm_flag = 1
        elif self.modify_widget.selected_button.isChecked() and self.modify_widget.selected_button is self.modify_widget.radio_button_add:
            self.subject = self.modify_widget.editor_label_subject_add.text()
            if (self.subject in self.scores_dict):    
                self.label_show_message.setText('warning: The subject is already in the database')
            else:
                self.score = self.modify_widget.editor_label_score_add.text()
                self.output_text = "Add"
                confirm_flag = 1
                
        if(confirm_flag == 1):
            if(self.subject!="" and self.score!=""):
                if(int(self.score) >= 0):
                    self.scores_dict[self.subject] = int(self.score)
                    self.send_command = ExecuteCommand(command="modify", data={'name': self.editor_label_Name.text(), 'scores': self.scores_dict})
                    self.send_command.start()
                    self.send_command.return_sig.connect(self.confirm_result)
            else:
                self.label_show_message.setText('!! Please enter the correct subject and the score !!')

    def confirm_result(self, result):
        result = json.loads(result)
        if result:
            self.label_show_message.setText("{} [{}, {}, {}] success".format(self.output_text, self.editor_label_Name.text(), self.subject, self.score))        
        else:
            self.label_show_message.setText("{} {} fail".format(self.output_text, self.editor_label_Name.text()))
        self.original_state()  

    def combo_box_select_changed(self, index):
        try:
            self.modify_widget.editor_label_score.setText(str(int(self.scores_dict[self.modify_widget.combo_box_score.currentText()])))
        except Exception:
            pass


        

class ModifyinfoWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("modify_stu_widget")
        layout = QtWidgets.QGridLayout()

        self.radio_button_change = QtWidgets.QRadioButton('Change a current score')
        self.radio_button_add = QtWidgets.QRadioButton('Add a new score')

        self.radio_button_change.toggled.connect(self.radio_button_on_clicked)
        self.radio_button_add.toggled.connect(self.radio_button_on_clicked)

        self.editor_label_score = LineEditComponent("")
        self.editor_label_score.setValidator(QtGui.QIntValidator(0,100))
        
        content_label_subject = LabelComponent(16, "Subject: ")
        self.editor_label_subject_add = LineEditComponent("subject")
        content_label_score = LabelComponent(16, "Score: ")
        self.editor_label_score_add = LineEditComponent("")
        self.editor_label_score_add.setValidator(QtGui.QIntValidator(0,100))

        self.combo_box_score = QtWidgets.QComboBox()

        self.button_confirm = ButtonComponent("Confirm")

        layout.addWidget(self.radio_button_change,0, 0, 1, 1)
        layout.addWidget(self.combo_box_score,1, 0, 1, 1)
        layout.addWidget(self.editor_label_score,1, 1, 1, 1)
        layout.addWidget(self.radio_button_add,3, 0, 1, 1)
        layout.addWidget(content_label_subject,4, 0, 1, 1)
        layout.addWidget(self.editor_label_subject_add,4, 1, 1, 1)
        layout.addWidget(content_label_score,5, 0, 1, 1)
        layout.addWidget(self.editor_label_score_add,5, 1, 1, 1)
        layout.addWidget(self.button_confirm,6, 3, 1, 1)

        self.setLayout(layout)

    def radio_button_on_clicked(self):
        self.selected_button = self.sender()
        if self.selected_button.isChecked():
            print("{}".format(self.selected_button.text()))

