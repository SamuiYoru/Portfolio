from PyQt5 import QtWidgets, QtGui, QtCore
from WorkWidgets.AddStuWidget import AddStuWidget
from WorkWidgets.ShowStuWidget import ShowStuWidget
from WorkWidgetComponents import LabelComponent
from WorkWidgetComponents import ButtonComponent


class MainWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setObjectName("main_widget")
        self.setAttribute(QtCore.Qt.WA_StyledBackground, True)

        self.setStyleSheet(
            """
                QWidget#main_widget{{
                    color: white;
                    border-image: url(\"{}\");
                }};
            """.format("./Image/base.png")
        )

        layout = QtWidgets.QGridLayout()
        header_label = LabelComponent(24, "")
        function_widget = FunctionWidget()
        menu_widget = MenuWidget(function_widget.update_widget)

        header_label.setObjectName("main_widget_header_label")
        header_label.setStyleSheet(
            """
              QLabel#main_widget_header_label
              {{
                color: white;
                border-image: url(\"{}\");
              }}
            """.format("./Image/header.png")
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
        self.update_widget_callback = update_widget_callback

        layout = QtWidgets.QVBoxLayout()
        add_button = ButtonComponent("Add\nStudent", 14)
        show_button = ButtonComponent("Show all")
        add_button.clicked.connect(lambda: self.update_widget_callback("add"))
        show_button.clicked.connect(lambda: self.update_widget_callback("show"))

        add_button.setObjectName("main_widget_add_button")
        add_button.setStyleSheet(
            """
              QPushButton#main_widget_add_button
              {{
                color: black;
                border-image: url(\"{}\");
              }}
            """.format("./Image/button.png")
        )

        button_label = LabelComponent(24, "")
        button_label.setObjectName("main_widget_button_label")
        button_label.setStyleSheet(
            """
              QLabel#main_widget_button_label
              {{
                color: black;
                border-image: url(\"{}\");
              }}
            """.format("./Image/button2.png")
        )
        empty_label = LabelComponent(24, "")

        layout.addWidget(add_button, stretch=1)
        layout.addWidget(show_button, stretch=1)
        layout.addWidget(button_label, stretch=1)
        layout.addWidget(empty_label, stretch=3)

        self.setLayout(layout)


class FunctionWidget(QtWidgets.QStackedWidget):
    def __init__(self):
        super().__init__()
        self.widget_dict = {
            "add": self.addWidget(AddStuWidget()),
            "show": self.addWidget(ShowStuWidget())
        }
        self.update_widget("add")
    
    def update_widget(self, name):
        self.setCurrentIndex(self.widget_dict[name])
        current_widget = self.currentWidget()
        current_widget.load()
