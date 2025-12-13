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
    ll ans= bfs(adj,"you");
    cout<<ans<<endl;
    
  
    return 0;
}
