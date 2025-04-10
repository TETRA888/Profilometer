import utilityFunctions
import graph
import tkinter
from PIL import ImageTk, Image

import PIL.Image

from utilityFunctions import connect, startScanning, startCalibrate, startHome, sendData, moveScanless, scanMoveless
from graph import graphProfile
from tkinter import *
from tkinter import ttk

# @author: Asad Melibaev <amelibaev@ucdavis.edu>
# @version: 2.0
# @since: 2025-21-09

# Creating a mainwindow refrence that will be called the root
# This will be the parent of all the children widgets within it
root = Tk()
root.title("Open Road Profiler 2.0")

# Putting a mainframe inside of the root
mainframe = ttk.Frame(root, padding = "5")
mainframe.grid(column = 0, row = 0, sticky = (N, W, E, S))

# This tells the geometry manager to dynamically adjust the window size to fit the 
# natural size of the widgets
root.columnconfigure(0, weight = 1)
mainframe.columnconfigure(0, weight = 1)
mainframe.rowconfigure(7, weight=1)     # Make row 7 expandable

# This function establishes a connection between the microcontroller and the Raspberrpi Pi
ser = connect() #REMOVE ME FOR ACTUAL TESTING

ttk.Label(mainframe, text = "Start Scanning From 0-2500mm").grid(column = 0, row = 1, sticky = (W, E))
ttk.Button(mainframe, text = "Scan", command = lambda: scanAndShow()).grid(column = 1, row = 1, sticky = (W, E))

ttk.Label(mainframe, text = "Home the laser head back to the start position at X = 0").grid(column = 0, row = 2, sticky = (W, E))
ttk.Button(mainframe, text = "Home", command = lambda: startHome(ser)).grid(column = 1, row = 2, sticky = (W, E))

ttk.Label(mainframe, text = "Check gantry calibration").grid(column = 0, row = 3, sticky = (W, E))
ttk.Button(mainframe, text = "Calibrate", command = lambda: startCalibrate(ser)).grid(column = 1, row = 3, sticky = (W, E))

ttk.Label(mainframe, text = "Send data to the DAQ").grid(column = 0, row = 4, sticky = (W, E))
ttk.Button(mainframe, text = "Send", command = lambda: sendData()).grid(column = 1, row = 4, sticky = (W, E))

ttk.Label(mainframe, text = "Move gantry head without scanning").grid(column = 0, row = 5, sticky = (W,E))
ttk.Button(mainframe, text = "Move Without Scan", command = lambda: moveScanless()).grid(column = 1, row = 5, sticky = (W,E))
ttk.Label(mainframe, text = "Scan without moving the gantry head").grid(column = 0, row = 6, sticky = (W,E))
ttk.Button(mainframe, text = "Scan Without Move", command = lambda: scanMoveless()).grid(column = 1, row = 6, sticky = (W,E))

def resizeFunction(imageName):
	pillowImage = PIL.Image.open(imageName)
	width, height = pillowImage.size
	resizedImage = pillowImage.resize((width//2,height//2), PIL.Image.Resampling.LANCZOS)
	return ImageTk.PhotoImage(resizedImage)

graph = resizeFunction("3DProfile.png")

def scanAndShow():
	startScanning(ser)
	graph = resizeFunction("3DProfile.png")
	root.update_idletasks()

graph1 = resizeFunction("profileGraph.png")
ttk.Label(mainframe, image = graph).grid(column = 0, row = 7, sticky = (N,S,E,W), padx=10, pady=10)
ttk.Label(mainframe, image = graph1).grid(column = 1, row = 7, sticky = (N,S,E,W), padx=10, pady=10)

# This simply goes through all of the children widgets within the mainframe and adds 
# padding around them to make it less scrunched together
for child in mainframe.winfo_children():
    child.grid_configure(padx=5, pady=5)

root.mainloop()

# Debugging functions
'''
# Placeholder debugging functions
# def startScanning():
#     print("Scanning")

# def startHome():
#     print("Homing")

# def startCalibrate():
#     print("Calibrating")

# def sendData():
#     print("Sending Data")
'''