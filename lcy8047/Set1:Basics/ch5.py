def encrypt(plain_text: str, key: bytes) -> bytes:
    res = ""
    s = bytes(plain_text, 'utf-8')
    for i, c in enumerate(s):
        res += padded_hex( c^key[i%3], 2 )[2:]
    return res

def padded_hex(n: int, padding_size: int) -> str:
    hex_string = "0x"
    if padding_size - len(hex(n)[2:]) > 0:
        hex_string += "0"*( padding_size-len(hex(n)[2:]) )
    return hex_string+hex(n)[2:]

key = b"ICE"
plain_text = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal"

print( encrypt(plain_text, key) )
print( "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f")