from tkinter import *
from random import randint
import GUI
root = Tk()
lab = Label(root)
lab.pack()
str = "Hello"

def update():
   lab['text'] = str
   root.after(1000, update) # run itself again after 1000 ms
   

# run first time
update()


root.mainloop()