#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<string> parseInput(string path) {
    ifstream f(path);
    vector<string> grid;
    string line;
    while (getline(f,line)) {
        grid.push_back(line);
    }
    f.close();
    return grid;
}

//kinda verbose tbh
int solve(vector<string> &grid) {
    int ans=0;
    int m=grid.size();
    int n=grid[0].size();
    vector<pair<int, int>> cache;
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            if(grid[i][j]!='@') continue;
            int curr=0;
            char a=(i+1<m)?grid[i+1][j]:'.';
            char b=(i-1>=0)?grid[i-1][j]:'.';
            char c=(j+1<n)?grid[i][j+1]:'.';
            char d=(j-1>=0)?grid[i][j-1]:'.';
            char e=(i+1<m && j+1<n)?grid[i+1][j+1]:'.';
            char f=(i-1>=0 && j-1>=0)?grid[i-1][j-1]:'.';
            char g =(i-1>=0 && j+1<n)?grid[i-1][j+1]:'.';
            char h =(i+1<m && j-1>=0)?grid[i+1][j-1]:'.';
            
            if(a=='@') curr++;
            if(b=='@') curr++;
            if(c=='@') curr++;
            if(d=='@') curr++;
            if(e=='@') curr++;
            if(f=='@') curr++;
            if(g=='@') curr++;
            if(h=='@') curr++;
            
            if(curr<4) {ans++;
                //the additional step for p2
                cache.push_back(make_pair(i, j));
            }

            
        }
    }
    
    for(auto &p:cache) {
        grid[p.first][p.second]='.';
    }
    return ans;
}

int main() {
    vector<string> grid = parseInput("input.txt");
    int m=grid.size(),n=grid[0].size();
    int ans;
    int prev=ans;
    for(int i=0;i<n*m;i++) {
        prev=ans;
        ans+=solve(grid);
        if(prev==ans) break;
    }
    cout<<ans<<endl;
    return 0;
}