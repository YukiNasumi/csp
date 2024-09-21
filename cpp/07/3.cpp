#include<bits/stdc++.h>
using namespace std;
int P;
string current_dir;
vector<string>split(string& dir){
    int start=0,end = 0;
    vector<string>res;
    if(!dir.length()) return res;
    int l = dir.length();
    if(dir[0]=='/') res.push_back("/");
    for(int i =0;i<l;i++){
        char c = dir[i];
        if(c=='/'){
            end = i;
            if(end-start)
                res.push_back(dir.substr(start,end-start));
            start = end+1;
        }
    }
    if(dir[l-1]!='/'){
        res.push_back(dir.substr(start,l));
    }
    return res;

}
typedef struct node{
    string name;
    map<string,node*>children;
}node;
node* root;
int main(){
    cin >> P;
    cin.ignore();
    getline(cin,current_dir);
    //cin >> current_dir;
    vector<string>l = split(current_dir);
    /*for(auto &a:l) cout << a << endl;
    return 0;*/
    for(int k=0;k<P;k++){
        root = new node;
        node* p = root;
        node* parent = root;
        for(vector<string>::iterator it=l.begin();it!=l.end();it++){
            string name = *it;
            p->name = name;
            p->children = {
                {".",p},
                {"..",parent},
                {"/",root}
            };
            if((it+1)==l.end()){
                break;
            }
            node * child = new node;
            p->children.insert(make_pair(*(it+1),child));
            parent =p;
            p=child;
        }
            //now p points to the current dir
        string path;
        getline(cin,path);
        //cin >> path;
        vector<string>path2 = split(path);
        node* cwd=p;//current work dir
        for(vector<string>::iterator it=path2.begin();it!=path2.end();it++){
            string name = *it;
            if(!cwd->children.count(name)){
                node* newchild = new node;
                newchild->name = name;
                newchild->children.insert(make_pair("/",root));
                newchild->children.insert(make_pair(string("."),newchild));
                newchild->children.insert(make_pair(string(".."),cwd));
                cwd->children.insert(make_pair(name,newchild));
            }
            cwd = cwd->children[name];
        }
        list<string>ans;
        do{
            ans.push_front(cwd->name);
            if(cwd->name=="/") break;
            cwd = cwd->children[string("..")];
        }while(1);
        for(list<string>::iterator it=ans.begin();it!=ans.end();it++){
            string name = *it;
            cout << name;
            if((++it)!=ans.end()&&name!="/") cout<<"/";
            it--;
        }
        cout << endl;
    }
    return 0;
}