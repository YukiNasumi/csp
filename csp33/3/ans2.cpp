#include <iostream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;

int n, m;
double a[50][50]; // 储存行列式 
double tmp;
string str, ch;
map<string, int> mp[50]; // 统计物质中各种元素的个数 
map<string, bool> cnt; // 标记方程式中出现过的元素 
bool fg;

int main() {
    int i, j, k, len, s, t, z;
    double p;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &m);
        for (i = 1; i < 50; i++)
            mp[i].clear();
        cnt.clear();
        for (i = 1; i <= m; i++) {
            cin >> str;
            len = str.length();
            for (j = 0; j < len;) {
                ch = "";
                s = 0;
                // 分离元素和数字 
                for (; j < len && str[j] >= 'a' && str[j] <= 'z'; j++)
                    ch = ch + str[j];
                for (; j < len && str[j] >= '0' && str[j] <= '9'; j++)
                    s = s * 10 + str[j] - '0';
                mp[i][ch] = s; // 在第i个物质中元素ch的个数为s 
                cnt[ch] = 1; // 标记在方程式中出现过元素ch 
            }
        }
        t = 0;
        for (auto &p : cnt) { // 遍历所有出现过的元素 
            t++;
            for (i = 1; i <= m; i++) // 遍历每个物质 
                a[t][i] = mp[i][p.first];
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
    }
    return 0;
}
