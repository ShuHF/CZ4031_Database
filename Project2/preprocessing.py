#reading the inputs and any preprocessing necessary to make ur alogrith work

#connection
import psycopg2
import sqlparse
import json
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT


def connect():
    """ Connect to the PostgreSQL database server """
    conn = None
    database_name = 'cz4031'
    try:
        # read connection parameters
        # connect to the PostgreSQL server
        print('Connecting to the PostgreSQL database...')
        conn = psycopg2.connect(database=database_name, user="postgres", password='root')
        conn.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)

        # create a cursor
        cur = conn.cursor()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        return cur
def validation(text):
    if not text:
        return "Empty string"
    else:
        sqlstatement = sqlparse.split(text)
        # if not sqlstatement.is_valid():
        #     return sqlstatement.errors
        # else:
        #     return text
def executeQuery(text):
    newStatement = "EXPLAIN (analyze, verbose, costs, format JSON) " + text
    cursor = connect()
    cursor.execute(newStatement)
    explain_query = cursor.fetchall()
    # open text file
    with open('output/queryplan.json', 'w') as f:
        json.dump(explain_query, f, ensure_ascii=False, indent=2)
    cursor.close()
    print(explain_query)
    return explain_query


