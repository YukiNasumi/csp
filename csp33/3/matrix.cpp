#include<bits/stdc++.h>
using namespace std;
#define MAX_NUM 50
int row,column;//the absolute row&col
int n;
double matrix[MAX_NUM][MAX_NUM];
bool isnum(char a){
    return a<='9'&&a>='0';
}
int show_matrix(int r,int c){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 1;
}
bool is_col_empty(int x,int y,int r){
    for(int i =0;i<r;i++){
        if(fabs(matrix[x+i][y])>=1e-5) return false;
    }
    return true;
}
void swap_row(int x1,int x2,int y,int c){
    for(int i=0;i<c;i++){
        double mid;
        mid = matrix[x1][y+i];
        matrix[x1][y+i]=matrix[x2][y+i];
        matrix[x2][y+i] = mid;
    }
    return ;
}
void modify_row(int x,int y,int target_r,int c){
    double first = matrix[x][y];
    double target = matrix[target_r][y];
    double factor = target/first;
    for(int i=0;i<c;i++){
        matrix[target_r][y+i]-=factor*matrix[x][y+i];
    }
}
int rank_transform(int x,int y, int r,int c){
    if(x>=row||y>=column) return 1;
    if(is_col_empty(x,y,r)) {
        rank_transform(x,y+1,r,c-1);
        return 1;};
    if(fabs(matrix[x][y])<=1e-5){//the start point element is zero
        int i=1;
        for(;i<r&&(matrix[x+i][y]<=1e-5);i++);
        swap_row(x,x+i,y,c);

    }
    for(int i=1;i<r;i++) modify_row(x,y,x+i,c);
    //show_matrix(row,column);
    rank_transform(x+1,y+1,r-1,c-1);
    return 1;
}
int cal_rank(){
    int rank=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(fabs(matrix[i][j])>=1e-5){
                rank+=1;
                break;
            }
        }
    }
    return rank;
}
size_t elm_find(string mat,string elm,size_t start){
    size_t pos = mat.find(elm,start);
    while(pos!=string::npos){
        if(isdigit(mat[pos+elm.length()])){
            //find the right pos
            return pos;
        }
        pos = mat.find(elm,pos+1);
    }
    return pos;
}
double a[MAX_NUM][MAX_NUM];
signed main(){
    cin >> n;
    for(int v=0;v<n;v++){
        vector<string>matrials;
        set<string>element;
        int m;
        cin >> m;
        for(int i=0;i<m;i++){
            string s;
            cin >> s;
            int begin=0;
            int end=0;
            for(;end<s.length();end++){
                if(!(s[end]<='9'&&s[end]>='0')) continue;//not a number,skip it
                element.insert(s.substr(begin,end-begin));
                //end is going to find the next alpha
                while(s[end]<='9'&&s[end]>='0') end++;
                //now 'end' point to next alpha
                begin = end;
            }
            matrials.push_back(s);
        }
        int r = element.size(),c = matrials.size();
        int i=0;// the index which point to the row to fill
        for(set<string>::iterator it = element.begin();it!=element.end();it++,i++){
            int j=0;//the idx which point to the column to fill
            string target_elm = *it;
            for(;j<c;j++){
                double ans=0;
                string matirial = matrials[j];
                int start = 0,end = 0;
                start = elm_find(matirial,target_elm,start);
                while(start != string::npos){
                    start += target_elm.length();//point to the number right after the target element
                    end = start;
                    while(end<matirial.length()&&isnum(matirial[end])) end++;
                    ans += stod(matirial.substr(start,end-start));
                    start = elm_find(matirial,target_elm,start);
                }
            matrix[i][j]=ans;
            }
        }
        row = r;
        column = c;
        rank_transform(0,0,r,c);
        if(cal_rank()<c) cout << 'Y' << endl;
        else cout << 'N' << endl;
        memset(matrix,0,sizeof(matrix));
    }
    return 0;
}