//snakes should not eat fruits as they are carnivores and their digestive system isn't meant for fruits xD
//put opposite control as to a s d w != left down right up; increase the difficulty
#include<iostream>
#include<time.h> //for srand
#include<stdlib.h> //for system("cls")
#include<conio.h> //for _kbhit, _getch
#include<windows.h> //for sleep
using namespace std;


bool exit_key; //Bool variable to mark the start & stop of the game.

const int height = 15; //Game-screen resolution.
const int width = 45;

int x, y; //Variables for Snake's head's position.
int target_x, target_y; //Variables for the target's position.
int score; //Variable to store points each time snake eats the target.

enum direction {snake_i=0, Left, Right, Up, Down}; //User-defined data type to hold the direction of the snake
direction dir; //Variable to hold the direction of the snake

int tail_size = 0; //Initially Snake's size = its head
//Max size of Snake = 100
int tail_x [100]; //Array to increment & keep storing Snake's tail's x-coordinate
int tail_y [100]; //Array to increment & keep storing Snake's tail's y-coordinate


void Initialize() //Function to initialize the game (default values and stuff)
{
    exit_key = false; //Game not started yet
    dir = snake_i; //Initial position of Snake. 0 means it has not started moving yet

    //Supposing snake starts from the top-left corner of the game-screen
    x = 3;
    y = 1;

    //We want our target to get created anywhere randomly
    srand(time(NULL));
    target_x = rand() % (width-2+1) +2; //This will generate x-coordinate for the target randomly with limit [2-width]
    target_y = rand() % height ; //This will generate y-coordinate for the target randomly with limit [0-height)

    score = 0; //Initially, the player's score will be = 0

}

void console_draw() //Function to print the console screen, snake and target
{
    system("cls"); //To clear the console screen and prevent it from flickering

    cout<<"\t\n\t\t  ZzzNAKE GAME!\n";
    //Game screen borders
    cout<<"  "; //2 spaces
    for(int i=1; i<width; i++) //top
        cout<<"_";
    cout<<"\n";

    for(int i=0; i<height; i++) //left & right //y-axis
    {
        for(int j=0; j<width; j++) //x-axis
        {
            if(j==1) //left wall
                cout<<"|";

            if(i == y  && j == x)
                cout<<"Z"; //print the snake's head

            else if(i == target_y && j == target_x )
                cout<<"T"; //print the target

            else //Print Snake's tail
            {
                bool print = false; //Boolean variable to keep track whether to print space or Snake's tail b/e the left and right walls
                for(int k=0; k<tail_size; k++)
                {
                    if(tail_x[k] == j && tail_y[k] == i)
                    {
                        cout<<"z";
                        print=true;
                    }
                }
                if(print != true)
                    cout<<" ";
            }

            if(j == width-1) //right wall
                cout<<"|";
        }
        cout<<"\n";
    }

    cout<<"  ";// 2 spaces
    for(int i=1; i<width; i++) //bottom
        cout<<"_";
    cout<<"\n"<<"\n";
    cout<<"\t\t    SCORE: "<<score<<endl;
}

void input() //Function to get the snake's direction input from the user (controlz)
{
    if(_kbhit() == true) //A key has been pressed
    {
        switch(_getch()) //To get the ASCII value of the character pressed
        {
            case 'j':
            case 'J':
                {
                    dir = Left; //For the Snake to turn/move in left direction
                    break;
                }

            case 'l':
            case 'L':
                {
                    dir = Right; //For the Snake to turn/move in right direction
                    break;
                }

            case 'i':
            case 'I':
                {
                    dir = Up; //For the Snake to turn/move in upward direction
                    break;
                }

            case 'k':
            case 'K':
                {
                    dir = Down; //For the Snake to turn/move in downward direction
                    break;
                }
            case 'x':
            case 'X':
                {
                    exit_key=true; //Exit the game
                    break;
                }
        }
    }

}

void logix() //Function to move the snake according to the direction & keep creating its tail
{
    int prev_x = tail_x[0]; //Variable to store tail's previous x-coordinate
    int prev_y = tail_y[0]; //Variable to store tail's previous y-coordinate
    tail_x[0] = x; //Setting the first tail element to follow the head (x-coordinate)
    tail_y[0] = y; //Setting the first tail element to follow the head (y-coordinate)

    int prev2_x,prev2_y;

    for(int i=1; i<tail_size; i++)
    {
        prev2_x = tail_x[i];
        prev2_y = tail_y[i];

        tail_x[i] = prev_x;
        tail_y[i] = prev_y;

        prev_x = prev2_x;
        prev_y = prev2_y;
    }

    switch (dir)
    {
        case Left:
            x--;
            break;

        case Right:
            x++;
            break;

        case Up:
            //Sleep(15); //to balance the irregularity in speed of snake's movement in the upwards & downwards direction
            y--; //not y++ because our j & y index are starting from 0 and not from the last index i.e. height-1
            break;

        case Down:
//            Sleep(15);
            y++; //not y-- because our j & y index are starting from 0 and not from the last index i.e. height-1
            break;

        default: //wrong input (neither 'x' nor 'AWSD')
            break;
    }

    /*
    if(x>width || x<0 || y>height || y<0) //Exit if Snake hits the wall
        exit_key = true;
    */

    //To pass through the wall & decrease the difficulty level
    if(x>=width)
        x=1;
    else if(x<=0)
        x=width-1;
    if(y>=height)
        y=0;
    else if(y<0)
        y=height-1;

    for(int i=0; i<tail_size; i++)
    {
        if(tail_x[i] == x  && tail_y[i] == y) //If Snake's bites its own tail then end the game
        {
            for(int temp1=0; temp1 <= width/2; temp1++)
            {
                for(int temp2=0; temp2 <= height/2; temp2++)
                {
                    if(temp1 == width/2 && temp2 == height/2)
                        cout<<"\n\t#--Oopz! The Snake bit itself!--#\n\n\t\t    GAME OVER!\n\n";
                }
            }
            exit_key = true;
        }

    }

    if(x == target_x && y == target_y) //Increase score & size of Snake if it eats the target
    {
        score+=10;
        target_x = rand() % (width-2+1) +2; //Reallocate target
        target_y = rand() % height ;
        tail_size+=1;
    }
}




int main ()
{
    Initialize();
    while(exit_key != true)
    {
        console_draw();
        input();
        logix();
        Sleep(10);
    }
    return 0;
}
