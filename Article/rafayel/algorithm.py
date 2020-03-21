import json

vital_items = [
    7, 111, 191, 237, 82, 303, 42, 85, 297, 163
]

won_times = 0

for i in range(5000):
    tree_file = open('tree.json', 'r')
    tree = json.loads(tree_file.read())
    tree_file.close()
    path = [1]
    path_indices = []
    running = True

    current_node = 1

    def do_game_over_stuff():
        for i in range(len(path)):
            try:
                tree[str(path[i])]['connections'][path_indices[i]]["score"] *= 1 - (((1/2)/len(path)) * (i+1))
            except IndexError:
                pass

        tree_file = open('tree.json', 'w')
        tree_file.write(json.dumps(tree))


    def do_game_won_stuff():
        for i in range(len(path)):
            try:
                tree[str(path[i])]['connections'][path_indices[i]]["score"] *= 1 + (((1/2)/len(path)) * (i+1))
            except IndexError:
                pass

        tree_file = open('tree.json', 'w')
        tree_file.write(json.dumps(tree))


    while running:
        # print("Current node:", current_node)
        node = tree[str(current_node)]

        if 'GameOver' in node["connections"]:
            do_game_over_stuff()
            running = False
            continue

        if 'GameWon' in node["connections"]:
            for item in vital_items:
                if item not in path:
                    do_game_over_stuff()
                    running = False
                    continue
                    
            do_game_won_stuff()
            print("Won!")
            won_times += 1
            running = False
            continue


        best_option = 0
        best_score = 0
        for option in node["connections"]:
            if option["score"] > best_score:
                best_option = node["connections"].index(option)
                best_score = option["score"]

        current_node = int(node["connections"][best_option]["to"])

        path_indices.append(best_option)
        path.append(current_node)

    # print("Final path => {}".format(path))

print("Won {} times".format(won_times))