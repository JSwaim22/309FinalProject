#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Player{
public:

    


};


// Console player object? inheritance?


class Board{
public:
    // make array for board


    //void PrintBoard(int pos, Player plyr)

    

    


};





int main()
{
    // game mode
    cout << "Please select game mode:\n"
        "Player vs Player - Enter '1'\n"
        "Player vs CPU - Enter '2'\n"
        "CPU vs CPU - Enter '3'" << endl;

    int gm;
    cin >> gm;

    if(gm < 1 || gm > 3) {
        cout << "Game Over!" << endl;
        return 0;
    }

    if(gm == 1){                    // Player vs Player

    Player One, Two;



    }

    if(gm == 2){                    // Player vs CPU



    }

    if(gm == 3){                    // CPU vs CPU



    }


    return 0;
}
