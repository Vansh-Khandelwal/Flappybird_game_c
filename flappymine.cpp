#include <iostream> 
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;


int check[30][21];  //variable for checking
int highscore=0;  //variable to compare the highscore
int jumpkey=0,score=0,t=0,birdx=0,birdy=0; //variaous variables for various operations
bool error; //boolean for error detection whether the fikle is openining or not

void game();  //function for the game
bool gameover(); //detecting contact between bird and pipe
void checkscore(); //check the score
void pipes();  //to display the obstacles and move them
void bird();   //to change the postion of the bird
void screen(); //to display the screen 
void menu(); //display the starting menu
void end(); //display the end menu
void credits(); //display the credits


int main()
{
    srand(time(0));  

    int a=0,b;
    char sl; 
    while(1) 
    {
        if(a==0) goto play; 
        if(a>0)               
        {
            score=0;
            cout<<"Do you want to play again? [y/n] ";
            cin>>sl;
            if(sl=='n') goto quit;
            else goto play;
        }
        play:
        menu(); 
        cin>>sl;
        switch(sl) //selecting option from the menu
        {
            case '1':
            {
                game(); 
                break;
            }
            case '2':
            {
                credits();
                goto play;
                break;
            }
            case '3':
            {
                goto quit; 
                break;
            }
            default:
            {
                goto play;
                break;
            }
        }
        a++; //variable for checking how many times you've played
    }
    quit:
    {
    cout<<"Quiting game ..."; 
    }

    return 0;
}

void screen() 
{
    int x,y;
    clrscr();
    for(y=0;y<21;y++) // shows the game screen 
    {
        for(x=0;x<30;x++)
        { 
            cout<<sp[x][y];
        }
        cout<<"\n";
    }
    cout<<""<<endl;
    cout<<"Your Score: "<<score;
}

void pipes() 
{
    int x, y, r;
    if (t == 10) //if time is 10, or loop has passed 10 times, it spawns a new pipe
    {
        r = (rand() % 11) + 5;   //generates random number, which will be the pipe's hole center
        for (y = 0; y < 20; y++) // only y coordinate is needed
        {
            sp[29][y] = '|';  //sets obstacle/pipe
            check[29][y] = 2;    //n will be 2, wherever '|' is present
        }
        sp[29][r - 1] = ' '; //sets hole
        sp[29][r] = ' ';
        sp[29][r + 1] = ' ';
        check[29][r - 1] = 0;
        check[29][r] = 0;
        check[29][r + 1] = 0;
        t = 0;
        goto moveobstacles; 
    }
    else
        goto moveobstacles;
    moveobstacles: 
    {
        for (y = 0; y < 20; y++) //loops for generating coordinates
        {
            for (x = 0; x < 30; x++)
            {
                if (sp[x][y] == '|') //All pipes moved to left by 1
                {
                    if (x > 0)
                    {
                        sp[x - 1][y] = '|';
                        check[x - 1][y] = 2;
                        sp[x][y] = ' ';
                        check[x][y] = 0;
                    }
                    if (x == 0) //if screen ends (x=0) pipe will dissapear, to prevent errors
                    {
                        sp[x][y] = ' ';
                        check[x][y] = 0;
                    }
                }
            }
        }
    }
}

void bird() 
{
    int x, y;
    if (jumpkey > 0) //if key is pressed, bird moves up
    {
        for (y = 0; y < 20; y++) //loops for finding bird coordinates
        {
            for (x = 0; x < 30; x++)
            {
                if (sp[x][y] == '*')
                {
                    if (y > 0)
                    {
                        sp[x][y - 1] = '*'; //bird moves up by 1;
                        sp[x][y] = ' ';
                        birdx = x;     //sets bird x coordinate
                        birdy = y - 1; //sets bird y coord
                        return;        //retuns to game func
                    }
                }
            }
        }
    }
    else //if no key is pressed, bird falls
    {
        for (y = 0; y < 20; y++)
        {
            for (x = 0; x < 30; x++)
            {
                if (sp[x][y] == '*')
                {
                    if (y < 20) //if bird is not on the ground
                    {
                        sp[x][y + 1] = '*';
                        sp[x][y] = ' ';
                        birdx = x;
                        birdy = y + 1;
                        return;
                    }
                    else
                    {
                        return; //if bird is already on the ground, function returns to check for game over.
                    }
                }
            }
        }
    }
}

