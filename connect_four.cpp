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
    Player(int num = 0, int pos = 0){   // constructor
        playernum = num;
        position = pos;
    }

    virtual int pickslot(){             // chosen by user
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

    virtual int pickslot(){             // chosen at random

        cout << "Pick a slot to drop your piece (1-7)" << endl;

        position = rand() % 7+1;

        cout << "CPU picks " << position << endl;

        return position;
    }

    virtual int playernumber(){
        return playernum;
    }
};

class Board{
public:

    array<char,43> locations;      // 1D array that represents 2D board     
    array<int,7> slotcount;

    Board(){                    // initialize board to be empty
        locations.fill('_');
        slotcount.fill(0);
    }

    void printboard() {

        cout << " 1 2 3 4 5 6 7" << endl;
        for (int k=35; k>=0; k-=7){        

            cout << "|";
            for (int i=1; i<=7; i++){ 
                cout << locations[i+k] << "|";
            }
            cout << endl;
        }

        return;
    }

    int dropdisc(int slot, Player *px) {

        while(slotcount[slot-1]>5){         // make sure column isnt full
            cout << "Please choose a different column" << endl;
            slot = px->pickslot();
        }

        int boardloc=slotcount[slot-1]*7 +slot;
        slotcount[slot-1]++;

        return boardloc;            // returns location of piece on 1D array
    }

    bool board_full(){

        for( int i=0; i<7; i++ ){
            if(slotcount[i] < 6){       // check if each column is full
                return false;
            }
        }
        // if statement not accessed, all columns must be full
        return true;
    }
};

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

ostream & operator << (ostream &out, Board board){   // overload cout
    board.printboard();
    return out;
}

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

    // iterate thru groups list
    for(list<four_in_a_row>::iterator it = groups.begin(); it != groups.end(); it++) {
        if(it->key % new_disc->location == 0) {

            if(it->color == none || it->color == new_disc->color) {
                it->color = new_disc->color;
                it->filled++;

                if(it->filled == 4) {
                    win = true;
                }
            } 
            else {
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

    Board board; 
    cout << board;                  // print empty board
    
    int winner = 0;

    while(1){                       // start game loop
        
        cout << "Player One: ";
        int slot = p1->pickslot();          // player chooses slot

        int boardloc = board.dropdisc(slot, p1);    // update board
        board.locations[boardloc]='x';
        
        if( check_win( boardloc-1, p1->playernumber() ) ){  // win?
            winner = p1->playernumber(); 
            break;
        }

        if(board.board_full()){         // check if board is full
            winner = 3;
            break;
        }

        cout << board;
        
        cout << "Player Two: ";         // repeat above for p2
        slot = p2->pickslot();

        boardloc = board.dropdisc(slot, p2);
        board.locations[boardloc]='o';
        
        if( check_win( boardloc-1, p2->playernumber() ) ){
            winner = p2->playernumber();
            break;
        }

        if(board.board_full()){
            winner = 3;
            break;
        }

        cout << board;
    }

    if (winner == 3){           // only accessed if tie game
        cout << board;
        cout << "Tie Game!" << endl;
        return 0;
    }
        
    // game is over, print winner and board
    cout << "Congratulations Player " << winner
        << ", You Win!" << endl << board << endl;

    return 0;
}
