#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


struct Person {//hate them
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


void displayPeopleFormatted(const vector<Person>& people) {

    const int idWidth = 5;
    const int nameWidth = 15;
    const int emailWidth = 25;
    const int genderWidth = 10;
    const int ipWidth = 15;

    cout << left << setw(idWidth) << "ID"
         << setw(nameWidth) << "First Name"
         << setw(nameWidth) << "Last Name"
         << setw(emailWidth) << "Email"
         << setw(genderWidth) << "Gender"
         << setw(ipWidth) << "IP Address"
         << endl;

    cout << string(idWidth + nameWidth * 2 + emailWidth + genderWidth + ipWidth, '-') << endl;


    for (auto it = people.begin(); it != people.end(); ++it) {
        const Person& person = *it;
        cout << left << setw(idWidth) << person.id
             << setw(nameWidth) << person.firstName
             << setw(nameWidth) << person.lastName
             << setw(emailWidth) << person.email
             << setw(genderWidth) << person.gender
             << setw(ipWidth) << person.ipAddress
             << endl;
    }
}

int main() {

    string filename = "data.csv";
    vector<Person> people = readPeopleFromFile(filename);

    if (people.empty()) {
        cerr << "No data was read from the file." << endl;
        return 1;
    }

    displayPeopleFormatted(people);

    return 0;
}