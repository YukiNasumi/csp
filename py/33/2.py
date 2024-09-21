if __name__ == "__main__":
    input()
    e1 = [s.lower() for s in input().split()]
    e2 = [s.lower() for s in input().split()]
    words={}
    s1={}
    s2={}
    for w in e1:
        s1[w]=1
    for w in e2:
        s2[w]=1
    for w in e1+e2:
        words[w]=1
    bing = len(words)
    jiao = len(s1)+len(s2)-bing
    print(jiao)
    print(bing)