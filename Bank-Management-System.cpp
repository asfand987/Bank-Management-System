#include <iostream>
#include <string>
#include<fstream>
#include <chrono>
#include <thread>

using namespace std;

class account {

    int id; //change to id
    char actHolderName[50];
    int balance;
    char type;   //checking or savings account.

public:

account() {
    int id = 0;
    char actHolderName;
    int balance = 0;
    char type;
    
};

account(int id, char actHolderName, int balance, char type) {
    id = id;
    actHolderName = actHolderName;
    balance = balance;
    type = type;
};

    void create_account(); 
    int return_account() const;
    void show_account() const;
    void depo(int n);   //deposit
    void withdraw(int n);
    void modify();
    void display_accounts();
};

//------------------------------------------------------------------------------------------------------------------------------

/***    
 * Function which displays the interface to the user who can then input the required values in order to make a new account.
***/
void account::create_account()  {

	cout  <<  "\n Enter The account No. :";
	cin >> id;
	
    cout << "\n\n Enter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(actHolderName,50);
	
    cout << "\n Enter Type of The account (c/s) : ";
	cin >> type;

    if((type != 'c') && (type != 's')) {
        cout << "Incorrect Account Type Enterred, Please Enter Correct Type (c/s) : ";
        cin >> type;
    }

    cout << "\n Enter Initial Deposit Amount: ";
    cin >> balance;

    cout << "\n Deposit Amount: " << balance << " Successful." << endl;
    cout << "\n Press Any Key To Continue...";

}

int account::return_account() const {
    return id;
}

void account::show_account() const {
    cout << "--------------------------------" << endl;
	cout << "        BALANCE ENQUIRY" << endl;
    cout << endl;
    cout << "        Account ID: " << id << endl;
    cout << "        Account Holder Name: " << actHolderName << endl;
    cout << "        Account Type: " << type << endl;
    cout << endl;
    cout << "        BALANCE: " << balance << endl;
    cout << "--------------------------------" << endl;
}

void account::depo(int n) {
    //cout << deposit << "1 " << endl;
    balance = balance + n;
    cout << "Amount Successfully Deposited, New Balance : " << balance << endl;
    cout << "Press Any Key To Continue...";
    //cout << deposit << "2 " << endl;
    //cout<<"\n\n\t Record Updated, Press Any Key To Continue...";
};

void account::withdraw(int n) {
    //int temp = deposit;
    int &checkValue = balance;
    checkValue = checkValue - n;
    //deposit = deposit - n;

    if(checkValue < 0) {
        //deposit = temp;
        //cout << temp << " " << checkValue;
        checkValue = checkValue + n;
        cout << "      Withdrawal Failed Due To Insufficient Funds, Press Any Key To Continue...";
    }
    else {
        balance = checkValue;
        cout << balance << endl;
        cout <<"      Withdrawal Successful, Press Any Key To Continue...";
    }
};

void account::modify() {
    char ch;
    
    cout << "Do You Want To Change Your Account No.? (y/n): ";
    cin >> ch;

    if(ch == 'y') {
        //int &i = acnt;
        //int temp;
        cout << "Enter New Account No. : ";
        cin >> id;
        cout << "Account No. Successfully Changed To: " << id << endl;
        //acnt = i;
        //cout << "Press Any Key To Continue...";
    }
    cin.ignore();
    
    cout <<"Do You Want To Change The Account Holder's Name? (y/n): ";
    cin >> ch;

    if(ch == 'y') {
        cout << "Enter New Account Holder Name: ";
        cin >> actHolderName;
        cout << "Account Holder Name Successully Changed. Press Any Key To Continue...";
    }
    
};

void account::display_accounts() {
    cout << "--------------------------------" << endl;
    cout << "ACCOUNTS LIST" << endl;
    cout << "Account ID: " << id << endl;
    cout << "Account Holder Name: " << actHolderName << endl;
    cout << "Account Type: " << type << endl;
    cout << "--------------------------------" << endl;
    cout << endl;
}   


//----------------------------------------------------------------------

void write_account();
void intro();
void display_balance(int);
void deposit_amount(int);
void withdraw_amount(int);
void close_account();
void modify_account();
void transfer_money();
void display_all();

/***
 * Function which wrties the data that the user entered in @create_account() into the "account.dat" file.
***/
void write_account() {
    account ac;
	ofstream outFile;

	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();

	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
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

//5
//6
void close_account() {
    account ac;
    int b;
    char c;

    //bool confirm = false;

    cout << "Enter Account You Want To Delete: ";
    cin >> b;

    cout << "Are You Sure You Want To Delete Your Account? (y/n)" << endl;
    cin >> c;

    if(c == 'n') {
        cout << "Account Will Not Be Deleted, Press Any Key To Return To Main Menu...";
        return;
    }

    ifstream inFile;
    ofstream newFile;

    inFile.open("account.dat",ios::binary);
    newFile.open("temp.dat",ios::binary);

    inFile.seekg(0,ios::beg);               //start at first pos.
    
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) {
        if(ac.return_account() != b) {
            newFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }

    inFile.close();
    newFile.close();

    remove("account.dat");
    rename("temp.dat", "account.dat");

    cout << "Account Successfully Closed, Press Any Key To Return To Main Menu...";
}

//7
void modify_account() {
    account ac;
    fstream File;
    int b;

    cout << "Enter The Account You Want To Modify: ";
    cin >> b;


    File.open("account.dat", ios::binary|ios::in|ios::out);

     while(!File.eof()) {
       File.read(reinterpret_cast<char *> (&ac), sizeof(account));
       if(ac.return_account() == b) {
           ac.modify();
       }
       else {
           cout << "Account Does Not Exist, Press Any Key To Continue...";
       }

        int pos=(-1)*static_cast<int>(sizeof(ac)); //...
		File.seekp(pos,ios::cur);       //sets the position where the next character is to be inserted to prevent copys.
        //found = true;
        File.write(reinterpret_cast<char *> (&ac), sizeof(account));
        break;
    }

    File.close();

}

//
void display_all() {
    account ac;
    ifstream File;

    File.open("account.dat",ios::binary);

    while(File.read(reinterpret_cast<char *> (&ac), sizeof(account))) {
        ac.display_accounts();   
    }

    File.close();
    cout << "Press Any Key To Continue..." << endl;
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

int main() {
    //Main menu

    char ch;
	int num;
    int account;
	intro();

	do {
		//system("cls");
		cout << "---------- MAIN MENU ----------" << endl;
        cout << "           01. NEW ACCOUNT" << endl;
        cout << "           02. DEPOSIT" << endl;
        cout << "           03. WITHDRAW" << endl;
        cout << "           04. BALANCE ENQUIRY" << endl;
        cout << "           05. CLOSE AN ACCOUNT" << endl;
        cout << "           06. MODIFY ACCOUNT" << endl;
        cout << "           07. ALL ACCOUNT" << endl;
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
            close_account();
			break;
        case '6': 
            modify_account();
            break;
        case '7':
            display_all();
            break;
        case '8':   
            cout << "Closing Application..." << endl;
            exit(0);
		default : cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}   while(ch != '8');
	return 0;
}
