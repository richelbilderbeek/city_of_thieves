import re

g_file = open('graph.gv', 'r')

for line in g_file:
    params = g_file.readline().strip()

    if re.search('([0-9]{1,3})\[label="([0-9]{1,3})" shape=([a-z])* color=([a-z])*\];', params):
        node_nr = re.findall('[0-9]{1,3}', params)[0]
        node_color = re.findall('color=([a-z]{3,5})', params)[0]
        print("Node details: {}; {}".format(node_nr, node_color))
    
    if re.search('([0-9]{1,3})->([0-9]{1,3}) \[ label="([a-zA-Z])*"\];', params):
        node_nr = re.findall('[0-9]{1,3}', params)
        print("Connection: from {} to {}".format(node_nr[0], node_nr[1]))
