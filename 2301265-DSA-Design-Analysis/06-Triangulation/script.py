import math
import glob
import argparse
import os

# Calculates the distance between two points
def distance(p1, p2):
    return math.sqrt((p2[0] - p1[0]) ** 2 + (p2[1] - p1[1]) ** 2)

# Calculates the perimeter of a triangle formed by points i, j, k
def perimeter(polygon, i, j, k):
    return distance(polygon[i], polygon[j]) + distance(polygon[j], polygon[k]) + distance(polygon[k], polygon[i])

# [BRUTE-FORCE] Calculates the minimum triangulation cost
# Time Complexity: O(n!)
def triangulate_bf(polygon):
    n = len(polygon)

    # Recursive triangulation
    def triangulate(i, j):
        if j - i < 2:
            return 0  # No triangle can be formed

        min_cost = float('inf')

        # Try every possible third vertex between i and j
        for k in range(i + 1, j):
            cost = triangulate(i, k) + triangulate(k, j) + perimeter(polygon, i, k, j)
            min_cost = min(min_cost, cost)

        return min_cost

    # Calls recursive triangulation function
    return triangulate(0, n - 1)

# [DYNAMIC-PROGRAMMING] Calculates the minimum triangulation cost
# Time Complexity: O(n^3)
def triangulate_dp(polygon):
    n = len(polygon)
    
    if n < 3:
        return 0  # No triangulation needed if less than 3 points

    # dp[i][j] will store the minimum triangulation cost for polygon points between i and j
    dp = [[0 for _ in range(n)] for _ in range(n)]

    # Fill the table in a bottom-up manner
    for gap in range(2, n):  # gap is the length of the subproblem we're solving
        for i in range(n - gap):
            j = i + gap
            dp[i][j] = float('inf')

            # Try all points k between i and j as the middle point of the triangulation
            for k in range(i + 1, j):
                cost = dp[i][k] + dp[k][j] + perimeter(polygon, i, k, j)
                dp[i][j] = min(dp[i][j], cost)

    # The result is the minimum triangulation cost for the entire polygon
    return dp[0][n - 1]

# Reads polygon coordinates from a file
def read_polygon_from_file(filename):
    with open(filename, 'r') as file:
        n = int(file.readline().strip())
        polygon = []
        for _ in range(n):
            x, y = map(int, file.readline().strip().split())
            polygon.append((x, y))
    return polygon

# Main Program (loops over all .txt files in the current directory)
if __name__ == "__main__":
    # Set up command-line argument parsing
    parser = argparse.ArgumentParser(description="Calculates the minimum triangulation cost for convex polygons")
    parser.add_argument('--method', choices=['bf', 'dp', 'both'], default='both', 
                        help="specify the method: 'bf' for brute-force, 'dp' for dynamic-programming, or 'both' (default)")
    
    args = parser.parse_args()

    # Brute-Force
    if args.method in ['bf', 'both']:
        print("Brute-Force")
        for filename in glob.glob('*.txt'):
            cost_bf = triangulate_bf(read_polygon_from_file(filename))
            print(f"{os.path.splitext(filename)[0]}: {cost_bf:.4f}")

    if args.method in ['both']:
        print()  # Prints newline

    # Dynamic-Programming
    if args.method in ['dp', 'both']:
        print("Dynamic-Programming")
        for filename in glob.glob('*.txt'):
            cost_dp = triangulate_dp(read_polygon_from_file(filename))
            print(f"{os.path.splitext(filename)[0]}: {cost_dp:.4f}")
