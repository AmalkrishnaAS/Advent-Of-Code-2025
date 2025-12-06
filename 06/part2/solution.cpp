#include <fstream>
#include <functional>
#include <numeric>
#include <string>
#define ll long long
#include <iostream>

using namespace std;

vector<string> parseInput(string path) {
    ifstream f(path);
    vector<string> lines;
    string line;
    while(getline(f,line)) {
        lines.push_back(line);
    }
    f.close();
    return lines;
}

ll solve(vector<string> &lines) {
    vector<ll> nums;
    ll ans=0;
    for(int i=lines[0].size()-1;i>=0;i--) {
        ll current=0;
        for(int j=0;j<lines.size()-1;j++) //skip the ops row in the end
        {
            if(lines[j][i]==' ') continue;
            current =current*10+(lines[j][i]-48);
        }
        nums.push_back(current);
        if(lines.back()[i]=='*') {
            ans+=accumulate(nums.begin(),nums.end(),1LL,multiplies<ll>());
            i--;
            nums.clear();

        } 
        else if(lines.back()[i]=='+') {
            ans+=accumulate(nums.begin(),nums.end(),0LL);
            i--;
            nums.clear();

        }
        
    }
    return ans;
}

int main() {
    vector<string> lines = parseInput("input.txt");
    ll ans=solve(lines);
    cout<<ans<<endl;
    
    return 0;
}