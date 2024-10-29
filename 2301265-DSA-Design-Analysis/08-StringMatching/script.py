import argparse
import glob

# Visualize Grid and Matched Patterns
def visualize_grid(grid, matches):
    print("Grid visualization with matches:")
    for i, row in enumerate(grid):
        visual_row = ""
        for j, cell in enumerate(row):
            if (i, j) in matches:
                visual_row += f"[{cell}]"
            else:
                visual_row += f" {cell} "
        print(visual_row)

# Compute KMP Prefix Array
def compute_prefix_array(pattern):
    m = len(pattern)
    pi = [0] * m
    j = 0  # length of previous longest prefix suffix
    for i in range(1, m):
        while j > 0 and pattern[i] != pattern[j]:
            j = pi[j - 1]
        if pattern[i] == pattern[j]:
            j += 1
            pi[i] = j
    return pi

# KMP Search Function
def kmp_search(text, pattern, pi):
    n = len(text)
    m = len(pattern)
    positions = []
    j = 0  # index for pattern[]
    for i in range(n):
        while j > 0 and text[i] != pattern[j]:
            j = pi[j - 1]
        if text[i] == pattern[j]:
            j += 1
        if j == m:  # Found a match
            positions.append(i - m + 1)  # Store the starting index of the match
            j = pi[j - 1]
    return positions

# Find pattern in 2D grid using KMP in four directions
def find_pattern_in_grid(grid, pattern):
    pi = compute_prefix_array(pattern)
    n = len(grid)
    m = len(grid[0])
    results = []
    matches = []

    # Search left-to-right (LR) and right-to-left (RL)
    for i in range(n):
        row = grid[i]

        # Left-to-right (LR)
        lr_matches = kmp_search(row, pattern, pi)
        #print(f"LR matches found at row {i}: {lr_matches}")
        for start in lr_matches:
            results.append((i + 1, start + 1, 'LR'))
            matches.append((i, start))
        
        # Right-to-left (RL)
        #reversed_pattern = pattern[::-1]
        rl_matches = kmp_search(row[::-1], pattern, pi)
        #print(f"RL matches found at row {i}: {rl_matches}")
        for start in rl_matches:
            adjusted_start = m - start
            results.append((i + 1, adjusted_start, 'RL'))
            matches.append((i, adjusted_start - 1))

    # Search top-to-bottom (UB) and bottom-to-top (BU)
    for j in range(m):
        column = [grid[i][j] for i in range(n)]
        
        # Top-to-bottom (UB)
        ub_matches = kmp_search(column, pattern, pi)
        #print(f"UB matches found at column {j}: {ub_matches}")
        for start in ub_matches:
            results.append((start + 1, j + 1, 'UB'))
            matches.append((start, j))
        
        # Bottom-to-top (BU)
        #reversed_pattern = pattern[::-1]
        bu_matches = kmp_search(column[::-1], pattern, pi)
        #print(f"BU matches found at column {j}: {bu_matches}")
        for start in bu_matches:
            adjusted_start = n - start
            results.append((adjusted_start, j + 1, 'BU'))
            matches.append((adjusted_start - 1, j))

    return pi, results, matches

# Parse the test case from file
def read_test_case_from_file(filename):
    with open(filename, 'r') as file:
        charset = file.readline().strip()
        n, m, pattern_length = map(int, file.readline().split())
        grid = [file.readline().strip().split() for _ in range(n)]
        pattern = file.readline().strip().split()  # Split pattern by spaces
    return charset, n, m, pattern, grid

# Main Program
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Solve 2D string matching using KMP")
    parser.add_argument('-v', '--visualize', action='store_true', help="Enable visualization of matches in the grid")
    
    args = parser.parse_args()

    # Process each .txt file
    for filename in glob.glob('*.txt'):
        print(f"\nProcessing file: {filename}")
        charset, n, m, pattern, grid = read_test_case_from_file(filename)
        print(f"Charset: {charset}, Grid size: {n}x{m}, Pattern: '{' '.join(pattern)}'")

        # Finding pattern and getting results
        pi, results, matches = find_pattern_in_grid(grid, pattern)
        
        # Displaying results
        print("Prefix array:", pi)
        print("Matches found:")
        for result in results:
            print(f"Position: ({result[0]}, {result[1]}) Direction: {result[2]}")

        # Visualizing matches in the grid
        if args.visualize:
            visualize_grid(grid, matches)
