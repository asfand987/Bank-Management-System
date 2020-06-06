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
    void depo(int);   //deposit
    void withdraw(int);
};

//-------------------------------------------------------------------

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

void account::depo(int n) {
    //cout << deposit << "1 " << endl;
    deposit = deposit + n;
    cout << "      Amount Successfully Deposited, Press Any Key To Continue...";
    //cout << deposit << "2 " << endl;
    //cout<<"\n\n\t Record Updated, Press Any Key To Continue...";
}

void account::withdraw(int n) {
    int temp = deposit;
    deposit = deposit - n;

    if(deposit < 0) {
        deposit = temp;
        cout << "      Withdrawal Failed Due To Insufficient Funds, Press Any Key To Continue...";
    }
    else {
        cout <<"      Withdrawal Successful, Press Any Key To Continue...";
    }
}

//----------------------------------------------------------------------

void write_account();
void intro();
void display_balance(int);
void deposit_amount(int);
void withdraw_amount(int);
void close_account(int);

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
            cout << "\n\n\t Enter The account No. : ";
            //cout << "\n\n\t Enter The Deposit Amount You Would Like To Make: ";
            cin >> num;
            deposit_amount(num);
            break;
        case '3': 
            cout << "\n\n\t Enter The account No. : ";
            cin >> num;
            withdraw_amount(num);
            break;
        case '4': 
            cout << "\n\n\t Enter The account No. : ";
            cin >> num;   //user enters account no.
			display_balance(num);
			break;
        case '5': 
        case '6': 
            cout << "\n\n\t Enter The account No. : ";
            cin >> num;   //user enters account no.
			display_balance(num);
			break;
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

//2
void deposit_amount(int n) {
    account ac;
    int amount;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    bool found = false;

    while(!File.eof()) {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if((ac.return_account() == n) && (n > 0)) {
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            ac.depo(amount);

            int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);       //sets the position where the next character is to be inserted to prevent copys.
            found = true;
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
	    	//cout<<"\n\n\t Record Updated, Press Any Key To Continue...";
            break;
        }

			//found=true;
    }

    File.close();
    if(found == false) {
        cout << "Record Does Not Exist... Press Any Key To Continue...";
    }
}

//3
void withdraw_amount(int n) {
    account ac; 
    int withdraw_amnt;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    bool found = false;

    while(!File.eof()) {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.return_account() == n) {

            cout << "Enter Amount You Would Like To Withdraw: ";
            cin >> withdraw_amnt;
            ac.withdraw(withdraw_amnt);

            int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);       //sets the position where the next character is to be inserted to prevent copys.
            found = true;
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            break;
        }
    }

    File.close();
    if(found == false) {
        cout << "Record Does Not Exist... Press Any Key To Continue...";
    }
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

//6
void close_account(int n) {
    account ac;
    int b;

    cout << "Enter account you want to delete : " <<  endl;
    cin >> b;

    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    ofstream newFile;
    newFile.open("temp.dat",ios::binary);

    inFile.seekg(0,ios::beg);
    
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) {
        if(ac.return_account() != n) {
            newFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }

    inFile.close();
    newFile.close();
    cout << "Account deleted";
    remove("account.dat");
    rename("temp.dat", "account.dat");
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
