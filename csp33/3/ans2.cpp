#include <iostream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;

int n, m;
double a[50][50]; // ��������ʽ 
double tmp;
string str, ch;
map<string, int> mp[50]; // ͳ�������и���Ԫ�صĸ��� 
map<string, bool> cnt; // ��Ƿ���ʽ�г��ֹ���Ԫ�� 
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
                // ����Ԫ�غ����� 
                for (; j < len && str[j] >= 'a' && str[j] <= 'z'; j++)
                    ch = ch + str[j];
                for (; j < len && str[j] >= '0' && str[j] <= '9'; j++)
                    s = s * 10 + str[j] - '0';
                mp[i][ch] = s; // �ڵ�i��������Ԫ��ch�ĸ���Ϊs 
                cnt[ch] = 1; // ����ڷ���ʽ�г��ֹ�Ԫ��ch 
            }
        }
        t = 0;
        for (auto &p : cnt) { // �������г��ֹ���Ԫ�� 
            t++;
            for (i = 1; i <= m; i++) // ����ÿ������ 
                a[t][i] = mp[i][p.first];
        }
        for (i = 1; i <= t; i++) {    
            // ����ȫΪ0����Ը���    
            for (j = 1; j <= m; j++)
                if (a[i][j] != 0)
                    break;
            if (j > m) continue;
            if (a[i][i] == 0) { // �����i��Ϊ0��������һ����Ϊ0�����н��� 
                for (j = i + 1; j <= t && a[j][i] == 0; j++);
                for (k = 1; k <= m; k++)
                    tmp = a[i][k],
                    a[i][k] = a[j][k],
                    a[j][k] = tmp;
            }
            for (j = i + 1; j <= t; j++) { // ������ÿһ�м�ȥ��i����Ӧ������ʹ��i�б��0 
                p = a[j][i] / a[i][i];
                for (k = i; k <= m; k++)
                    a[j][k] = a[j][k] - a[i][k] * p;
            }
        }
        z = 0;
        for (i = 1; i <= t; i++) { // ͳ�Ʋ�ȫΪ0����������������� 
            for (j = 1; j <= m && a[i][j] == 0; j++);
            if (j <= m) z++;
        }
        if (z < m) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
