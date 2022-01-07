import base64
import struct


s = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
n = bytearray.fromhex(s)
print(n.decode())
p = b"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

v = bytes(n)

res = base64.b64encode(v)

print(res)