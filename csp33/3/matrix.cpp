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
void swap_col(int x,int y1,int y2,int r){
    for(int i=0;i<r;i++){
        double mid;
        mid = matrix[x+i][y1];
        matrix[x+i][y1] = matrix[x+i][y2];
        matrix[x+i][y2] = mid;
    }
    return ;
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
bool is_row_empty(int x,int y,int c){
    for(int i=0;i<c;i++){
        if(fabs(matrix[x][y+i]>=1e-5)) return false;
    }
    return true;
}
int rank_transform(int x,int y, int r,int c){
    if(x>=row||y>=column) return 1;
    if(is_col_empty(x,y,r)) {
        rank_transform(x+1,y+1,r-1,c-1);
        return 1;};
    if(fabs(matrix[x][y])<=1e-5){//the start point element is zero
        int i=1;
        for(;i<r&&is_row_empty(x+i,y,c);i++);
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
        //show_matrix(r,c);
        int  j, k, len, s, t, z;
        double tmp = 0;
        double p;
        t = row,m = column;
        for(int i =0;i<row;i++){
            for(int j=0;j<column;j++){
                a[i+1][j+1]=matrix[i][j];
            }
        }
        for (i = 1; i <= t; i++) {    
            // 检验全为0则忽略该行    
            for (j = 1; j <= m; j++)
                if (a[i][j] != 0)
                    break;
            if (j > m) continue;
            if (a[i][i] == 0) { // 如果第i列为0，向下找一个不为0的整行交换 
                for (j = i + 1; j <= t && a[j][i] == 0; j++);
                for (k = 1; k <= m; k++)
                    tmp = a[i][k],
                    a[i][k] = a[j][k],
                    a[j][k] = tmp;
            }
            for (j = i + 1; j <= t; j++) { // 将后面每一行减去第i行相应倍数，使第i列变成0 
                p = a[j][i] / a[i][i];
                for (k = i; k <= m; k++)
                    a[j][k] = a[j][k] - a[i][k] * p;
            }
        }
        z = 0;
        for (i = 1; i <= t; i++) { // 统计不全为0的行数，即矩阵的秩 
            for (j = 1; j <= m && a[i][j] == 0; j++);
            if (j <= m) z++;
        }
        if (z < m) printf("Y\n");
        else printf("N\n");
    
        /*rank_transform(0,0,r,c);
        if(cal_rank()<c) cout << 'Y' << endl;
        else cout << 'N' << endl;*/
        memset(matrix,0,sizeof(matrix));
    }
    return 0;
}