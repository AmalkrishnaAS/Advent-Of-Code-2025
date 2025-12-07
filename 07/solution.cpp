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
    cout<<ans<<endl;
    return 0;
}