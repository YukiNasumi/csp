if __name__ == "__main__":
    n,m = map(int,input().split())
    essays = []
    words = {}
    for _ in range(n):
        article = input().split()[1:]
        essay = {}
        for word in article:
            if word in words:
                words[word]+=1
            else:
                words[word]=1
            essay[word]=1
        essays.append(essay)
    for i in range(1,m+1):
        name = str(i)
        cnt_arti = 0
        for essay in essays:
            if name in essay:
                cnt_arti+=1
        cnt_num = words[name]
        print(cnt_arti,cnt_num)