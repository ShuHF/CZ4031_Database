
#MAIN running
import psycopg2

from Project2.preprocessing import connect
from Project2.interface import *

if __name__ == "__main__":
    try:
        connect()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        gui = interface()
        gui.gui()
        print("Welcome to CZ4031 database gui")
