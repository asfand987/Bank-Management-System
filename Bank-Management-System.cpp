#include <iostream>
#include <string>
#include<fstream>
#include <chrono>
#include <thread>

using namespace std;

/***
 * Banking-Management-System.
***/

class account {

    int id; 
    char actHolderName[50];
    int balance;
    char type;   

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
// Functions with access to Account.

/***    
 * Function which displays the interface to the user who can then input the required values in order to make a new account.
 * Function is called by @write_account() method.
***/
void account::create_account()  
{
    cout  <<  "\n         Enter The Account No. : ";

    bool inputValid = false;

    while (!inputValid) 
    {
        cin >> id;

        if(!std::cin.fail() && (std::cin.peek()==EOF || std::cin.peek()=='\n'))  
        {
            inputValid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Error, Please Enter A number: ";
        }
    }

    inputValid = false;
	
    cout << "\n         Enter The Name of The Account Holder : ";
    cin.ignore(); 
    cin.getline(actHolderName,50);
	
    cout << "\n         Enter Type of The Account (c/s) : ";

    while (!inputValid) 
    {
        cin >> type;

        if((type != 'c') && (type != 's')) 
        {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Incorrect Account Type Enterred, Please Enter Correct Type (c/s) : ";
        }
        else 
        {
            inputValid = true;
        }
    }

    inputValid = false;
    
    cout << "\n         Enter Initial Deposit Amount: ";

    while (!inputValid) 
    {
        cin >> balance;

        if(balance <= 0) 
        {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Error, Please Enter An Intital Deposit Amount of > 0 : ";
        }
        else 
        {
            cout << "\n         Deposit Amount: " << balance << ", Successful." << endl;
            cout << "\n         Press Any Key To Continue...";
            inputValid = true;
        }
    }
}

/***
 * Returns the id of the account.
***/
int account::return_account() const 
{
    return id;
}

/***
 * Function which displays all the information about the account. 
 * Function is called by @display_actInfo(int) which is used in @main.
***/
void account::show_account() const 
{
    cout << "--------------------------------" << endl;
    cout << "        ACCOUNT ENQUIRY" << endl;
    cout << endl;
    cout << "        Account ID: " << id << endl;
    cout << "        Account Holder Name: " << actHolderName << endl;
    cout << "        Account Type: " << type << endl;
    cout << endl;
    cout << "        BALANCE: " << balance << endl;
    cout << "--------------------------------" << endl;
}

/***
 * Function deposits amount that the user entered into the account.
 * Function is called by @deposit_amount(int) which is used in @main.
***/
void account::depo(int n) 
{
    balance = balance + n;
    cout << "         Amount Successfully Deposited, New Balance : " << balance << endl;
    cout << "         Press Any Key To Continue...";
    
};

/***
 * Function withdraws money from the account.
 * Function is called by @withdraw_amount(int) which is used in @main.
***/
void account::withdraw(int n) 
{    
    int &checkValue = balance;
    checkValue = checkValue - n;

    if(checkValue < 0) 
    {    
        checkValue = checkValue + n;
        cout << "         Withdrawal Failed Due To Insufficient Funds, Press Any Key To Continue..." << endl;
    }
    else 
    {
        balance = checkValue;
        cout << "         Withdrawal Successful, New Balance: " << balance << endl;
        cout << "         Press Any Key To Continue..." << endl;
    }
};

/***
 * Function which allows account holder to modify details about the account owned.
 * Function is used in @modify_account() which is used in @main.
***/
void account::modify() 
{
    char ch;
    
    cout << "       Do You Want To Change Your Account No.? (y/n): ";
    cin >> ch;

    if(ch == 'y') 
    {

        cout << "       Enter New Account No. : ";
        cin >> id;
        cout << "       Account No. Successfully Changed To: " << id << endl;

    }
    cin.ignore();
    
    cout <<"       Do You Want To Change The Account Holder's Name? (y/n): ";
    cin >> ch;

    if(ch == 'y') 
    {
        cout << "       Enter New Account Holder Name: ";
        cin >> actHolderName;
        cout << "       Account Holder Name Successully Changed. Press Any Key To Continue...";
    }
    else 
    {
        cout <<"       Press Any Key To Continue..." << endl;
    }
    
};

/***
 * Function displays a list of all accounts currently in the database.
 * Function is called by @display_all() which is used in @main.
***/
void account::display_accounts() 
{
    cout << "--------------------------------------------" << endl;
    cout << "               ACCOUNT:" << endl;
    cout << "       Account ID: " << id << endl;
    cout << "       Account Holder Name: " << actHolderName << endl;
    cout << "       Account Type: " << type << endl;
    cout << "--------------------------------------------" << endl;
    cout << endl;
}   


//-----------------------------------------------------------------------------------------------------------------------
//Functions used in @main().

/***
 * Information user sees upon starting the program.
***/
void intro();

/***
 * 01. 
***/
void write_account();

/***
 * 02. 
***/
void deposit_amount(int);

/***
 * 03. 
***/
void withdraw_amount(int);

/***
 * 04. 
***/
void display_actInfo(int);

/***
 * 05. 
***/
void close_account();

/***
 * 06. 
***/
void modify_account();

/***
 * 07. 
***/
void display_all();

//-----------------------------------------------------------------------------------------------------------------------------

/***
 * Function used to display information at the start of the program.
***/
void intro()
{
    cout << "\n\n\n\t   BANK";
    cout << "\n\n\tMANAGEMENT";
    cout << "\n\n\t  SYSTEM";
    cout << "\n\n\n\nMADE BY : ASFAND KHAN";
    cout << "\n\nPRESS ENTER TO CONTINUE: ";
    cout << endl;
    cin.get();
}

/***
 * 01.
 * Function which wrties the data that the user entered in @create_account() into the "account.dat" file.
***/
void write_account() 
{
    account ac;
    ofstream outFile;

    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();

    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));

    outFile.close();
}

