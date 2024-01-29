def is_SS(uid):
    if uid[0]=="S" and uid[1]=="S":
        return True
    else:
        return False

def sum_of_digits(uid):
    return int(uid[2]) + int(uid[3]) + int(uid[4]) + int(uid[5])

def total_SS(filename):
    hell = []
    file = open(filename, "r")
    pain = file.readlines()
    for i in pain:
        blood = i.strip()
        if is_SS(blood):
            hell.append(sum_of_digits(blood))
    file.close()
    return hell

total_SS("number.txt")