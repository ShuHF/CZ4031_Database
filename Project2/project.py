
#MAIN running
import psycopg2
import csv
import pandas as pd

from interface import *

#Remove last "|" from each line, in testing
def fileProcessing():
    files = [["csv/customer.csv", "customer.csv" ], ["csv/lineitem.csv","lineitem.csv"], ["csv/nation.csv", "nation.csv"],
             ["csv/orders.csv", "orders.csv"], ["csv/part.csv","part.csv"], ["csv/partsupp.csv","partsupp.csv"],
             ["csv/region.csv","region.csv"], ["csv/supplier.csv","supplier.csv"]]
    for filename,output in files:
        rows = list()
        file = open(filename, "r")
        lines = file.read().split("\n")

        for line in lines:
            rows.append(line[:-1])

        df = pd.DataFrame(rows)
        df.to_csv("edit/" + output, header=False, index=False)
        file.close()

if __name__ == "__main__":
        gui = interface()
        gui.gui()
        print("Welcome to CZ4031 database gui")
        #fileProcessing()


