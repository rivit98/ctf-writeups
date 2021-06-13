from binascii import unhexlify

enc = list(map(lambda x: int(x, 16),
               'B6A46EE913B33E19 BCA67BD510B43632 A4B56AFE13AC1A1E BDAA7FE602E4775E EDF63AB850E67010'.split(" ")))
key = 0xD4C70F8A67D5456D

recovered = [unhexlify(hex(e ^ key)[2:]).decode() for e in enc]

print(''.join(recovered))
