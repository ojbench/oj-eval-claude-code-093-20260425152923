#include <bits/stdc++.h>
using namespace std;

struct StateKey {
    int x, y, dir;
    bool operator==(const StateKey &o) const {
        return x == o.x && y == o.y && dir == o.dir;
    }
};

struct StateKeyHash {
    size_t operator()(StateKey const &s) const noexcept {
        return ((s.x * 31u + s.y) * 31u + s.dir);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 10;
    vector<vector<int>> g(N, vector<int>(N));
    int sx = -1, sy = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(cin >> g[i][j])) return 0; // invalid input
            if (g[i][j] == 4) { sx = i; sy = j; }
        }
    }
    if (sx == -1 || sy == -1) return 0;

    // Directions: 0=up,1=right,2=down,3=left
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int x = sx, y = sy;
    int dir = 0; // start facing up
    long long score = 0;
    int eaten = 0; // number of pellets eaten

    // Treat start cell as empty after leaving; if we ever step onto a 2, eat it
    // If start cell initially had pellet (not possible by spec), still handled

    unordered_map<StateKey, int, StateKeyHash> seen;

    auto inb = [&](int nx, int ny) {
        return nx >= 0 && nx < N && ny >= 0 && ny < N;
    };

    // Record initial state
    seen[{x, y, dir}] = eaten;

    while (true) {
        // Choose next direction by right-hand rule priority: right, straight, left, back
        int candidates[4] = { (dir + 1) % 4, dir, (dir + 3) % 4, (dir + 2) % 4 };
        bool moved = false;
        int ndir = dir;
        int nx = x, ny = y;
        for (int k = 0; k < 4; ++k) {
            int td = candidates[k];
            int tx = x + dx[td];
            int ty = y + dy[td];
            if (inb(tx, ty) && g[tx][ty] != 0) {
                ndir = td;
                nx = tx; ny = ty;
                moved = true;
                break;
            }
        }
        if (!moved) {
            // No possible move -> stuck forever
            cout << "Silly Pacman\n";
            return 0;
        }

        // Move
        dir = ndir;
        x = nx; y = ny;

        // Check ghost
        if (g[x][y] == 3) {
            score -= 500;
            cout << score << "\n";
            return 0;
        }

        // Eat pellet if present
        if (g[x][y] == 2) {
            score += 2;
            ++eaten;
            g[x][y] = 1; // consumed
        }

        // Loop detection: if we revisit (x,y,dir) with same eaten count as last time
        StateKey key{x, y, dir};
        auto it = seen.find(key);
        if (it != seen.end()) {
            if (it->second == eaten) {
                cout << "Silly Pacman\n";
                return 0;
            } else {
                // Update with new eaten count
                it->second = eaten;
            }
        } else {
            seen.emplace(key, eaten);
        }
    }
}
