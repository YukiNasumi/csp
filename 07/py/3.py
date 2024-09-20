P = int(input())
class node():
    def __init__(self,name=None):
        self.name = name
        self.children = []

def init_node(dir,nodes):
    nodes.name = dir[0]
    del dir[0]
    l = len(dir)
    if not l == 0:
        nodes.children.append(node())
        init_node(dir,nodes.children[-1])
    
root = node()
cd = input().split('/')#current dir
cd.insert(0,'/')
init_node(cd,root)
for _ in range(P):
    path = input
