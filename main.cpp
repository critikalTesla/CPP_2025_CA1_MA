#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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


int findPersonByGender(const vector<Person>& people, const string& gender) {
    for (size_t i = 0; i < people.size(); ++i) {
        if (people[i].gender == gender) {
            return i;
        }
    }
    return -1;
}


void displayPerson(const Person& person) {
    cout << left << setw(5) << "ID" << ": " << person.id << endl;
    cout << setw(15) << "First Name" << ": " << person.firstName << endl;
    cout << setw(15) << "Last Name" << ": " << person.lastName << endl;
    cout << setw(15) << "Email" << ": " << person.email << endl;
    cout << setw(15) << "Gender" << ": " << person.gender << endl;
    cout << setw(15) << "IP Address" << ": " << person.ipAddress << endl;
    cout << "-------------------------" << endl;
}

int main() {
    string filename = "data.csv";


    vector<Person> people = readPeopleFromFile(filename);

    if (people.empty()) {
        cerr << "No data was read from the file." << endl;
        return 1;
    }


    string searchGender;
    cout << "Enter the gender to search for (e.g., Male, Female, Bigender, etc.): ";
    cin >> searchGender;


    int index = findPersonByGender(people, searchGender);

    if (index != -1) {

        cout << "\nPerson found:\n";
        displayPerson(people[index]);
    } else {

        cout << "\nNo person with gender '" << searchGender << "' was found.\n";
    }

    return 0;
}