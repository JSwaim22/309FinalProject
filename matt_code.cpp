#include <iostream>
#include <vector>
#include <array>



using namespace std;


int dropdisc(int slot, array<int,7>& slotcount) {

    int boardloc=42;

    boardloc=slotcount[slot-1]*7 +slot;
    slotcount[slot-1]++;

    return boardloc;
}


void printboard(array<char,43> board) {

    cout<<" 1 2 3 4 5 6 7"<<endl;
    for (int k=35;k>=0;k-=7){


        cout<<"|";
        for (int i=1; i<=7; i++){ cout<<board[i+k]<<"|";}
        cout<<k/7<<endl;

    }

    return;
}


int main() {

    char line='|';

    int player=1;
    int slot=8;
    int boardloc=42;

    array<char,43> board; board.fill('_');
    array<int,7> slotcount; slotcount.fill(0);
    vector<int> xpos;
    vector<int> opos;

    printboard(board);



    for (int i=0; i<14;i++){
        slot=8;
        while(slot<0 || slot >7){
            cout<< "player "<<player<< "enter a number:";
            cin>>slot;
            if(slotcount[slot-1]>5) {slot=8;}
        }

        boardloc=dropdisc(slot,slotcount);      cout<<"slot|slotcount|boardloc:  "<<slot<<line<<slotcount[slot-1]<<line<<boardloc<<endl;
        if(player==1) {
            xpos.push_back(boardloc);
            board[boardloc]='x';
            player=2;
        }
        else {
            opos.push_back(boardloc);
            board[boardloc]='o';
            player=1;
        }

        printboard(board);

    }



    return 0;
}
