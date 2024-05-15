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
        if((line[i] >= 48 && line[i] <= 57) || line[i] == 46){
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


vector<vector<double>> get_zombies_data(string line) {
    vector<string> zombies = split(line, ',');
    vector<vector<double>> result;
    for (int i = 0; i < zombies.size(); i++)
    {
        vector<string> each_zombie_data = split(zombies[i], '-');
        vector<double> row;
        if(each_zombie_data[0] == "regular") {
            row.push_back(0);
        } else {
            row.push_back(1);
        }
        for (int j = 1; j < each_zombie_data.size(); j++)
        {
            row.push_back(stod(each_zombie_data[j]));
        }
        result.push_back(row);
    }
    return result;
}

vector<vector<double>> get_plants_data(string line) {
    vector<string> zombies = split(line, ',');
    vector<vector<double>> result;
    for (int i = 0; i < zombies.size(); i++)
    {
        vector<string> each_zombie_data = split(zombies[i], '-');
        vector<double> row;

        if(each_zombie_data[0] == "peashooter")
            row.push_back(0);
        else if(each_zombie_data[0] == "sunflower")
            row.push_back(1);
        else if(each_zombie_data[0] == "walnut")
            row.push_back(2);
        else
            row.push_back(3);

        for (int j = 1; j < each_zombie_data.size(); j++)
            row.push_back(stod(each_zombie_data[j]));
        result.push_back(row);
    }
    return result;
}

int main()
{
    vector<string> lines = getting_input();
    vector<vector<double>> zombies_data = get_zombies_data(lines[0]);
    vector<vector<double>> plants_data = get_plants_data(lines[1]);
    System system(zombies_data, plants_data, find_vector(lines[2]), find_vector(lines[3]));
    system.run();
}
