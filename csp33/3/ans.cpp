#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n;
    while(n--) {
        map<string, int> mo;
        typedef pair<string, int> pr;
        map<pr, double> mp;
        string s[40], ss[40];
        cin >> m;
        int cnt = 0;
        for(int i = 0; i < m; i++) {
            cin >> s[i];
            string ned = "";
            for(int j = 0; j < s[i].length(); j++) {//analyzing each char
                if(isalpha(s[i][j])) ned += s[i][j];
                if(isdigit(s[i][j])) {//cut when a digital shows up,'ned' must be an element
                    if(mo[ned] != 1) ss[cnt++] = ned, mo[ned] = 1;//if 
                    mp[{ned, i}] = 0;
                    while(isdigit(s[i][j])) {
                        mp[{ned, i}] *= 10;
                        mp[{ned, i}] += double(s[i][j] - '0');
                        j++;
                    }
                    j--; ned = "";
                }
            }
        }
        int ood = 0;
        for(int i = 0; i < m; i++) {
            int e = 0;
            for(int j = ood; j < cnt; j++) if(mp[{ss[j], i}] == 0) e++;
            if(e == cnt - ood) continue;
            if(mp[{ss[ood], i}] == 0) {
                int j = ood + 1;
                for(; j < cnt; j++) if(mp[{ss[j], i}] != 0) break;
                for(int k = 0; k < m; k++) swap(mp[{ss[ood], k}], mp[{ss[j], k}]);
            }
            for(int k = ood + 1; k < cnt; k++) {
                if(mp[{ss[k], i}] != 0) {
                    double ned = mp[{ss[k], i}] / mp[{ss[ood], i}];
                    for(int v = i; v < m; v++) mp[{ss[k], v}] -= ned * mp[{ss[ood], v}];
                }
            }
            ood += 1;
        }
        int rk = cnt;
        for(int i = 0; i < cnt; i++) {
            int e = 0;
            for(int j = 0; j < m; j++) if(mp[{ss[i], j}] == 0) e++;
            if(e == m) rk--;
        }
        if(rk < m) cout << 'Y' << endl;
        else cout << 'N' << endl;
    }
    return 0;
}