/***
 * 02.
 * Function used to deposit money into the account. 
 * @depo(int) function used from Account class.
***/
void deposit_amount() 
{
    account ac;
    fstream File;
    int amount;
    int id;
    bool found = false;
    bool isValid = false;

    File.open("account.dat", ios::binary|ios::in|ios::out);
    
    cout << "\n\n\t Enter The account No. : ";

    while (!isValid) 
    {
        cin >> id;

        if(id <= 0) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Error, Please Enter Correct Account (Integer): ";
        }
        else 
        {
            isValid = true;
        }
    }

    isValid = false;
    

    while(!File.eof()) 
    {

        File.read(reinterpret_cast<char *> (&ac), sizeof(account));

        if((ac.return_account() == id) && (id > 0)) 
        {

            cout << "         Enter Deposit Amount: ";

            while(!isValid) 
            {
                cin >> amount;

                if(amount <= 0) 
                {
                    cin.clear();
                    cin.ignore(256,'\n');
                    cout << "         Error, Please Enter An Amount > 0 : ";
                }
                else 
                {
                    isValid = true;
                }
            }

            ac.depo(amount);

            //sets the position where the next character is to be inserted to prevent copys.
            int pos = (-1)*static_cast<int>(sizeof(ac));
	    File.seekp(pos,ios::cur);   

            found = true;
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
	    	
            break;
        }
    }

    File.close();

    if(!found) 
    {
        cout << "         Record Does Not Exist... Press Any Key To Continue..." << endl;
    }
}

/***
 * 03.
 * Function used to withdraw money out of the account. 
 * @withdraw(int) function used from Account class.
***/
void withdraw_amount() 
{
    account ac; 
    fstream File;
    int amount;
    int id;
    bool isValid;
    

    File.open("account.dat", ios::binary|ios::in|ios::out);
    bool found = false;

    cout << "\n\n\t Enter The account No. : ";
    cin >> id;

    while (!isValid) 
    {
        cin >> id;

        if(id <= 0) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Error, Please Enter Correct Account (Integer): ";
        }
        else 
        {
            isValid = true;
        }
    }

    isValid = false;

    while(!File.eof()) 
    {
        
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        
        if(ac.return_account() == id) 
        {

            cout << "         Enter Amount You Would Like To Withdraw: ";
            
            while(!isValid) 
            {
                cin >> amount;

                if(amount <= 0) 
                {
                    cin.clear();
                    cin.ignore(256,'\n');
                    cout << "         Error, Please Enter An Amount > 0 : ";
                }
                else 
                {
                    isValid = true;
                }
            }
            
            ac.withdraw(amount);

            int pos = (-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);       //sets the position where the next character is to be inserted to prevent copys.
            
            found = true;
            
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            break;
        }
    }

    File.close();
    
    if(!found) 
    {
        cout << "Record Does Not Exist... Press Any Key To Continue..." << endl;
    }
}


