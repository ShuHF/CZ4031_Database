import json
import tkinter
from tkinter import *


# Designing login as main  window
from Project2.preprocessing import validateconnect, executeQuery


#load the login page/first page(main) first)
def main_account_screen():
    global main_screen
    main_screen = Tk()
    main_screen.geometry("350x300")
    main_screen.title("Account Login")

    global username_verify
    global password_verify
    global db_verify

    username_verify = StringVar()
    password_verify = StringVar()
    db_verify = StringVar()

    global username_entry
    global password_entry
    global db_entry
    Label(main_screen, text="CASE SENSITIVE", width="300", height="2", font=("Courier", 14)).pack(padx=2)
    Label(main_screen, text="Username:", width="300", height="2", font=("Courier", 14)).pack()
    username_entry = Entry(main_screen, textvariable=username_verify)
    username_entry.pack()

    Label(main_screen, text="Password:", width="300", height="2", font=("Courier", 14)).pack()
    password_entry = Entry(main_screen, textvariable=password_verify, show='*')
    password_entry.pack()

    Label(main_screen, text="Database Name:", width="300", height="2", font=("Courier", 14)).pack()
    db_entry = Entry(main_screen, textvariable=db_verify, show='*')
    db_entry.pack()

    Button(main_screen, text="Login", width=10, height=1, command=validatelogin).pack(pady=10)

    main_screen.mainloop()

#validate the user input in the main login
def validatelogin():
    username1 = username_verify.get()
    password1 = password_verify.get()
    db1 = db_verify.get()
    result = validateconnect(username1, password1, db1)
    if result:
        guiforSQL()
    else:
        login_fail()

#a pop up wil appear if login fail
def login_fail():
    global login_fail_screen
    login_fail_screen = Toplevel(main_screen)
    login_fail_screen.title("Fail")
    login_fail_screen.geometry("300x100")
    Label(login_fail_screen, text="Incorrect login credential",font=("Courier", 14)).pack()
    Button(login_fail_screen, text="OK", command=delete_login_fail).pack()

#delete the popup
def delete_login_fail():
    login_fail_screen.destroy()
#delete the popup
def delete_main():
    main_screen.destroy()
#delete the popup
def delete_quiforSQL():
    window.destroy()
#delete the popup
def delete_changeprompt():
    login_change.destroy()

#create a popup for user changing the connection(success/fail)
def change_login():
    global login_change
    login_change = Toplevel(relogpop)
    login_change.geometry("200x200")
    text = NONE
    if result2:
        text = "Change!"
    else:
        text = "Incorrect"
    login_change.title(text)
    Label(login_change, text=text + "!", font=("Courier",14)).pack()
    Button(login_change, text="OK", width=10, height=1, command=delete_changeprompt).pack()

#Submit function to test if it is empty and also the result
def submitsql():
    text = panel_1_textarea.get("1.0", "end-1c")
    if not text:
        panel_2_textarea.configure(state='normal')
        panel_2_textarea.delete('1.0', END)
        panel_2_textarea.insert(END, "Empty String")
        panel_2_textarea.config(fg="Red")
        panel_2_textarea.configure(state='disabled')
    else:
        x = executeQuery(text)
        f = open('queryplan.json', "r")
        data = json.load(f)
        panel_2_textarea.configure(state='normal')
        panel_2_textarea.delete('1.0', END)
        panel_2_textarea.insert(END, data)
        if not x:
            panel_2_textarea.config(fg="Red")
        panel_2_textarea.configure(state='disabled')

#the popup for change connection in the middle (same as the main_screen)
def relog():
    global relogpop
    relogpop = Toplevel(window)
    relogpop.geometry("350x300")
    relogpop.title("Change account")
    global username_verify2
    global password_verify2
    global db_verify2

    username_verify2 = StringVar()
    password_verify2 = StringVar()
    db_verify2 = StringVar()

    global username_entry2
    global password_entry2
    global db_entry2
    Label(relogpop, text="Username:", width="300", height="2", font=("Courier", 14)).pack()
    username_entry2 = Entry(relogpop, textvariable=username_verify2)
    username_entry2.pack()

    Label(relogpop, text="Password:", width="300", height="2", font=("Courier", 14)).pack()
    password_entry2 = Entry(relogpop, textvariable=password_verify2, show='*')
    password_entry2.pack()

    Label(relogpop, text="Database Name:", width="300", height="2", font=("Courier", 14)).pack()
    db_entry2 = Entry(relogpop, textvariable=db_verify2, show='*')
    db_entry2.pack()

    Button(relogpop, text="Login", width=10, height=1, command=validatelogin2).pack(pady=10)

#validate user input upon pressing setting (change conn in the middle)
def validatelogin2():
    username2 = username_verify2.get()
    password2 = password_verify2.get()
    db2 = db_verify2.get()
    global result2
    result2 = validateconnect(username2, password2, db2)
    change_login()


#gui for the main applicaiton
def guiforSQL():
    delete_main()
    global window
    global panel_1_textarea
    global panel_2_textarea
    window = Tk()
    window.geometry("1030x750")
    window.title("CZ4031")
    # menubar
    menubar = Menu(window)
    menubar.add_command(label="Setting", command=relog)
    menubar.add_command(label="Exit", command=delete_quiforSQL)
    window.config(menu=menubar)
    #Userinput
    panel_1 = PanedWindow(bd=2, relief=RIDGE, height=350, width=500)
    panel_1.place(x=10, y=20)
    panel_1_label = Label(panel_1, text="User input")
    panel_1_label.config(font=("Courier", 14))
    panel_1_textarea = Text(panel_1, height=20, width=62)
    panel_1_label.pack()
    panel_1_textarea.pack()
    # Submit button
    submitbtn = Button(window, text="Submit", relief=RIDGE, font=("arial", 12, "bold"), width=20,
                       command=submitsql)
    submitbtn.place(x=300, y=340)

    # panel2(annotated input)
    panel_2 = PanedWindow(bd=2, relief=RIDGE, height=350, width=500)
    panel_2.place(x=10, y=380)
    panel_2_label = Label(panel_2, text="Annotated Result")
    panel_2_textarea = Text(panel_2, height=20, width=62)
    panel_2_textarea.configure(state='disabled')
    panel_2_label.config(font=("Courier", 14))
    panel_2_label.pack()
    panel_2_textarea.pack()

    # panel3(QEP display)
    panel_3 = PanedWindow(bd=2, relief=RIDGE, height=710, width=500)
    panel_3.place(x=520, y=20)
    panel_3_label = Label(panel_3, text="Visualize")
    panel_3_label.config(font=("Courier", 14))
    panel_3_label.place(relx=0.0, rely=0.0)
    window.mainloop()



main_account_screen()