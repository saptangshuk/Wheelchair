from tkinter import *
from PIL import ImageTk,Image
from random import randint

def emergency_call():
    pass

root = Tk()
root.title("Wheelchair")
root.geometry("1060x600")
#root.iconbitmap('wheelchair-icon.ico')
#emergency function
def emergency_click():
    print("Emergency button pressed")
    emergency_call()
#update the heartbeat    
def update_heartbeat():
   heart_Beat['text'] = randint(0,1000)
   root.after(1000, update_heartbeat)    

heart_Beat = Label(root)
heart_Beat.grid(row = 0 , column = 0)
#label for showing heart beat
heart_Beat_text = Label(root,text = " bpm ")
heart_Beat_text.grid(row = 0 , column = 1)
"""
#heartbeat image
heart_img = ImageTk.PhotoImage(Image.open("heart_image.png.png"))
heart_img_label = Label(image=heart_img)
heart_img_label.image = heart_img
heart_img_label.grid(row = 0 , column = 0)
"""

update_heartbeat()


#Button for emergency
emergency_button = Button(root,text="Emergency",padx=30,pady=30,command=emergency_click)
emergency_button.grid(row = 1,column= 0)

root.mainloop()
