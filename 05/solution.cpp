#define ll long long
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct InputVectors {
    vector<pair<ll, ll>> ranges;
    vector<ll> values;
};

InputVectors parseInput(string path) {
    vector<pair<ll, ll>> ranges;
    vector<ll> values;
    
    ifstream f(path);
    string line;
    bool range_done=false;
    while (getline(f,line)) {
    if(!range_done) {
        if(line.empty()) {
            range_done=true;
           // cout<<"============================"<<endl;
            continue;
        }
        ll it=find(line.begin(),line.end(),'-')-line.begin();
        ll startValue = stoll(line.substr(0,it));
        ll endValue = stoll(line.substr(it+1));
        //cout<<startValue<<","<<endValue<<endl;
        ranges.push_back(make_pair(startValue, endValue));
        } else {
            //cout<<line<<endl;
            values.push_back(stoll(line));
        }
    }
    f.close();

    InputVectors result;
    result.values=values;
    result.ranges=ranges;
    return result;
}

ll solve(InputVectors input ) {
    ll ans = 0;
    vector<pair<ll, ll>> ranges = input.ranges;
    vector<ll> values = input.values;
    for(auto &value:values) {
        bool found = false;
        for(auto range:ranges) {
            if(found) break;
            if(value>=range.first && value<=range.second) {ans++;found=true;}
        }
    }
    
    return ans;
}

int main() {
    InputVectors input = parseInput("input.txt");
    ll  ans=solve(input);
    cout<<ans<<endl;
    return 0;
}