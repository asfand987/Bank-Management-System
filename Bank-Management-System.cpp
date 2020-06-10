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

account() {
    int acnt = 0;
    char actHolderName;
    int deposit = 0;
    char type;
    
};

account(int acnt, char actHolderName, int deposit, char type) {
    acnt = acnt;
    actHolderName = actHolderName;
    deposit = deposit;
    type = type;
};

    void create_account(); 
    int return_account() const;
    void show_account() const;
    void depo(int);   //deposit
    void withdraw(int);
    void modify();
    void transfer(int);
    void t(account &account, int balance);
   
};

//-------------------------------------------------------------------


void account::create_account()
{
    int &temp = deposit;
    char tempCh;

	cout  <<  "\n Enter The account No. :";
	cin >> acnt;
	
    cout << "\n\n Enter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(actHolderName,50);
	
    cout << "\n Enter Type of The account (c/s) : ";
	cin >> tempCh;

    if((tempCh != 'c') && (tempCh != 's')) {
        cout << "Incorrect Account Type Enterred, Please Enter Correct Type (c/s) : ";
        cin >> type;
    }
	//type = toupper(type);
	
    cout << "\n Enter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin >> temp;
    if((type == 'c') && (temp >= 1000)) {
	    cout << "\n\n\n Current Account Created......Press Any Key To Continue..." << endl;
    }
    else if((type == 's') && (temp >= 500)) {
	    cout << "\n\n\n Savings Account Created......Press Any Key To Continue..." << endl;
    }
    else if((type == 'c') && (temp < 1000)) {
        cout << "Minimum deposit required for 's' Account Is 1000, Please Enter Your Deposit Again: ";
        cin >> temp;
        deposit = temp;
        cout << "Current Account Created, Press Any Key To Continue..." << endl;
    }
    else if((type == 's') && (temp < 500)) {
        cout << "Minimum deposit required for 's' Account Is 500, Please Enter Your Deposit Again: ";
        cin >> temp;
        deposit = temp;
        cout << " Savings Account Created, Press Any Key To Continue..." << endl;
    }
    else {
        cout << "Error, Please Press Any Key To Continue...";
    }

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
    cout << "Amount Successfully Deposited, New Balance : " << deposit << endl;
    cout << "Press Any Key To Continue...";
    //cout << deposit << "2 " << endl;
    //cout<<"\n\n\t Record Updated, Press Any Key To Continue...";
}

void account::withdraw(int n) {
    //int temp = deposit;
    int &checkValue = deposit;
    checkValue = checkValue - n;
    //deposit = deposit - n;

    if(checkValue < 0) {
        //deposit = temp;
        //cout << temp << " " << checkValue;
        checkValue = checkValue + n;
        cout << "      Withdrawal Failed Due To Insufficient Funds, Press Any Key To Continue...";
    }
    else {
        deposit = checkValue;
        cout << deposit << endl;
        cout <<"      Withdrawal Successful, Press Any Key To Continue...";
    }
}

void account::modify() {
    char ch;
    
    cout << "Do You Want To Change Your Account No.? (y/n): ";
    cin >> ch;

    if(ch == 'y') {
        //int &i = acnt;
        //int temp;
        cout << "Enter New Account No. : ";
        cin >> acnt;
        cout << "Account No. Successfully Changed To: " << acnt << endl;
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
    
}

void account::transfer(int amount) {
    int &checkValue = deposit;
    int val = -amount;
    checkValue = checkValue + val;
    //cout << checkValue << " " << amount;
    deposit = checkValue;
}

void t(account a, int bal) {
    //cout << "Deposit1 : " << deposit << endl;
   /* int &balance = deposit;
    balance = balance - bal;
    deposit = balance;
    cout << balance << endl;
    
    int &balance2 = a.deposit;
    balance2 = balance2 + bal;  
    a.deposit = balance2;
    cout << balance2 << endl;*/
    deposit = bal;
    a.deposit = a.deposit - bal;
  
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

//5
void transfer_money() {
    account ac, ac2;
    int acnt1, acnt2;
    int val;

    fstream File;
    fstream File2;

    cout << "Enter Your Account: ";
    cin >> acnt1;

    cout << "Enter Other Account: ";
    cin >> acnt2;

    File.open("account.dat", ios::binary|ios::in|ios::out);
    File2.open("account.dat", ios::binary|ios::in|ios::out);

    cout << "Enter Amount You Would Like To Transer: ";
    cin >> val;

    while(!File.eof() &&!File2.eof()) {
     
       File.read(reinterpret_cast<char *> (&ac), sizeof(account));
       File2.read(reinterpret_cast<char *> (&ac2), sizeof(account));

       if(ac.return_account() == acnt1) {
           cout << "Yes It's Working" << endl;
       }

       if(ac2.return_account() == acnt2) {
           cout << "Yup" << endl;
       }

       ac.t(ac2, val); 

       int pos2 = (-1)*static_cast<int>(sizeof(ac2)); //...
	   File2.seekp(pos2,ios::cur);
       
       int pos = (-1)*static_cast<int>(sizeof(ac)); //...
	   File.seekp(pos,ios::cur);       //sets the position where the next character is to be inserted to prevent copys.
       //found = true;
       File.write(reinterpret_cast<char *> (&ac), sizeof(account));
       File2.write(reinterpret_cast<char *> (&ac2), sizeof(account));
       
       //File.write(reinterpret_cast<char *> (&ac2), sizeof(account));

       break; 
     }

    File.close();
    File2.close();
}

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
        cout << "           05. TRANSFERS" << endl;
        cout << "           06. CLOSE AN ACCOUNT" << endl;
        cout << "           07. MODIFY ACCOUNT" << endl;
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
            //Must only be possible if two accounts exists.
            //int account;
            transfer_money();
            break;
        case '6': 
            close_account();
			break;
        case '7': 
            modify_account();
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
