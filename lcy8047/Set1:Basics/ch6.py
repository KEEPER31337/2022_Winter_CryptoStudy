import base64

def xor_encrypt(plain_text: bytes, key: bytes) -> bytes:
    res = ""
    for i, c in enumerate(plain_text):
        res += padded_hex( c^key[i%len(key)], 2 )[2:]
    return res

def is_ascii(s: bytes) -> bool:
    for c in s:
        if not ( 0x20 <= c and c <= ord('z') or c == 0xa ):
            return False
    return True

def calc_frequency(s: bytes) -> int:
    f1 = {"A": 8.2, "B": 1.5, "C": 2.8, "D": 4.3, "E": 13, "F": 2.2, "G": 2, "H": 6.1, "I": 7, "J": 0.15, "K": 0.77, "L": 4, "M": 2.5, "N": 6.7, "O": 7.5, "P": 1.9, "Q": 0.095, "R": 6, "S": 6.3, "T": 9.1, "U": 2.8, "V": 0.98, "W": 2.4, "X": 0.15, "Y": 2, "Z": 0.074}
    res = 0
    for c in s:
        try:
            if( 0x20 <= c and c <= ord('z') or c == 0xa ):
                res += 1
            idx = chr(c).upper()
            res += f1[idx]
        except:
            continue
    
    return res

def padded_hex(n: int, padding_size: int) -> str:
    hex_string = "0x"
    if padding_size - len(hex(n)[2:]) > 0:
        hex_string += "0" * ( padding_size-len(hex(n)[2:]) )
    return hex_string+hex(n)[2:]

f = open("./6.txt", "r")
text = ""
while True:
    line = f.readline().strip()
    if not line: break
    text += line

f.close()

b = base64.b64decode(text)

key = b""
key_size = 0
score = 0
highest_score_str = ""
for ks in range(2, 41):
    b_hex = ""
    for i,c in enumerate(b):
        if i%ks == 0:
            b_hex += padded_hex(c,2)[2:]
    b_text = bytes(bytearray.fromhex(b_hex))

    for j in range(0x100):
        res = ""
        for i,c in enumerate(b_text):
            res += padded_hex((c^j), 2)[2:]
        res = bytes(bytearray.fromhex(res))
        
        cur_score = calc_frequency(res)
        
        if cur_score > score and is_ascii(res):
            score = cur_score
            highest_score_str = res
            key_size = ks
            key = bytes( chr(j), "ascii" ) 

for key_offset in range(1,key_size):
    key_score = 0
    key_highest_score_str = ""
    key += b"A"
    b_hex = ""
    for i,c in enumerate(b):
        if i%key_size == key_offset:
            b_hex += padded_hex(c,2)[2:]
    b_text = bytes(bytearray.fromhex(b_hex))

    for j in range(0x100):
        res = ""
        for i,c in enumerate(b_text):
            res += padded_hex((c^j), 2)[2:]
        res = bytes(bytearray.fromhex(res))
        
        cur_score = calc_frequency(res)

        if cur_score > key_score and is_ascii(res):
            key_score = cur_score
            key_highest_score_str = res
            key = key[0:key_offset]+bytes( chr(j), "ascii" )

print("key :", key)
a = xor_encrypt(b, key)
print("result :\n",bytes(bytearray.fromhex(a)))
