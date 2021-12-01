#include <iostream>
#include <array>
#include <vector>
#include <list>

#define none        0
#define empty       0
#define red         1
#define yellow      2

using namespace std;


class Player{
private:
    int playernum;          // way to discern p1 or p2
    int position;           // must be 1-7
    
public:
    Player(int num = 0, int pos = 0){
        playernum = num;
        position = pos;
    }

    virtual int pickslot(){
        cout << "Pick a slot to drop your piece (1-7)" << endl;

        cin >> position;

        while(position < 1 || position > 7){          // make sure 1-7
            cout << "Please Enter a Number 1-7" << endl;
            cin >> position;
        }

        return position;
    }

    virtual int playernumber(){
        return playernum;
    }

};

class ConsolePlayer : public Player{
private:
    int playernum;          // way to discern p1 or p2
    int position;           // must be 1-7

public:
    ConsolePlayer(int num = 0, int pos = 0){
        playernum = num;
        position = pos;
    }

    virtual int pickslot(){

        cout << "Pick a slot to drop your piece (1-7)" << endl;

        position = rand() % 7+1;

        cout << "CPU picks " << position << endl;

        return position;
    }

    virtual int playernumber(){
        return playernum;
    }
};


void printboard(array<char,43> board) {

    cout << " 1 2 3 4 5 6 7" << endl;
    for (int k=35; k>=0; k-=7){

        cout << "|";
        for (int i=1; i<=7; i++){ 
            cout << board[i+k] << "|";
        }
        cout<<k/7<<endl;

    }

    return;
}

int dropdisc(int slot, array<int, 7>& slotcount) {

    int boardloc=42;

    boardloc=slotcount[slot-1]*7 +slot;
    slotcount[slot-1]++;

    return boardloc;
}


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

int keys [69] = {   
    // Horizontal Group Keys
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
    22698649, 2611349, 129583561, 33840293, 4529803, 153122363, 40394243, 172027201  
};

int locs [42] = {   
    2,      3,      5,      7,      11,     13,     17, 
    19,     23,     29,     31,     37,     41,     43,
    47,     53,     59,     61,     67,     71,     73,
    79,     83,     89,     97,     101,    103,    107,
    109,    113,    127,    131,    137,    139,    149,
    151,    157,    163,    167,    173,    179,    181     
};

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


int main()
{
    srand(time(0));
    // set groups
    for(int i = 0; i < 69; i++) {
        groups.push_back(four_in_a_row(keys[i], none, empty));
    }

    // game mode
    cout << "Please select game mode:\n"
        "Player vs Player - Enter '1'\n"
        "Player vs CPU - Enter '2'\n"
        "CPU vs CPU - Enter '3'" << endl;

    int gm;
    cin >> gm;

    while(gm < 1 || gm > 3){                  // make sure 1-3
        cout << "Please Enter 1, 2, or 3" << endl;
        cin >> gm;
    }

    Player* p1;
    Player* p2;
    
    if(gm == 1){                    // Player vs Player
        
        Player player1(1,0);
        p1 = &player1;

        Player player2(2,0);
        p2 = &player2;

    }
  
    if(gm == 2){                    // Player vs CPU
        
        Player player1(1,0);
        p1 = &player1;

        ConsolePlayer player2(2,0);
        p2 = &player2;

    }

    if(gm == 3){                    // CPU vs CPU
        
        ConsolePlayer player1(1,0);
        p1 = &player1;

        ConsolePlayer player2(2,0);
        p2 = &player2;

    }

    array<char,43> board;           // initialize board to be empty
    board.fill('_');

    int slot;
    array<int,7> slotcount; 
    slotcount.fill(0);

    vector<int> xpos;
    vector<int> opos;

    printboard(board);              // print empty board

    
    int winner = 0;

    while(1){                       // start game loop
        
        cout << "Player One: ";
        
        slot=8;
        while(slot<1 || slot>7) {
            slot = p1->pickslot();
            if(slotcount[slot-1]>5) {slot=8;}
        }
            
        int boardloc = dropdisc(slot,slotcount);

        // update player 1
        xpos.push_back(boardloc);
        board[boardloc]='x';
        
        if( check_win( boardloc-1, p1->playernumber() ) ){
            winner = p1->playernumber();
            break;
        }


        printboard(board);
        
        cout << "Player Two: ";
        
        slot=8;
        while(slot<1 || slot>7) {
            slot = p2->pickslot();
            if(slotcount[slot-1]>5) {slot=8;}
        }

        boardloc = dropdisc(slot,slotcount);

        // update player 2
        opos.push_back(boardloc);
        board[boardloc]='o';
        
        if( check_win( boardloc-1, p2->playernumber() ) ){
            winner = p2->playernumber();
            break;
        }

        printboard(board);
        
    }

    // we're in the end game now
    cout << "Congratulations Player " << winner
        << ", You Win!" << endl;

    printboard(board);

    return 0;
}
