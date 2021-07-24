# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'device.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_device(object):
    def setupUi(self, device):
        device.setObjectName("device")
        device.resize(1179, 733)
        self.centralwidget = QtWidgets.QWidget(device)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.scrollArea = QtWidgets.QScrollArea(self.centralwidget)
        self.scrollArea.setStyleSheet("background-color:rgb(255, 248, 254)\n"
"")
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 1155, 658))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.list = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        self.list.setGeometry(QtCore.QRect(0, 0, 321, 761))
        self.list.setStyleSheet("background-color:rgb(255, 223, 183)")
        self.list.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.list.setFrameShadow(QtWidgets.QFrame.Raised)
        self.list.setObjectName("list")
        self.networksetting = QtWidgets.QPushButton(self.list)
        self.networksetting.setGeometry(QtCore.QRect(50, 220, 181, 51))
        font = QtGui.QFont()
        font.setFamily("Segoe UI")
        font.setPointSize(10)
        self.networksetting.setFont(font)
        self.networksetting.setObjectName("networksetting")
        self.gatewaysetting = QtWidgets.QPushButton(self.list)
        self.gatewaysetting.setGeometry(QtCore.QRect(50, 140, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.gatewaysetting.setFont(font)
        self.gatewaysetting.setObjectName("gatewaysetting")
        self.devicesetting = QtWidgets.QPushButton(self.list)
        self.devicesetting.setGeometry(QtCore.QRect(50, 300, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.devicesetting.setFont(font)
        self.devicesetting.setObjectName("devicesetting")
        self.historical = QtWidgets.QPushButton(self.list)
        self.historical.setGeometry(QtCore.QRect(50, 450, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.historical.setFont(font)
        self.historical.setObjectName("historical")
        self.line = QtWidgets.QFrame(self.list)
        self.line.setGeometry(QtCore.QRect(310, 0, 20, 761))
        font = QtGui.QFont()
        font.setBold(False)
        font.setWeight(50)
        self.line.setFont(font)
        self.line.setFrameShape(QtWidgets.QFrame.VLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.testtool = QtWidgets.QPushButton(self.list)
        self.testtool.setGeometry(QtCore.QRect(50, 530, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.testtool.setFont(font)
        self.testtool.setObjectName("testtool")
        self.telemetrycontrol = QtWidgets.QPushButton(self.list)
        self.telemetrycontrol.setGeometry(QtCore.QRect(50, 380, 181, 51))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.telemetrycontrol.setFont(font)
        self.telemetrycontrol.setObjectName("telemetrycontrol")
        self.gatewaysetting.raise_()
        self.devicesetting.raise_()
        self.historical.raise_()
        self.line.raise_()
        self.networksetting.raise_()
        self.testtool.raise_()
        self.telemetrycontrol.raise_()
        self.seial_workspace = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        self.seial_workspace.setGeometry(QtCore.QRect(320, 0, 841, 721))
        self.seial_workspace.setStyleSheet("background-color:rgb(255, 255, 255)")
        self.seial_workspace.setObjectName("seial_workspace")
        self.table = QtWidgets.QTableWidget(self.seial_workspace)
        self.table.setGeometry(QtCore.QRect(0, 0, 851, 501))
        self.table.setObjectName("table")
        self.table.setColumnCount(11)
        self.table.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.table.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(3, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(4, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(5, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(6, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(7, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(8, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(9, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(10)
        item.setFont(font)
        self.table.setHorizontalHeaderItem(10, item)
        self.deletechannel = QtWidgets.QPushButton(self.seial_workspace)
        self.deletechannel.setGeometry(QtCore.QRect(530, 560, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.deletechannel.setFont(font)
        self.deletechannel.setObjectName("deletechannel")
        self.add = QtWidgets.QPushButton(self.seial_workspace)
        self.add.setGeometry(QtCore.QRect(340, 560, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.add.setFont(font)
        self.add.setObjectName("add")
        self.view = QtWidgets.QPushButton(self.seial_workspace)
        self.view.setGeometry(QtCore.QRect(160, 560, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.view.setFont(font)
        self.view.setObjectName("view")
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.verticalLayout.addWidget(self.scrollArea)
        device.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(device)
        self.statusbar.setObjectName("statusbar")
        device.setStatusBar(self.statusbar)
        self.menubar = QtWidgets.QMenuBar(device)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1179, 26))
        self.menubar.setObjectName("menubar")
        device.setMenuBar(self.menubar)

        self.retranslateUi(device)
        QtCore.QMetaObject.connectSlotsByName(device)

    def retranslateUi(self, device):
        _translate = QtCore.QCoreApplication.translate
        device.setWindowTitle(_translate("device", "TEST TOOL"))
        self.networksetting.setText(_translate("device", "NETWORK SETTING"))
        self.gatewaysetting.setText(_translate("device", "GATEWAY SETTING"))
        self.devicesetting.setText(_translate("device", "DEVICE SETTING"))
        self.historical.setText(_translate("device", "HISTORICAL RECORD"))
        self.testtool.setText(_translate("device", "TESTTOOL"))
        self.telemetrycontrol.setText(_translate("device", "TELEMETRY CONTROL"))
        item = self.table.horizontalHeaderItem(0)
        item.setText(_translate("device", "No"))
        item = self.table.horizontalHeaderItem(1)
        item.setText(_translate("device", "Port"))
        item = self.table.horizontalHeaderItem(2)
        item.setText(_translate("device", "Slave Address"))
        item = self.table.horizontalHeaderItem(3)
        item.setText(_translate("device", "Function"))
        item = self.table.horizontalHeaderItem(4)
        item.setText(_translate("device", "Device Channel"))
        item = self.table.horizontalHeaderItem(5)
        item.setText(_translate("device", "Data Type"))
        item = self.table.horizontalHeaderItem(6)
        item.setText(_translate("device", "Device Type"))
        item = self.table.horizontalHeaderItem(7)
        item.setText(_translate("device", "Device Name"))
        item = self.table.horizontalHeaderItem(8)
        item.setText(_translate("device", "Channel Title"))
        item = self.table.horizontalHeaderItem(9)
        item.setText(_translate("device", "Scale"))
        item = self.table.horizontalHeaderItem(10)
        item.setText(_translate("device", "Device Status"))
        self.deletechannel.setText(_translate("device", "DELETE CHANNEL"))
        self.add.setText(_translate("device", "ADD DEVICE"))
        self.view.setText(_translate("device", "LOAD DATA"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    device = QtWidgets.QMainWindow()
    ui = Ui_device()
    ui.setupUi(device)
    device.show()
    sys.exit(app.exec_())