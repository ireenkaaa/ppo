
using std::cout;
using std::endl;
MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode):mode_(mode) {
    game_status=RUNNING;
    if(width>0 && width<100)
    {
        width_=width;

    }
    else{
        cout<<"Incorrect value. I set width to 10"<<endl;
        width_=10;
    }
    if(height>0 && height<100)
    {
        height_=height;
    } else{
        cout<<"Incorrect value. I set height to 10"<<endl;
        height_=10;
    }
    board_[height_][width_];
    for(int j=0; j<height_; j++) {
        for (int i = 0; i < width_; i++) {
            board_[i][j].hasFlag=0;
            board_[i][j].hasMine=0;
            board_[i][j].isRevealed=0;
        }

    }
    number_of_mines_=0;
    if(mode==DEBUG)
    {

        for(int j=0; j<height_; j++) {
            for (int i = 0; i < width_; i++) {
                if(i==j || i==0 && j%2==0 || j==0 )
                {
                    board_[i][j].hasMine=1;
                    number_of_mines_+=1;
                }

            }
        }

    }
    if(mode!=DEBUG) {
        number_of_mines_=(width_*height_*mode)*0.1;
        for (int j = 0; j < number_of_mines_; j++) {
            board_[rand() % width_][rand() % height_].hasMine = 1;
        }
    }

}
void MinesweeperBoard::debug_display() const {
    for(int j=0; j<height_; j++) {
        for (int i = 0; i <width_; i++) {
            cout<<"[";
            if(board_[i][j].hasMine==0)
            {
                cout<<".";
            } else{
                cout<<"M";
            }
            if(board_[i][j].isRevealed==0)
            {
                cout<<".";
            } else{
                cout<<"o";
            }
            if(board_[i][j].hasFlag==0)
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
    return width_;
}
int MinesweeperBoard::getBoardHeight() const
{
    return height_;
}
int MinesweeperBoard::getMineCount() const
{
    return number_of_mines_;
}
MinesweeperBoard::~MinesweeperBoard()
{}
int MinesweeperBoard::countMines(int x, int y) const
{
    if(x>=width_ || y>=height_ || board_[x][y].isRevealed==0)
    {
        return -1;
    }
    else{
        int temp_mine_counter=0;
        for(int i=(x+1); i>(x-2); i--)
        {
            for(int j=(y+1); j>(y-2);j--)
            {
                if (i>=0 && j>=0) {
                    if (board_[i][j].hasMine == 1) {
                        temp_mine_counter += 1;
                    }
                }
            }
        }
        return temp_mine_counter;
    }
}
bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if(x>=width_ || y>=height_ || board_[x][y].hasFlag==0 || board_[x][y].isRevealed==1)
    {
        return false;
    }
    else if(board_[x][y].hasFlag==1)
    {
        return true;
    }
    else
        return false;
}
void MinesweeperBoard::toggleFlag(int x, int y)
{
    if(board_[x][y].isRevealed==1 || x>=width_ || y>=height_ || game_status!=RUNNING)
    {
    }
     else if(board_[x][y].isRevealed==0)
    {
        board_[x][y].hasFlag=1;
    }
}
void MinesweeperBoard::revealField(int x, int y)
{
    if(board_[x][y].isRevealed==1 || x>=width_ || y>=height_ || board_[x][y].hasFlag==1 || game_status!=RUNNING )
    {}
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasMine==0)
    {
        board_[x][y].isRevealed=1;
    }
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasMine==1)
    {
        if(this->isFirstMove()==1 && this->mode_!=DEBUG)
        {
            board_[x][y].hasMine=0;
            board_[rand() % width_][rand() % height_].hasMine = 1;
            board_[x][y].isRevealed=1;
        }
        else
        {
            this->game_status=FINISHED_LOSS;
            cout<<"koniec gry";
        }
    }
}
bool MinesweeperBoard::isRevealed(int x, int y) const
{
    if(board_[x][y].isRevealed==1)
    {
        return true;
    }
    else
        return false;
}
char MinesweeperBoard::getFieldInfo(int x, int y) const
{
    if(x>width_ || y>height_)
    {
        return '#';
    }
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasFlag==1 )
    {
        return 'F';
    }
    else if(board_[x][y].isRevealed==0 && board_[x][y].hasFlag==0 )
    {
        return '_';
    }
    else if(board_[x][y].isRevealed==1 && board_[x][y].hasMine==1 )
    {
        return 'x';
    }
    else if(board_[x][y].isRevealed==1 && countMines(x,y)==0 )
    {
        return ' ';
    }
    else if(board_[x][y].isRevealed==1 && countMines(x,y)!=0 )
    {

        return countMines(x, y)+'0';
    }
    else
        return '?';

}

bool MinesweeperBoard::isFirstMove()
{
    int temp_counter=0;
    for(int j=0; j<height_; j++) {
        for (int i = 0; i < width_; i++) {
            if(board_[i][j].isRevealed==0)
            {
                temp_counter++;
            }

        }

    }
    if(temp_counter==(width_*height_))
    {
        return true;
    }
    else
        return false;
}
GameState MinesweeperBoard::getGameState() const
{
    if(this->whenWin()==true)
        return FINISHED_WIN;
    else if(this->game_status==RUNNING)
        return RUNNING;
    else if (this->game_status==FINISHED_LOSS)
        return FINISHED_LOSS;
    else
        return  RUNNING;

}
bool MinesweeperBoard::whenWin() const
{

    int temp_counter_flags=0;
    int temp_counter_revealed=0;
    for(int j=0; j<height_; j++) {
        for (int i = 0; i < width_; i++) {
            if(board_[i][j].hasMine==1 && board_[i][j].hasFlag==1)
            {
                temp_counter_flags++;
            }
            if(board_[i][j].hasMine==1 && board_[i][j].isRevealed==0)
            {
                temp_counter_revealed++;
            }

        }

    }
    if(temp_counter_flags==this->getMineCount() || temp_counter_revealed==this->getMineCount())
    {
        return true;
    }
    else
        return false;


}