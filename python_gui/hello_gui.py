from Tkinter import *
import tkMessageBox

window = Tk()
window.title("My app title 1")

def helloCallback():
    tkMessageBox.showinfo("title python", "Hello World")

btn = Button(window, text="Click here", command=helloCallback)
btn.pack()

window.mainloop()
