#reading the inputs and any preprocessing necessary to make ur alogrith work

#connection
import psycopg2
import sqlparse
import json
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT

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
    print(username, pwd, database_name)
    try:
        # read connection parameters
        # connect to the PostgreSQL server
        print('Connecting to the PostgreSQL database...')
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
    cursor = connect()
    cursor.execute(newStatement)
    explain_query = cursor.fetchall()
    # open text file
    with open('queryplan.json', 'w') as f:
        json.dump(explain_query, f, ensure_ascii=False, indent=2)
    cursor.close()
    print(explain_query)
    return explain_query


