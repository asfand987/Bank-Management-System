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


void create_account();

int main() {
    //Main menu

    int i;
    do {
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
        cout << "Select Your Option <1-8>: ";  
        cin >> i;
        
        switch(i) {
            case '1' :
                create_account();
                break;
            default:
                cout << "INCORRECT INPUT" << endl;
        }

    } while(i != '8'); {
        return 0;
    }
}

void account::create_account() {
    cout << "YOU SELECTED 01" << endl;
    cout << "CREATE NEW ACCOUNT" << endl;
}