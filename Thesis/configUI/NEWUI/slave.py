# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'slave.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_slave(object):
    def setupUi(self, slave):
        slave.setObjectName("slave")
        slave.resize(638, 767)
        self.centralwidget = QtWidgets.QWidget(slave)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.scrollArea = QtWidgets.QScrollArea(self.centralwidget)
        self.scrollArea.setStyleSheet("background-color:rgb(255, 248, 254)\n"
"")
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 614, 692))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.seial_workspace = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        self.seial_workspace.setGeometry(QtCore.QRect(0, 0, 611, 691))
        self.seial_workspace.setStyleSheet("background-color:rgb(255, 255, 255)")
        self.seial_workspace.setObjectName("seial_workspace")
        self.groupBox_2 = QtWidgets.QGroupBox(self.seial_workspace)
        self.groupBox_2.setGeometry(QtCore.QRect(80, 30, 451, 621))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setUnderline(False)
        self.groupBox_2.setFont(font)
        self.groupBox_2.setObjectName("groupBox_2")
        self.label_23 = QtWidgets.QLabel(self.groupBox_2)
        self.label_23.setGeometry(QtCore.QRect(30, 60, 41, 21))
        font = QtGui.QFont()
        font.setPointSize(9)
        font.setBold(True)
        font.setWeight(75)
        self.label_23.setFont(font)
        self.label_23.setObjectName("label_23")
        self.label_24 = QtWidgets.QLabel(self.groupBox_2)
        self.label_24.setGeometry(QtCore.QRect(20, 110, 121, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_24.setFont(font)
        self.label_24.setObjectName("label_24")
        self.label_25 = QtWidgets.QLabel(self.groupBox_2)
        self.label_25.setGeometry(QtCore.QRect(20, 160, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_25.setFont(font)
        self.label_25.setObjectName("label_25")
        self.lineEdit = QtWidgets.QLineEdit(self.groupBox_2)
        self.lineEdit.setGeometry(QtCore.QRect(160, 50, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.lineEdit.setFont(font)
        self.lineEdit.setText("")
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit_2 = QtWidgets.QLineEdit(self.groupBox_2)
        self.lineEdit_2.setGeometry(QtCore.QRect(160, 100, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.lineEdit_2.setFont(font)
        self.lineEdit_2.setText("")
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.code_2 = QtWidgets.QComboBox(self.groupBox_2)
        self.code_2.setGeometry(QtCore.QRect(160, 150, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.code_2.setFont(font)
        self.code_2.setObjectName("code_2")
        self.code_2.addItem("")
        self.code_2.addItem("")
        self.code_2.addItem("")
        self.code_2.addItem("")
        self.code_2.addItem("")
        self.code_2.addItem("")
        self.label_26 = QtWidgets.QLabel(self.groupBox_2)
        self.label_26.setGeometry(QtCore.QRect(20, 210, 131, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_26.setFont(font)
        self.label_26.setObjectName("label_26")
        self.lineEdit_3 = QtWidgets.QLineEdit(self.groupBox_2)
        self.lineEdit_3.setGeometry(QtCore.QRect(160, 200, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.lineEdit_3.setFont(font)
        self.lineEdit_3.setText("")
        self.lineEdit_3.setObjectName("lineEdit_3")
        self.label_27 = QtWidgets.QLabel(self.groupBox_2)
        self.label_27.setGeometry(QtCore.QRect(20, 260, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_27.setFont(font)
        self.label_27.setObjectName("label_27")
        self.label_28 = QtWidgets.QLabel(self.groupBox_2)
        self.label_28.setGeometry(QtCore.QRect(20, 310, 111, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_28.setFont(font)
        self.label_28.setObjectName("label_28")
        self.label_29 = QtWidgets.QLabel(self.groupBox_2)
        self.label_29.setGeometry(QtCore.QRect(20, 360, 111, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_29.setFont(font)
        self.label_29.setObjectName("label_29")
        self.lineEdit_6 = QtWidgets.QLineEdit(self.groupBox_2)
        self.lineEdit_6.setGeometry(QtCore.QRect(160, 350, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.lineEdit_6.setFont(font)
        self.lineEdit_6.setText("")
        self.lineEdit_6.setObjectName("lineEdit_6")
        self.label_30 = QtWidgets.QLabel(self.groupBox_2)
        self.label_30.setGeometry(QtCore.QRect(20, 410, 121, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_30.setFont(font)
        self.label_30.setObjectName("label_30")
        self.lineEdit_7 = QtWidgets.QLineEdit(self.groupBox_2)
        self.lineEdit_7.setGeometry(QtCore.QRect(160, 400, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.lineEdit_7.setFont(font)
        self.lineEdit_7.setText("")
        self.lineEdit_7.setObjectName("lineEdit_7")
        self.label_31 = QtWidgets.QLabel(self.groupBox_2)
        self.label_31.setGeometry(QtCore.QRect(20, 460, 101, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_31.setFont(font)
        self.label_31.setObjectName("label_31")
        self.label_32 = QtWidgets.QLabel(self.groupBox_2)
        self.label_32.setGeometry(QtCore.QRect(20, 510, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.label_32.setFont(font)
        self.label_32.setObjectName("label_32")
        self.lineEdit_9 = QtWidgets.QLineEdit(self.groupBox_2)
        self.lineEdit_9.setGeometry(QtCore.QRect(160, 500, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.lineEdit_9.setFont(font)
        self.lineEdit_9.setText("")
        self.lineEdit_9.setObjectName("lineEdit_9")
        self.connect_2 = QtWidgets.QPushButton(self.groupBox_2)
        self.connect_2.setGeometry(QtCore.QRect(190, 570, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.connect_2.setFont(font)
        self.connect_2.setObjectName("connect_2")
        self.code_3 = QtWidgets.QComboBox(self.groupBox_2)
        self.code_3.setGeometry(QtCore.QRect(160, 250, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.code_3.setFont(font)
        self.code_3.setObjectName("code_3")
        self.code_3.addItem("")
        self.code_3.addItem("")
        self.code_4 = QtWidgets.QComboBox(self.groupBox_2)
        self.code_4.setGeometry(QtCore.QRect(160, 300, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.code_4.setFont(font)
        self.code_4.setObjectName("code_4")
        self.code_4.addItem("")
        self.code_4.addItem("")
        self.code_4.addItem("")
        self.code_5 = QtWidgets.QComboBox(self.groupBox_2)
        self.code_5.setGeometry(QtCore.QRect(160, 450, 241, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.code_5.setFont(font)
        self.code_5.setObjectName("code_5")
        self.code_5.addItem("")
        self.code_5.addItem("")
        self.code_5.addItem("")
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.verticalLayout.addWidget(self.scrollArea)
        slave.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(slave)
        self.statusbar.setObjectName("statusbar")
        slave.setStatusBar(self.statusbar)
        self.menubar = QtWidgets.QMenuBar(slave)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 638, 26))
        self.menubar.setObjectName("menubar")
        slave.setMenuBar(self.menubar)

        self.retranslateUi(slave)
        QtCore.QMetaObject.connectSlotsByName(slave)

    def retranslateUi(self, slave):
        _translate = QtCore.QCoreApplication.translate
        slave.setWindowTitle(_translate("slave", "Setting Slave"))
        self.groupBox_2.setTitle(_translate("slave", "Device setting"))
        self.label_23.setText(_translate("slave", "No"))
        self.label_24.setText(_translate("slave", "Slave Address"))
        self.label_25.setText(_translate("slave", "Function"))
        self.code_2.setItemText(0, _translate("slave", "0x01"))
        self.code_2.setItemText(1, _translate("slave", "0x02"))
        self.code_2.setItemText(2, _translate("slave", "0x03"))
        self.code_2.setItemText(3, _translate("slave", "0x04"))
        self.code_2.setItemText(4, _translate("slave", "0x05"))
        self.code_2.setItemText(5, _translate("slave", "0x06"))
        self.label_26.setText(_translate("slave", "Device Channel"))
        self.label_27.setText(_translate("slave", "Data Type"))
        self.label_28.setText(_translate("slave", "Device Type"))
        self.label_29.setText(_translate("slave", "Device Name"))
        self.label_30.setText(_translate("slave", "Channel Title"))
        self.label_31.setText(_translate("slave", "Value Type"))
        self.label_32.setText(_translate("slave", "Scale"))
        self.connect_2.setText(_translate("slave", "SAVE"))
        self.code_3.setItemText(0, _translate("slave", "U16"))
        self.code_3.setItemText(1, _translate("slave", "U32"))
        self.code_4.setItemText(0, _translate("slave", "INVERETER"))
        self.code_4.setItemText(1, _translate("slave", "METER"))
        self.code_4.setItemText(2, _translate("slave", "WEATHER STATION"))
        self.code_5.setItemText(0, _translate("slave", "NUMBER"))
        self.code_5.setItemText(1, _translate("slave", "BOOLEAN\'"))
        self.code_5.setItemText(2, _translate("slave", "STRING"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    slave = QtWidgets.QMainWindow()
    ui = Ui_slave()
    ui.setupUi(slave)
    slave.show()
    sys.exit(app.exec_())