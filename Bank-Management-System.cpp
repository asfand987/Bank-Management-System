#include <iostream>
#include <string>
#include<fstream>
using namespace std;

class account {
    int accountNumber;
    char actHolderName[50];
    int deposit;
    char type;   //checking or savings account.


public:
    void create_account();              //create new account.
};

void account::create_account() {
    cout << "Testing" << endl;
}


void write();

int main() {
    //Main menu

    char ch;
	int num;
	//intro();
	do
	{
		system("cls");
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
        cin >> num;
        
		system("cls");
		switch(ch)
		{
		case '1':
			write();
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


void write() {
    account ac;
	ofstream outFile;
	outFile.open("list.txt",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void intro() {

}