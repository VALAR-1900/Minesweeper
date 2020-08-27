#include<bits/stdc++.h>
using namespace std;

#define BOMB '*'
#define FREE_CELL '-'

int lines = 9;
int column = 9;
int bombs = 10; 
int movesLeft = lines * column - bombs;
int mines[10][2];
int counter;
int gg = 0;
int veri[9][9];
vector<pair<int, int> >q;
vector<int> vx;
vector<int> vy;
bool gameover = false;

char board[100][100], user_board[100][100];

bool is_inside(int line, int col)
{
	return 0<= line && line < lines && 0 <= col && col < column;
}

void place_bombs()
{
	vector<pair<int, int> >positions;
	for (int line = 0; line < lines; ++line)
	{
		for (int col = 0; col < column; ++col)
		{
			positions.push_back(make_pair(line, col));
		}
	}
	random_shuffle(positions.begin(), positions.end());
	for (int idx = 0; idx < bombs; ++idx)
	{
		board[positions[idx].first][positions[idx].second] = BOMB;
		veri[positions[idx].first][positions[idx].second] = 2;
		mines[idx][0] = positions[idx].first;
		mines[idx][1] = positions[idx].second;
	}
}

int compute_neighbours(int line, int col)
{
	int num_bombs = 0;
	for (int line_offset = -1; line_offset <= 1; ++line_offset)
	{
		for(int col_offset = -1; col_offset <= 1; ++col_offset)
		{
			int next_line = line + line_offset, next_col = col + col_offset;
			if (is_inside(next_line, next_col) && board[next_line][next_col] == BOMB)
			{
				++num_bombs;
			}
		}
	}
	return num_bombs;
}

void init_board(){
	for (int line = 0; line < lines; ++line)
	{
		for (int col = 0; col < column; ++col)
		{
			user_board[line][col] = FREE_CELL;
		}
	}
	place_bombs();
	for (int line = 0; line < lines; ++line)
	{
		for (int col = 0; col < column; ++col)
		{
			if (board[line][col] != BOMB){
				board[line][col] = compute_neighbours(line, col) + '0';
			}
		}
	}
}

void print_board() {
	cout << "   ";
	for (int i = 0 ; i < column; i++)
	{
		cout << i%10 << " ";
	}
    cout << endl;
    cout << endl;
	for (int line = 0; line < lines; ++line)
	{
		cout << line%10; 
		cout << "  ";
		for (int col = 0; col < column; ++col)
		{
			cout << user_board[line][col] << " ";
		}
		cout << "\n";
	}
}

void print_board1() {
	cout << "   ";
	for (int i = 0 ; i < column; i++)
	{
		cout << i%10 << " ";
	}
    cout << endl;
    cout << endl;
	for (int line = 0; line < lines; ++line)
	{
		cout << line%10; 
		cout << "  ";
		for (int col = 0; col < column; ++col)
		{
			cout << board[line][col] << " ";
		}
		cout << "\n";
	}
}

void replaceMine(int line, int col)
{
	vector<pair<int, int> >positions;
	for (int line = 0; line < lines; ++line)
	{
		for (int col = 0; col < column; ++col)
		{
			positions.push_back(make_pair(line, col));
		}
	}
	random_shuffle(positions.begin(), positions.end());
    
    int idx = 0;
    for (int idx = 0; idx < lines*column; idx++)
    {
		if (board[positions[idx].first][positions[idx].second] != BOMB && positions[idx].first != line && positions[idx].second != col)
		{
			board[positions[idx].first][positions[idx].second] = BOMB;
			// veri[positions[idx].first][positions[idx].second] = 2;
			board[line][col] = FREE_CELL;
			board[line][col] = compute_neighbours(line, col) + '0';
			break;
		}
	}
}

void mark_mine(int line, int col)
{
	user_board[line][col] = '+';
}

