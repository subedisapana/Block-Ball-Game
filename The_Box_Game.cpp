#include <graphics.h>
#include <iostream>
using namespace std;
#include <conio.h>
#include <string.h>
#include <sstream>
#include <fstream>

int k = 0;
int score = 0;
int lives = 3;
int level = 2;
int high_score;
int prev_score;

class circles
{

    public:
        int x;
        int y;
        circles()
        {
            x = getmaxx() - 7;
            y = rand() % (getmaxy() - 7) + 7;
        }
        void move_circles(int r_x, int r_y)
        {
            if(x >= 0)
            {
                fillellipse(x, y, 7, 7);
                x -= level;

                ///Increasing the levels of the game:///
                if(k >=0 && k < 7)  level = 3;
                else if(k >=7 && k < 12)    level = 4;
                else if(k >= 12 && k < 17)   level = 5;
                else if(k >= 17 && k < 25)   level = 6;
                else    level = 8;

                if(x <= 50)
                {
                    if(y >= r_x && y <= r_y)
                    {
                        score++;
                        x = -500;
                    }
                }
            }
            else if(x == -500)  k++;
            else
            {
                k++;
                lives--;
            }
        }
};




int main()
{
    ///Initializing the graphics driver///

    int gd = DETECT, gm;
    char driver[] = "C:\\TC\\BGI";
    initgraph(&gd, &gm, driver);


    int maxx = getmaxx();
    int maxy = getmaxy();

    ///READING PREVIOUS HIGH SCORE FROM THE FILE:///
    ifstream myfile;
    myfile.open("score.txt");
    myfile >> prev_score;
    myfile.close();

    ///Opening Page of the Console///
    bar(0, 0, maxx, maxy);
    char title[] = "WELCOME TO THE BOX GAME!";
    settextstyle(10, HORIZ_DIR, 1);
    outtextxy(170, maxy/2-50, title);
    char text[] = "Press any key to PLAY";
    outtextxy(190, maxy/2+50, text);
    delay(1000);
    while(!kbhit()){}

    ///Initial Position for the Square///
    int x = maxy/2 - 25;
    int y = maxy/2 + 25;

    int i = 0;


    circles c[100];    ///Creating objects for the circles

    ///Game Loop///
    int input = 0;
    char text1[] = "SCORE: ";
    char text2[] = "LIFE: ";

    while(1)
    {
        if(kbhit()) input = getch();
        else    input = 0;

        setcolor(WHITE);

        ///DISPLAYING CURRENT SCORE IN THE GAME:///
        outtextxy(500, 10, text1);
        stringstream ss1;
        ss1 << score;
        string s1 = ss1.str();
        char* score_s1 = (char*) s1.c_str();
        outtextxy(570, 10, score_s1);

        ///DISPLAYING THE REMAINING LIVES:///
        outtextxy(500, 30, text2);
        stringstream ss2;
        ss2 << lives;
        string s2 = ss2.str();
        char* score_s2 = (char*) s2.c_str();
        outtextxy(570, 30, score_s2);

        ///DISPLAYING THE PREVIOUS HIGH SCORE:///
        char text4[] = "HIGH SCORE: ";
        outtextxy(maxx-160, maxy-20, text4);
        stringstream ss4;
        ss4 << prev_score;
        string s4 = ss4.str();
        char* score_s4 = (char*) s4.c_str();
        outtextxy(maxx-35, maxy-20, score_s4);

        if(input != 0)
        {
            if(x >= 1 && y <= maxy-1)
            {
                if(input == 72)
                {
                    y -= 20;
                    x -= 20;
                }
                else if(input == 80)
                {
                    y += 20;
                    x += 20;
                }

            }
            else
            {
                if(x <= 1)
                {
                    x = 10;
                    y = 60;
                }
                else
                {
                    x = maxy - 60;
                    y = maxy - 10;
                }
            }
        }
        ///THE GAME SQUARE///
        setcolor(RED);
        rectangle(0, x, 50, y);

        ///FOR THE CIRCLES:///
        for(int j = k; j <= i; j++)
        {
            /*cout<<"c.x = "<<c[j].x<<" c.y = "<<c[j].y<<endl;
            cout<<"rect.x = "<<x<<" rect.y = "<<y<<endl;
            cout<<"Lives = "<<lives<<endl;*/
            c[j].move_circles(x, y);
            if(c[j].x > maxx - 500) break;
        }
        delay(12);
        cleardevice();     //Clearing the opening page
        i++;
        if(lives == 0)
            break;
    }

    ///GAME OVER SCREEN///
    bar(0, 0, maxx, maxy);
    char title123[] = "GAME OVER!!!";
    settextstyle(10, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(220, maxy/2-50, title123);

    ///FOR THE FINAL SCORE///
    stringstream ss3;
    ss3 << score;
    string s3 = ss3.str();
    char* score_s3 = (char*) s3.c_str();
    char text3[] = "FINAL SCORE: ";
    outtextxy(220, maxy/2, text3);
    outtextxy(360, maxy/2, score_s3);

    ///CHECKING FILE FOR HIGH SCORE:///

    if(score > prev_score)
    {
        ofstream myfile;
        myfile.open("score.txt");
        myfile << score;
        high_score = score;
        char text5[] = "NEW HIGH SCORE: ";
        outtextxy(220, maxy/2+50, text5);
        stringstream hss;
        hss << high_score;
        string hs = hss.str();
        char* score_hs = (char*) hs.c_str();
        outtextxy(385, maxy/2+50, score_hs);
    }
    else
    {
        high_score = prev_score;
        char text5[] = "HIGH SCORE: ";
        outtextxy(220, maxy/2+50, text5);
        stringstream hss;
        hss << high_score;
        string hs = hss.str();
        char* score_hs = (char*) hs.c_str();
        outtextxy(345, maxy/2+50, score_hs);
    }



    delay(10000);

    ///WATING FOR AN INPUT FROM USER TO EXIT:///
    while(!kbhit()){}

    getch();
    closegraph();
    return 0;
}

