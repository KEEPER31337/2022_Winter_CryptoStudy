def calc_frequency(s: bytes) -> int:
    f1 = {"A": 8.2, "B": 1.5, "C": 2.8, "D": 4.3, "E": 13, "F": 2.2, "G": 2, "H": 6.1, "I": 7, "J": 0.15, "K": 0.77, "L": 4, "M": 2.5, "N": 6.7, "O": 7.5, "P": 1.9, "Q": 0.095, "R": 6, "S": 6.3, "T": 9.1, "U": 2.8, "V": 0.98, "W": 2.4, "X": 0.15, "Y": 2, "Z": 0.074}
    f2 = {"A": 7.8,"B": 2,"C": 4,"D": 3.8,"E": 11,"F": 1.4,"G": 3,"H": 2.3,"I": 8.2,"J": 0.21,"K": 2.5,"L": 5.3,"M": 2.7,"N": 7.2,"O": 6.1,"P": 2.8,"Q": 0.24,"R": 7.3,"S": 8.7,"T": 6.7,"U": 3.3,"V": 1,"W": 0.91,"X": 0.27,"Y": 1.6,"Z": 0.44}
    f3 = {"A" : 1, "B" : 1, "C" : 1, "D" : 1, "E" : 1, "F" : 1, "G" : 1, "H" : 1, "I" : 1, "J" : 1, "K" : 1, "L" : 1, "M" : 1, "N" : 1, "O" : 1, "P" : 1, "Q" : 1, "R" : 1, "S" : 1, "T" : 1, "U" : 1, "V" : 1, "W" : 1, "X" : 1, "Y" : 1, "Z" : 1} 
    res = 0
    for c in s:
        try:
            if( 0x20 <= c and c <= 0x7e ):
                res += 1
            idx = chr(c).upper()
            res += f1[idx]
        except:
            continue
    
    return res

def padded_hex(n: int, padding_size: int) -> str:
    hex_string = "0x"
    if padding_size - len(hex(n)[2:]) > 0:
        hex_string += "0"*( padding_size-len(hex(n)[2:]) )
    return hex_string+hex(n)[2:]

input_file = open("./file", 'r')

score = 0
highest_score_str = ""
while True:
    b = input_file.readline()
    if not b: break
    s = bytes(bytearray.fromhex(b))
    
    for j in range(0xff):
        res = ""
        for i,c in enumerate(s):
            #print(i, c^j, padded_hex(c^j,2))
            res += padded_hex(c^j, 2)[2:]
        res = bytes(bytearray.fromhex(res))
        cur_score = calc_frequency(res)
        if cur_score > score:
            score = cur_score
            highest_score_str = res

print(highest_score_str, score, "len =", len(highest_score_str))

input_file.close()
