import re
import json

g_file = open('graph.gv', 'r')

story_tree = {}

for line in g_file:
    params = line.strip()

    if re.search(r'([0-9]{1,3})\[label="([0-9]{1,3})" shape=([a-z])* color=([a-z])*\];', params):
        node_nr = re.findall(r'[0-9]{1,3}', params)[0]
        node_color = re.findall(r'color=([a-z]{3,5})', params)[0]

        # f = True
        # for room in story_tree:
        #     if room["id"] == node_nr:
        #         f = False
        
        # if f:
        story_tree[node_nr] = {
            "id": node_nr,
            "type": node_color,
            "connections": []
        }

        print("Node details: {}; {}".format(node_nr, node_color))
    
    if re.search(r'([0-9]{1,3})->([0-9]{1,3}) \[ label="([a-zA-Z])*"\];', params) or re.search(r'([0-9]{1,3})->([0-9]{1,3});', params):
        node_nr = re.findall(r'[0-9]{1,3}', params)

        if node_nr[0] in story_tree:
            story_tree[node_nr[0]]["connections"].append(node_nr[1])

        print("Connection: from {} to {}".format(node_nr[0], node_nr[1]))

    if re.search(r'([0-9]{1,3})-> GameOver;', params):
        node_nr = re.findall(r'[0-9]{1,3}', params)[0]

        if node_nr in story_tree:
            story_tree[node_nr[0]]["connections"].append("GameOver")

        print("GameOver: from {}".format(node_nr))

with open('tree.json', 'w+') as tree_file:
    tree_file.write(json.dumps(story_tree))
