#include<bits/stdc++.h>
#define int long long
#define MAX_CLASS 2010
#define exist 1;
using namespace std;
typedef struct tree{
    int id;
    int w;
    struct tree *parent;
    vector<struct tree*>children;
    int flag;
    int children_w;
    tree(int a,int b){
        this->id = a;
        this->w = b;
        this->flag = exist;
        this->children_w = 0;
        this->parent = NULL;
    }
}tree;
int cal_children_w(tree* t){
    if(!t->flag) return 0;
    t->children_w = 0;
    for(vector<tree*>::iterator it=t->children.begin();it!=t->children.end();it++){
        tree* child_p = *it;
        if(!child_p->flag) continue;
        t->children_w += child_p->w+cal_children_w(child_p); 
    }
    return t->children_w;
}
tree *classes[MAX_CLASS];
int n,m;
list<pair<int,int>>get_w_delta(int sum){
    list<pair<int,int>>l;
    for(int i=1;i<=n;i++){
        tree* t = classes[i];
        if(!t->flag) continue;
        int w = t->children_w + t->w;
        int w_delta = llabs((sum-w)-w);
        l.push_back(make_pair(i,w_delta));
    }
    return l;
}
bool ischild(tree* father,int q){
    tree* child = classes[q];
    while(child){
        if(child->id == father->id) return true;
        child = child->parent;
    }
    return false;
}
void del1(tree* root,int except){
    //delete all the node except one
    if(root->id==except) return;
    root->flag = 0;
    for(vector<tree*>::iterator it=root->children.begin();it!=root->children.end();it++){
        tree* child = *it;
        if(!child->flag) continue;
        del1(child,except);
    }
}
void del2(tree* t){
    //del t node and all its children
    t->flag=0;
    for(vector<tree*>::iterator it = t->children.begin();it!=t->children.end();it++){
        tree* child = *it;
        if(!child->flag) continue;
        del2(child);
    }
}
void recover_tree(){
    for(int i=1;i<=n;i++) classes[i]->flag=exist;
}
signed main(signed argc,char* argv[]){
    /*freopen("../in.txt","r",stdin);*/
    cin >> n >> m;
    int sum=0;
    for(int i=1;i<=n;i++){
        int w;
        cin >> w;
        sum+=w;
        classes[i] = new tree(i,w);
    }
    for(int i=2;i<=n;i++){
        int father;
        cin >> father;
        tree* parent = classes[father];
        parent->children.push_back(classes[i]);
        classes[i]->parent = parent;
    }
    int copy = sum;
    for(int k=0;k<m;k++){
        int q;
        cin >> q;
        tree* root = classes[1];
        cal_children_w(root);
        list<pair<int,int>>l = get_w_delta(sum);
        while(l.size()!=1){
            pair<int,int> node = *min_element(l.begin(),l.end(),[](const pair<int,int>&a,const pair<int,int>&b){
                if(a.second==b.second) return a.first<b.first;
                return a.second<b.second;
            });
            int idx = node.first;//the minmum w delta
            cout << idx << " ";
            if(ischild(classes[idx],q)){
                del1(root,idx);
                root = classes[idx];
                sum = root->w + root->children_w;
            }
            else{
                del2(classes[idx]);
                sum-=(classes[idx]->w+classes[idx]->children_w);
                cal_children_w(root);
            }
            l = get_w_delta(sum);
        }
        cout << endl;
        recover_tree();
        sum = copy;
    }
    return 0;
}