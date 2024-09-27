#define MOD 1000000007
#include<bits/stdc++.h>
using namespace std;
#define oper -1
#define cst -2
typedef int ID;
map<ID,long long>Valuetable;
set<string>ops={"+","-","*"};
struct tree{
    string x;
    ID id;
    tree *lchild,*rchild;
    bool cal;
    long long val;
    tree(string s):x(s){
        if(ops.count(x)){
            id=oper;
        }
        else if(isdigit(x[0])||x[0]=='-'){
            id=cst;
        }
        else{
            id = stoi(x.substr(1,x.length()-1));
        }
        lchild=NULL;
        rchild=NULL;
        cal=false;
    }
    void reset();
    ~tree(){}
    long long value();
    long long grad(ID id);
};
void tree::reset(){
    this->cal=false;
    if(this->lchild){
        this->lchild->reset();
        this->rchild->reset();
    }
    return;
}
long long tree::value(){
    if(this->id!=oper){
        if(!this->cal){
        if(this->id==cst){
            this->val = stoi(this->x);
        }
        else this->val = Valuetable[this->id];
        this->cal=true;
        }
        return this->val;
    }
    if(this->cal) return this->val;
    this->cal=true;
    if(this->x=="+") {this->val = this->lchild->value()+this->rchild->value();}
    else if(this->x=="-") {this->val = this->lchild->value()-this->rchild->value();}
    else this->val = this->lchild->value()*this->rchild->value();
    return this->val;
}
long long tree::grad(ID id){
    if(this->id!=oper){
        if(this->id==cst||this->id!=id) return 0;
        else return 1;
    }
    if(this->x == "+") return this->lchild->grad(id)+this->rchild->grad(id);
    else if(this->x == "-") return this->lchild->grad(id)-this->rchild->grad(id);
    else return this->lchild->grad(id)*this->rchild->value()+this->lchild->value()*this->rchild->grad(id);
}

int n,m;
stack<tree*>eq;
signed main(){
    cin >> n>> m;
    do{
        string elm;
        cin >> elm;
        tree* node = new tree(elm);
        if(ops.count(elm)){
            tree* rchild = eq.top();
            eq.pop();
            tree* lchild = eq.top();
            eq.pop();
            node->lchild = lchild;
            node->rchild = rchild;
            eq.push(node);
        }
        else eq.push(node);
    }
    while(cin.get()==' ');
    tree* root = eq.top();
    for(int k=0;k<m;k++){
        ID id;
        cin >> id;
        for(int i=1;i<=n;i++){
            int v;
            cin >> v;
            Valuetable[i]=v;
        }
        long long ans = root->grad(id);
        //cout << ans <<endl;
        if(ans<0){
            do{
                ans+=MOD;
            }
            while(ans<0);
        }
        else ans = ans%MOD;
        cout << ans<<endl;
        root->reset();
    }
    return 0;
}