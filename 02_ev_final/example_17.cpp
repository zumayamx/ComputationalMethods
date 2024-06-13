#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

//Clase para representar un libro
class Book {
public:
    Book(string title, string author, int year)
        : title(title), author(author), year(year), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    void displayInfo() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }

private:
    string title;
    string author;
    int year;
    bool isBorrowed;
};

//Clase para representar un usuario
class User {
public:
    User(string name, int id) : name(name), id(id) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

private:
    string name;
    int id;
};

//Clase para representar un prestamo
class Borrow {
public:
    Borrow(int userId, string bookTitle, time_t borrowDate)
        : userId(userId), bookTitle(bookTitle), borrowDate(borrowDate) {}

    int getUserId() const { return userId; }
    string getBookTitle() const { return bookTitle; }
    time_t getBorrowDate() const { return borrowDate; }

    void displayInfo() const {
        cout << "User ID: " << userId << ", Book Title: " << bookTitle
             << ", Borrow Date: " << ctime(&borrowDate);
    }

private:
    int userId;
    string bookTitle;
    time_t borrowDate;
};

//Class to represent a library
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addUser(const User& user) {
        users.push_back(user);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayInfo();
        }
    }

    void borrowBook(int userId, const string& bookTitle) {
        auto userIt = find_if(users.begin(), users.end(), [userId](const User& user) {
            return user.getId() == userId;
        });

        if (userIt == users.end()) {
            cout << "User not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt == books.end()) {
            cout << "Book not found!" << endl;
            return;
        }

        if (bookIt->getIsBorrowed()) {
            cout << "Book is already borrowed!" << endl;
            return;
        }

        bookIt->borrowBook();
        time_t now = time(0);
        borrows.push_back(Borrow(userId, bookTitle, now));
        cout << "Book borrowed successfully!" << endl;
    }

    void returnBook(int userId, const string& bookTitle) {
        auto borrowIt = find_if(borrows.begin(), borrows.end(), [userId, &bookTitle](const Borrow& borrow) {
            return borrow.getUserId() == userId && borrow.getBookTitle() == bookTitle;
        });

        if (borrowIt == borrows.end()) {
            cout << "Borrow record not found!" << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&bookTitle](const Book& book) {
            return book.getTitle() == bookTitle;
        });

        if (bookIt != books.end()) {
            bookIt->returnBook();
        }

        borrows.erase(borrowIt);
        cout << "Book returned successfully!" << endl;
    }

    void displayAllBorrows() const {
        for (const auto& borrow : borrows) {
            borrow.displayInfo();
        }
    }

private:
    vector<Book> books;
    vector<User> users;
    vector<Borrow> borrows;
};

//Menu functions
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Users" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Borrows" << endl;
    cout << "8. Exit" << endl;
}

void addBook(Library& library) {
    string title, author;
    int year;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    library.addBook(Book(title, author, year));
}

void addUser(Library& library) {
    string name;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    library.addUser(User(name, id));
}

void borrowBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.borrowBook(userId, bookTitle);
}

void returnBook(Library& library) {
    int userId;
    string bookTitle;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, bookTitle);
    library.returnBook(userId, bookTitle);
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addUser(library);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                library.displayAllUsers();
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                library.displayAllBorrows();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}