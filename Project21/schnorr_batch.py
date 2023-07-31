import random
import time
import hashlib
import binascii


p = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
n = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
G = (0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798, 0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8)

sk1=0x0000000000000000000000000000000000000000000000000000000000000001
sk2=0x0000000000000000000000000000000000000000000000000000000000000001
sk3=0x0000000000000000000000000000000000000000000000000000000000000001

message1='0000000000000000000000000000000000000000000000000000000000000001'
message2='0000000000000000000000000000000000000000000000000000000000000001'
message3='0000000000000000000000000000000000000000000000000000000000000001'

R_list=[]
sig_list=[]
pubkey_list=[]
result=[]

def point_add(p1, p2):
    if (p1 is None):
        return p2
    if (p2 is None):
        return p1
    if (p1[0] == p2[0] and p1[1] != p2[1]):
        return None
    if (p1 == p2):
        lam = (3 * p1[0] * p1[0] * pow(2 * p1[1], p - 2, p)) % p
    else:
        lam = ((p2[1] - p1[1]) * pow(p2[0] - p1[0], p - 2, p)) % p
    x3 = (lam * lam - p1[0] - p2[0]) % p
    return (x3, (lam * (p1[0] - x3) - p1[1]) % p)

def point_mul(p, n):
    r = None
    for i in range(256):
        if ((n >> i) & 1):
            r = point_add(r, p)
        p = point_add(p, p)
    return r

def bytes_point(p):
    return (b'\x03' if p[1] & 1 else b'\x02') + p[0].to_bytes(32, byteorder="big")

def sha256(b):
    return int.from_bytes(hashlib.sha256(b).digest(), byteorder="big")

def on_curve(point):
    return (pow(point[1], 2, p) - pow(point[0], 3, p)) % p == 7

def jacobi(x):
    return pow(x, (p - 1) // 2, p)

def schnorr_sign(msg, seckey):
    k = sha256(seckey.to_bytes(32, byteorder="big") + msg)
    R=point_mul(G, k)
    if jacobi(R[1]) != 1:
        k = n - k
    e = sha256(R[0].to_bytes(32, byteorder="big") + bytes_point(point_mul(G, seckey)) + msg)
    s= k + e * seckey
    return R,s

def create_input(sk1,G,message1):
    return point_mul(G, sk1),bytearray.fromhex(message1)

pk1,message1=create_input(sk1,G,message1)
pk2,message2=create_input(sk2,G,message2)
pk3,message3=create_input(sk3,G,message3)

sk_list=[sk1,sk2,sk3]
msg_list=[message1,message2,message3]

for sk in sk_list:
    pubkey_list.append(point_mul(G, sk))

for i in range(0,len(msg_list)):
    result.append(schnorr_sign(msg_list[i], sk_list[i]))

for i in range(0,len(result)):
    R_list.append(result[i][0])

for i in range(0,len(result)):
    sig_list.append(result[i][1])

#下面进行签名验证对比

t1=time.time()

for i in range(len(msg_list)):
    if (not on_curve(pubkey_list[i])):print("第",i+1,"次签名验证结果为：",False)
    List1 = sha256(R_list[i][0].to_bytes(32, byteorder="big") + bytes_point(pubkey_list[i]) + msg_list[i])
    s1 = point_add(R_list[i], point_mul(pubkey_list[i], List1))
    s2 = point_mul(G, sig_list[i])
    if s1 == s2:print("第",i+1,"次签名验证结果为：",True)
    else:print("第",i+1,"次签名验证结果为：",False)

t2=time.time()
t3=t2-t1
print("总共判断所用时间为：",t3,"s")

#下面进行batch验证对比

t1=time.time()

sig=0
for i in sig_list:sig+=i
s1 = point_mul(G, sig)
pp1=None
List1=[]
for i in range(0,len(msg_list)):
    List1.append(sha256(R_list[i][0].to_bytes(32, byteorder="big") + bytes_point(pubkey_list[i]) + msg_list[i]))
for i in range(0,len(msg_list)):
    pp1=point_add(pp1, point_mul(pubkey_list[i], List1[i]))
pp2=None
for i in range(0, len(msg_list)):
    pp2=point_add(pp2, R_list[i])
s2=point_add(pp1, pp2)
if s1==s2:print("运行后得到batch验证结果为：",True)
else:print("运行后得到batch验证结果为：",False)

t2=time.time()
t4=t2-t1
print("batch验证所用的时间为：",t4,"s.")
print("由此可见，batch验证所用时间是前者的",'percent: {:.2%}'.format(t4/t3))