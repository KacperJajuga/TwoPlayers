#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void throwDice();                                                     //declaration of void function, which will simulate the dice throw
int firstPlayer();                                                    //declaration of int function, which contains the instructions for the first throw for player one
int secondPlayer();                                                   //declaration of int function, which contains the instructions for the first throw for player two
void nextRound();                                                     //declaration of void function, which will encapsulate the other void functions
int nextThrow(int whichPlayer);                                       //declaration of int function, which will cover the case where nobody wins on the first throw
void displayDice(int pipNumber);                                      //declaration of void function, which "graphically" displays the dice drawn
void whoWon(int didPlayer1, int didPlayer2);                          //declaration of void function, which will check which player has won, allocate the money to the appropriate person, or alternatively it will say that there was a draw. it will also display the appropriate messages
int drawnNumber1, drawnNumber2, sum;                                  //Variables used in the dice throw
int scorePlayer1, moneyPlayer1 = 100;                                 //Variables used for playera 1.
int scorePlayer2, moneyPlayer2 = 100;                                 //Variables used for playera 2.
bool theEnd;                                                          //variable checking whether the game should end
int auxiliary1, auxiliary2;                                           //variables that will facilitate the checking of the condition
int player;                                                           //auxiliary variable for the nextThrow function



int main ()
{
    srand(time(0));
    cout << setw(40) << "()()()()()()()()"<< endl;
    cout << setw(40) << "() Dice game! ()"<< endl;
    cout << setw(40) << "()()()()()()()()"<< endl;
    cout << endl;
    cout << "Game rules:" << endl;
    cout << "There are two players, each has PLN100. " << endl;
    cout << "Each rolls two dice. If during the first throw of the round the sum equals: " << endl;
    cout << "  1. 7 or 11, then that player wins, and receives PLN20 from the opponent;" << endl;
    cout << "  2. 2, 3 or 12, then that player loses, and gives the opponent PLN20; " << endl;
    cout << "  3. any other number, then that number becomes the player's score." << endl;
    cout << "     To win, a player must get the same number as their score. " << endl;
    cout << "     However, if they get 7, that player loses." << endl;
    cout << endl;
    cout << "The game lasts 10 rounds. If a player loses all their money, they lose the whole game. "<< endl;
    cout << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore();                                                                          //stopping the programme so that the user can read the rules of the game
    for(int i = 1; i <= 10; i++)                                                           //this loop will ensure that we have a maximum of 10 rounds
    {
        if (moneyPlayer1 > 0 && moneyPlayer2 > 0)                                            //checking whether the players have the money to continue playing
        {
            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------" << endl;          //Such lines make the information displayed more user-friendly
            cout << setw(40) << "Round " << i << endl;
            cout << endl;
            cout << endl;
            theEnd = 0;
            nextRound();                                                                //calling a function that binds the whole game together
            cout << "PLAYER 1's money: " << moneyPlayer1 << endl;               //displaying how much money players have left
            cout << "PLAYER 2's money: " << moneyPlayer2 << endl;
            cout << "-----------------------------------------------------------------------------------------------" << endl;
            cout << "Press Enter to continue..." << endl;
            cin.ignore();                                                                  //you can look at the round and the remaining amounts before moving on to the next round
        }
        else                                                                               //instructions that will be executed when one of the players runs out of money
        {
            cout << "One of the players loses all their money. The end." << endl;
            if(moneyPlayer1 > moneyPlayer2)
            {
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOo" << endl;
                cout << setw(40) << "oO PLAYER 1 wins Oo" << endl;
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOo" << endl;
            }
            else
            {
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOo" << endl;
                cout << setw(40) << "oO PLAYER 2 wins Oo" << endl;
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOo" << endl;
            }
            cout << "-----------------------------------------------------------------------------------------------" << endl;
            break;                                                                         //break; will break the for loop, one of the players has run out of money, so there is nothing to play for
        }
    }
    return 0;
}

