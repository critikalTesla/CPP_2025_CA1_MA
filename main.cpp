#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
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


        auto readNextColumn = [&](string& field) {
            getline(ss, field, ',');
        };

        readNextColumn(token); // ID
        person.id = stoi(token);

        readNextColumn(person.firstName);
        readNextColumn(person.lastName);
        readNextColumn(person.email);
        readNextColumn(person.gender);
        readNextColumn(person.ipAddress);


        people.push_back(person);
    }

    file.close();
    return people;
}


void displayPeople(const vector<Person>& people) {

    for_each(people.begin(), people.end(), [](const Person& person) {
        cout << "ID: " << person.id << endl;
        cout << "First Name: " << person.firstName << endl;
        cout << "Last Name: " << person.lastName << endl;
        cout << "Email: " << person.email << endl;
        cout << "Gender: " << person.gender << endl;
        cout << "IP Address: " << person.ipAddress << endl;
        cout << "-------------------------" << endl;
    });
}

int main() {
    string filename = "data.csv";
    vector<Person> people = readPeopleFromFile(filename);
    if (people.empty()) {
        cerr << "No data was read from the file." << endl;
        return 1;
    }
    displayPeople(people);

    return 0;
}