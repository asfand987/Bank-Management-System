#include <iostream>
#include <string>
using namespace std;

class account {
    int accountNumber;
    char actHolderName[50];
    int deposit;
    char type;   //checking or savings account.


public:
    void create_account();              //create new account.
};

int main() {
    //Main menu 

    cout << "---------- MAIN MENU ----------" << endl;
    cout << "           01. NEW ACCOUNT" << endl;
    cout << "           02. DEPOSIT" << endl;
    cout << "           03. WITHDRAW" << endl;
    cout << "           04. BALANCE ENQUIRY" << endl;
    cout << "           05. ALL ACCOUNT HOLDER LIST" << endl;
    cout << "           06. CLOSE AN ACCOUNT" << endl;
    cout << "           07. MODIFY AND ACCOUNT" << endl;
    cout << "           08. EXIT" << endl;
    cout << "-------------------------------" << endl;

    //User inputs
    int i;
    cout << "Select Your Option <1-8>: ";  
    cin >> i;
}

void account::create_account() {
    
}