#include <iostream>
#include <string>
#include<fstream>
#include <chrono>
#include <thread>

using namespace std;

class account {
    int acnt;
    char actHolderName[50];
    int deposit;
    char type;   //checking or savings account.


public:
    void create_account(); 
    int return_account() const;
    void show_account() const;
};

void account::create_account()
{
	cout  <<  "\n Enter The account No. :";
	cin >> acnt;
	
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

int account::return_account() const {
    return acnt;
}

void account::show_account() const {
    cout << "--------------------------------" << endl;
	cout << "        BALANCE ENQUIRY" << endl;
    cout << endl;
    cout << "        Account: " << acnt << endl;
    cout << "        Account Holder Name: " << actHolderName << endl;
    cout << "        Account Type: " << type << endl;
    cout << endl;
    cout << "        BALANCE: " << deposit << endl;
    cout << "--------------------------------" << endl;
}

void write_account();
void intro();
void display_balance(int);

int main() {
    //Main menu

    char ch;
	int num;
	intro();

	do  {
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
            cout << "\n\n\t Enter The account No. : ";
            cin >> num;   //user enters account no.
			display_balance(num);
			break;
        case '5': 
        case '6': 
        case '7': 
        case '8':   
		default : cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}   while(ch!='8');
	return 0;
}


void write_account() {
    account ac;
	ofstream outFile;
    //outFile.open("test.txt");
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


//4
void display_balance(int n) {
    account ac;
    ifstream inFile;
	inFile.open("account.dat",ios::binary);
    
    bool found = false;

    if(!inFile) {
        cout<<"File could not be open !! Press any Key To Continue...";
		return;
        /*cout << "Account " << n << " does not exist." << endl;
        cout << endl;
        cout <<"You Will Now Be Redirected Back To Main Menu..." << endl;
        chrono::seconds dura( 2);
        this_thread::sleep_for( dura );
      
        return;*/
    }

    cout << endl;

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))  //reinterpret_cast<char *> (&ac) = treating &ac as a char 
    {
        if(ac.return_account() == n) {
            found = true;
            ac.show_account(); 
        }
      
	}

    if(found == false) {
         cout << endl;
            cout << "Account Does Not Exist In Database..." << endl;
    }

    cout << endl;
    cout << "Press Any Key To Continue...";
    inFile.close(); 
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
