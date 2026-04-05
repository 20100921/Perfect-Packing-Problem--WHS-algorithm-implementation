#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;
using namespace chrono;

// ==============================
// 1D WHS 极限求解
// ==============================
bool dfs1d(vector<int>& items, int idx, int sum, int target) {
    if (sum == target) return true;
    for (int i = idx; i < items.size(); i++) {
        if (sum + items[i] > target) continue;
        if (dfs1d(items, i + 1, sum + items[i], target)) return true;
    }
    return false;
}

bool solve1d(int L) {
    vector<int> items;
    int total = 0;
    for (int s : {2, 3}) while (total + s <= L) { items.push_back(s); total += s; }
    return dfs1d(items, 0, 0, L);
}

// ==============================
// 2D WHS 极限求解
// ==============================
vector<vector<int>> g2d;
vector<int> items2d;
int n2d;

bool dfs2d(int idx) {
    if (idx == items2d.size()) return true;
    int s = items2d[idx];
    int x = -1, y = -1;
    for (int i = 0; i < n2d && x < 0; i++)
        for (int j = 0; j < n2d && x < 0; j++)
            if (!g2d[i][j]) { x = i; y = j; }

    for (int i = x; i <= n2d - s; i++) {
        for (int j = y; j <= n2d - s; j++) {
            bool ok = 1;
            for (int a = 0; a < s && ok; a++)
                for (int b = 0; b < s && ok; b++)
                    if (g2d[i+a][j+b]) ok = 0;
            if (!ok) continue;

            for (int a = 0; a < s; a++)
                for (int b = 0; b < s; b++)
                    g2d[i+a][j+b] = 1;

            if (dfs2d(idx+1)) return 1;

            for (int a = 0; a < s; a++)
                for (int b = 0; b < s; b++)
                    g2d[i+a][j+b] = 0;
        }
    }
    return false;
}

bool solve2d(int N) {
    n2d = N;
    g2d.assign(N, vector<int>(N, 0));
    items2d.clear();
    int area = 0;
    for (int s : {2,3}) while (area + s*s <= N*N) {
        items2d.push_back(s);
        area += s*s;
    }
    return dfs2d(0);
}

// ==============================
// 3D WHS 极限求解
// ==============================
vector<vector<vector<int>>> g3d;
vector<int> items3d;
int n3d;

bool dfs3d(int idx) {
    if (idx == items3d.size()) return true;
    int s = items3d[idx];
    int x = -1, y = -1, z = -1;
    for (int i = 0; i < n3d && x < 0; i++)
        for (int j = 0; j < n3d && x < 0; j++)
            for (int k = 0; k < n3d && x < 0; k++)
                if (!g3d[i][j][k]) { x = i; y = j; z = k; }

    for (int i = x; i <= n3d - s; i++)
        for (int j = y; j <= n3d - s; j++)
            for (int k = z; k <= n3d - s; k++) {
                bool ok = 1;
                for (int a = 0; a < s && ok; a++)
                    for (int b = 0; b < s && ok; b++)
                        for (int c = 0; c < s && ok; c++)
                            if (g3d[i+a][j+b][k+c]) ok = 0;
                if (!ok) continue;

                for (int a = 0; a < s; a++)
                    for (int b = 0; b < s; b++)
                        for (int c = 0; c < s; c++)
                            g3d[i+a][j+b][k+c] = 1;

                if (dfs3d(idx+1)) return 1;

                for (int a = 0; a < s; a++)
                    for (int b = 0; b < s; b++)
                        for (int c = 0; c < s; c++)
                            g3d[i+a][j+b][k+c] = 0;
            }
    return false;
}

bool solve3d(int N) {
    n3d = N;
    g3d.assign(N, vector<vector<int>>(N, vector<int>(N, 0)));
    items3d.clear();
    int vol = 0;
    for (int s : {2,3}) while (vol + s*s*s <= N*N*N) {
        items3d.push_back(s);
        vol += s*s*s;
    }
    return dfs3d(0);
}

// ==============================
// 主函数：极限测试
// 1D 60s / 2D 3600s / 3D 36000s
// ==============================
int main() {
    cout << "========== WHS Limit Test ==========\n";
    auto start = steady_clock::now();
    int max1d = 0;
    for (int L = 100; L <= 10000; L++) {
        if (duration_cast<seconds>(steady_clock::now() - start).count() > 60) break;
        if (solve1d(L)) max1d = L;
    }
    cout << "1D Max (60s): " << max1d << endl;

    start = steady_clock::now();
    int max2d = 0;
    for (int N = 10; N <= 100; N++) {
        if (duration_cast<seconds>(steady_clock::now() - start).count() > 3600) break;
        if (solve2d(N)) max2d = N;
    }
    cout << "2D Max (1h): " << max2d << endl;

    start = steady_clock::now();
    int max3d = 0;
    for (int N = 4; N <= 30; N++) {
        if (duration_cast<seconds>(steady_clock::now() - start).count() > 36000) break;
        if (solve3d(N)) max3d = N;
    }
    cout << "3D Max (10h): " << max3d << endl;
    return 0;
}
