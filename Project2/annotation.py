#generating the annotations
import json

Node_Descriptions = {
    'Seq Scan': 'The tables are read using sequential scan.',
    'Hash Join': 'This join is implemented by the hash join operator.'
}

# extract "Node Type" from json file
def get_node_type():
    with open('C:/Users/Xin Yi Loh/OneDrive/Documents/GitHub/CZ4031_Database/Project2/queryplan_join.json', 'r') as json_file: 
        data = json.loads(json_file.read())
        type = data['Plan']['Node Type']
        print(type)

    return type


# get node description based on node type
def get_node_description(type):
    description = ''
    if type in Node_Descriptions:
        description = Node_Descriptions[type]
    
    return description

# generate annotations with given Node Descriptions

if __name__ == "__main__":
        print("Welcome to CZ4031 database gui")
        type = get_node_type()
        description = get_node_description(type)
        print(description)