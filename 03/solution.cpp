#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

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

int getMax(string line) {
    // int value=INT_MIN;
    
    // for(int i=0;i<line.length()-1;i++) {
    //     for(int j=i+1;j<line.length();j++) {
    //         int  cand = (line[i]-48)*10+(line[j]-48);
    //         value= max(cand,value);
    //     }
    // }
    //cout<<value<<endl;
    int value = 0;
    auto it1=max_element(line.begin(),line.end()-1);
    auto it2=max_element(it1+1,line.end());
    // cout<<*it1<<endl;
    //cout<<it1-line.begin()<<" "<<it2-line.begin()<<endl;
    value = (*it1-48)*10+(*it2-48);
    //cout<<value<<endl;
    return value;
}

long long getMax2(string line) {
    int DIGITS=12;
    int n=DIGITS;
    
    
    long long value = 0;
    auto it1=line.begin()-1;
    while (n--) {
    it1=max_element(it1+1,line.begin()+(line.length()-n));
    value  = value*10+(*it1-48);
    }
    // cout<<value<<endl;
    return value;
}


long long solve (vector<string>&lines ) {
    unsigned long long  ans=0;
    for(auto &line:lines) {
        ans+=getMax2(line);
    }
    return ans;
}
int main() {
    
    vector<string> lines =parseInput("input.txt");
    unsigned long long ans  = solve(lines);
    cout<<ans<<endl;
    return 0;
}