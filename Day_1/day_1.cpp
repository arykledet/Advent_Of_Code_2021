#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> get_inputs(string file_path);
vector<int> sliding_window(const vector<int> input);
int get_num_increases(const vector<int> input);

// Convert inputs into a vector
vector<int> get_inputs(string file_path)
{
    vector<int> output;
    string value;
    ifstream InFile(file_path);

    while(!InFile.eof())
    {
        getline(InFile, value);
        output.push_back(stoi(value));
    }

    InFile.close();

    return output;
}

// Count the number of times a depth measurement increases
int get_num_increases(const vector<int> input)
{
    int output = 0;
    for(vector<int>::const_iterator itr = input.begin(); itr < input.end(); itr++)
    {
        output += ( *(itr+1) > *(itr) );
    }
    return output;
}

// Get average using a 3 measurment sliding window 
vector<int> sliding_window(const vector<int> input)
{
    vector<int> output = input;
    for(vector<int>::iterator itr = output.begin(); itr < output.end(); itr++)
    {
        *itr = *itr + *(itr+1) + *(itr+2);
    }

    return output;
}

int main()
{
    const vector<int> input = get_inputs("day_1_input.txt");
    int num_increases = get_num_increases(input);

    // Part 1 answer
    cout << "Number of increases: " << num_increases << endl;

    vector<int> avg_input = sliding_window(input);
    int num_avg_increases = get_num_increases(avg_input);

    // Part 2 answer
    cout << "Number of sum increases: " << num_avg_increases << endl;

    return 0;
}