void nextRound()
{
    cout << "Press Enter to roll dice for PLAYER 1." << endl;
    cin.ignore();                                                               //such lines are an illusion of interactivity, they could be absent but then all the rounds would be displayed at once, you would have to scroll to see and analyse them all
    cout << endl;
    auxiliary1 = firstPlayer();
    cout << "Press Enter to roll dice for PLAYER 2." << endl;
    cin.ignore();
    auxiliary2 = secondPlayer();
    whoWon(auxiliary1, auxiliary2);
    while(theEnd == 0)
    {
        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cout << "These are the dice of the next throw for PLAYER 1." << endl;
        player = 1;
        auxiliary1 = nextThrow(player);
        cout << endl;
        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cout << "These are the dice of the next throw for PLAYER 2." << endl;
        player = 2;
        auxiliary2 = nextThrow(player);
        whoWon(auxiliary1, auxiliary2);
    }
}

void whoWon(int didPlayer1, int didPlayer2)                            //the function takes the values returned by the functions firstPlayer, secondPlayer, and in the case of next throws of the dice - the values returned by the nextThrow function. the variables auxiliary1, auxiliary2 helped me a lot here
{
    if (didPlayer1 == 1 && (didPlayer2 == 2 || didPlayer2 == 3))           //instructions for the case where player 1 has won and player 2 has lost or failed to draw the correct number
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ PLAYER 1 wins this round. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        moneyPlayer1 +=20;
        moneyPlayer2 -=20;
        theEnd = 1;
    }
    else if ((didPlayer1 == 2 || didPlayer1 == 3) && didPlayer2 == 1)      //instructions for the case where player 2 has won and player 1 has lost or failed to draw the correct number
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ PLAYER 2 wins this round. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        moneyPlayer2 += 20;
        moneyPlayer1 -= 20;
        theEnd = 1;
    }
    else if (didPlayer1 == 2 && didPlayer2 == 3)                          //instructions for the case where player 1 loses and player 2 fails to draw any function number
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ PLAYER 2 wins this round. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        moneyPlayer2 += 20;
        moneyPlayer1 -= 20;
        theEnd = 1;
    }
    else if (didPlayer1 == 3 && didPlayer2 == 2)                          //instructions for the case where player 2 loses and player 1 fails to draw any function number
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ PLAYER 1 wins this round. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        moneyPlayer1 += 20;
        moneyPlayer2 -= 20;
        theEnd = 1;
    }
    else if ((didPlayer1 == 1 && didPlayer2 == 1) || (didPlayer1 == 2 && didPlayer2 == 2))          //instructions for the case where on the same throw of the dice both players have lost or won
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ Draw. Nobody wins this round. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        theEnd = 1;
    }
    else                                                                //instructions for the remaining cases, the case in which none of the players has thrown a functional number
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~                    Nobody wins yet.                      ~" << endl;
        cout << "~ PLAYER 1 must throw " << scorePlayer1 << " and PLAYER 2 must throw " << scorePlayer2 << " to win. ~" << endl;
        cout << "~               The one who throws 7 loses.                ~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        theEnd = 0;
    }
}

int firstPlayer()                                                              //the numbers returned by these functions allow me to determine what the case is – the player has won/lost/tied/must throw again
{
    cout << "Dice for PLAYER 1." << endl;
    throwDice();
    if ((sum == 7)||(sum == 11))                                               //winning condition for the first throw
    {
        return 1;
    }
    else if ((sum == 2) || (sum == 3) || (sum == 12))                          //losing condition for the first throw
    {
        return 2;
    }
    else                                                                       //for any other case - sums equal to 4, 5, 6, 8, 9, 10 - the following instructions will be executed
    {
        scorePlayer1 = sum;                                                    //assigning the sum value to the scorePlayer1 variable will allow to check if the next time you throw the same number
        return 3;
    }
}

