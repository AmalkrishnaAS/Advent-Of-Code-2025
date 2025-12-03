#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <vector>

using namespace std;

vector<pair<long long , long long  >> parseInput(string path) {
    vector<pair<long long, long long >> ranges;
    ifstream f= ifstream(path);
    string line;
    getline(f,line);
    
    vector<string> parts;
    istringstream tokenStream(line);
    string part;
    
    while(getline(tokenStream,part,',')) {
        parts.push_back(part);
    }
    
    for(auto &part:parts) {
        if(part.empty()) continue;
        string start =  part.substr(0,part.find('-'));
        string end = part.substr(part.find('-')+1,part.size()-1);
        //cout<<"here"<<endl;
        
        //cout<<start<<" "<<end<<endl;
        ranges.push_back({stoll(start),stoll(end)});
    }
    f.close();
   
    return ranges;
    
}

long long solve (vector<pair<long long  , long long >> &ranges) {
    long long ans=0;
    for(auto &range:ranges) {
       long long start= range.first;
       long long end=range.second;
        
    for(long long i=start;i<=end;i++) {
        string value = to_string(i);
        long long length= value.size();
        if(length%2==1) continue;
        long long splitPoint=length/2;
        string part1= value.substr(0,splitPoint);
        string part2=value.substr(splitPoint,length-1);
        
        if(part1==part2) ans+=(stoll(value));
    }
    
}
return ans;
}

int  main() {
    std::vector<pair<long long,long long  >> ranges = parseInput("input.txt");
    // for(auto &range:ranges) {
    //     cout<<range.first<<" "<<range.second<<endl;
    // }
    long long ans = solve(ranges);
    cout<<ans;
    return 0;
}
