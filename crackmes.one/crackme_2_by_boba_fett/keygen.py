from z3 import *

s = Solver()


def Left(s, howMany):
    return s[:howMany]


def Right(s, howMany):
    if howMany == 0:
        return ""
    return s[-howMany:]


name = "Rivit"
serial = Int('x')
serial_found = None

var_19C = name
i = 0
var_1FC = 0
while var_19C:
    i += 1
    var_1FC += ord(Left(Left(var_19C, i), 1))
    var_19C = Right(var_19C, len(name) - i)

var_98 = 112
var_A8 = 1564
var_B8 = 1464
var_168 = 11

var_108 = (((var_98 * var_A8) ^ var_B8) - 10)
var_128 = (var_108 * var_1FC)
var_148 = serial * var_108

s.add(var_148 != serial)
s.add(var_148 >= var_128)
s.add((var_148 + var_168) <= (var_128 + 11))

while s.check() == sat:
    m = s.model()
    print(f"Name: {name} - serial: {m[serial].as_long()}")
    serial_found = m[serial].as_long()
    s.add(serial != m[serial])

# s.reset()
#
# input_field = Int('y')
#
# var_98 = 144
# var_A8 = 135
# var_B8 = 1234
# var_F8 = (var_B8 % (var_98 ^ var_A8)) + input_field * 100
# print(var_F8)
#
# # var_168 = int(str(serial_found)[1])
# var_168 = int(Left(str(serial_found), 3))
# var_128 = input_field * var_168
# print(var_128)
# var_178 = (var_F8 * var_168) - 18
#
# s.add(var_128 == var_178)
#
# print(s)
# while s.check() == sat:
#     m = s.model()
#     print(f"Input: {m[input_field].as_long()}")
#     serial_found = m[input_field].as_long()
#     s.add(input_field != m[input_field])
# else:
#     print("Not found")

