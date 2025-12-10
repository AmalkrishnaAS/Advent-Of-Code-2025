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

ll rows=0,cols=0;

vector<pair<ll, ll>> parseInput(string path) {
    ifstream f(path);
    vector<pair<ll, ll>> ans;
    string line;
    
    while(getline(f,line)) {
        stringstream ss(line);
        int splitind = line.find(',');
        ll first = stoll(line.substr(0,splitind));
        rows= max(rows,first+2);
        ll second= stoll(line.substr(splitind+1));
        cols=max(cols,second+2);
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
            
            ll l = abs(p1.first-p2.first)+1;
            ll b=abs(p1.second-p2.second)+1;
            //if(minMaxEdge>l && minMaxEdge>b) continue;
            //minMaxEdge = max(min(l,b),minMaxEdge);
            ans= max(ans,l*b);
            
        }
    }
    return ans;
    
}

void printGrid(vector<vector<char>> grid) {
    for(auto i:grid) {
        cout<<endl;
        for(auto j:i) {
            cout<<j<<" ";
        }
    }
}

void floodFill(vector<vector<char>> &grid,ll r,ll c) {
    //base case;
    if(r>=rows || r<0 || c>=cols || c<0 ) return;
   
   if(grid[r][c] !='.') return;
   grid[r][c] = 'O'; // <--- You forgot this!
   floodFill(grid, r + 1, c);
   floodFill(grid, r - 1, c);
    floodFill(grid, r, c + 1);
    floodFill(grid, r, c - 1);
   
}

vector<vector<char>> makeGrid(vector<pair<ll, ll>> &tiles ) {
    vector<vector<char>> grid(rows,vector<char>(cols,'.'));
    //set hashes
    for(auto &p:tiles) {
        grid[p.first][p.second] = '#';
        
    }
    
    for(int i=0;i<tiles.size();i++) {
        pair<ll, ll> p1=tiles[i];
        pair<ll, ll> p2=tiles[(i+1)%tiles.size()];
        
        //same row
        if(p1.first==p2.first) {
            ll x=p1.first;
            ll start=min(p1.second,p2.second);
            ll end = max(p1.second,p2.second);
            
            for(ll y=start+1;y<=end;y++) {
                grid[x][y]='x';
            }
        }
        else if (p1.second == p2.second) {
                    // Horizontal Line (Same Y, changing X)
                    ll y = p1.second;
                    ll start = min(p1.first, p2.first);
                    ll end = max(p1.first, p2.first);
        
                    for (ll x = start ; x <= end; ++x) {
                         grid[x][y] = 'x';
                    }
                }
    }
   floodFill(grid,0,0);
   
   for(auto &row:grid) {
       for(auto &el:row) {
           if(el=='.') el='x';
           else if(el=='O') el='.';
       }
   }
    
    return grid;
}

ll solve2(vector<vector<char>> &grid,vector<pair<ll, ll>> &tiles) {
    ll ans=0;
   for(int i =0;i<tiles.size()-1;i++) {
       for(int j=i+1;j<tiles.size();j++) {
           if(grid[tiles[i].first][tiles[j].second]=='.' || grid[tiles[j].first][tiles[i].second] =='.') continue;
           else {
               ll l=abs(tiles[i].first-tiles[j].first)+1;
               ll b=abs(tiles[i].second-tiles[j].second)+1;
               ans= max(ans,l*b);
               
           }
       }
   }
   return  ans;
}
int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
        // 2. Run your logic
        vector<pair<ll, ll>> tiles = parseInput("input.txt");
        vector<vector<char>> grid = makeGrid(tiles);
        ll ans = solve2(grid, tiles);
    
        // 3. Stop the timer
        auto stop = std::chrono::high_resolution_clock::now();
    
        // 4. Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
        // 5. Output results
        cout << "Answer: " << ans << endl;
        cout << "Time taken: " << duration.count() << " ms" << endl;
    
        return 0;
}