#include <iostream>
#include <list>
using namespace std;

#define none        0
#define empty       0
#define red         1
#define yellow      2
#define p1          false
#define p2          true

class four_in_a_row {
    public:
        int color;
        int key;
        int filled;
        four_in_a_row(int k, int c, int f){
            key = k;
            color = c;
            filled = f;
        }
};

class discs {
    public:
        int location;
        int color;
        discs(int l, int c){
            location = l;
            color = c;
        }
};

int keys [69] = {   // Horizontal Group Keys
                    210, 1155, 5005, 17017, 392863, 765049, 1363783, 2022161, 8965109, 12780049, 
                    17120443, 21182921, 56606581, 72370439, 89809099, 107972737, 204917929, 
                    257557397, 316818391, 371700317, 645328247, 739349581, 842952707, 936039509,
                    // Vertical Group Keys
                    141094, 7689623, 61112267, 303531, 11433001, 78042659, 761395, 19339433, 
                    108700951, 1283989, 24028937, 129446209, 2754169, 34301923, 160384667, 
                    3897829, 41676787, 181954753, 5709841, 50045077, 210654859,
                    // Diagonal Group Keys
                    82736309, 11740613, 106901371, 263258, 18033173, 140345129, 536007, 24834991, 
                    155004599, 1069655, 31875719, 1967623, 849961, 16546963, 1669877, 92635027, 
                    22698649, 2611349, 129583561, 33840293, 4529803, 153122363, 40394243, 172027201  };

int locs [42] = {   2,      3,      5,      7,      11,     13,     17, 
                    19,     23,     29,     31,     37,     41,     43,
                    47,     53,     59,     61,     67,     71,     73,
                    79,     83,     89,     97,     101,    103,    107,
                    109,    113,    127,    131,    137,    139,    149,
                    151,    157,    163,    167,    173,    179,    181     };

list<four_in_a_row> groups;

bool check_win(int index, int color) {
    discs *new_disc = new discs(locs[index], color);

    bool win = false;

    for(list<four_in_a_row>::iterator it = groups.begin(); it != groups.end(); it++) {
        if(it->key % new_disc->location == 0) {
            if(it->color == none || it->color == new_disc->color) {
                it->color = new_disc->color;
                it->filled++;
                if(it->filled == 4) {
                    win = true;
                }
            } else {
                it = groups.erase(it);
                it--;
            }
        }
    }

    delete new_disc;
    return win;
}

int main() {

    for(int i = 0; i < 69; i++) {
        groups.push_back(four_in_a_row(keys[i], none, empty));
    }

    bool stop = false;
    int input;
    bool player = p1;

    
    while(stop == false) {
        cin >> input;
        if(input < 0 || input > 41) {
            stop = true;
        } else {
            if(player == p1) {
                if(check_win(input, red)) {
                    cout << "p1 wins!" << endl;
                    break;
                }
            } else {
                if(check_win(input, yellow)) {
                    cout << "p2 wins!" << endl;
                    break;
                }   
            }
            player = !player;
        }
    }

    return 0;
}
