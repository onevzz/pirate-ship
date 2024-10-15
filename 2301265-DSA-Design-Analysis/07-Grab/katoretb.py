def greedy(arr, k):
    n = len(arr)
    Gi = [i for i in range(n) if arr[i] == 'G']  # all G indices
    Pi = [i for i in range(n) if arr[i] == 'P']  # all P indices

    G, P = 0, 0  # Pointers for P & G
    count = 0

    while G < len(Gi) and P < len(Pi):
        if abs(Gi[G] - Pi[P]) <= k:  # Check if the passenger is within range
            count += 1
            G += 1
            P += 1
        elif Gi[G] < Pi[P]:  # if G behind P
            G += 1
        else:  # if P behind G
            P += 1

    return count

def bruteforce(arr, k):
    Find = ""
    count = 0
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
                    break
    return count


def run():
    t = 0
    print("-"*10)
    print("1: Brute force")
    print("2: Greedy")
    print("3: Both")
    print("0: Exit")
    print("-"*10)
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

        if(t == 1):
            print("Brute force: ", bruteforce(l, k))
        if(t == 2):
            print("Greedy: ", greedy(l, k))
        if(t == 3):
            print("Greedy: ", greedy(l, k))
            print("Brute force: ", bruteforce(l, k))
        if input("Continue press type 1: ").strip() == "1":
            run()

run()