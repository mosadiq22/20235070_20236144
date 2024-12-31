#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>  // For std::numeric_limits
using namespace std;

// Enumeration for user roles
enum class UserRole {
    Admin,
    Librarian,
    Member
};

// Function to hash passwords (basic hashing for demonstration purposes)
string hashPassword(const string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return to_string(hash);
}

// Structure to store user information
struct User {
    string username;
    string hashedPassword;
    string email;
    UserRole role;  // User role

    User(string uname, string mail, string pass, UserRole r) : username(uname), email(mail), hashedPassword(pass), role(r) {}
};

// Function to validate email format
bool validateEmail(const string& email) {
    int atPos = email.find('@');
    int dotPos = email.find('.', atPos);
    return (atPos != string::npos && dotPos != string::npos && dotPos > atPos);
}

// Function to validate password length
bool validatePassword(const string& password) {
    return password.length() >= 6;
}

// Function to register a new user
void registerUser(vector<User>& users) {
    string username, email, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter email: ";
    cin >> email;

    if (!validateEmail(email)) {
        cout << "Invalid email format. Please try again.\n";
        return;
    }

    cout << "Enter password (at least 6 characters): ";
    cin >> password;

    if (!validatePassword(password)) {
        cout << "Password is too short. It must be at least 6 characters long.\n";
        return;
    }

    // Hash the password before storing
    string hashedPassword = hashPassword(password);
    users.push_back(User(username, email, hashedPassword, UserRole::Member));  // Default role is Member
    cout << "Registration successful!\n";
}

// Function to validate user login
UserRole loginUser(const vector<User>& users) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string hashedPassword = hashPassword(password);
    for (const auto& user : users) {
        if (user.username == username && user.hashedPassword == hashedPassword) {
            cout << "Login successful!\n";
            return user.role;  // Return the role
        }
    }
    cout << "Invalid username or password.\n";
    return UserRole::Member;  // Return a default role if login fails
}

// Book structure to represent a book
struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;

    Book(int id, string title, string author) : id(id), title(title), author(author), isAvailable(true) {}
};

// Library class to manage users and books
class Library {
private:
    vector<Book> books;

public:
    void addBook(const string& title, const string& author) {
        int id = books.size() + 1;  // Simple ID assignment
        books.push_back(Book(id, title, author));
        cout << "Book added successfully!\n";
    }

    void removeBook(int id) {
        auto it = find_if(books.begin(), books.end(), [id](const Book& book) { return book.id == id; });
        if (it != books.end()) {
            books.erase(it);
            cout << "Book removed successfully!\n";
        }
        else {
            cout << "Book not found!\n";
        }
    }

    void displayBooks() const {
        cout << "\nAvailable Books:\n";
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
        }
    }

    void borrowBook(int id) {
        auto it = find_if(books.begin(), books.end(), [id](Book& book) { return book.id == id; });
        if (it != books.end()) {
            if (it->isAvailable) {
                it->isAvailable = false;
                cout << "You have borrowed \"" << it->title << "\" successfully!\n";
            }
            else {
                cout << "Sorry, this book is currently not available.\n";
            }
        }
        else {
            cout << "Book not found!\n";
        }
    }

    void returnBook(int id) {
        auto it = find_if(books.begin(), books.end(), [id](Book& book) { return book.id == id; });
        if (it != books.end()) {
            it->isAvailable = true;
            cout << "You have returned \"" << it->title << "\" successfully!\n";
        }
        else {
            cout << "Book not found!\n";
        }
    }

    void searchBooks(const string& filter) const {
        cout << "\n--- Search Results ---\n";
        for (const auto& book : books) {
            if (book.title.find(filter) != string::npos) {
                cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << endl;
            }
        }
    }
};

// Function to display the Management System menu
void displayManagementMenu() {
    cout << "\n--- Management System ---\n";
    cout << "1. User Management\n";
    cout << "2. Admin Management\n";
    cout << "3. Librarian Management\n";
    cout << "4. Exit\n";
}

// Function to display user role menu
void displayUserRoleMenu() {
    cout << "\n--- User Role Selection ---\n";
    cout << "1. Admin\n";
    cout << "2. Librarian\n";
    cout << "3. Member\n";
    cout << "4. Back to Management System\n";
}

// Function to display menu based on user type
void displayMenu(const UserRole& userType, Library& library) {
    if (userType == UserRole::Admin) {
        cout << "\n--- Admin Menu ---" << endl;
        cout << "1. Add New User\n";
        cout << "2. Remove User\n";
        cout << "3. View System Reports\n";
        cout << "4. Manage Library Settings\n";
        cout << "5. Logout\n";
    }
    else if (userType == UserRole::Librarian) {
        cout << "\n--- Librarian Menu ---" << endl;
        cout << "1. Add New Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. View Member Records\n";
        cout << "6. Logout\n";
    }
    else if (userType == UserRole::Member) {
        cout << "\n--- Member Menu ---" << endl;
        cout << "1. Search Books\n";
        cout << "2. View Available Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Logout\n";
    }
    else {
        cout << "\nInvalid user type. Please contact the administrator." << endl;
    }
}

int main() {
    vector<User> users;
    Library library;  // Library instance
    int choice;

    do {
        displayManagementMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int roleChoice;
            do {
                displayUserRoleMenu();
                cout << "Enter your choice: ";
                cin >> roleChoice;

                switch (roleChoice) {
                case 1:
                    registerUser(users);
                    break;
                case 2:
                    registerUser(users);
                    break;
                case 3:
                    registerUser(users);
                    break;
                case 4:
                    cout << "Returning to Management System.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }
            } while (roleChoice != 4);
            break;
        }
        case 2: {
            UserRole role = loginUser(users);
            displayMenu(role, library);
            break;
        }
        case 3:
            cout << "Librarian Management selected.\n";
            // Librarian management code goes here
            break;
        case 4:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}