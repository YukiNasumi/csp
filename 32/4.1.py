n , m = map(int,input().split())
arr = [[i for i  in map(int,input().split())] for j in range(n)]
def mul_1(a,b):
    return [(a[0]*b[0]+a[1]*b[2])%998244353,(a[0]*b[1]+a[1]*b[3])%998244353,
            (a[2]*b[0]+a[3]*b[2])%998244353,(a[2]*b[1]+a[3]*b[3])%998244353]
for i in range(m):
    que = []
    a = list(map(int,input().split()))
    v = a[0]
    if v == 1:
        arr[a[1]-1].clear()
        for j in range(2,len(a)):
            arr[a[1]-1].append(a[j])
        continue
    if v == 2:
        pos_in = 0
        l , r = a[1],a[2]
        for j in range(l-1,r):
            v1 = arr[j][0]
            if v1 == 1:
                pos_in += 1
                que.insert(0, [arr[j][1], arr[j][2], arr[j][3], arr[j][4],pos_in])
                continue
            if v1 == 2:
                pos_in += 1
                x = len(que)
                que.insert(x, [arr[j][1], arr[j][2], arr[j][3], arr[j][4],pos_in])
                continue
            if v1 == 3:
                if len(que) != 0:
                    for v in range(len(que)):
                        if que[v][4] == pos_in:
                            que.pop(v)
                            pos_in -=1
                            break
    x = len(que)
    if x == 0:
        print(f"1 0 0 1")
    else:
        mid = que[0][0:4]
        for i in range(1, x):
            mid = mul_1(mid, que[i])
        print(*mid)