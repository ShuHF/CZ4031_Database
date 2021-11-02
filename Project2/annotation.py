#generating the annotations
import json

Node_Descriptions = {
    'Seq Scan': 'The tables are read using sequential scan.',
    'Hash Join': 'This join is implemented by the hash join operator.'
}

# extract "Node Type" from json file
def get_node_type():
    with open('queryplan_select.json') as json_file:
        data = json.loads(json_file)
        type = data["Node Type"]
        print(type)

    return type


# get node description based on node type
def get_node_description(type):
    description = ''
    if type in Node_Descriptions:
        description = Node_Descriptions[type]

# generate annotations with given Node Descriptions