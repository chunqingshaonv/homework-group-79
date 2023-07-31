import time

iv = 0x7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e
MAX = 2 ** 32

def rotate_left(a, k):
    k = k % 32
    return ((a << k) & 0xFFFFFFFF) | ((a & 0xFFFFFFFF) >> (32 - k))

def p0(x):
    return x ^ rotate_left(x, 9) ^ rotate_left(x, 17)

def p1(x):
    return x ^ rotate_left(x, 15) ^ rotate_left(x, 23)

def t_j(j):
    if j <= 15:
        return 0x79cc4519
    else:
        return 0x7a879d8a

def ff(x, y, z, j):
    if j <= 15:
        return x ^ y ^ z
    else:
        return (x & y) | (x & z) | (y & z)

def gg(x, y, z, j):
    if j <= 15:
        return x ^ y ^ z
    else:
        return (x & y) | ((x ^ 0xFFFFFFFF) & z)

def StrToBin(msg):
    l = len(msg)
    s_dec = 0
    for m in msg:
        s_dec = s_dec << 8
        s_dec += ord(m)

    msg_bin = bin(s_dec)[2:].zfill(l * 8)
    return msg_bin

def IntToBin(a, k):
    return bin(a)[2:].zfill(k)

def IntToHex(a, k):
    return hex(a)[2:].zfill(k)

def BinToHex(a, k):
    return hex(int(a, 2))[2:].replace('L', '').zfill(k)

def padding(msg_bin):
    l = len(msg_bin)
    k = 448 - (l + 1) % 512
    if k < 0:
        k += 512
    l_bin = IntToBin(l, 64)
    msg_padding = msg_bin + '1' + '0' * k + l_bin
    return msg_padding

def cf(vi, bi):
    w, w1 = extension(bi)
    t = []
    for i in range(8):
        t.append(int(vi[i * 32:(i + 1) * 32], 2))
    a, b, c, d, e, f, g, h = t
    for j in range(64):
        ss1 = rotate_left((rotate_left(a, 12) + e + rotate_left(t_j(j), j)) % MAX, 7)
        ss2 = ss1 ^ rotate_left(a, 12)
        tt1 = (ff(a, b, c, j) + d + ss2 + w1[j]) % MAX
        tt2 = (gg(e, f, g, j) + h + ss1 + w[j]) % MAX
        d = c
        c = rotate_left(b, 9)
        b = a
        a = tt1
        h = g
        g = rotate_left(f, 19)
        f = e
        e = p0(tt2)
    vi_1 = IntToBin(a, 32) + IntToBin(b, 32) + IntToBin(c, 32) + IntToBin(d, 32) \
           + IntToBin(e, 32) + IntToBin(f, 32) + IntToBin(g, 32) + IntToBin(h, 32)
    vi_1 = int(vi_1, 2) ^ int(vi, 2)
    return IntToBin(vi_1, 256)

def iteration(msg):
    n = len(msg) // 512
    b = []
    for i in range(n):
        b.append(msg[512 * i:512 * (i + 1)])
    v = [IntToBin(iv, 256)]
    for i in range(n):
        v.append(cf(v[i], b[i]))

    return BinToHex(v[n], 64)

def extension(bi):
    w = []
    for j in range(16):
        w.append(int(bi[j * 32:(j + 1) * 32], 2))

    for j in range(16, 68):
        w_j = p1(w[j - 16] ^ w[j - 9] ^ rotate_left(w[j - 3], 15)) ^ rotate_left(w[j - 13], 7) ^ w[j - 6]
        w.append(w_j)

    w1 = []
    for j in range(64):
        w1.append(w[j] ^ w[j + 4])

    return w, w1

def sm3(msg):
    s_bin = StrToBin(msg)
    s_fill = padding(s_bin)
    s_sm3 = iteration(s_fill)
    return s_sm3.upper().replace("L", "")

s1 = 'sm4softwareimplementation'
t1=time.time()
s1_sm3 = sm3(s1)
t2=time.time()
t3=t2-t1

print("待加密的字符串为：{}\n加密后的字符串为：{}".format(s1, s1_sm3))
print("加密所用时间为：",t3*1000,"ms")

