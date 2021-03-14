def ascii_sum(s):
    return sum([ord(c) for c in s])


name = "Rivit"  # put your name here
serial = ascii_sum(name)
print(f"Name: {name} - serial: {serial}")
