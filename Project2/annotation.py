import json
from typing import Annotated

typelist = []

def get_plan():
    with open('C:/Users/Xin Yi Loh/OneDrive/Documents/GitHub/CZ4031_Database/queryplan.json') as json_file: 
        data = json.load(json_file)
        data = data[0]
        data = data[0]
        data = data[0]
        plan = data['Plan']
    return plan

def getplanlist(plan):
    recursive_calling(plan)
    for i in typelist:
        if 'Plans' in i:
            i.pop('Plans')

    return typelist

def recursive_calling(plan):
    typelist.append(plan)
    for keys in plan:
         #This will be a child node left.left
        if keys == "Plans":
            x = plan[keys]
            for y in x:
                recursive_calling(y)

# generate annotations with given Node Descriptions
def generate(query, plans):
    annotated = 'SUBMITTED QUERY:\n' + query + '\n\n' + 'QEP EXPLANATION: \n' # separate inputted query with explanation
    i = len(plans) - 1
    # Explanation
    while i >= 0:
        # Get Node Type for each plan
        node_type = plans[i]['Node Type']
        print(node_type)
        match node_type:
            case 'Seq Scan':
                annotated += 'The table [{}] is read using Sequential Scan operation. '.format(plans[i]['Relation Name'])
                if "Filter" in plans[i]:
                    annotated += 'And filtered by [{}]'.format(plans[i]['Filter'])
                annotated += '\n'
            case 'Index Scan':
                annotated += 'The table [{}] is read using the Index Scan operation '.format(plans[i]["Relation Name"])
                if "Index Cond" in plans[i]:
                    cond = plans[i]['Index Cond']
                    split = cond.split(":", 1)
                    annotated += 'with condition(s): [{}]. '.format(cond[0])
                if "Filter" in plans[i]:
                    annotated += 'The result is then filtered by [{}]. '.format(plans[i]['Filter'])
                annotated += '\n'
            case 'Index Only Scan':
                annotated += 'An Index Only Scan operation is performed using the index on table [{}]'.format(plans[i]['Index Name'])
                if "Index Cond" in plans[i]:
                    annotated += 'with condition(s): [{}]. '.format(plans[i]['Index Cond'])
                if "Filter" in plans[i]:
                    annotated += 'The result is then filtered by [{}]. '.format(plans[i]['Filter'])
                annotated += '\n'
            case 'Hash':
                annotated += 'The Hash function will then generate a hash table from the records in the previous operation.' + '\n'
            case 'Hash Join':
                annotated += 'The Hash Join operation will then joins the previous operations with a hash [{}] join on the condition(s): [{}].'.format(plans[i]['Join Type'],plans[i]['Hash Cond']) + '\n'
            
            case 'Merge Join':
                annotated += 'The Merge Join operation will then joins the previous operations using on the condition(s): [{}]. '.format([plans[i]['Merge Cond']])
                if "Join Type" in plans[i]:
                    annotated += 'However, only the rows from the left table is returned. '
                annotated += '\n'
            
            case 'Aggregate':
                strategy = plans[i]["Strategy"]
                if strategy == "Sorted":
                    annotated += 'The Aggregate operation will sort the tuples based on the keys: [{}]'.format(plans[i]["Group Key"])
                    if "Filter" in plans[i]:
                        annotated += 'The result is then filtered by [{}]. '.format(plans[i]['Filter'])
                if strategy == "Plain":
                    annotated += 'The Aggregate operation will be performed.'
                if strategy == "Hashed":
                    annotated += 'The Aggregate operation will hash the rows based on keys: [{}]. The selected rows are then returned '.format(plans[i]["Group Key"])
                annotated += '\n'
            
            case 'Gather Merge':
                annotated += 'The Gather Merge operation is performed.' + '\n'
            
            case 'Sort':
                annotated += 'The Sort operation sorts the rows based on the key: {}'.format(plans[i]['Sort Key'])
                if "INC" in plans[i]["Sort Key"]:
                    annotated += 'in increasing order.'
                if "DESC" in plans[i]["Sort Key"]:
                    annotated += 'in decreasing order.'
                annotated += '\n'
           
            case 'CTE_Scan':
                annotated += 'The table is scanned using CTE Scan operation '
                if "Index Cond" in plans[i]:
                    annotated += 'with condition: [{}] '.format(plans[i]['Index Cond'])
                if "Filter" in plans[i]:
                    annotated += 'and filtered by [{}]'.format(plans[i]['Filter'])
                annotated += '\n'
            
            case 'Nested Loop':
                annotated += 'The Nested Loop operation is performed.' + '\n'
            
            case 'Limit':
                annotated += 'The Limit operation will limit the scanning, with a limitation of [{}] rows'.format(plans[i]['Plan Rows']) + '\n'
        i=i-1
    print(annotated)
    return annotated