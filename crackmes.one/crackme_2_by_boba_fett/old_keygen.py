def serial1_calc(s):
    return sum([ord(c) for c in s])

name = "Rivit"
serial1 = serial1_calc(name)

var_168 = int(str(serial1)[:3])
if name.isnumeric():
    var_F8 = 15 + int(name) * 100
else:
    var_F8 = 15

serial2 = ((var_F8 * var_168) - 18) / var_168

print(f"Name: {name} Serial1: {serial1} Serial2: {serial2}")

