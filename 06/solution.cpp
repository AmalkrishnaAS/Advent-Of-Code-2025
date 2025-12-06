#define ll long long

#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Input {
vector<vector<ll>> nums;
 vector<char> ops;
};

Input setValues(vector<string> &lines) {
  Input ans;
  vector<char> ops;
  vector<vector<ll>> nums;
  ll s=lines.size();
  for(int j=0;j<s-1;j++) {
    nums.push_back({});
  }
  ll i=0;
  for(auto &line:lines) {
    if(i==s-1) {
      string t;
      stringstream sst(line);
      while(getline(sst,t,' ')) {
        if(t.empty()) continue;
        ops.push_back(t[0]);
      }
    }
    stringstream ss(line);
    string token;
    while(getline(ss,token,' ')) {
      if(token[0]==' ') continue;
        //if(!isnumber(token[0])) ops.push_back(token[0]);
      else if(isnumber(token[0])) {
        nums[i].push_back(stoi(token));
      }
    }
    i++;
      
  }
    
  Input ip;
  ip.nums = nums;
  ip.ops=ops;
  return ip;
    
}

Input parseInput(string path) {
  ifstream f(path);
    
  vector<string> lines;
  string temp;
    
  while(getline(f,temp)) {
    lines.push_back(temp);
  }
    
  f.close();
  return setValues(lines);
}

ll solve(Input input) {
  ll ans=0;
  vector<vector<ll>> nums = input.nums;
  vector<char> ops = input.ops;
  ll n= nums[0].size(),m=nums.size();
    
  for(ll i=0;i<n;i++) {
    //cout<<"here"<<endl;
    char op= ops[i];
    ll curr=op=='+'?0:1;
    for(ll j=0;j<m;j++) {
      ///cout<<nums[j][i]<<endl;
      if(op=='+' ) {
        curr+=nums[j][i];
      }
      else {
        curr*=nums[j][i];
      }
    }
    ans+=curr;
  }
  return ans;
}

int main() {
  Input input = parseInput("input.txt");
  //cout<<input.nums.size()<<endl;
  ll ans=solve(input);
    cout<<ans<<endl;
    
  return 0;
}