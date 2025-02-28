#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;


struct Person {
    int id;
    string firstName;
    string lastName;
    string email;
    string gender;
    string ipAddress;
};


vector<Person> readPeopleFromFile(const string& filename) {
    vector<Person> people;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return people;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Person person;

        // Read each column of the CSV line
        getline(ss, token, ','); // ID
        person.id = stoi(token);

        getline(ss, person.firstName, ',');
        getline(ss, person.lastName, ',');
        getline(ss, person.email, ',');
        getline(ss, person.gender, ',');
        getline(ss, person.ipAddress, ',');

        people.push_back(person);
    }

    file.close();
    return people;
}


map<string, int> countUniqueValues(const vector<Person>& people, const string& column) {
    map<string, int> countMap;

    for (const auto& person : people) {
        string value;
        if (column == "gender") {
            value = person.gender;
        } else if (column == "ipAddress") {
            value = person.ipAddress;
        } else if (column == "email") {
            value = person.email;
        } else if (column == "firstName") {
            value = person.firstName;
        } else if (column == "lastName") {
            value = person.lastName;
        } else {
            cerr << "Invalid column name provided." << endl;
            return countMap;
        }


        countMap[value]++;
    }

    return countMap;
}


void displayCountMap(const map<string, int>& countMap, const string& column) {
    cout << "Count of unique values in column '" << column << "':\n";
    cout << setw(20) << left << "Value" << "Count\n";
    cout << string(30, '-') << endl;

    for (const auto& pair : countMap) {
        cout << setw(20) << left << pair.first << pair.second << endl;
    }
}

int main() {
    string filename = "data.csv";

    vector<Person> people = readPeopleFromFile(filename);

    if (people.empty()) {
        cerr << "No data was read from the file." << endl;
        return 1;
    }


    string column;
    cout << "Enter the column name to count unique values (e.g., gender, ipAddress, email, firstName, lastName): ";
    cin >> column;

    map<string, int> countMap = countUniqueValues(people, column);

    // Display the count map
    displayCountMap(countMap, column);

    return 0;
}