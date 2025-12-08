#include <unordered_map>
#include <unordered_set>
#include <vector>
#define ll long long 
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
struct Input {
    vector<string> grid;
    int start;
};


Input parseInput(string path) {
    ifstream f(path);
    string line;
    vector<string> grid;
    int start;
    bool first=true;
    while(getline(f,line)) {
        grid.push_back(line);
    }
    for(int i=0;i<grid[0].size();i++) {
        if(grid[0][i]=='S') {
            start=i;
        }
    }
    Input ip;
    ip.start =start;
    ip.grid=grid;
    return ip;
    
}

//bfs (kinda....)
ll solve(Input input) {
    int start=input.start;
    vector<string> grid = input.grid;
    ll ans=0;
    unordered_set<int> curr;
    curr.insert(start);
    unordered_set<int> next;
    //cout<<grid[1][start]<<endl;
    for(int i=1;i<grid.size();i++) {
        for(auto &el:curr) {
            //cout<<grid[i][el]<<" ";
            if(grid[i][el]=='.') next.insert(el);
            if(grid[i][el]=='^') {
                next.insert(el-1);
                next.insert(el+1);
                ans++;
                
            }
            
        }
        curr=next;
        next.clear();
    }
    
     return ans;
}

ll solve2(vector<string> &grid,int row,int col,vector<vector<ll>> &memo) {
    if(row==grid.size()) return 1;  //reached the bottom ; valid timeline
    if(col==grid[0].size() || col==-1) return 0; // went out of the grid before it reached the bottom , invalid
    
    if(memo[row][col]!=-1) return memo[row][col];
    
    if(grid[row][col]=='.') return memo[row+1][col]=solve2(grid, row+1, col,memo); //just move straight down
    else {
        memo[row+1][col+1]= solve2(grid, row+1, col+1,memo);
        memo[row+1][col-1]= solve2(grid, row+1, col-1,memo);
        return memo[row+1][col+1]+memo[row+1][col-1]; // spawn two rays
    }
    
}
int main() {
    Input input=parseInput("input.txt");
    // cout<<"start : "<<input.start<<endl;
    // for(auto &s:input.grid) {
    //     for(auto &c:s) {
    //         cout<<c<<" ";
    //     }
    // }
        //cout<<endl;
    ll ans=solve(input);
    // cout<<ans<<endl;
    unordered_set<int> curr,next;
    vector<vector<ll>> memo(input.grid.size()+1, vector<ll>(input.grid[0].size(), -1));
    curr.insert(input.start);    
    ans= solve2(input.grid,1,input.start,memo);
    cout<<ans<<endl;
    return 0;
}
