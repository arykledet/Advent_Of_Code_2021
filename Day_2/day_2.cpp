#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct MyPos
{
    int x;
    int y;
    int aim;
    MyPos() : x(0), y(0), aim(0) {}
};

vector<string> split_string(string input, char token);
void part_1_parser(string file_path, MyPos &mypos);
void part_2_parser(string file_path, MyPos &mypos);

// Split up strings to a vector of strings
vector<string> split_string(string input, char token)
{
    vector<string> output;
    string temp;

    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] != token)
        {
            temp += input[i];
        }
        else
        {
            output.push_back(temp);
            temp = "\0";
        }
    }
    output.push_back(temp);
    
    return output;
}

// Read through the input file and update the postion
void part_1_parser(string file_path, MyPos &mypos)
{
    string input;
    ifstream InFile(file_path);

    vector<string> command;

    while(!InFile.eof())
    {
        getline(InFile, input);
        command = split_string(input, ' ');

        if(command[0] == "forward")
        {
            mypos.x += stoi(command[1]);
        }
        else if(command[0] == "up")
        {
            mypos.y -= stoi(command[1]);
        }
        else if(command[0] == "down")
        {
            mypos.y += stoi(command[1]);
        }
    }

    InFile.close();
}

// Adds aim to the equation
void part_2_parser(string file_path, MyPos &mypos)
{
    string input;
    ifstream InFile(file_path);

    vector<string> command;

    while(!InFile.eof())
    {
        getline(InFile, input);
        command = split_string(input, ' ');

        if(command[0] == "forward")
        {
            mypos.x += stoi(command[1]);
            mypos.y += stoi(command[1]) * mypos.aim;
        }
        else if(command[0] == "up")
        {
            mypos.aim -= stoi(command[1]);
        }
        else if(command[0] == "down")
        {
            mypos.aim += stoi(command[1]);
        }
    }

    InFile.close();
}

int main()
{
    MyPos mypos_1, mypos_2;

    part_1_parser("day_2_input.txt", mypos_1);
    cout << "Part 1: " << mypos_1.x * mypos_1.y << endl;

    part_2_parser("day_2_input.txt", mypos_2);
    cout << "Part 2: " <<  mypos_2.x * mypos_2.y << endl;

    return 0;
}