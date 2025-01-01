from PyQt5 import QtWidgets, QtGui, QtCore
from .AddStuWidget import AddStuWidget
from .WidgetComponents import LabelComponent
from .WidgetComponents import LabelComponent
from .WidgetComponents import ButtonComponent
from .ShowStuWidget import ShowStuWidget
from .ModifyStuWidget import ModifyStuWidget

class MainWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("main_widget")
        self.setAttribute(QtCore.Qt.WA_StyledBackground, True)

        layout = QtWidgets.QGridLayout()
        header_label = LabelComponent(24, "Student Management System")
        header_label.setStyleSheet('''
                background-color: #e2eafc;
                border-bottom: 5px double #001845;    
            '''
        )
        header_label.setAlignment(QtCore.Qt.AlignCenter)
        function_widget = FunctionWidget()
        menu_widget = MenuWidget(function_widget.update_widget)
        self.setStyleSheet(
            """
                QWidget#main_widget
              {{
                color: #0096c7;
                border-image: url(\"{}\");
              }}
            """.format("./Image/background.png")
        )

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
        self.setAttribute(QtCore.Qt.WA_StyledBackground, True)
        self.update_widget_callback = update_widget_callback
        self.setStyleSheet('''
            QWidget#menu_widget{
                border-right: 5px double #1B4965;
            }
            QPushButton:enabled{
                background-color:#a2d2ff;
                border:0px solid #023e8a;
                border-radius:5px;
                color:#0077b6;
                }
            '''
        )
        layout = QtWidgets.QVBoxLayout()
        add_button = ButtonComponent("Add student")
        #add_button.setStyleSheet('background-color:#001845;color:#ffffff;')
        modify_button = ButtonComponent("Modify")
        #modify_button.setStyleSheet('background-color:#001845;color:#ffffff;')
        show_button = ButtonComponent("Show all")


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
        self.widget_dict = {
            "add": self.addWidget(AddStuWidget()),
            "show": self.addWidget(ShowStuWidget()),
            "modify": self.addWidget(ModifyStuWidget())
        }
        self.setStyleSheet('''
            QWidget#show_stu_widget{
                border: none;
            }
             QPushButton:disabled{
                background-color:transparent;
                border:0px solid #ffffff;
                border-radius:5px;
                color:#0077b6}

            QPushButton:enabled{
                background-color:#a2d2ff;
                border:0px solid #023e8a;
                border-radius:5px;
                color:#0077b6;
                }
            '''
        )
        self.update_widget("add")
    
    def update_widget(self, name):
        self.setCurrentIndex(self.widget_dict[name])
        current_widget = self.currentWidget()
        current_widget.load()
