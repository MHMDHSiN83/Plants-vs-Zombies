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

vector<double> find_vector(string line){
    string number = "";
    vector <double> inf;
    for(int i = 0; i < line.size(); i++){
        if(line[i] >= 48 && line[i] <= 57){
            number += line[i];
        }
        if((line[i] == '-' && number != "" ) || i == line.size() - 1){
            inf.push_back(stod(number));
            number = "";
        }
    }
    return inf;
}

vector <string> getting_input() {
    ifstream file("input.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        exit(0);
    }
    string line;
    vector<string> lines;
    while (getline(file, line)) {
        lines.push_back(line);
        
    }
    file.close();
    return lines;
}

void set_vector(vector<string> &lines){
    vector <double> zombies_inf = find_vector(lines[0]);
}

int main()
{
    // getting_input();
    // return 0;
    vector<string> lines = getting_input();
    System system(find_vector(lines[0]), find_vector(lines[1]), find_vector(lines[2]), find_vector(lines[3]));
    system.run();
}