int secondPlayer()                                                             //the numbers returned by these functions allow me to determine what the case is – the player has won/lost/tied/must throw again
{
    cout << "Dice for PLAYER 2." << endl;
    throwDice();
    if ((sum == 7)||(sum==11))                                                 //winning condition for the first throw
    {
        return 1;
    }
    else if ((sum == 2) || (sum == 3) || (sum == 12))                          //losing condition for the first throw
    {
        return 2;
    }
    else                                                                       //for any other case - sums equal to 4, 5, 6, 8, 9, 10 - the following instructions will be executed
    {
        scorePlayer2 = sum;                                                    //assigning the sum value to the scorePlayer2 variable will allow to check if the next time you throw the same number
        return 3;
    }
}

int nextThrow(int whichPlayer)                                                 //the numbers returned by these functions allow me to determine what the case is – the player has won/lost/tied/must throw again
{
    switch(whichPlayer)
    {
    case 1:                                                                    //the case when we check the next sum of the dice drawn for player 1
        throwDice();
        if (sum == 7)
        {
            return 2;
        }
        else if (scorePlayer1 == sum)
        {
            return 1;
        }
        else
        {
            return 3;
        }
        break;
    case 2:                                                                    //the case when we check the next sum of the dice drawn for player 2
        throwDice();
        if (sum == 7)
        {
            return 2;
        }
        else if (scorePlayer2 == sum)
        {
            return 1;
        }
        else
        {
            return 3;
        }
        break;
    default:
        cout << "HOW?!" << endl;
        break;
    }
}

void throwDice()                                                                       //function draws two numbers
{
    cout << endl;
    cout << "************************************************************************************************" << endl;
    drawnNumber1 = rand()%6+1;                                                        //draws a number from 1 to 6, rand() gives a random number, the %6 instruction makes it draw a number from 0 to 5, and +1 gives us a range from 1 to 6
    cout << "First dice: " << endl;
    displayDice(drawnNumber1);                                                        //displaying the dice according to the number drawn
    drawnNumber2 = rand()%6+1;
    cout << "Second dice: " << endl;
    displayDice(drawnNumber2);
    sum = drawnNumber1 + drawnNumber2;                                               //addition of the drawn values and assigning them to the variable sum
    cout << "Sum of pips: " << sum << endl;
    cout << "************************************************************************************************" << endl;
    cout << endl;
}

void displayDice(int pipNumber)                                                     //function displays dice according to the number drawn
{
    switch(pipNumber)
    {
    case 1:
        cout << "-----" << endl;
        cout << "|   |" << endl;
        cout << "| o |" << endl;
        cout << "|   |" << endl;
        cout << "-----" << endl;
        break;
    case 2:
        cout << "-----" << endl;
        cout << "|o  |" << endl;
        cout << "|   |" << endl;
        cout << "|  o|" << endl;
        cout << "-----" << endl;
        break;
    case 3:
        cout << "-----" << endl;
        cout << "|o  |" << endl;
        cout << "| o |" << endl;
        cout << "|  o|" << endl;
        cout << "-----" << endl;
        break;
    case 4:
        cout << "-----" << endl;
        cout << "|o o|" << endl;
        cout << "|   |" << endl;
        cout << "|o o|" << endl;
        cout << "-----" << endl;
        break;
    case 5:
        cout << "-----" << endl;
        cout << "|o o|" << endl;
        cout << "| o |" << endl;
        cout << "|o o|" << endl;
        cout << "-----" << endl;
        break;
    case 6:
        cout << "-----" << endl;
        cout << "|o o|" << endl;
        cout << "|o o|" << endl;
        cout << "|o o|" << endl;
        cout << "-----" << endl;
        break;
    default:
        cout << "How did you manage to do that?" << endl;            //the switch must have a default case, one that executes for every case other than those declared
        break;
    }
}


// I have checked the program many times, it seems to be working correctly at the moment. I think maybe it would be possible to make this program using classes, but I don't understand them very well yet.
//I tried to make the console program look as good as possible, so there are a lot of redundant (from the program correctness point of view) lines. But it made testing easier, and more user-friendly for those who don't understand the code or the console and haven't seen them before.
//Program every time player has to throw another one it displays a message how many they have to throw. This also made testing easier for me, and reminds possible players and shows them why no one won.
