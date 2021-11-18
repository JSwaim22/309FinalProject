#include <iostream>
#include <list>
using namespace std;

#define none        0
#define empty       0
#define red         1
#define yellow      2

//  Prime Locations
#define a1          2
#define a2          19
#define a3          47
#define a4          79
#define a5          109
#define a6          151

#define b1          3
#define b2          23
#define b3          53
#define b4          83
#define b5          113
#define b6          157

#define c1          5
#define c2          29
#define c3          59
#define c4          89
#define c5          127
#define c6          163

#define d1          7
#define d2          31
#define d3          61
#define d4          97
#define d5          131
#define d6          167

#define e1          11
#define e2          37
#define e3          67
#define e4          101
#define e5          137
#define e6          173

#define f1          13
#define f2          41
#define f3          71
#define f4          103
#define f5          139
#define f6          179

#define g1          17
#define g2          43
#define g3          73
#define g4          107
#define g5          149
#define g6          181


//  Prime Products
#define hor1_1      0
#define hor1_2      1
#define hor1_3      2
#define hor1_4      3
#define hor2_1      4
#define hor2_2      5
#define hor2_3      6
#define hor2_4      7
#define hor3_1      8
#define hor3_2      9
#define hor3_3      10
#define hor3_4      11
#define hor4_1      12
#define hor4_2      13
#define hor4_3      14
#define hor4_4      15
#define hor5_1      16
#define hor5_2      17
#define hor5_3      18
#define hor5_4      19
#define hor6_1      20
#define hor6_2      21
#define hor6_3      22
#define hor6_4      23

int keys [69] = { 210, 1155, 5005, 17017, 392863, 765049, 1363783, 2022161, 8965109, 12780049, 
                17120443, 21182921, 56606581, 72370439, 89809099, 107972737, 204917929, 257557397,
                316818391, 371700317, 645328247, 739349581, 842952707, 936039509 };

class four_in_a_row {
    private:

    public:
        int color;
        int key;
        int filled;
        four_in_a_row(int k, int c, int f){
            key = k;
            color = c;
            filled = f;
        }

        ~four_in_a_row() {
            cout << "not an option" << endl;
        }
};

class discs {
    private:

    public:
        int location;
        int color;
        discs(int l, int c){
            location = l;
            color = c;
        }
};

int main() {

    list<four_in_a_row> groups;
    list<discs> pieces;

    for(int i = hor1_1; i <= hor6_4; i++) {
        groups.push_back(four_in_a_row(keys[i], none, empty));
    }

    cout << groups.front().key << endl;

    pieces.push_back(discs(a1, red));

    if(groups.front().key % pieces.front().location == 0) {
        if(groups.front().color == none) {
            groups.front().color = pieces.front().color;
            groups.front().filled++;
        } else if(groups.front().color == pieces.front().color) {
            groups.front().filled++;
        } else {
            groups.pop_front();
        }
    }

    cout << "Hello World!" << groups.front().color << endl;

    return 0;
}