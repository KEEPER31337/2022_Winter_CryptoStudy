s = 0x1c0111001f010100061a024b53535009181c
h = 0x686974207468652062756c6c277320657965

#h = "686974207468652062756c6c277320657965"

'''
b = bytearray.fromhex(h)
a = b.decode()
print(a)
'''
a = bytearray.fromhex( hex(s^h)[2:] )
print(a.decode())

#print(hex(s^h)[2:])