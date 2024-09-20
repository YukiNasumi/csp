#include<bits/stdc++.h>
using namespace std;
int p;
string current_dir;
vector<string>split(string& dir){
    int start=0,end = 0;
    vector<string>res;
    if(dir[0]=='/') {
        res.push_back("/");
        dir.replace(0,1,"");
        }
    start = dir.find("/",end);
    end = dir.find("/",start+1);
    while(end<dir.length()&&end!=string::npos){
        res.push_back(dir.substr(start,end-start))
    }

}
int main(){
    cin >> p;
    cin >> current_dir;

}