bool is_revealed(int line, int col)
{
	if (user_board[line][col] != '-')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void reveal(int line, int col)
{
	user_board[line][col] = board[line][col];
}

bool is_checked(int line, int col)
{
	if (is_inside(line+1, col) && is_revealed(line+1, col))
	{
		return false;
	}
	if (is_inside(line+1, col+1) && is_revealed(line+1, col+1))
	{
		return false;
	}
	if (is_inside(line+1, col-1) && is_revealed(line+1, col-1))
	{
		return false;
	}
	if (is_inside(line, col+1) && is_revealed(line+1, col-1))
	{
		return false;
	}
	if (is_inside(line+1, col+1) && is_revealed(line+1, col+1))
	{
		return false;
	}
	if (is_inside(line-1, col) && is_revealed(line-1, col))
	{
		return false;
	}
	if (is_inside(line-1, col+1) && is_revealed(line-1, col+1))
	{
		return false;
	}
	if (is_inside(line-1, col+1) && is_revealed(line-1, col-1))
	{
		return false;
	}
	return true;
}

int revealed_mines(int line, int col)
{
	int count = 0;
	
	if (is_inside(line+1, col))
	{
		if (user_board[line+1][col] == '+')
		{
			count++;
		}
	}
	if (is_inside(line+1, col+1))
	{
		if (user_board[line+1][col+1] == '+')
		{
			count++;
		}
	}
	if (is_inside(line+1, col-1))
	{
		if (user_board[line+1][col-1] == '+')
		{
			count++;
		}
	}
	if (is_inside(line, col+1))
	{
		if (user_board[line][col+1] == '+')
		{
			count++;
		}
	}
	if (is_inside(line, col-1))
	{
		if (user_board[line][col-1] == '+')
		{
			count++;
		}
	}
	if (is_inside(line-1, col))
	{
		if (user_board[line-1][col] == '+')
		{
			count++;
		}
	}
	if (is_inside(line-1, col+1))
	{
		if (user_board[line-1][col+1] == '+')
		{
			count++;
		}
	}
	if (is_inside(line-1, col-1))
	{
		if (user_board[line-1][col-1] == '+')
		{
			count++;
		}
	}
	return count;
}

void non_revealed(int line, int col)
{
	counter = 0;
	vx.clear();
	vy.clear();
	if (is_inside(line+1, col))
	{
		if (user_board[line+1][col] == '-')
		{
			counter++;
			vx.push_back(line+1);
			vy.push_back(col);
		}
	}
	if (is_inside(line+1, col+1))
	{
		if (user_board[line+1][col+1] == '-')
		{
			counter++;
			vx.push_back(line+1);
			vy.push_back(col+1);
		}
	}
	if (is_inside(line+1, col-1))
	{
		if (user_board[line+1][col-1] == '-')
		{
			counter++;
			vx.push_back(line+1);
			vy.push_back(col-1);
		}
	}
	if (is_inside(line, col+1))
	{
		if (user_board[line][col+1] == '-')
		{
			counter++;
			vx.push_back(line);
			vy.push_back(col+1);
		}
	}
	if (is_inside(line, col-1))
	{
		if (user_board[line][col-1] == '-')
		{
			counter++;
			vx.push_back(line);
			vy.push_back(col-1);
		}
	}
	if (is_inside(line-1, col))
	{
		if (user_board[line-1][col] == '-')
		{
			counter++;
			vx.push_back(line-1);
			vy.push_back(col);
		}
	}
	if (is_inside(line-1, col+1))
	{
		if (user_board[line-1][col+1] == '-')
		{
			counter++;
			vx.push_back(line-1);
			vy.push_back(col+1);
		}
	}
	if (is_inside(line-1, col-1))
	{
		if (user_board[line-1][col-1] == '-')
		{
			counter++;
			vx.push_back(line-1);
			vy.push_back(col-1);
		}
	}
}

void playMinesweeperUtil(int line, int col)
{
	// if (user_board[line][col] != '-') 
 //        return (false); 
  
    int i, j;
	if (board[line][col] == '*') 
    { 
        user_board[line][col]='*'; 
  
        for (i=0; i<bombs; i++) 
            user_board[mines[i][0]][mines[i][1]]='*'; 
  
        print_board(); 
        printf ("\nYou lost!\n"); 
 		gameover = true;
    }
    else
    {
    	reveal(line, col);
    	int qwe;
    	qwe = revealed_mines(line, col);
    	cout << revealed_mines(line, col);
 		
    	int fg = board[line][col] - '0';
    	non_revealed(line, col);
    	if(fg  == qwe)
    	{
    		cout << endl << qwe << endl;
    		if (is_inside(line+1, col) && user_board[line+1][col] != '+' && is_revealed(line+1, col))
    		{
    			reveal(line+1, col);
    			veri[line+1][col] = 1;			
    		}
    		if (is_inside(line+1, col+1) && user_board[line+1][col+1] != '+' && is_revealed(line+1, col+1))
    		{
    			reveal(line+1, col+1);
    			veri[line+1][col+1] = 1;
    		}
    		if (is_inside(line+1, col-1) && user_board[line+1][col-1] != '+' && is_revealed(line+1, col-1))
    		{
    			reveal(line+1, col-1);
    			veri[line+1][col-1] = 1;
    		}
    		if (is_inside(line, col+1) && user_board[line][col+1] != '+' && is_revealed(line, col+1))
    		{
    			reveal(line, col+1);
    			veri[line][col+1] = 1;
    		}
    		if (is_inside(line, col-1) && user_board[line][col-1] != '+' && is_revealed(line, col-1))
    		{
    			reveal(line, col-1);
    			veri[line][col-1] = 1;
    		}
    		if (is_inside(line-1, col) && user_board[line-1][col] != '+' && is_revealed(line-1, col))
    		{
    			reveal(line-1, col);
    			veri[line-1][col] = 1;
    		}
    		if (is_inside(line-1, col+1) && user_board[line-1][col+1] != '+' && is_revealed(line-1, col+1))
    		{
    			reveal(line-1, col+1);
    			veri[line-1][col+1] = 1;
    		}
    		if (is_inside(line-1, col-1) && user_board[line-1][col-1] != '+' && is_revealed(line-1, col-1))
    		{
    			reveal(line-1, col-1);
    			veri[line-1][col-1] = 1;
    		}
    		// print_board();
    	}
    	if(counter == (fg - qwe))
    	{
    		for (int i = 0; i < vx.size(); i++)
    		{
    			if (board[vx[i]][vy[i]] == '*'){
    				mark_mine(vx[i], vy[i]);
    			}
    		}
    		// print_board();
    	}
    	counter = 0;
    }
    print_board();

}

void playminesweeper()
{
	gameover = false;
	int currentMoveIndex = 0;
	int x,y,line,col;
	cin >> x >> y;
	line = x;
	col = y;
	// print_board1();
	while (gameover == false) 
    { 
        printf ("Current Status of Board : \n"); 
        print_board();  
   
        if (currentMoveIndex == 0) 
        {   
        	if (is_inside(line, col))
        	{
            	if (board[line][col] == BOMB)
                	replaceMine (line, col); 
            } 
            reveal(line, col);
            // veri[line][col] = 2;
        } 
  
  		print_board();
        currentMoveIndex ++; 
     //    for (int i = 0; i < 9; i++)
	    // {
	    // 	for (int j = 0; j < 9; j++)
	    // 	{
	    // 		if (is_checked(i, j) && !is_revealed(i, j))
			  //   {
			  //   	veri[i][j] = 2;
			  //   	gg++;
			  //   }
	    // 	}
	    // }

        for (int i = 0; i < 9; i++)
	    {
	    	for (int j = 0; j < 9; j++)
	    	{
	    		if (!is_checked(i, j) && !is_revealed(i, j) && user_board[i][j] != '+')
	    		{
	    			playMinesweeperUtil(i, j);
	    		}
	    	}
	    } 	
	    int abcd = 0;
	    for (int i = 0; i < 9; i++)
	    {
	    	for (int j = 0; j < 9; j++)
	    	{
	    		if (is_checked(i, j))
	    		{
	    			abcd++;
	    		}
	    	}
	    }

        if ((gameover == false) && (abcd == 81))
        { 
            printf ("\nYou won !\n"); 
            gameover = true; 
        } 
    }

}

int main(){
	for (int i = 0; i < 9;i++)
	{
		for (int j = 0; j < 9;j++)
		{
			veri[i][j] = 0;
		}
	}
	srand(time(0));
	init_board();
	print_board1();
	playminesweeper();
}