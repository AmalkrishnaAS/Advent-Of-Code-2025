#include <algorithm>
#include <utility>
#define ll long long
#include <cmath>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Input {
    vector<string> lines;
};

Input parseInput(string path) {
    ifstream f(path);
    Input ip;
    string temp;
    size_t max_len = 0;

    while(getline(f, temp)) {
        ip.lines.push_back(temp);
        max_len = max(max_len, temp.size());
    }
    f.close();

    for(auto &line : ip.lines) {
        if(line.size() < max_len) {
            line += string(max_len - line.size(), ' ');
        }
    }
    return ip;
}

ll processBlock(vector<ll> &nums, char op) {
    if(nums.empty()) return 0;
    
    ll ans = (op == '+') ? 0 : 1;
    
    for(ll val : nums) {
        if(op == '+') ans += val;
        else ans *= val;
    }
    return ans;
}

ll solve2(Input input) {
    ll grand_total = 0;
    vector<string> lines = input.lines;
    if(lines.empty()) return 0;

    int width = lines[0].size();
    int height = lines.size();

    vector<ll> current_block_nums;
    char current_op = ' ';
    bool block_active = false;

    for(int x = width - 1; x >= -1; x--) {
        
        bool is_empty_col = true;
        
        if(x >= 0) {
            for(const string &line : lines) {
                if(line[x] != ' ') {
                    is_empty_col = false;
                    break;
                }
            }
        }

        if(is_empty_col) {
            if(block_active) {
                grand_total += processBlock(current_block_nums, current_op);
                current_block_nums.clear();
                current_op = ' ';
                block_active = false;
            }
            continue;
        }

        block_active = true;
        string num_str = "";
        char col_op = ' ';

        for(int y = 0; y < height; y++) {
            char c = lines[y][x];
            if(isdigit(c)) {
                num_str += c;
            } else if(c == '+' || c == '*') {
                col_op = c;
            }
        }

        if(col_op != ' ') current_op = col_op;

        if(!num_str.empty()) {
            current_block_nums.push_back(stoll(num_str));
        }
    }

    return grand_total;
}

int main() {
    Input input = parseInput("input.txt");
    ll ans = solve2(input);
    cout << ans << endl;
    return 0;
}