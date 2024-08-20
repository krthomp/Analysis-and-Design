#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

class Course {
public:
    string courseId;
    string title;
    vector<string> prerequisites;

    // Default constructor
    Course() : courseId(""), title(""), prerequisites() {}

    // Parameterized constructor
    Course(string id, string t, vector<string> prereqs)
        : courseId(id), title(t), prerequisites(prereqs) {}

    // Function to print course information
    void printCourseInfo() const {
        cout << "Course ID: " << courseId << endl;
        cout << "Title: " << title << endl;
        if (prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        }
        else {
            cout << "Prerequisites: ";
            for (const auto& prereq : prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
};

// Function prototypes
void loadCourses(const string& filename, map<string, Course>& courses);
void printCourseList(const map<string, Course>& courses);
void printCourseInfo(const map<string, Course>& courses, const string& courseId);
void showMenu();

int main() {
    map<string, Course> courses;
    int choice = 0;

    while (choice != 9) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter file name or path (e.g., CS_300.csv): ";
            cin >> filename;
            loadCourses(filename, courses);
            break;
        }
        case 2:
            printCourseList(courses);
            break;
        case 3: {
            string courseId;
            cout << "Enter course ID: ";
            cin >> courseId;
            printCourseInfo(courses, courseId);
            break;
        }
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

void showMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "1. Load Courses" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

void loadCourses(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, title, prereq;
        vector<string> prerequisites;

        // Read course ID
        getline(iss, id, ',');
        // Read course title
        getline(iss, title, ',');
        // Read prerequisites
        while (getline(iss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        courses[id] = Course(id, title, prerequisites);
    }
    file.close();
    cout << "Courses loaded successfully." << endl;
}

void printCourseList(const map<string, Course>& courses) {
    vector<string> courseIds;
    for (const auto& pair : courses) {
        courseIds.push_back(pair.first);
    }

    sort(courseIds.begin(), courseIds.end());

    cout << "Course List:" << endl;
    for (const auto& id : courseIds) {
        cout << id << ": " << courses.at(id).title << endl;
    }
}

void printCourseInfo(const map<string, Course>& courses, const string& courseId) {
    auto it = courses.find(courseId);
    if (it != courses.end()) {
        it->second.printCourseInfo();
    }
    else {
        cout << "Course not found." << endl;
    }
}
