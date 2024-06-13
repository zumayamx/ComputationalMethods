#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    Student(string name, int age, string course) : name(name), age(age), course(course) {}

    string getName() const { return name; }
    int getAge() const { return age; }
    string getCourse() const { return course; }

    void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", Course: " << course << endl;
    }

private:
    string name;
    int age;
    string course;
};

class StudentManager {
public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void removeStudent(const string& name) {
        students.erase(remove_if(students.begin(), students.end(), [&name](const Student& student) {
            return student.getName() == name;
        }), students.end());
    }

    void displayAllStudents() const {
        for (const auto& student : students) {
            student.displayInfo();
        }
    }

    void findStudent(const string& name) const {
        auto it = find_if(students.begin(), students.end(), [&name](const Student& student) {
            return student.getName() == name;
        });
        if (it != students.end()) {
            it->displayInfo();
        } else {
            cout << "Student not found!" << endl;
        }
    }

private:
    vector<Student> students;
};

int main() {
    StudentManager manager;
    manager.addStudent(Student("Alice", 20, "Computer Science"));
    manager.addStudent(Student("Bob", 22, "Mathematics"));
    manager.addStudent(Student("Charlie", 19, "Physics"));

    cout << "All students:" << endl;
    manager.displayAllStudents();

    cout << "Finding Alice:" << endl;
    manager.findStudent("Alice");

    cout << "Removing Bob:" << endl;
    manager.removeStudent("Bob");

    cout << "All students after removal:" << endl;
    manager.displayAllStudents();

    return 0;
}