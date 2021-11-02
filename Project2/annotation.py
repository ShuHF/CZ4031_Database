#generating the annotations
import json

Node_Descriptions = {
    'Seq Scan': 'The tables are read using sequential scan.',
    'Hash Join': 'This join is implemented by the hash join operator.'
}

# extract "Node Type" from json file
with open('queryplan_select.json') as json_file:
    data = json.loads(json_file)
    type = data["Node Type"]
    print(type)

# generate annotations with given Node Descriptions