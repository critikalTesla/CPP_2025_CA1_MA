#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

void read_file() {
    ifstream fin("data.csv");


    int idnum;
    cout << "Enter the id of the people to display details: ";
    cin >> idnum;

    map<int, vector<string>> dataMap;
    string line;

    while (getline(fin, line)) {
        vector<string> row;
        stringstream s(line);
        string word;

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        int id = stoi(row[0]);
        dataMap[id] = row;
    }

    fin.close();

    auto it = dataMap.find(idnum);
    if (it != dataMap.end()) {
        vector<string>& row = it->second;
        cout << "Details of ID " << row[0] << " : \n";
        cout << "Name: " << row[1] << "\n";
        cout << "Last Name: " << row[2] << "\n";
        cout << "Email: " << row[3] << "\n";
        cout << "Gender: " << row[4] << "\n";
        cout << "IP Address: " << row[5] << "\n";
    } else {
        cout << "Record not found\n";
    }
    if (!fin.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
}

int main() {
    read_file();
    return 0;
}