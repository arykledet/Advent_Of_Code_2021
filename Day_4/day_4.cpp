#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define BOARD_LENGTH 5
#define BOARD_HEIGHT 5

struct bingo_sq{
    bool selected;  
    int value;
    bingo_sq() : selected(0), value(0) {}
};

struct bingo_board{
    bool won;
    int score;
    int id;
    bingo_sq elements[BOARD_HEIGHT][BOARD_LENGTH];
};

vector<unsigned int> parse_bingo_calls(string calls)
{
    vector<unsigned int> output;
    string temp;
    char token = ',';

    for(int i = 0; i < calls.size(); i++)
    {
        if(calls[i] != token)
        {
            temp += calls[i];
        }
        else
        {
            output.push_back(stoi(temp));
            temp = "\0";
        }
    }

    output.push_back(stoi(temp));

    return output;
}

bingo_board parse_bingo_board(vector<string> board)
{
    bingo_board output;
    string buff;

    // Since single digit numbers do not use 0, will parse by counting
    // Every number is represented by 2 characters followed by a space

    int k = 0;

    for(int i = 0; i < board.size(); i++)
    {
      for(int j = 0; j <= board[i].size(); j++)
        {
            if((j+1)%3 != 0)
            {
                buff += board[i][j];
            }
            else
            {
                output.elements[i][k].value = stoi(buff);
                buff = "";
                k++;
            }
        }
        k = 0;
    }


    return output;
}

void parse_inputs(string file_path, vector<unsigned int> &bingo_calls, vector<bingo_board> &bingo_boards )
{
    // Bingo calls occupy first line
    // Boards are separated by empty lines

    ifstream InFile(file_path);
    string buffer;
    vector<string> board;
    bingo_board board_buff;

    // Parse the bingo calls
    getline(InFile, buffer);
    bingo_calls = parse_bingo_calls(buffer);
    InFile.ignore(1000, '\n');

    int board_id = 0;

    // Parse the boards
    while(!InFile.eof())
    {
        getline(InFile, buffer);

        if(buffer == "")
        {
            board_buff = parse_bingo_board(board);
            board_buff.id = board_id++;
            board_buff.won = false;
            bingo_boards.push_back(board_buff);
            board.clear();
        }
        else
        {
            board.push_back(buffer);
        }
    }
}

void mark_board(bingo_board &board, unsigned int number)
{
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        for(int j = 0; j < BOARD_LENGTH; j++)
        {
            if(board.elements[i][j].value == number)
                board.elements[i][j].selected = true;
        }
    }
}

void print_board(bingo_board &board)
{
    printf("Board_ID = %d\n", board.id);
    printf("Board Won = %d\n", board.won);
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        for(int j = 0; j < BOARD_LENGTH; j++)
        {
            printf("[%d](%d) ", board.elements[i][j].value, board.elements[i][j].selected);
        }
        printf("\n");
    }
}

void print_all_boards(vector<bingo_board> &boards)
{
    for(int i = 0; i < boards.size(); i++)
    {
        print_board(boards[i]);
        printf("\n");
    }
}

int calculate_score(bingo_board &board, int itr)
{
    int sum = 0;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for(int j = 0; j < BOARD_LENGTH; j++)
        {
            sum += (board.elements[i][j].selected) ? 0 : board.elements[i][j].value;
        }
    }

    return sum*itr;
}

bool check_horizontal(bingo_board &board, int itr)
{
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        if(board.elements[itr][i].selected == false)
            return false;
    }

    return true;    
}

bool check_vertical(bingo_board &board, int itr)
{
    for(int i = 0; i < BOARD_LENGTH; i++)
    {
        if(board.elements[i][itr].selected == false)
            return false;
    }

    return true;    
}


// Look for bingo by checking horizontal and vertical rows of board
// Return true if board is winner
bool check_for_winner(bingo_board &board)
{
    for(int i = 0; i < BOARD_LENGTH; i++)
    {
        if( check_vertical(board, i) )
        {
            board.won = true;
            return true;
        }
    }

    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        if( check_horizontal(board, i) )
        {
            board.won = true;
            return true;
        }
    }

    return false;
}

// Draw all the numbers and check for winners
int draw_numbers(vector<unsigned int> &calls, vector<bingo_board> &boards)
{
    unsigned int number;
    unsigned int score;

    // Mark each board and check for winners
    for(int i = 0; i < calls.size(); i++)
    {
        number = calls[i];

        for(int j = 0; j < boards.size(); j++)
        {
            mark_board(boards[j], number);

            if( check_for_winner(boards[j]) )
            {
                score = calculate_score(boards[j], number);
                
                cout << "Score = " << score << endl;
                return 1;
            }
        }
    }

    return 0;
}

int main()
{
    vector<unsigned int> calls;
    vector<bingo_board> boards;

    parse_inputs("day_4_input.txt", calls, boards);

    draw_numbers(calls, boards);

    return 0;
}