#include<bits/stdc++.h>
#define int long long
#define MAX_CLASS 2000
using namespace std;
typedef struct tree{
    int id;
    int w;
    struct tree *lchild, *rchild,*parent;
    tree(int a,int b){
        this->id = a;
        this->w = b;
        this->lchild = NULL;
        this->rchild = NULL;
    }
}tree;
tree *classes[MAX_CLASS];
int n,m;
signed main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int w;
        cin >> w;
        tree t(i,w);
        classes[i] = &t;
    }
    for(int i=2;i<=n;i++){
        int father;
        cin >> father;
        tree* parent = classes[father];
        if(!parent->lchild) parent->lchild = classes[i];
        else parent->rchild = classes[i];
        classes[i]->parent = parent;
    }
}