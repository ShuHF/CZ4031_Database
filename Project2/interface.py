import json
import threading
import tkinter
from tkinter import *


# Designing login as main  window
from preprocessing import validateconnect, executeQuery, createQEPDiagram

from annotation import *

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
    db_entry = Entry(main_screen, textvariable=db_verify)
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
    text = userinput.get("1.0", "end-1c")
    panel_2_textarea.configure(state='normal')
    panel_2_textarea.delete('1.0', END)
    if not text:
        panel_2_textarea.insert(END, "Empty String")
        panel_2_textarea.config(fg="Red")
        panel_2_textarea.configure(state='disabled')

    # Generate annotation based on user query
    else: 
        x = executeQuery(text)
        if not x:
            panel_2_textarea.config(fg="Red")
            panel_2_textarea.insert(END, "Please check your sql statement")
        else:
            plan = get_plan()
            plans = getplanlist(plan)
            # print(plan)
            # print(plans)
            annotated = generate(text, plans)
            panel_2_textarea.config(fg="Black")
            panel_2_textarea.insert(END, annotated)
            plans.clear()

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
    db_entry2 = Entry(relogpop, textvariable=db_verify2)
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


def viewJson():
    json_textarea.configure(state='normal')
    json_textarea.delete('1.0', END)
    try:
        with open('queryplan.json', 'r') as fp:
            data = json.load(fp)

        json_textarea.insert(END, data)
        json_textarea.config(fg="Black")
    except IOError:
        json_textarea.insert(END, "File not found.")
        json_textarea.config(fg="Red")

    finally:
        json_textarea.configure(state='disabled')

#function to visualize the QEP json file into a tree structure
def viewQEPTree():
    def callback():
        createQEPDiagram()
    t = threading.Thread(target=callback)
    t.start()

#gui for the main applicaiton
def guiforSQL():
    delete_main()
    global window
    global userinput
    global panel_2_textarea
    global json_textarea
    window = Tk()
    window.geometry("1030x750")
    window.title("CZ4031")
    # menubar
    menubar = Menu(window)
    menubar.add_command(label="Setting", command=relog)
    menubar.add_command(label="Exit", command=delete_quiforSQL)
    window.config(menu=menubar)


    # # #create panel1 for the user input
    inputpanel = PanedWindow()
    inputpanel_label = Label(inputpanel, text="User input")
    inputpanel_label.config(font=("Courier", 14))
    inputpanel_label.pack(pady=5)
    inputpanel.pack()
    #scrollbar
    scrollbar = Scrollbar(inputpanel)
    scrollbar.pack(side=RIGHT, fill=Y)
    #textarea for the user to write their sql statement
    userinput = Text(inputpanel,height=10, relief='groove', wrap='word', font=('courier',10),yscrollcommand=scrollbar.set)
    userinput.pack()
    scrollbar.config(command=userinput.yview)

    #a div/panel to hold the two button which allow it to be side bvy side
    div = PanedWindow()
    # call the preprocessing.py to execute the query
    submitbtn = Button(div, text="Submit", relief=RIDGE, font=("Courier", 12, "bold"), width=20, command=submitsql)
    submitbtn.pack(side=LEFT, padx=5)
    #call a webpage to display the QEP

    qeptreebtn = Button(div, text="Visualize", relief=RIDGE, font=("Courier", 12, "bold"), width=20,command=print("hi"))
    qeptreebtn = Button(div, text="Visualize QEP Tree", relief=RIDGE, font=("Courier", 12, "bold"), width=20,command=viewQEPTree)
    qeptreebtn.pack(side=LEFT, padx=5)
    
    #Display the json format
    jsonbtn = Button(div, text="Json File", relief=RIDGE, font=("Courier", 12, "bold"), width=20,
                        command=viewJson)
    jsonbtn.pack()
    div.pack(pady=10)

    #Panel 2 for annotated
    panel_2 = PanedWindow()
    panel_2_label = Label(panel_2, text="Annotated Query", font=("Courier", 14))
    panel_2_label.pack()
    panel_2.pack()
    # scrollbar
    scrollbar2 = Scrollbar(panel_2)
    scrollbar2.pack(side=RIGHT, fill=Y)
    # textarea for the user to write their sql statement
    panel_2_textarea = Text(panel_2, state='disabled',height=10, relief='groove', wrap='word', font=('courier', 10), yscrollcommand=scrollbar2.set)
    panel_2_textarea.pack()
    scrollbar2.config(command=panel_2_textarea.yview)

    # Panel 3 for viewing JSON file
    json_panel = PanedWindow()
    json_panel_label = Label(json_panel, text="View JSON QEP", font=("Courier", 14))
    json_panel_label.pack()
    json_panel.pack()
    # scrollbar
    scrollbar3 = Scrollbar(json_panel)
    scrollbar3.pack(side=RIGHT, fill=Y)
    # textarea for the user to write their sql statement
    json_textarea = Text(json_panel, height=10,state='disabled', relief='groove', wrap='word', font=('courier', 10),
                            yscrollcommand=scrollbar3.set)
    json_textarea.pack()
    scrollbar3.config(command=json_textarea.yview)
    window.mainloop()



