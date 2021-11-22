#include <iostream>

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
        srand(time(0));

        position = rand() % 7+1;

        return position;
    }

    virtual int playernumber(){
        return playernum;
    }
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

    while(gm < 1 || gm > 3){                        // make sure 1-3
        cout << "Please Enter 1, 2, or 3" << endl;
        cin >> gm;
    }

    
    Player* p1;
    Player* p2;
    
    
    if(gm == 1){                    // Player vs Player
        
        Player player1(1,0);    // create player 1 and assign to p1
        p1 = &player1;

        Player player2(2,0);    // create player 2
        p2 = &player2;

    }

    
    if(gm == 2){                    // Player vs CPU
        
        Player player1(1,0);
        p1 = &player1;

        ConsolePlayer player2(2,0);     // create player 2 as a console player
        p2 = &player2;

    }

    if(gm == 3){                    // CPU vs CPU
        
        ConsolePlayer player1(1,0);
        p1 = &player1;

        ConsolePlayer player2(2,0);
        p2 = &player2;

    }
    
    /*                          test code i set up to make sure functions work. can be deleted later
    cout << "Player 1" << endl
        << "Player Number: \n" << p1->playernumber() << endl
        << "Slot Number: \n" << p1->pickslot() << endl;
    
    
    cout << "Player 2" << endl
        << "Player Number: \n" << p2->playernumber() << endl
        << "Slot Number: \n" << p2->pickslot() << endl;

    */
    
    /*              explanation of functions
        pX->pickslot() prompts player to pick slot or randomizes
        pX->playernumber() returns 1 or 2 for player number
    */

    int winner = 0;

    while(1){       // example main code

        int slot = p1->pickslot();

        //updateboard

        // update groups
        // check win condition
            // if win == true, set winner = player1
            // break

        // display board
        
        slot = p2->pickslot();

        //updateboard

        // update groups
        // check win condition
            // if win == true, set winner = player2
            // break

        // display board

    }

    // display winning board
    cout << "Congratulations Player " << winner 
        << ", You Win!" << endl;


    return 0;
}
