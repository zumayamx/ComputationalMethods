#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
public:
    Book(string title, string author, int year) : title(title), author(author), year(year) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author << ", Year: " << year << endl;
    }

private:
    string title;
    string author;
    int year;
};

class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const string& title) {
        books.erase(remove_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.getTitle() == title;
        }), books.end());
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void findBook(const string& title) const {
        auto it = find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.getTitle() == title;
        });
        if (it != books.end()) {
            it->displayInfo();
        } else {
            cout << "Book not found!" << endl;
        }
    }

private:
    vector<Book> books;
};

int main() {
    Library library;
    library.addBook(Book("1984", "George Orwell", 1949));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", 1960));
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", 1925));

    cout << "All books:" << endl;
    library.displayAllBooks();

    cout << "Finding 1984:" << endl;
    library.findBook("1984");

    cout << "Removing The Great Gatsby:" << endl;
    library.removeBook("The Great Gatsby");

    cout << "All books after removal:" << endl;
    library.displayAllBooks();

    return 0;
}