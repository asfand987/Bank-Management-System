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
    void create_account(); 
    void deposit();             
    //3
    void balance_enquiry();
};

void account::create_account()
{
	cout  <<  "\n Enter The account No. :";
	cin >> accountNumber;
	
    cout << "\n\n Enter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(actHolderName,50);
	
    cout << "\n Enter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	
    cout << "\n Enter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin >> deposit;
	cout << "\n\n\n Account Created......Press Any Key To Continue..." << endl;
}


}


void write_account();
void intro();

int main() {
    //Main menu

    char ch;
	int num;
	intro();

	do
	{
		//system("cls");
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
        cin >> ch;
        
		//system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
        case '2': 
        case '3': 
        case '4': 
        case '5': 
        case '6': 
        case '7': 
        case '8':   
		default : cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


void write_account() {
    account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();

    /*cout << "Testing :" << endl;
    account ac;
	ofstream outFile;
	outFile.open("list.txt",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();*/
}


void intro()
{
	cout << "\n\n\n\t  BANK";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\t  SYSTEM";
	cout << "\n\n\n\nMADE BY : ASFAND KHAN";
	cout << "\n\nPRESS ENTER TO CONTINUE: ";
    cout << endl;
	cin.get();
}
