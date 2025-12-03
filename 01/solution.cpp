#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <stdlib.h>
#include <utility>
using namespace std;

const int  START= 50;
const int TOTAL =100;
vector<pair<char, int>> parseInput(ifstream &f)  {
    string temp;
    vector<pair<char,int>> moves;
    while (getline(f,temp)) {
        char direction = temp[0];
        int  magnitude=stoi(temp.substr(1,temp.size()));
        moves.push_back({direction,magnitude});
        //cout<<direction<<":"<<magnitude<<endl;
        
    }
    f.close();
    return moves;
    
}

int makeMoves(vector<pair<char,int>> &moves) {
    int current = START;
    int ans =0;
    //cout<<moves.size()<<endl;
    for(auto &move:moves) {
        char dir = move.first;
        int mag = move.second;
        mag= dir=='L'?mag*-1:mag;
        //cout<<mag<<endl;
        while(mag<0) {
            mag = TOTAL+mag;
        }
        current= (current+mag) %TOTAL;
        //cout<<current<<endl;
        if(current==0) ans++;
        
        
    }
    return ans;
}
//shitty solution
int makeMoves2(vector<pair<char,int>> &moves) {
    int current = START;
    int ans =0;
    //cout<<moves.size()<<endl;
    for(auto &move:moves) {
        char dir = move.first;
        int mag = move.second;
        
        if(dir=='R') {
            for(int i=0;i<mag;i++) {
                current = (current+1)%TOTAL;
                if(current ==0 ) ans++;
            }
        } 
        else {
            for(int i=0;i<mag;i++) {
                current = (current-1+TOTAL)%TOTAL;
                if(current==0) ans++;
            }
        }
       
        }
    return ans;
}
int main() {
    ifstream f("input.txt");
    if(!f.is_open()) return 1;
    vector<pair<char,int>> moves = parseInput(f);
    int ans= makeMoves2(moves);
    cout<<ans<<endl;
   
    return 0;
    
}