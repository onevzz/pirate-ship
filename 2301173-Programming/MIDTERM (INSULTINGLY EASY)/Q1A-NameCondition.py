def total_length(fname,lname):
    return len(fname) + len(lname)

def username(fname,lname):
    hell = total_length(fname,lname)
    if hell > 10:
        return fname[0] + lname[0] + lname[1]
    elif hell > 5:
        return fname
    else:
        return lname