#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define ll long long

using namespace std;

// this is a pure bruteforce solution by simulating all possible combinations of button presses. I ran out of variable names in the end :-)

struct Input {
    vector<string> targets;
    vector<vector<vector<ll>>> presses;
};

Input parseInput(string path) {
    Input ip;
    ifstream f(path);
    string line;
    string target="";
    vector<vector<vector<ll>>> presses;
    while(getline(f,line)) {
        vector<vector<ll>> press;
        target="";
        if(line.empty()) continue;
        stringstream ss(line);
        string token;
        while (getline(ss,token,' ')) {
            if(token.empty()) continue;
            if(target.size()==0) {
                target=token.substr(1,token.size()-2); //strip the brackets
                continue;
            }
            
            string curr=token.substr(1,token.size()-2);
            
            stringstream ss1(curr);
            vector<ll> button;
            string t;
            
            while (getline(ss1,t,',')) {
                
                button.push_back(stoll(t));
                
            }
            press.push_back(button);
        }
        ip.targets.push_back(target);
        press.pop_back();
        presses.push_back(press);

    }
    //ip.target=target;
    ip.presses=presses;
    f.close();
    return ip;
}

void printInput(Input input) {
    for(auto &target:input.targets) {
        cout<<target<<endl;
    }
    
    for(auto &press:input.presses) {
        cout<<endl<<"++++++++++++++++"<<endl;
        for(auto &el:press) {
           cout<<endl;
           for(auto b:el) {
               cout<<b<<" ";
           }
        }
    }
}

void backtrack(vector<vector<ll>> &v,vector<vector<ll>> &curr,ll index,int n,vector<vector<vector<ll>>> &ans) {
    if(index==n) {
        ans.push_back(curr);
        return;
    }
    curr.push_back(v[index]);
    backtrack(v, curr, index+1, n, ans);
    curr.pop_back();
    backtrack(v, curr, index + 1, n, ans);
    
}

string toggle(vector<ll> &click,string s) {
    for(auto &c:click) {
        if(s[c]=='.') s[c]='#';
        else s[c]='.';
    }
    return s;
}

string executePress(vector<vector<ll>> press,string s) {
    for(auto &click:press) {
        s=toggle(click,s);
    }
    return s;
}
ll subSolve(vector<vector<vector<ll>>> &presses ,string target) {
    for(auto &press:presses) {
        string s(target.size(),'.');
        string res = executePress(press,s);
        if(res ==target) return press.size();
    }
    return 0;
}


ll solve(vector<vector<vector<vector<ll>>>> &lineSets,vector<string> targets) {
    //go through line by line and compute individual res
    ll ans= 0;
    for(int i=0;i<targets.size();i++) {
        sort(lineSets[i].begin(), lineSets[i].end(), [](const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
                return a.size() < b.size();
            });
        ans+=subSolve(lineSets[i],targets[i]);
    }
    return ans;
} 

int main() {
    Input input = parseInput("input.txt");
    //printInput(input);
    //vector<vector<ll>> curr;
    vector<vector<vector<vector<ll>>>> lineSets;
    for(int i=0;i<input.presses.size();i++)  {
        vector<vector<ll>> curr;
        vector<vector<vector<ll>>> subsets; 
        backtrack(input.presses[i],curr,0LL,input.presses[i].size(),subsets);
        Input ip;
        ip.presses = subsets;
        vector<string> t;
        t.push_back("");
       // printInput(ip);
        lineSets.push_back(subsets);
        curr.clear();
    }
    
    ll ans = solve(lineSets,input.targets);
    cout<<ans<<endl;
        
    return 0;
    
}