/***
 * 04.
 * Function used to display all information about the account required. 
 * @show_account() function used from Account class.
***/
void display_actInfo() 
{
    account ac;
    ifstream inFile;
    int id;
    bool isValid = false;
    bool found = false;

    inFile.open("account.dat",ios::binary);

    cout << "\n\n\t Enter The account No. : ";

    while (!isValid) 
    {
        cin >> id;

        if(id <= 0) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Error, Please Enter Correct Account (Integer): ";
        }
        else 
        {
            isValid = true;
        }
    }

    if(!inFile) {
        cout<<"File could not be open !! Press any Key To Continue...";
		return;
    }

    cout << endl;

    //reinterpret_cast<char *> (&ac) = treating &ac as a char 
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))  
    {
        if(ac.return_account() == id) 
        {
            found = true;
            ac.show_account(); 
        }
      
	}

    if(found == false) 
    {
         cout << endl;
         cout << "Account Does Not Exist In Database..." << endl;
    }

    cout << endl;
    cout << "Press Any Key To Continue...";

    inFile.close(); 
}

/***
 * 05.
 * Function used to close an account and remove all information about the account.
***/
void close_account() 
{
    account ac;
    int id;
    bool isValid = false;
    char confirm;

    cout << "Enter Account You Want To Delete: ";

    while (!isValid) 
    {
        cin >> id;

        if(id <= 0) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Error, Please Enter Correct Account (Integer): ";
        }
        else 
        {
            isValid = true;
        }
    }

    cout << "Are You Sure You Want To Delete Your Account? (y/n)" << endl;
    cin >> confirm;

    if(confirm == 'n') 
    {
        cout << "Account Will Not Be Deleted, Press Any Key To Return To Main Menu...";
        return;
    }

    ifstream inFile;
    ofstream newFile;

    inFile.open("account.dat",ios::binary);
    newFile.open("temp.dat",ios::binary);

    //start at first pos.
    inFile.seekg(0,ios::beg);             
    
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) 
    {
        if(ac.return_account() != id) 
        {
            newFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }

    inFile.close();
    newFile.close();

    remove("account.dat");
    rename("temp.dat", "account.dat");

    cout << "Account Successfully Closed, Press Any Key To Return To Main Menu...";
}

/***
 * 06.
 * Function used to modify a account.
 * Funcion calles @modify() from the account class.
***/
void modify_account() 
{
    account ac;
    fstream File;
    int id;
    bool isValid = false;

    cout << "       Enter The Account You Want To Modify: ";
    
    while (!isValid) 
    {
        cin >> id;

        if(id <= 0) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "         Error, Please Enter Correct Account (Integer): ";
        }
        else 
        {
            isValid = true;
        }
    }


    File.open("account.dat", ios::binary|ios::in|ios::out);

    while(!File.eof()) 
    {

       File.read(reinterpret_cast<char *> (&ac), sizeof(account));

       if(ac.return_account() == id) 
       {
           ac.modify();
       }
       else 
       {
           cout << "        Account Does Not Exist, Press Any Key To Continue...";
       }

        //sets the position where the next character is to be inserted to prevent copys.
        int pos = (-1)*static_cast<int>(sizeof(ac));
		File.seekp(pos,ios::cur);     
        File.write(reinterpret_cast<char *> (&ac), sizeof(account));
        
        break;
    }

    File.close();
}

/***
 * 07.
 * Function used to display a list of all accounts in the database.
 * Funcion calles @display_accounts() from the account class.
***/
void display_all() 
{
    account ac;
    ifstream File;

    File.open("account.dat",ios::binary);

    while(File.read(reinterpret_cast<char *> (&ac), sizeof(account))) 
    {
        ac.display_accounts();   
    }

    File.close();
    cout << "Press Any Key To Continue..." << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------


int main() 
{
    //Main menu

    char ch;
    int id;
    int account;

	intro();

	do {

	cout << "---------- MAIN MENU ----------" << endl;
        cout << "           01. NEW ACCOUNT" << endl;
        cout << "           02. DEPOSIT" << endl;
        cout << "           03. WITHDRAW" << endl;
        cout << "           04. ACCOUNT INFORMATION" << endl;
        cout << "           05. CLOSE AN ACCOUNT" << endl;
        cout << "           06. MODIFY ACCOUNT" << endl;
        cout << "           07. ALL ACCOUNT LIST" << endl;
        cout << "           08. EXIT" << endl;
        cout << "-------------------------------" << endl;

        cout << "Select Your Option <1-8>: ";  
        cin >> ch;
        
	switch(ch)
	{
	case '1':
	    write_account();
	    break;
        case '2': 
            deposit_amount();
            break;
        case '3': 
            withdraw_amount();
            break;
        case '4': 
            display_actInfo();
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
            cout << "Closing application, goodbye..." << endl;
            exit(0);
	    default : cout<<"\a";
	}
	cin.ignore();
	cin.get();
    }   while(ch != '8');
	return 0;
}
