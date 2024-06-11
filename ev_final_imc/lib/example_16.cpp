#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Task {
public:
    Task(string description, string dueDate) : description(description), dueDate(dueDate), completed(false) {}

    string getDescription() const { return description; }
    string getDueDate() const { return dueDate; }
    bool isCompleted() const { return completed; }

    void markCompleted() {
        completed = true;
    }

    void displayInfo() const {
        cout << "Description: " << description << ", Due Date: " << dueDate
             << ", Completed: " << (completed ? "Yes" : "No") << endl;
    }

private:
    string description;
    string dueDate;
    bool completed;
};

class TaskManager {
public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void removeTask(const string& description) {
        tasks.erase(remove_if(tasks.begin(), tasks.end(), [&description](const Task& task) {
            return task.getDescription() == description;
        }), tasks.end());
    }

    void displayAllTasks() const {
        for (const auto& task : tasks) {
            task.displayInfo();
        }
    }

    void markTaskCompleted(const string& description) {
        auto it = find_if(tasks.begin(), tasks.end(), [&description](const Task& task) {
            return task.getDescription() == description;
        });
        if (it != tasks.end()) {
            it->markCompleted();
        } else {
            cout << "Task not found!" << endl;
        }
    }

private:
    vector<Task> tasks;
};

int main() {
    TaskManager manager;
    manager.addTask(Task("Finish the report", "2024-06-30"));
    manager.addTask(Task("Prepare presentation", "2024-06-15"));
    manager.addTask(Task("Buy groceries", "2024-06-10"));

    cout << "All tasks:" << endl;
    manager.displayAllTasks();

    cout << "Marking 'Buy groceries' as completed:" << endl;
    manager.markTaskCompleted("Buy groceries");

    cout << "All tasks after marking one as completed:" << endl;
    manager.displayAllTasks();

    cout << "Removing 'Finish the report':" << endl;
    manager.removeTask("Finish the report");

    cout << "All tasks after removal:" << endl;
    manager.displayAllTasks();

    return 0;
}