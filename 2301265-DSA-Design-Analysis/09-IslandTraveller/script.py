import glob
import argparse
import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict

# Kosaraju's Algorithm Implementation
def kosaraju(n, edges):
    graph = defaultdict(list)
    transpose_graph = defaultdict(list)
    for u, v in edges:
        graph[u].append(v)
        transpose_graph[v].append(u)

    def dfs(vertex, visited, stack):
        visited[vertex] = True
        for neighbor in graph[vertex]:
            if not visited[neighbor]:
                dfs(neighbor, visited, stack)
        stack.append(vertex)

    def dfs_transpose(vertex, visited):
        visited[vertex] = True
        size = 1
        for neighbor in transpose_graph[vertex]:
            if not visited[neighbor]:
                size += dfs_transpose(neighbor, visited)
        return size

    visited = [False] * (n + 1)
    stack = []
    for i in range(1, n + 1):
        if not visited[i]:
            dfs(i, visited, stack)

    visited = [False] * (n + 1)
    max_island_count = 0
    while stack:
        node = stack.pop()
        if not visited[node]:
            scc_size = dfs_transpose(node, visited)
            max_island_count = max(max_island_count, scc_size)

    return max_island_count

# Tarjan's Algorithm Implementation
def tarjan(n, edges):
    from collections import defaultdict

    graph = defaultdict(list)
    for u, v in edges:
        graph[u].append(v)

    index = 0
    stack = []
    indices = [-1] * (n + 1)
    low_link = [-1] * (n + 1)
    on_stack = [False] * (n + 1)
    max_island_count = 0

    def strong_connect(v):
        nonlocal index, max_island_count
        indices[v] = low_link[v] = index
        index += 1
        stack.append(v)
        on_stack[v] = True
        current_scc_size = 0

        #print(f"Visiting node {v}: indices={indices}, low_link={low_link}, stack={stack}")

        for w in graph[v]:
            if indices[w] == -1:  # Node w has not been visited yet
                strong_connect(w)
                low_link[v] = min(low_link[v], low_link[w])
            elif on_stack[w]:  # Check if w is in the current SCC
                low_link[v] = min(low_link[v], indices[w])

        # If v is a root node, pop the stack and generate an SCC
        if low_link[v] == indices[v]:
            #print(f"Found SCC with root {v}")
            while True:
                w = stack.pop()
                on_stack[w] = False
                current_scc_size += 1
                if w == v:
                    break
            max_island_count = max(max_island_count, current_scc_size)
            #print(f"SCC size: {current_scc_size}")

    for i in range(1, n + 1):
        if indices[i] == -1:
            strong_connect(i)

    return max_island_count

# Visualization function using networkx and matplotlib
def visualize_graph(n, edges, title="Graph Visualization"):
    G = nx.DiGraph()
    G.add_edges_from(edges)

    pos = nx.spring_layout(G)
    plt.figure(figsize=(10, 8))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray', node_size=3000, font_size=15)
    plt.title(title)
    plt.show()

# Function to read test case data from a file
def read_test_case_from_file(filename):
    with open(filename, 'r') as file:
        n, m = map(int, file.readline().split())
        edges = [tuple(map(int, line.split())) for line in file]
    return n, m, edges

# Main Program
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Solve the Island Problem using graph algorithms")
    parser.add_argument('-k', '--kosaraju', action='store_true', help="Run Kosaraju's algorithm")
    parser.add_argument('-t', '--tarjan', action='store_true', help="Run Tarjan's algorithm")
    parser.add_argument('-v', '--visualize', action='store_true', help="Enable visualization of the graph")

    args = parser.parse_args()
    
    # If no specific algorithm is selected, default to running both
    if not args.kosaraju and not args.tarjan:
        args.kosaraju = True
        args.tarjan = True

    # Process each .txt file
    for filename in glob.glob('*.txt'):
        print(f"\nProcessing file: {filename}")
        n, m, edges = read_test_case_from_file(filename)
        print(f"Number of islands: {n}, Number of roads: {m}")

        if args.visualize:
            visualize_graph(n, edges, title=f"Graph for {filename}")

        if args.kosaraju:
            result_kosaraju = kosaraju(n, edges)
            print("Kosaraju's algorithm result:", result_kosaraju)

        if args.tarjan:
            result_tarjan = tarjan(n, edges)
            print("Tarjan's algorithm result:", result_tarjan)

        # Ensure consistency if both algorithms are run
        if args.kosaraju and args.tarjan:
            if result_kosaraju == result_tarjan:
                print("Both algorithms produced the same result.")
            else:
                print("WARNING: Results differ between the algorithms!")
