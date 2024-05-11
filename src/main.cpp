#include "../include/system.hpp"

vector<string> split(string input, char spliter)
{
    vector<string> splited_string;
    string temp;
    int pre_index = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if(i == input.size() - 1) {
            temp = input.substr(pre_index, i - pre_index + 1);
            splited_string.push_back(temp);
            if(input[i] == spliter)
                splited_string.push_back("");
        }
        else if(input[i] == spliter) {
            temp = input.substr(pre_index, i - pre_index);
            splited_string.push_back(temp);
            pre_index = i + 1;
        }
    }
    return splited_string;
}

void getting_input() {
    ifstream file("input.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        exit(0);
    }
    string line;
    while (getline(file, line)) {
        
    }
    file.close();
}



int main()
{
    // getting_input();
    // return 0;
    System system;
    system.run();
}
