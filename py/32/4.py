class matrix():
    def __init__(self,a,b,c,d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d
    def show(self):
        print()
        print(self.a%MOD,self.b%MOD,self.c%MOD,self.d%MOD)
def matmul(A,B):
    #global MOD
    """return matrix(A.a*B.a+A.b*B.c,
                A.a*B.b+A.b*B.d,
                A.c*B.a+A.d*B.c,
                A.c*B.b+A.d*B.d)"""
    return matrix((((A.a%MOD)*(B.a%MOD)%MOD)+((A.b%MOD)*(B.c%MOD)%MOD))%MOD, 
                    (((A.a%MOD)*(B.b%MOD)%MOD)+((A.b%MOD)*(B.d%MOD)%MOD))%MOD, 
                    (((A.c%MOD)*(B.a%MOD)%MOD)+((A.d%MOD)*(B.c%MOD)%MOD))%MOD, 
                    (((A.c%MOD)*(B.b%MOD)%MOD)+((A.d%MOD)*(B.d%MOD)%MOD))%MOD)
    
def main():
    global n,m,prompts,eyes
    for _ in range(n):
        prompts.append(input().split())
    for _ in range(m):
        issue = input().split()
        if issue[0] == '1':
            idx = int(issue[1])-1
            prompts[idx]=issue[2:]
        else:
            deque = [eyes]#deque<matrix>
            l,r = int(issue[1]),int(issue[2])
            for p in prompts[l-1:r]:
                if p[0]=='1':
                    elm = [int(c) for c in p[1:]]
                    deque.insert(0,matrix(*elm))
                    deque.append(eyes)
                elif p[0]=='2':
                    elm = [int(c) for c in p[1:]]
                    deque.insert(0,eyes)
                    deque.append(matrix(*elm))
                else:
                    if(len(deque)==1):
                        continue
                    del deque[0], deque[-1]
            ans = eyes

            for mat in deque:
                ans = matmul(ans,mat)
            print(ans.a%MOD,ans.b%MOD,ans.c%MOD,ans.d%MOD)
            
    pass

if __name__ == "__main__":
    MOD = 998244353
    eyes = matrix(1,0,0,1)
    n,m = map(int,input().split())#[int(x) for x in input().split()]
    prompts = []#list(str)
    main()