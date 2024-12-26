#include <iostream>
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

void registerUser() {
    string username, email, password;

    cout << "Enter username: "; cin >> username;

    cout << "Enter email: "; cin >> email;

    if (!validateEmail(email)) {

        cout << "Invalid email format. Please try again.\\n";

        return;
    }

    cout << "Enter password (at least 6 characters): "; cin >> password;

    if (!validatePassword(password)) {

        cout << "Password is too short. It must be at least 6 characters long.\\n";

        return;
    }

    cout << "Registration successful!\\n";

    cout << "Username: " << username << "\\n";

    cout << "Email: " << email << "\\n";

}

int main() {
    cout << "Welcome to User Registration System!\n";
    registerUser();
    return 0;
}