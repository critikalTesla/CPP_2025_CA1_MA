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

void displaySubsetByGender(const vector<Person>& people, const string& gender) {
    bool found = false;

    cout << left << setw(5) << "ID"
         << setw(15) << "First Name"
         << setw(15) << "Last Name"
         << setw(25) << "Email"
         << setw(10) << "Gender"
         << setw(15) << "IP Address"
         << endl;

    cout << string(85, '-') << endl;

    for (const auto& person : people) {
        if (person.gender == gender) {
            found = true;
            cout << left << setw(5) << person.id
                 << setw(15) << person.firstName
                 << setw(15) << person.lastName
                 << setw(25) << person.email
                 << setw(10) << person.gender
                 << setw(15) << person.ipAddress
                 << endl;
        }
    }

    if (!found) {
        cout << "No records found for gender: " << gender << endl;
    }
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


void findFirstPersonByGender(const vector<Person>& people, const string& gender) {
    for (const auto& person : people) {
        if (person.gender == gender) {
            cout << "\nFirst person found with gender '" << gender << "':\n";
            cout << left << setw(5) << "ID" << ": " << person.id << endl;
            cout << setw(15) << "First Name" << ": " << person.firstName << endl;
            cout << setw(15) << "Last Name" << ": " << person.lastName << endl;
            cout << setw(15) << "Email" << ": " << person.email << endl;
            cout << setw(15) << "Gender" << ": " << person.gender << endl;
            cout << setw(15) << "IP Address" << ": " << person.ipAddress << endl;
            cout << "-------------------------" << endl;
            return;
        }
    }
    cout << "\nNo person with gender '" << gender << "' was found.\n";
}

void findAllPersonsByGender(const vector<Person>& people, const string& gender) {
    bool found = false;

    cout << left << setw(5) << "ID"
         << setw(15) << "First Name"
         << setw(15) << "Last Name"
         << setw(25) << "Email"
         << setw(10) << "Gender"
         << setw(15) << "IP Address"
         << endl;

    cout << string(85, '-') << endl;

    for (const auto& person : people) {
        if (person.gender == gender) {
            found = true;
            cout << left << setw(5) << person.id
                 << setw(15) << person.firstName
                 << setw(15) << person.lastName
                 << setw(25) << person.email
                 << setw(10) << person.gender
                 << setw(15) << person.ipAddress
                 << endl;
        }
    }

    if (!found) {
        cout << "No records found for gender: " << gender << endl;
    }
}

int main() {
    string filename = "data.csv";

    vector<Person> people = readPeopleFromFile(filename);

    if (people.empty()) {
        cerr << "No data was read from the file." << endl;
        return 1;
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display subset of rows by gender\n";
        cout << "2. Count unique values in a column\n";
        cout << "3. Search for the first person by gender\n";
        cout << "4. Search for all persons by gender\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string searchGender;
                cout << "Enter the gender to filter by (e.g., Male, Female, Bigender, etc.): ";
                cin >> searchGender;
                displaySubsetByGender(people, searchGender);
                break;
            }
            case 2: {
                string column;
                cout << "Enter the column name to count unique values (e.g., gender, ipAddress, email, firstName, lastName): ";
                cin >> column;
                map<string, int> countMap = countUniqueValues(people, column);
                displayCountMap(countMap, column);
                break;
            }
            case 3: {
                string searchGender;
                cout << "Enter the gender to search for (e.g., Male, Female, Bigender, etc.): ";
                cin >> searchGender;
                findFirstPersonByGender(people, searchGender);
                break;
            }
            case 4: {
                string searchGender;
                cout << "Enter the gender to search for (e.g., Male, Female, Bigender, etc.): ";
                cin >> searchGender;
                findAllPersonsByGender(people, searchGender);
                break;
            }
            case 5: {
                cout << "Exiting the program.\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 5);

    return 0;
}