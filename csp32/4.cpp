#include<bits/stdc++.h>
using namespace std;
#define int long long
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
}
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
                if(name==3){
                    if(latest==HEAD){
                        pw.pop_front();
                    }
                    else{
                        pw.pop_back();
                    }
                    continue;
                }
                if(name==1){
                    pw.push_front(matrix{p[1],p[2],p[3],p[4]});
                    latest = HEAD;
                }
                else{
                    pw.push_back(matrix{p[1],p[2],p[3],p[4]});
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
                    pw.pop_front();
                }
                cout << ans.a << " " << ans.b<< " "<< ans.c << " "<<ans.d<<endl;
            }
        }
    }

}