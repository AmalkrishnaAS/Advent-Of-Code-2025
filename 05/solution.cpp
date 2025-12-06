#include <algorithm>
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

vector<pair<ll, ll>> mergeRanges(vector<pair<ll, ll>> &ranges) {
    vector<pair<ll, ll>> merged;
    sort(ranges.begin(),ranges.end());
    merged.push_back(make_pair(ranges[0].first, ranges[0].second));
    
    //ranges: [3-5 3-7 4-8 10-12 ]
    // merged: [ 3-5 ]
    for(int i=1;i<ranges.size();i++) {
        pair<ll, ll> last = merged[merged.size()-1];
        if(ranges[i].first<=last.second) {
            merged[merged.size()-1].first=min(ranges[i].first,last.first);
            merged[merged.size()-1].second=max(ranges[i].second,last.second);
        } else {
            merged.push_back(ranges[i]);
        }
    }
    // for(auto &it:merged) {
    //     cout<<it.first<<","<<it.second<<endl;
    // }
    return merged;
    
}

ll solve2(InputVectors input ) {
    ll ans = 0;
    vector<pair<ll, ll>> ranges = input.ranges;
    ranges =mergeRanges(ranges);
    vector<ll> values = input.values;
   for(auto &it:ranges) {
       ans+=(it.second-it.first+1);
   }
    
    return ans;
}

int main() {
    InputVectors input = parseInput("input.txt");
    ll  ans=solve2(input);
    //mergeRanges(input.ranges);
    cout<<ans<<endl;
    return 0;
}