#include "utility.h"
using std::cout;
using std::endl;
Borrower UI::user;

void UI::printMainUI(){
	system("cls");
	cout << "\t\t\tWelcome to the library Management created by jacksonSang!" << endl;
	cout<< endl << endl;
	cout <<"if u have regiseted, please input 1 select log in." << endl;
	cout <<"if u haven't registed, please input 2 select register." << endl;
	cout << "if u want to leave now, please input q" << endl;
	cout << endl << endl;
}

void UI::printLoginUI(){
	string borrowerid;
	string password;
	string name;
	string sex;
	string address;
	string city;
	system("cls");
	cout << "please input your borrowerid: " << endl;
	cin >> borrowerid;
	user.SetBorrowerId(borrowerid);
	while(user.ExistData()){
		cout << "please select other id, the id u input have existed" << endl;
		cin >> borrowerid;
	}
	cout << "please input your password: " << endl;
	cin >> password;
	user.SetPassword();
	cout << "please input your name: " << endl;
	cin >> name;
	user.SetName();
	cout << "please input your sex(male or female): " << endl;
	cin >> sex;
	user.SetSex();
	cout << "please input your address: " << endl;
	cin >> address;
	user.SetAddress();
	cout << "please input your city: " << endl;
	cin >> city;
	user.SetCity();
	user.StoreData();
	cout << "
};
