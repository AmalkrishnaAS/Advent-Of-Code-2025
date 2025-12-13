#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define ll long long 

using namespace std;

unordered_map<string , ll> memo;
bool starts_with(string s,string prefix) {
    return s.compare(0,prefix.size(),prefix)==0;
} 

unordered_map<string, vector<string>> parseInput(string path) {
    unordered_map<string, vector<string>> m;
    ifstream f(path);
    string line;
    while (getline(f,line)) {
        //if(!m.count("you") && !starts_with(line, "you")) continue;
        if(line.empty()) continue;
        string key = line.substr(0,3);
        if(!m.count(key)) m[key]={};
        string rest = line.substr(5);
        stringstream ss(rest);
        string temp;
        while (getline(ss,temp,' ')) {
            if(temp.empty()) continue;
            
            m[key].push_back(temp);
        
        }
        
    
    }
  
    
    
    f.close();
    return m;
}

ll dfs(unordered_map<string , vector<string>> &adj,vector<string> &currPath,string start,string req1,string req2,string tgt,bool f1,bool f2) {
    if(start=="fft") f1=true;
    if(start=="dac") f2=true;
    string key = start +"|" + (f1?"true":"false")+"|"+(f2?"true":"false");
    if(memo.count(key)) return memo[key];
    if(start==tgt) {
        // currPath.pop_back();
        if(f1 && f2) return true;
    }
    ll total =0;
    if(adj.count(start)) {
        for(auto &v:adj[start]) {
            currPath.push_back(v);
            total+=dfs(adj,currPath,v,req1,req2,tgt,f1,f2);
            currPath.pop_back();
        }
    }
    return memo[key]=total;
}

void printInput(unordered_map<string,vector<string>> adj) {
    for(auto it:adj) {
        cout<<it.first<<endl;
        cout<<"=============="<<endl;
        for(auto &el:it.second) {
            cout<<el<<" ";
        }
        cout<<endl;
    }
}

ll bfs(unordered_map<string, vector<string>> adj,string start) {
    queue<string> q;
    q.push(start);
    ll ans=0;
   // set<string> visited;
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        if(true) {
            vector<string> neighbours= adj[curr];
            //visited.insert(curr);
            for(auto &it:neighbours) {
                if(it=="out") ans++;
                q.push(it);
            }
        }
    
    }
    return ans;
    
}

int main() {
    unordered_map<string, vector<string>> adj =parseInput("input.txt");
    // printInput(adj);
    vector<string> currPath;
    ll ans= dfs(adj,currPath,"svr","fft","dac","out",false,false);
    cout<<ans<<endl;
    
  
    return 0;
}
