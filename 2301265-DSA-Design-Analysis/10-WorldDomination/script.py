import glob
import heapq
import argparse
import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict

def read_test_case_from_file(filename):
    with open(filename, 'r') as file:
        # Read the first line for countries, roads, and living cost
        n, m, living_cost = map(int, file.readline().split())
        # Read the second line for people required per country
        people_needed = list(map(int, file.readline().split()))
        # Read all edges until the last line
        lines = file.readlines()
        edges = [tuple(map(int, line.split())) for line in lines[:-1]]
        print(edges)
        # Read the last line for the total number of people
        k = int(lines[-1].strip())
    return n, m, living_cost, people_needed, edges, k

def visualize_graph(n, edges, people_assignments, title="Graph Visualization"):
    G = nx.DiGraph()
    G.add_weighted_edges_from(edges)

    pos = nx.spring_layout(G)
    plt.figure(figsize=(10, 8))

    labels = {i: f'{i} ({people_assignments[i-1]})' for i in range(1, n + 1)}
    nx.draw(G, pos, labels=labels, with_labels=True, node_color='lightblue', edge_color='gray', node_size=3000, font_size=10)
    plt.title(title)
    plt.show()

def dijkstra(n, edges):
    graph = defaultdict(list)
    for u, v, w in edges:
        graph[u].append((w, v))

    distances = {i: float('inf') for i in range(1, n + 1)}
    distances[1] = 0
    min_heap = [(0, 1)]
    
    while min_heap:
        current_distance, u = heapq.heappop(min_heap)
        if current_distance > distances[u]:
            continue
        for weight, v in graph[u]:
            distance = current_distance + weight
            if distance < distances[v]:
                distances[v] = distance
                heapq.heappush(min_heap, (distance, v))
    return distances

def assign_people(n, m, living_cost, people_needed, edges, k, full_governance):
    distances = dijkstra(n, edges)
    sorted_countries = sorted(range(1, n + 1), key=lambda x: distances[x])
    results = []
    person_count = 0
    people_assignments = [0] * n

    for country in sorted_countries:
        if person_count >= k:
            break
        required_people = people_needed[country - 1]
        travel_cost = distances[country]

        if travel_cost == float('inf'):
            continue  # Skip unreachable countries
        
        # Full governance enforcement if required
        if full_governance and person_count + required_people > k:
            break  # Stop if not enough people for full governance
        
        # Partial or full governance based on flag
        for _ in range(required_people if person_count + required_people <= k else k - person_count):
            total_cost = travel_cost + living_cost
            results.append(total_cost)
            people_assignments[country - 1] += 1
            person_count += 1
            if person_count >= k:
                break

    # Fill remaining slots with -1 if fewer people are assigned than needed
    while len(results) < k:
        results.append(-1)
    
    return results, people_assignments

# Main Program
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Solve the World Domination Problem using Dijkstra\'s Algorithm")
    parser.add_argument('-f', '--full-governance', action='store_true', help="Enforce full governance requirements")
    parser.add_argument('-p', '--partial-governance', action='store_true', help="Allow partial governance of countries")
    parser.add_argument('-v', '--visualize', action='store_true', help="Enable visualization of the graph with assignments")

    args = parser.parse_args()
    
    # If no specific governance mode is selected, default to partial governance
    if not args.full_governance and not args.partial_governance:
        args.partial_governance = True

    # Process each .txt file
    for filename in glob.glob('*.txt'):
        print(f"\nProcessing file: {filename}")
        n, m, living_cost, people_needed, edges, k = read_test_case_from_file(filename)
        print(f"Countries: {n}, Roads: {m}, Living Cost: {living_cost}, Total People: {k}")
        print(f"People needed per country: {people_needed}")

        if args.partial_governance:
            results, people_assignments = assign_people(n, m, living_cost, people_needed, edges, k, False)
            print("==== PARTIAL GOVERNANCE ================")
            print("Assignment Costs:", results)
            print("People Assignments per Country:", people_assignments)
        
        if args.full_governance:
            results, people_assignments = assign_people(n, m, living_cost, people_needed, edges, k, True)
            print("==== FULL GOVERNANCE ===================")
            print("Assignment Costs:", results)
            print("People Assignments per Country:", people_assignments)
        
        if args.visualize:
            visualize_graph(n, edges, people_assignments, title=f"Graph for {filename}")
