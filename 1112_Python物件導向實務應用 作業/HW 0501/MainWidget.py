from PyQt5 import QtWidgets, QtGui, QtCore
from AddStuWidget import AddStuWidget
from WidgetComponents import LabelComponent


class MainWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("main_widget")

        layout = QtWidgets.QVBoxLayout()

        header_label = LabelComponent(24, "Student Management System")
        T_label = LabelComponent(24, "TTT")
        add_stu_widget = AddStuWidget()

        layout.addWidget(header_label, stretch=15)
        layout.addWidget(add_stu_widget, stretch=85)

        self.setLayout(layout)
