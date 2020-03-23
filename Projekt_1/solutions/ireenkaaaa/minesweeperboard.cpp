#include <iostream>
#include "minesweeperboard.h"
using std::cout;
using std::endl;



MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode):mode(mode), width(width), height(height) {
    this->game_status=RUNNING;
    this->board[this->height][this->width];
    number_of_mines=0;
    if(mode==DEBUG)
    {

        for(int j=0; j<this->height; j++) {
            for (int i = 0; i < this->width; i++) {
                if(i==j || j==0 || (i==0 && j%2==0))
                {
                    this->board[i][j].hasMine=1;
                    number_of_mines+=1;
                }

            }
        }

    }
    if(mode!=DEBUG) {
        number_of_mines=(this->width*this->height*mode)*0.1;
        for (int j = 0; j < number_of_mines; j++) {
            int random1 = rand() % this->width;
            int random2 = rand() % this->height;
            while( this->board[random1][random2].hasMine==1) {
                random1 = rand() % this->width;
                random2 = rand() % this->height;
            }
            this->board[random1][random2].hasMine = 1;
        }

    }

}
bool MinesweeperBoard::correctValue(int x, int y) const
{
    if(x<this->width && x>=0 && y<this->height && y>=0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
void MinesweeperBoard::debug_display() const {
    for(int j=0; j<this->height; j++) {
        for (int i = 0; i <this->width; i++) {
            cout<<"[";
            if(this->board[i][j].hasMine==0)
            {
                cout<<".";
            } else{
                cout<<"M";
            }
            if(this->board[i][j].isRevealed==0)
            {
                cout<<".";
            } else{
                cout<<"o";
            }
            if(this->board[i][j].hasFlag==0)
            {
                cout<<".";
            } else{
                cout<<"f";
            }
            cout<<"]";

        }
        cout<<endl;
    }
}
int MinesweeperBoard::getBoardWidth() const
{
    return this->width;
}
int MinesweeperBoard::getBoardHeight() const
{
    return this->height;
}
int MinesweeperBoard::getMineCount() const
{
    return number_of_mines;
}
MinesweeperBoard::~MinesweeperBoard()
{}
bool MinesweeperBoard::isRevealed(int x, int y) const
{
    if( this->correctValue(x,y)==true)
    {
        return this->board[x][y].isRevealed;

    }

}
char MinesweeperBoard::getFieldInfo(int x, int y) const
{
    if( this->correctValue(x, y)==false )
    {
        return '#';
    }
    else if(this->board[x][y].isRevealed==0 && this->board[x][y].hasFlag==1 )
    {
        return 'F';
    }
    else if(this->board[x][y].isRevealed==0 && this->board[x][y].hasFlag==0 )
    {
        return '_';
    }
    else if(this->board[x][y].isRevealed==1 && this->board[x][y].hasMine==1 )
    {
        return 'x';
    }
    else if(this->board[x][y].isRevealed==1 && countMines(x,y)==0 )
    {
        return ' ';
    }
    else if(this->board[x][y].isRevealed==1 && countMines(x,y)!=0 )
    {

        return countMines(x, y)+'0';
    }

}
int MinesweeperBoard::countMines(int x, int y) const
{
    if(this->correctValue(x, y)==true && this->isRevealed(x,y) == true)
    {
        int temp_mine_counter=0;
        for(int i=(x+1); i>(x-2); i--)
        {
            for(int j=(y+1); j>(y-2);j--)
            {
                if (i>=0 && j>=0) {
                    if (this->board[i][j].hasMine == 1) {
                        temp_mine_counter += 1;
                    }
                }
            }
        }
        return temp_mine_counter;
    }
    else
    {
        return -1;
    }
}
bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if(this->correctValue(x, y)==0 || this->board[x][y].hasFlag==0 || this->board[x][y].isRevealed==1)
    {
        return false;
    }
    else if(this->board[x][y].hasFlag==1)
    {
        return true;
    }
    else
        return false;
}
void MinesweeperBoard::toggleFlag(int x, int y)
{
    if(this->correctValue(x, y)==true && this->board[x][y].hasFlag==0 && this->board[x][y].isRevealed==0 && game_status==RUNNING)
    {
        this->board[x][y].hasFlag=1;
    }
    else if(this->correctValue(x, y)==true && this->board[x][y].hasFlag==1 && this->board[x][y].isRevealed==0 && game_status==RUNNING)
    {
        this->board[x][y].hasFlag=0;
    }

}
void MinesweeperBoard::revealField(int x, int y)
{
    if(isRevealed(x,y)==false && this->board[x][y].hasMine==false && this->correctValue(x, y)==true && this->board[x][y].hasFlag==false && game_status==RUNNING)
    {

        this->board[x][y].isRevealed=1;

    }
    else if(this->board[x][y].isRevealed==0 && this->board[x][y].hasMine==1 &&  this->correctValue(x, y)==true && this->board[x][y].hasFlag==0 && game_status==RUNNING)
    {
        if(this->isFirstMove()==true && this->mode!=DEBUG)
        {
            this->board[x][y].hasMine=0;
            this->board[rand() % this->width][rand() % this->height].hasMine = 1;
            this->board[x][y].isRevealed=1;
        }
        else if(this->isFirstMove()==false || this->mode==DEBUG)
        {

            this->game_status=FINISHED_LOSS;
            this->board[x][y].isRevealed=1;
        }
    }
}
bool MinesweeperBoard::isFirstMove() const
{
    int temp_counter=0;
    for(int j=0; j<this->height; j++) {
        for (int i = 0; i < this->width; i++) {
            if(this->board[i][j].isRevealed==0)
            {
                temp_counter++;
            }

        }

    }
    return temp_counter == (this->width*this->height);

}
GameState MinesweeperBoard::getGameState() const
{
    if(this->whenWin()==true)
    {
        return FINISHED_WIN;
    }
    else if (this->whenWin()==false){
        return this->game_status;
    }

}
bool MinesweeperBoard::whenWin() const
{
    int temp_counter_flags=0;
    int temp_counter_revealed=0;
    for(int j=0; j<this->height; j++) {
        for (int i = 0; i < this->width; i++) {
            if(this->board[i][j].hasMine==1 && this->board[i][j].hasFlag==1 &&  this->board[i][j].isRevealed==0)
            {
                temp_counter_flags++;

            }
            else if(this->board[i][j].hasMine==1 && this->board[i][j].isRevealed==0 && this->board[i][j].hasFlag==0)
            {
                temp_counter_revealed++;
            }
        }

    }
    int temp_counter=0;
    for(int j=0; j<this->height; j++) {
        for (int i = 0; i < this->width; i++) {
            if(this->board[i][j].isRevealed==0)
            {
                temp_counter++;
            }

        }

    }
    return (temp_counter_flags == temp_counter || temp_counter_revealed == temp_counter);
}