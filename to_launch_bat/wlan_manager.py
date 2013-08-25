import sys
from PyQt4 import QtGui, QtCore
 
class Wlan_Manager(QtGui.QWidget):
    def __init__(self):
        QtGui.QWidget.__init__(self)

        '''
        okButton = QtGui.QPushButton("OK")
        cancelButton = QtGui.QPushButton("Cancel")
        goodButton = QtGui.QPushButton("Good")

        hbox = QtGui.QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(okButton)
        hbox.addWidget(cancelButton)

        hbox2 = QtGui.QHBoxLayout()
        hbox2.addWidget(goodButton)
        

        vbox = QtGui.QVBoxLayout()
        vbox.addStretch(1)
        vbox.addLayout(hbox)
        vbox.addLayout(hbox2)
        
        self.setLayout(vbox)    
        
        self.setGeometry(300, 300, 300, 150)
        '''
        self.setWindowTitle("Wlan_Manager")

        self.layout = QtGui.QHBoxLayout()
        self.layoutBtn = QtGui.QHBoxLayout()
        self.mainLayout = QtGui.QVBoxLayout()
        
 
        self.label = QtGui.QLabel("Choose command:")
        self.commandList = QtGui.QComboBox()
        self.commandList.addItem("wlan start")
        self.commandList.addItem("wlan stop")
        self.runBtn = QtGui.QPushButton("Run")
        self.quitBtn = QtGui.QPushButton("Quit")

        self.layout.addWidget(self.label)
        self.layout.addWidget(self.commandList)
        
        self.layoutBtn.addWidget(self.runBtn)
        self.layoutBtn.addWidget(self.quitBtn)
 
        self.mainLayout.addLayout(self.layout)
        self.mainLayout.addLayout(self.layoutBtn)
        self.setLayout(self.mainLayout)
        self.setGeometry(300, 300, 300, 150)
        
 
        
 
    def run_command(self, name):
        # Set the output text
        self.output.setText("Hello " + name + "!")
 
if __name__ == "__main__":
        # Create QApplication
        app = QtGui.QApplication(sys.argv)
 
        # Create a HelloQt window and show it
        WM = Wlan_Manager()
        WM.show()
       
        # Run the mainloop
        sys.exit(app.exec_())
