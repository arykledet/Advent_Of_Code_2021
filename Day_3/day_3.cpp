#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define INPUT_WIDTH 12

vector<string> get_inputs(string file_path);
int get_gamma(bool (&most_common)[INPUT_WIDTH]);
int get_epsilon(bool (&most_common)[INPUT_WIDTH]);
void get_most_common(vector<string> bits, bool (&most_common)[INPUT_WIDTH]);
int get_co2_rating(vector<string> inputs, bool most_common_bits[INPUT_WIDTH]);
int get_oxygen_rating(vector<string> inputs, bool most_common_bits[INPUT_WIDTH]);

vector<string> get_inputs(string file_path)
{
    ifstream input(file_path);
    string temp;
    vector<string> output;

    while(!input.eof())
    {
        getline(input, temp);
        output.push_back(temp);
    }

    return output;
}

int get_gamma(bool (&most_common)[INPUT_WIDTH])
{
    int output = 0;
    
    for(int i = 0; i < INPUT_WIDTH; i++)
    {
        output |= most_common[i] << ((INPUT_WIDTH - 1)-i);
    }

    return output;
}

int get_epsilon(bool (&most_common)[INPUT_WIDTH])
{
    int output = 0;

    for(int i = 0; i < INPUT_WIDTH; i++)
    {
        output |= (!most_common[i]) << ((INPUT_WIDTH - 1)-i);
    }

    return output;
}

void get_most_common(vector<string> bits, bool (&most_common)[INPUT_WIDTH])
{
    int ones_count[INPUT_WIDTH];
    int zeros_count[INPUT_WIDTH];

    for(int i = 0; i < INPUT_WIDTH; i++)
    {
        ones_count[i] = 0;
        zeros_count[i] = 0;
    }


    for(vector<string>::iterator itr = bits.begin(); itr < bits.end(); itr++)
    {
        for(int i = 0; i < INPUT_WIDTH; i++)
        {
            ones_count[i] += ( (*itr)[i] == '1');
            zeros_count[i] += ((*itr)[i] == '0');
        }
    }

    for(int i = 0; i < INPUT_WIDTH; i++)
    {
        if(ones_count[i] >= zeros_count[i])
        {
            most_common[i] = 1;
        }
        else
        {
            most_common[i] = 0;
        }
    }
}

int get_co2_rating(vector<string> inputs, bool most_common_bits[INPUT_WIDTH])
{
    int output = 0;

    bool mc_buff[INPUT_WIDTH];

    for(int i = 0; i < INPUT_WIDTH; i++)
        mc_buff[i] = most_common_bits[i];

    for(int i = 0; i < INPUT_WIDTH; i++)
    {
        for(vector<string>::iterator itr = inputs.begin(); itr < inputs.end(); itr++)
        {
            if( ((*itr)[i] - '0') == mc_buff[i])
            {
                inputs.erase(itr);
                itr--;
            }
        }

        if(inputs.size() == 1)
            break;

        get_most_common(inputs, mc_buff);
    }

    for(vector<string>::iterator itr = inputs.begin(); itr < inputs.end(); itr++)
    {
        for(int i = 0; i < INPUT_WIDTH; i++)
            output |= ((*itr)[i] - '0') << ( (INPUT_WIDTH-1) - i);
    }

    return output;

}


int get_oxygen_rating(vector<string> inputs, bool most_common_bits[INPUT_WIDTH])
{
    int output = 0;

    bool mc_buff[INPUT_WIDTH];

    for(int i = 0; i < INPUT_WIDTH; i++)
        mc_buff[i] = most_common_bits[i];

    for(int i = 0; i < INPUT_WIDTH; i++)
    {
        for(vector<string>::iterator itr = inputs.begin(); itr < inputs.end(); itr++)
        {
            if(((*itr)[i] - '0') != mc_buff[i])
            {
                inputs.erase(itr);
                itr--;
            }
        }

        if(inputs.size() == 1)
            break;
        
        get_most_common(inputs, mc_buff);

    }
    for(vector<string>::iterator itr = inputs.begin(); itr < inputs.end(); itr++)
    {
        for(int i = 0; i < INPUT_WIDTH; i++)
            output |= ((*itr)[i] - '0') << ( (INPUT_WIDTH-1) -i );
    }

    return output;
}

int main()
{
    bool most_common_bits[INPUT_WIDTH];
    vector<string> inputs = get_inputs("day_3_input.txt");

    get_most_common(inputs, most_common_bits);
    
    int gamma = get_gamma(most_common_bits);
    int epsilon = get_epsilon(most_common_bits);

    // Part 1
    cout << "Power consumption = " << gamma * epsilon << endl;

    int oxygen_rating = get_oxygen_rating(inputs, most_common_bits);
    int co2_rating = get_co2_rating(inputs, most_common_bits);

    // Part 2
    cout << "Life support rating = " << oxygen_rating * co2_rating << endl;

    return 0;
}