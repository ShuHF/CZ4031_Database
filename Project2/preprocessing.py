#reading the inputs and any preprocessing necessary to make ur alogrith work

#connection
import psycopg2
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT


def connect():
    """ Connect to the PostgreSQL database server """
    conn = None
    try:
        # read connection parameters
        # connect to the PostgreSQL server
        print('Connecting to the PostgreSQL database...')
        conn = psycopg2.connect("user=postgres password='root'")
        conn.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)

        # create a cursor
        cur = conn.cursor()
        cur.execute("SELECT datname FROM pg_database;")

        list_database = cur.fetchall()
        database_name = 'cz4031'

        if (database_name,) not in list_database:
            sqlCreateDatabase = "create database " + database_name + ";"
            cur.execute(sqlCreateDatabase)
            # print("'{}' has been created successfully.".format(database_name))
        #to be deleted
        else:
            print("{} database already exist.".format(database_name))
        # close the communication with the PostgreSQL
        cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
            print('Database connection closed.')


