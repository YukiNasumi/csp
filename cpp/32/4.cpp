#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define HEAD 1
#define TAIL 0
#define MOD 998244353
typedef struct matrix{
    int a,b,c,d;

public:
    void show(){
        cout << a<<" " << b<< endl << c << " " << d<< endl;
    }
} matrix;
matrix matmul(matrix A,matrix B){
    return matrix{(((A.a%MOD)*(B.a%MOD)%MOD)+((A.b%MOD)*(B.c%MOD)%MOD))%MOD, 
                    (((A.a%MOD)*(B.b%MOD)%MOD)+((A.b%MOD)*(B.d%MOD)%MOD))%MOD, 
                    (((A.c%MOD)*(B.a%MOD)%MOD)+((A.d%MOD)*(B.c%MOD)%MOD))%MOD, 
                    (((A.c%MOD)*(B.b%MOD)%MOD)+((A.d%MOD)*(B.d%MOD)%MOD))%MOD};
    /*return matrix{
        A.a*B.a+A.b*B.c,
        A.a*B.b+A.b*B.d,
        A.c*B.a+A.d*B.c,
        A.c*B.b+A.d*B.d        };*/
}
matrix eyes = {1,0,0,1};
int n,m;
vector<vector<int>>prompt;
signed main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        int name;
        cin >> name;
        vector<int>p;
        p.push_back(name);
        if(name == 3) {
            prompt.push_back(p);
            continue;
        }
        for(int j =0;j<4;j++){
            int x;
            cin >> x;
            p.push_back(x);
        }
        prompt.push_back(p);
    }
    for(int i=0;i<m;i++){
        int name;
        cin >> name;
        if(name == 1){
            int seq;
            cin >> seq;
            int name1;
            cin >> name1;
            vector<int>p;
            p.push_back(name1);
            if(name1 == 3) {
                prompt[seq-1]=p;
                continue;
            }
            for(int j =0;j<4;j++){
                int x;
                cin >> x;
                p.push_back(x);
            }
            prompt[seq-1]=p;
            }
        else{
            int l,r;
            cin >> l >> r;
            deque<matrix>pw;
            int latest;
            for(int j=l-1;j<r;j++){
                vector<int>p = prompt[j];
                int name = p[0];
                if(name==3&&(!pw.empty())){
                    pw.pop_back();
                    pw.pop_front();
                    continue;
                }
                if(name==1){
                    pw.push_front(matrix{p[1],p[2],p[3],p[4]});
                    pw.push_back(eyes);
                    latest = HEAD;
                }
                else{
                    pw.push_back(matrix{p[1],p[2],p[3],p[4]});
                    pw.push_front(eyes);
                    latest = TAIL;
                }
            }
            if(pw.empty()){
                cout << "1 0 0 1" << endl;
            }
            else{
                matrix ans = {1,0,0,1};
                while(!pw.empty()){
                    ans = matmul(ans,pw.front());
                    cout<<pw.front().a <<"|"<< pw.front().b<<"|" << pw.front().c <<"|" << pw.front().d<<endl;
                    pw.pop_front();
                }
                cout << ans.a%MOD << " " << ans.b%MOD<< " "<< ans.c%MOD << " "<<ans.d%MOD<<endl;
            }
        }
    }

return 0;
}