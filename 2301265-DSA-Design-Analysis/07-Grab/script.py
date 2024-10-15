import argparse
import glob
import os

# New function to print verbose output
def print_verbose_pairs(pairs):
    if pairs:
        print("Paired Grab and Passenger positions:")
        for G, P in pairs:
            print(f"Grab at {G} -> Passenger at {P}")
    else:
        print("No valid pairs found.")

# Greedy method with pair tracking
def greedy(arr, k, verbose=False):
    n = len(arr)
    Gi = [i for i in range(n) if arr[i] == 'G']  # all G indices
    Pi = [i for i in range(n) if arr[i] == 'P']  # all P indices

    G, P = 0, 0  # Pointers for P & G
    count = 0
    pairs = []  # To store the pairs of Grab and Passenger

    while G < len(Gi) and P < len(Pi):
        if abs(Gi[G] - Pi[P]) <= k:  # Check if the passenger is within range
            count += 1
            pairs.append((Gi[G], Pi[P]))  # Track the pair
            G += 1
            P += 1
        elif Gi[G] < Pi[P]:  # if G behind P
            G += 1
        else:  # if P behind G
            P += 1

    if verbose:
        print_verbose_pairs(pairs)

    return count

# Brute Force method with pair tracking
def bruteforce(arr, k, verbose=False):
    Find = ""
    count = 0
    pairs = []  # To store the pairs of Grab and Passenger

    for i in range(len(arr)):
        if arr[i] == "P":
            Find = "G"
        elif arr[i] == "G":
            Find = "P"
        else:
            continue

        for j in range(1, k+1):
            if i + j < len(arr):
                if Find == arr[i + j]:
                    arr[i + j] = "-"
                    arr[i] = "-"
                    count += 1
                    pairs.append((i, i + j))  # Track the pair
                    break

    if verbose:
        print_verbose_pairs(pairs)

    return count

# Function for manual entry
def run(verbose=False):
    t = 0
    print("-" * 10)
    print("1: Brute Force")
    print("2: Greedy")
    print("3: Both")
    print("0: Exit")
    print("-" * 10)
    while True:
        try:
            tt = int(input("Type: "))
            if tt == 0:
                break
            if tt > 3 or tt < 1:
                continue
            t = tt
            break
        except:
            continue

    if t != 0:
        l = list(input("Array: ").strip().upper())
        k = int(input("Range: "))

        if t == 1:
            print("Brute Force: ", bruteforce(l[:], k, verbose=verbose))
        if t == 2:
            print("Greedy: ", greedy(l[:], k, verbose=verbose))
        if t == 3:
            print("Greedy: ", greedy(l[:], k, verbose=verbose))
            print("Brute Force: ", bruteforce(l[:], k, verbose=verbose))

        if input("To continue type 1: ").strip() == "1":
            run(verbose)

# Reads the test case from a file
def read_test_case_from_file(filename):
    with open(filename, 'r') as file:
        arr = list(file.readline().strip())
        k = int(file.readline().strip())
    return arr, k

# Main Program
if __name__ == "__main__":
    # Set up command-line argument parsing
    parser = argparse.ArgumentParser(description="Solves the Grab and Passenger problem using Brute Force and Greedy methods")
    parser.add_argument('--method', choices=['bf', 'gd', 'both', 'manual'], default='manual', 
                        help="Specify the method: 'bf' for brute-force, 'gd' for greedy, 'both' for both or 'manual' for manual entry (default)")
    parser.add_argument('--verbose', action='store_true', help="Enable verbose output to show Grab and Passenger pairs")
    
    args = parser.parse_args()
    
    # Greedy Method
    if args.method in ['gd', 'both']:
        print("Greedy")
        for filename in glob.glob('*.txt'):
            arr, k = read_test_case_from_file(filename)
            count_greedy = greedy(arr[:], k, verbose=args.verbose)
            print(f"{os.path.splitext(filename)[0]}: {count_greedy}")
            #print() if args.verbose else None
    
    if args.method in ['both']:
        print()  # Prints newline
    
    # Brute-Force
    if args.method in ['bf', 'both']:
        print("Brute-Force")
        for filename in glob.glob('*.txt'):
            arr, k = read_test_case_from_file(filename)
            count_bf = bruteforce(arr[:], k, verbose=args.verbose)
            print(f"{os.path.splitext(filename)[0]}: {count_bf}")
            #print() if args.verbose else None

    # Manual Entry
    if args.method == 'manual':
        run(verbose=args.verbose)
