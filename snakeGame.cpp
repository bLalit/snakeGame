#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void initialSnake(); //Initial snake.
void inputKey();     //Takes input from the keyboard (arrow keys).
void snakeLogic();   //Logic for the snake game.
void sketchMap();    //Prints the game on the console.

#define height 25
#define width 100
#define KEY_UP 72 //This number is for the UP Arrow.
#define KEY_DOWN 80 //This number is for the DOWN Arrow.
#define KEY_LEFT 75 //This number is for the LEFT Arrow.
#define KEY_RIGHT 77 //This number is for the RIGHT Arrow.

bool tailEaten; //To check weather or not the snake has collided with its self

enum snakeDirection{stop = 0, up, down, Left, Right}; //states for the movement of the snake in four directions
snakeDirection direction;

int x, y, score, foodX, foodY, tailX[100], tailY[100], nthTail;


int main()
{
    initialSnake();

    while(!tailEaten)
    {
        sketchMap();
        inputKey();
        snakeLogic();
        //Sleep(40);
    }
    return 0;
}


void initialSnake() //This function sets the initial conditions of the game
{                   //The snake starts in the center of the map
    score = 0;
    tailEaten = false;
    direction = stop;
    x = width/2;
    y = height/2;
    foodX = rand() % width; //Random x coordinate of the location of the food
    foodY = rand() % height; //Random y coordinate of the location of the food
}

void inputKey() //This function changes the state of the direction of the snake
{               //according to the input on the console.
    if(_kbhit())
    {
        switch (_getch())
        {
            case KEY_UP:
                direction = up;
                break;

            case KEY_DOWN:
                direction = down;
                break;

            case KEY_LEFT:
                direction = Left;
                break;

            case KEY_RIGHT:
                direction = Right;
                break;

            case 'x':               //Clicking 'x' terminates the game giving the current score.
                tailEaten = true;
                break;

        }
    }
}

void snakeLogic()
{
    int nextX,nextY,nextNextX,nextNextY;
    nextX = tailX[0];   //When the snake consumes new food, it is updated to the head of the snake
    nextY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;

    for(int i=1; i<nthTail ; i++) //This for loop updates the snake array every time it consumes food
    {                             //It moves each of the previous tails added by 1 position to add a new one to the head.
        nextNextX = tailX[i];
        nextNextY = tailY[i];
        tailX[i] = nextX;
        tailY[i] = nextY;
        nextX = nextNextX;
        nextY = nextNextY;
    }

    switch (direction) //Here the coordinates of the the head of the snake is calculated after every step
    {                   //This is done by assuming the top left corner of the console as (0,0)
        case up:
            y--;
            break;

        case down:
            y++;
            break;

        case Left:
            x--;
            break;

        case Right:
            x++;
            break;

        default:
            break;
    }

    if(x>=width) //If the snake goes beyond bounds in x direction
        x=0;
    else if(x<0)
        x=width-1;

    if(y>=height) //If the snake goes beyond bounds in y direction
        y=0;
    else if(y<0)
        y=height-1;

    for(int i=0 ; i<nthTail ; i++) //If the snake collides with its self, the game ends
    {
        if(tailX[i]==x && tailY[i]==y)
            tailEaten = true;
    }

    if(x==foodX && y==foodY) //every time a food is consumed, the score is updated and the tail is incremented
    {                           //A new random location for the next food is generated
        score += 1;
        foodX = rand() % width;
        foodY = rand() % height;
        nthTail++;
    }


}

void sketchMap()
{
    system("cls"); //refreshes the screen before every updated world is drawn.

    cout<<"USE ARROW KEYS TO CONTROL THE SNAKE"<<endl;

    for(int i=0 ; i<width+2 ; i++) //Draws the top side of the border
    {
        cout<<"-";
    }
    cout<<endl;

    for(int i=0 ; i<height ; i++) //This nested for loop scans the entire map from the top left to the bottom right,
    {                             //and prints the most updated position of the snake and food.
        for(int j=0 ; j<width ; j++)
        {
            if(j==0)    //prints the right side border
                cout<<"|";
            if(i==y && j==x) //Head of the snake
                cout<<"S";
            else if(i==foodY && j==foodX) //location of the food
                cout<<"F";
            else
            {
                bool print = false;
                for(int k=0 ; k<nthTail ; k++) //prints all the tails of the snake in series
                {
                    if(tailY[k]==i && tailX[k]==j)
                    {
                        cout<<"s";
                        print = true;
                    }
                }
                if(!print) //if there is no tail, it prints " "
                    cout<<" ";
            }
            if(j==width-1) //prints the right side of the border
                cout<<"|";
        }
        cout<<endl;
    }

    for(int i=0 ; i<width+2 ; i++) //prints the bottom side of the border
            cout<<"-";
    cout<<endl;
    cout<<"The Score is = "<<score<<endl;
}

