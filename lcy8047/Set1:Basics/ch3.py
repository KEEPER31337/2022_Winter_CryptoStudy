p = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
b = bytearray.fromhex(p)
s = b.decode()

for j in range(0xff):
    res = ""
    try:
        for i,c in enumerate(s):
            res += hex((ord(c)^j))[2:]
        b = bytearray.fromhex(res)
        res = b.decode()
    except:
        continue
    print(res)

'''
Cooking MC's like a pound of bacon
'''
    

