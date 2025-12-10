#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <chrono>

#define ll long long
using namespace std;

ll rows=0,cols=0;
vector<ll> uX, uY;

int getIdx(const vector<ll>& vec, ll val) {
    return lower_bound(vec.begin(), vec.end(), val) - vec.begin();
}

void compressCoordinates(const vector<pair<ll, ll>>& tiles) {
    uX.clear();
    uY.clear();
    for(const auto& p : tiles) {
        uX.push_back(p.first);
        uX.push_back(p.first + 1); 
        uY.push_back(p.second);
        uY.push_back(p.second + 1);
    }
    sort(uX.begin(), uX.end());
    uX.erase(unique(uX.begin(), uX.end()), uX.end());
    sort(uY.begin(), uY.end());
    uY.erase(unique(uY.begin(), uY.end()), uY.end());
}

vector<pair<ll, ll>> parseInput(string path) {
    ifstream f(path);
    vector<pair<ll, ll>> ans;
    string line;

    while(getline(f,line)) {
        stringstream ss(line);
        int splitind = line.find(',');
        ll first = stoll(line.substr(0,splitind));
        ll second = stoll(line.substr(splitind+1));
        ans.push_back(make_pair(first, second));
    }
    f.close();
    return ans;
}

void floodFill(vector<vector<char>> &grid,ll r,ll c) {
    if(r>=rows || r<0 || c>=cols || c<0 ) return;
    if(grid[r][c] !='.') return;
    grid[r][c] = 'O';
    floodFill(grid, r + 1, c);
    floodFill(grid, r - 1, c);
    floodFill(grid, r, c + 1);
    floodFill(grid, r, c - 1);
}

vector<vector<char>> makeGrid(vector<pair<ll, ll>> &tiles ) {
    rows = uY.size() + 2;
    cols = uX.size() + 2;
    vector<vector<char>> grid(rows,vector<char>(cols,'.'));

    for(auto &p:tiles) {
        grid[getIdx(uY, p.second)+1][getIdx(uX, p.first)+1] = '#';
    }

    for(int i=0;i<tiles.size();i++) {
        pair<ll, ll> p1=tiles[i];
        pair<ll, ll> p2=tiles[(i+1)%tiles.size()];

        int x1 = getIdx(uX, p1.first) + 1;
        int y1 = getIdx(uY, p1.second) + 1;
        int x2 = getIdx(uX, p2.first) + 1;
        int y2 = getIdx(uY, p2.second) + 1;

        if(x1 == x2) {
            int start=min(y1, y2);
            int end = max(y1, y2);
            for(int y=start+1;y<end;y++) grid[y][x1]='x';
        }
        else if (y1 == y2) {
            int start = min(x1, x2);
            int end = max(x1, x2);
            for (int x = start + 1; x < end; ++x) grid[y1][x] = 'x';
        }
    }
    floodFill(grid,0,0);

    for(auto &row:grid) {
        for(auto &el:row) {
            if(el=='.') el='x';
            else if(el=='O') el='.';
        }
    }
    return grid;
}

ll solve2(vector<vector<char>> &grid,vector<pair<ll, ll>> &tiles) {
    ll ans=0;
    for(int i =0;i<tiles.size()-1;i++) {
        for(int j=i+1;j<tiles.size();j++) {

            // Optimization: If area is smaller than current max, skip
            ll l=abs(tiles[i].first-tiles[j].first)+1;
            ll b=abs(tiles[i].second-tiles[j].second)+1;
            if (l*b <= ans) continue;

            int x1 = getIdx(uX, tiles[i].first) + 1;
            int y1 = getIdx(uY, tiles[i].second) + 1;
            int x2 = getIdx(uX, tiles[j].first) + 1;
            int y2 = getIdx(uY, tiles[j].second) + 1;

            int startX = min(x1, x2);
            int endX = max(x1, x2);
            int startY = min(y1, y2);
            int endY = max(y1, y2);

            bool hole = false;
            for(int y = startY; y <= endY; y++) {
                for(int x = startX; x <= endX; x++) {
                    if(grid[y][x] == '.') {
                        hole = true;
                        break;
                    }
                }
                if(hole) break;
            }

            if(!hole) {
               ans= max(ans,l*b);
            }
        }
    }
    return ans;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    vector<pair<ll, ll>> tiles = parseInput("input.txt");
    compressCoordinates(tiles);

    vector<vector<char>> grid = makeGrid(tiles);

    ll ans = solve2(grid, tiles);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << "Answer: " << ans << endl;
    cout << "Time taken: " << duration.count() << " ms" << endl;

    return 0;
}
