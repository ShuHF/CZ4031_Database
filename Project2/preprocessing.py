#reading the inputs and any preprocessing necessary to make ur alogrith work

#connection
import psycopg2
import json
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT
from selenium import webdriver
from selenium.webdriver.common.by import By

def validateconnect(username, password, database_name):
    conn = None
    try:
        conn = psycopg2.connect(database=database_name, user=username, password=password)
        conn.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
        verify = True
        info = {
            "username" : username,
            "password" : password,
            "database" : database_name
        }
        json_object = json.dumps(info, indent=4)
        with open("logininfo.json", "w") as outputfile:
            outputfile.write(json_object)
    except (Exception, psycopg2.DatabaseError) as error:
        verify = False
    return verify


def connect():
    """ Connect to the PostgreSQL database server """
    conn = None
    f = open('logininfo.json', "r")
    data = json.load(f)
    username = data['username']
    pwd = data['password']
    database_name = data['database']
    try:
        # read connection parameters
        #username = postgres, pwd = root
        conn = psycopg2.connect(database=database_name, user=username, password=pwd)
        conn.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
        # create a cursor
        cur = conn.cursor()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        return cur

def executeQuery(text):
    newStatement = "EXPLAIN (analyze, verbose, costs, format JSON) " + text

    try:
        cursor = connect()
        cursor.execute(newStatement)
        explain_query = cursor.fetchall()
        executesuccess = True
    except(Exception, psycopg2.DatabaseError) as error:
        explain_query = "Please check your sql statement: \n" + text
        executesuccess = False
    finally:
        cursor.close()

    # open text file
    with open('queryplan.json', 'w') as f:
        json.dump(explain_query, f, ensure_ascii=False, indent=2)
    return executesuccess


# load json to a dictionary
def loadjson():
    with open('queryplan.json') as json_file:
        data = json.load(json_file)
    dict_plan_inner = data[0][0]
    return dict_plan_inner


# function to create the QEP Tree Diagram
def createQEPDiagram():
    data = loadjson()
    # Detach webpage to ensure the web browser does not close
    options = webdriver.EdgeOptions
    options.add_experimental_option("detach", True)

    # Open a webpage using Microsoft Edge
    driver = webdriver.Edge(options=options, executable_path='msedgedriver.exe')

    driver.maximize_window()
    driver.get("https://tatiyants.com/pev/#/plans/new")
    driver.implicitly_wait(5)
    id_box = driver.find_element(By.CLASS_NAME, "input-box-lg").send_keys(json.dumps(data))
    driver.implicitly_wait(5)
    submit_btn = driver.find_element(By.CLASS_NAME, "btn-default").click()


