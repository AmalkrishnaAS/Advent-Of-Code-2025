#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define ll long long
using namespace std;

vector<pair<ll, ll>> parseInput(string path) {
    ifstream f(path);
    vector<pair<ll, ll>> ans;
    string line;
    
    while(getline(f,line)) {
        stringstream ss(line);
        int splitind = line.find(',');
        ll first = stoll(line.substr(0,splitind));
        ll second= stoll(line.substr(splitind+1));
        ans.push_back(make_pair(first, second));
    }
    f.close();
    return  ans;
    
}
ll calculatePirwiseArea(vector<pair<ll, ll>> &tiles) {
    ll minMaxEdge = INT_MIN;
    ll ans= INT_MIN;
    for(int i =0;i<tiles.size()-1;i++) {
        for(int j=i+1;j<tiles.size();j++) {
            pair<ll, ll> p1= tiles[i];
            pair<ll,ll> p2=tiles[j];
            
            ll l = abs(p1.first-p2.first+1);
            ll b=abs(p1.second-p2.second+1);
            //if(minMaxEdge>l && minMaxEdge>b) continue;
            //minMaxEdge = max(min(l,b),minMaxEdge);
            ans= max(ans,l*b);
            
        }
    }
    return ans;
    
}
int main() {
    vector<std::pair<ll,ll>> tiles= parseInput("input.txt");
    
    ll ans = calculatePirwiseArea(tiles);
    cout<<ans<<endl;
    
    return 0;
}