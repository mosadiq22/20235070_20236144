#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool validateEmail(const string& email) {
    int atPos = email.find('@');
    int dotPos = email.find('.', atPos);
    return (atPos != string::npos && dotPos != string::npos && dotPos > atPos);
}

bool validatePassword(const string& password) {
    return password.length() >= 6;
}

class User {
public:
    string username;
    string email;
    string password;

    User(string uname, string mail, string pass) : username(uname), email(mail), password(pass) {}

    void displayUser() const {
        cout << "Username: " << username << "\n";
        cout << "Email: " << email << "\n";
    }
};

class Admin {
public:
    vector<User> users;

    void addUser(const string& username, const string& email, const string& password) {
        bool emailValid = validateEmail(email);
        bool passwordValid = validatePassword(password);

        if (!emailValid && !passwordValid) {
            cout << "Invalid email format! The email should contain '@' and a '.' after '@'.\n Please try again.\n";
            cout << "Password is too short! It must be at least 6 characters long.\n Please try again.\n";
            return;
        }

        if (!emailValid) {
            cout << "Invalid email format! The email should contain '@' and a '.' after '@'.\n Please try again.\n";
            return;
        }

        if (!passwordValid) {
            cout << "Password is too short! It must be at least 6 characters long.\n Please try again.\n";
            return;
        }

        users.push_back(User(username, email, password));
        cout << "User added successfully!\n";
    }

    void deleteUser(const string& username) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->username == username) {
                users.erase(it);
                cout << "User " << username << " deleted successfully!\n";
                return;
            }
        }
        cout << "User not found!\n";
    }

    void updateUser(const string& username, const string& newEmail, const string& newPassword) {
        bool emailValid = validateEmail(newEmail);
        bool passwordValid = validatePassword(newPassword);

        if (!emailValid && !passwordValid) {
            cout << "Invalid email format! The email should contain '@' and a '.' after '@'.\n Please try again.\n";
            cout << "Password is too short! It must be at least 6 characters long.\n Please try again.\n";
            return;
        }

        if (!emailValid) {
            cout << "Invalid email format! The email should contain '@' and a '.' after '@'.\n Please try again.\n";
            return;
        }

        if (!passwordValid) {
            cout << "Password is too short! It must be at least 6 characters long.\n Please try again.\n";
            return;
        }

        for (auto& user : users) {
            if (user.username == username) {
                user.email = newEmail;
                user.password = newPassword;
                cout << "User information updated successfully!\n";
                return;
            }
        }

        cout << "User not found!\n";
    }

    void viewAllUsers() const {
        if (users.empty()) {
            cout << "No users available.\n";
            return;
        }

        cout << "List of users:\n";
        for (const auto& user : users) {
            user.displayUser();
            cout << "----------\n";
        }
    }

    void changeUserPassword(const string& username, const string& newPassword) {
        bool passwordValid = validatePassword(newPassword);

        if (!passwordValid) {
            cout << "Password is too short! It must be at least 6 characters long.\n Please try again.\n";
            return;
        }

        for (auto& user : users) {
            if (user.username == username) {
                user.password = newPassword;
                cout << "Password for user " << username << " changed successfully!\n";
                return;
            }
        }

        cout << "User not found!\n";
    }
};

void adminMenu(Admin& admin) {
    int choice;
    string username, email, password;

    while (true) {
        cout << "\nAdmin Menu\n";
        cout << "1. Add User\n";
        cout << "2. Delete User\n";
        cout << "3. Update User\n";
        cout << "4. Change User Password\n";
        cout << "5. View All Users\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> password;
            admin.addUser(username, email, password);
            break;

        case 2:
            cout << "Enter username to delete: ";
            cin >> username;
            admin.deleteUser(username);
            break;

        case 3:
            cout << "Enter username to update: ";
            cin >> username;
            cout << "Enter new email: ";
            cin >> email;
            cout << "Enter new password: ";
            cin >> password;
            admin.updateUser(username, email, password);
            break;

        case 4:
            cout << "Enter username to change password: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> password;
            admin.changeUserPassword(username, password);
            break;

        case 5:
            admin.viewAllUsers();
            break;

        case 6:
            cout << "Exiting admin menu.\n";
            return;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}

int main() {
    Admin admin;
    adminMenu(admin);

    return 0;
}
