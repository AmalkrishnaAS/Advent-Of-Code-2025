#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


#define ll long long

using namespace std;


ll n_lines=0;

class Dsu {
    vector<ll> parent;
    vector<ll> size;
    public:
    Dsu(ll n) {
        parent.resize(n);
        size.resize(n,1);
       for(int i=0;i<n;i++) {
           parent[i]=i;
       }
    }
    ll findParent(ll el) {
        if(parent[el]==el) return  el;
        else {
            return parent[el]=findParent(parent[el]);
        }
    }
    bool unite(ll u,ll v) {
        ll ru=findParent(u);
        ll rv =findParent(v);
        if(ru==rv) return false;
        if(size[ru]>size[rv]) {
            parent[rv]=ru;
            size[ru]+=size[rv];
        }
        
        else {
            parent[ru]=rv;
            size[rv]+=size[ru];
        }
        return true;
    }
    
    vector<ll> getSize() {
        return size;
    }
    
    
};

vector<vector<ll>> parseInput(string path) {
    vector<vector<ll>> points;
    ifstream f(path);
    string line;
    while(getline(f,line)) {
        string t;
        stringstream ss(line);
        vector<ll> point;
        while(getline(ss,t,',')) {
            point.push_back(stoll(t));
        }
        points.push_back(point);
    }
    f.close();
    return points;
}

ll euclid(vector<ll> &p1,vector<ll> &p2) {
    ll x2=(p1[0]-p2[0])*(p1[0]-p2[0]);
    ll y2=(p1[1]-p2[1])*(p1[1]-p2[1]);
    ll z2=(p1[2]-p2[2])*(p1[2]-p2[2]);
    return x2+y2+z2;


} 
vector<pair<ll,pair<ll, ll>>> getPairWiseDist(vector<vector<ll>> &points) {
    vector<pair<ll, pair<ll, ll>>> ans;
    for(int i=0;i<points.size()-1;i++) {
        for(int j=i+1;j<points.size();j++) {
            ans.push_back(make_pair(euclid(points[i], points[j]), make_pair(i, j)));
        }
    }
    sort(ans.begin(),ans.end()); // by default pairs are sorted by the first element :-)
    return ans;
}

int main() {
    vector<vector<ll>> points = parseInput("input.txt");
    
    // for(auto &p:points) {
    //     for(auto &c:p) {
    //         cout<<c<<" ";
    //     }
    //     cout<<endl;
    // }
    
    vector<pair<ll,pair<ll,ll>>> pairDist = getPairWiseDist(points);
    // for(auto &el:pairDist) {
    //     cout<<el.first<<endl;
        
    // }    
    pair<ll,ll> lastMerge;
    ll count=1000;
    Dsu dsu = Dsu(points.size());
    for(auto &el:pairDist) {
        //if(!count) break;
        bool success= dsu.unite(el.second.first, el.second.second);
        if(success) lastMerge= make_pair(el.second.first, el.second.second);
        count--;
        
    }
    
    ll p2=points[lastMerge.first][0]*points[lastMerge.second][0];
    cout<<"part 2:"<<p2<<endl;
    vector<ll> sizes=dsu.getSize();
    sort(sizes.begin(),sizes.end(),greater<ll>());
    //cout<<sizes[0]<<" "<<sizes[1]<<" "<<sizes[2]<<endl;
    //cout<< sizes[0]*sizes[1]*sizes[2]<<endl;
    
}