void checkscore()  
{
    for(int y=0;y<20;y++)
    {
        if(sp[birdx][y]=='|')  //if bird x coord is equal to pipe's coord, you get 1 point
        {
            score++;
            return;
        }
    }
}

bool gameover() 
{
    int x, y, f = 0;
    if (birdy > 19) //checks if bird hits ground
    {
        sp[birdx][19] = '*'; 
        sp[birdx][20] = '-';
        f = 1; 
        goto quit;
    }
    else
    {
        if (check[birdx][birdy] > 0 ) //check if birds has hit the obstacle 
        {
            sp[birdx][birdy] = '|';
            sp[birdx - 1][19] = '*';
            f = 1;
            goto quit;
        }
    }
    quit:
        if (f == 1)
            return true;
        else
            return false;
}

void end() 
{
    screen();  
    cout<<""<<endl<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<"|    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
    cout<<"|   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
    cout<<"|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
    cout<<"|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |"<<endl;
    cout<<"|    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                        Y O U R   S C O R E : "<<score<<endl<<endl;
    cout<<"                        H I G H   S C O R E : "<<highscore<<endl;
    cout<<""<<endl<<endl;
}

void menu() 
{
    clrscr();
    cout<<""<<endl;
    cout<<" --------------------------------------------------------  "<<endl;
    cout<<"|                                                        | "<<endl;
    cout<<"|   **** *    **** **** **** *   *    ***  * ***  ***    | "<<endl;
    cout<<"|   *    *    *  * *  * *  * *   *    *  * * *  * *  *   | "<<endl;
    cout<<"|   ***  *    **** **** **** *****    ***  * ***  *  *   | "<<endl;
    cout<<"|   *    *    *  * *    *      *      *  * * *  * *  *   | "<<endl;
    cout<<"|   *    **** *  * *    *      *      ***  * *  * ***    | "<<endl;
    cout<<"|                                                        | "<<endl;
    cout<<" --------------------------------------------------------  "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                  High Score:  "<<highscore<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"                     M E N U:    "<<endl<<endl;
    cout<<"                  1: Start Game  "<<endl<<endl;
    cout<<"                  2: Credits     "<<endl<<endl;
    cout<<"                  3: Exit        "<<endl<<endl;
}

void credits()
{
    char sel;
    clrscr();
    while(true)
    {
    cout<<""<<endl<<endl;
    cout<<"               Programmers: Tejas Sharma(2K20/A15/36) and Vansh Khandelwal(2K20/A15/49)"<<endl<<endl;
    cout<<"     Go back? [y/n]  ";
    cin>>sel;
    if(sel=='y') return;
    else system("cls");
    }
}

void game() //function for playing game
{
    int x, y;
    char s;
    for (y = 0; y < 21; y++) //setting screen
    {
        for (x = 0; x < 30; x++)
        {
            if (y < 20)
            {
                sp[x][y] = ' ';
                check[x][y] = 0;
            }
            if (y == 20)
            {
                sp[x][y] = '-';
                check[x][y] = 2;
            }
        }
    }
    sp[10][10] = '*'; //in these coordinates will be our bird, marked *
    screen();         //calls func for showin screen
    while (1)         
    {
        s = '~';          //default control variable
        Sleep(10); //this sets how fast everyhing moves
        t++;              //this is a variable for storing 'time',or how many times a loop passed
        if (kbhit())      //if key is pressed, certain operations are done for bird to move up.
        {
            s = getch(); //gets what key is pressed
            if (s != '~')
                jumpkey = 1; 
        }
        for (x = 0; x < 30; x++) //setting ground
        {
            sp[x][20] = '-';
            check[x][20] = 2;
        }

        bird();       
        checkscore();

        if (gameover() == true)
            goto gameEnd; 

        pipes();      

        if (score > highscore)
            highscore = score; 

        screen();        

        if (jumpkey > 0)
            jumpkey++; //if key is pressed, bird will fly up 2 times.
        if (jumpkey == 3)
            jumpkey = 0; //after that, bird falls
    }
    gameEnd: 
    {
        if (score > highscore)
            highscore = score;

        screen(); //shows ending screen, and returns to int main
        end();
        return;
    }
}