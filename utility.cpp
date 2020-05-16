#include "utility.h"
using std::cout;
using std::endl;
using std::cin;
Borrower UI::user;

void UI::PrintStartUI(){
	char option;
	system("clear");
	cout << "\t\t\t\t\t\t\t\t\t\tWelcome to the library Management created by jacksonSang!" << endl;
	cout<< endl << endl;
	cout <<"\t\t\t\t\t\t\t\t\t\tif u have regiseted, please input 1 select log in." << endl;
	cout <<"\t\t\t\t\t\t\t\t\t\tif u haven't registed, please input 2 select register." << endl;
	cout << "\t\t\t\t\t\t\t\t\t\tif u want to leave now, please input other character" << endl;
	cout << endl << endl;
	cin >> option;
	if(option == '1')
		PrintLoginUI();
	else if(option == '2')
		PrintRegisterUI();
	else 
		exit(0);
}

void UI::PrintLoginUI(){
	string borrowerid;
	string password;
	string option;
	do{
		system("clear");
		cout << "please input your borrowerid: " << endl;
		cin >> borrowerid;
		user.SetBorrowerId(borrowerid);
		cout << "please input your password: " << endl;
		cin >> password;
		user.SetPassword(password);
		if(!user.LoginCheck()){
			cout << "borrowerid or password is not correct!" << endl;
			cout << "input 1 to reinput borrowerid and correct, other character to exit " << endl;
			cin >> option;
		}else{
			cout << "\t\t\t\t\t\t\t\t\tlog in successful" << endl;
			cout << "\t\t\t\t\t\t\t\t\tWelcome to Library Management System" << "Mr./Mrs " << user.GetName() << endl;
			return;
		}
	}while(option == "1");
	//option != 1 && !user.LoginCheck() user want to leave
	PrintLeaveUI();
}

void UI::PrintRegisterUI(){
	string borrowerid;
	string password;
	string name;
	string sex;
	string address;
	string city;
	system("clear");
	cout << "please input your borrowerid: " << endl;
	cin >> borrowerid;
	user.SetBorrowerId(borrowerid);
	while(user.ExistData()){
		cout << "please select other id, the id u input have existed" << endl;
		cin >> borrowerid;
		user.SetBorrowerId(borrowerid);
	}
	cout << "please input your password: " << endl;
	cin >> password;
	user.SetPassword(password);
	cout << "please input your name: " << endl;
	cin >> name;
	user.SetName(name);
	cout << "please input your sex(male or female): " << endl;
	cin >> sex;
	user.SetSex(sex);
	cout << "please input your address: " << endl;
	cin >> address;
	user.SetAddress(address);
	cout << "please input your city: " << endl;
	cin >> city;
	user.SetCity(city);
	user.StoreData();
	cout << "\t\t\t\t\t\t\t\t\t\t\tRegister Success!" << endl;
}

void UI::PrintLeaveUI(){
	cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------"<< endl;
	cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t----------------------Bye-------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------"<< endl;
	cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------" << endl;
	exit(0);	
}

void UI::PrintMainUI(){
	char option;
	do{
		system("clear");
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\tUser : " << user.GetName() << endl;
		cout <<"\t\t\t\t\t\t\t\t\t\t\tthere are some operation you can do:" << endl;
		cout <<"\t\t\t\t\t\t\t\t\t\t1. search book \t\t2. borrow book \t\t3. return book " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t4. reserve book \t5. unreserve book \t6. add title(m)" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t7. delete Title(m) \t8. add item \t\t9. delete item(m) " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\ta. checkInfo \t\tq. quit" << endl;
		cout << "Caution: (m) means only manager can do this operation! " << endl;
		cout << "Please input number between 0 and a (or q)" << endl;
		cin >> option;
		switch(option){
			case '1': 
			    searchBook();	
			    break;
			case '2':
			    borrowBook();
			    break;
			case '3':
			    returnBook();
			    break;
			case '4':
			    reserveBook();
			    break;
			case '5':
			    unreserveBook();
		   	    break;
			case '6':
			    addTitle();
			    break;
			case '7':
			    deleteTitle();
			    break;
			case '8':
			    addItem();
			    break;
			case '9':
			    deleteItem();
			    break;
			case 'a':
			    checkInfo();
			    break;
			case 'q':
			    break;
			default:	
			    cout << "please input number between 1 and 10 " << endl;
			    break;
				
		}
	}while(option != 'q');
}

void UI::searchBook(){
	string bookName;
	string option;
	system("clear");
	do{
		cout << "please input the book's name you want to search: " << endl;
		cin >> bookName;
		Title title{bookName};
		if(!title.ExistData()){
			cout << bookName <<  " doesn't exist" << endl;
		}else{
			title.LoadData();
			list<Item *> itemList;
			title.GetItemList(itemList);
			list<Item *>::iterator iter;
			//cout << "the size of itemList is " << itemList.size() << endl;;
			cout << "\tbookName\tbookAuthor\tbookItem\tisBorrowed" << endl;
			for(iter = itemList.begin(); iter != itemList.end();++iter)
				cout <<	"\t" << bookName << "\t" << title.GetAuthor() << "\t\t" << (*iter)->GetItemId() << "\t\t" << (*iter)->IsBorrowed() << endl;
		}
		cout << "input 1 to continue searching, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}

void UI::borrowBook(){
	string itemid;
	string option;
	system("clear");
	do{
		cout << "please input the item's id that you want to borrow" << endl;
		cin >> itemid;
		Item *item = new Item("",itemid);
		if(!item->ExistData()){
			cout << "the item doesn't exist, please confirm the itemid" << endl;
		}else if(item->IsBorrowed()){
			cout << "the item have been borrowed, please switch another book to borrow" << endl;
		}else{
			Loan *l = new Loan(itemid,user.GetBorrowerId());
			if(l->StoreData()){
				cout << "successful! You have borrowed your book " << endl;
				//user.AddLoan(l);
			}
			else 
				cout << "something goes wrong!" << endl;
			delete l;
		}
		delete item;
		cout << "input 1 to continue borrowing, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}

void UI::returnBook(){
	string itemid;
	string option;
	system("clear");
	do{
		user.LoadData();
		list<Loan *> loanList;
		user.GetLoanList(loanList);
		list<Loan *>::iterator iter;
		cout << "here is your borrow list :" << endl;
		cout << "\ttitleName\titemid" << endl;
		for(iter = loanList.begin();iter != loanList.end();++iter){
			string itemid = (*iter)->GetItemId();
			Item *i = new Item("",itemid);
			i->LoadData();
			cout <<"\t" << i->GetTitleName() <<"\t" << i->GetItemId() << endl; 
			delete i;
		}

		cout << "please input the item'id that you want to return " << endl;
		cin >> itemid;
		Loan *loan = new Loan(itemid,user.GetBorrowerId());
		if(!loan->ExistData()){
			cout << "the itemid is not correct! " << endl;
		}else{
			//avoid people return book that don't belong to them
			loan->LoadData();
			if(loan->GetBorrowerId() == user.GetBorrowerId()){
				if(loan->DeleteData())
					cout << "successful! You have returned this book " << endl;
				else
					cout << "something goes wrong!" << endl;
			}else{
				cout << "you haven't borrowed this book, so you cann't return it" << endl;
			}
		}
		delete loan;
		cout << "input 1 to cotinue returning, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}

void UI::reserveBook(){
	string titleName;
	string option;
	system("clear");
	do{
		cout << "please input the title's name that you want to reserve" << endl;
		cin >> titleName;
		Title title = Title(titleName);
		if(!title.ExistData()){
			cout << "the book doesn't exist, please confirm the title's Name" << endl;
		}else{
			Reservation *r = new Reservation(titleName,user.GetBorrowerId());
			if(r->StoreData())
				cout << "successful! You have reserved your book " << endl;
			else
				cout << "something goes wrong!" << endl;
			delete r;
		}
		cout << "input 1 to continue reservng, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}

void UI::unreserveBook(){
	string titleName;
	string option;
	system("clear");
	do{
		cout << "please input the title's name that you want to unreserve" << endl;
		cin >> titleName;
		Title title = Title(titleName);
		if(!title.ExistData()){
			cout << "the book doesn't exist, please confirm the title's Name" << endl;
		}else{
			Reservation *r = new Reservation(titleName,user.GetBorrowerId());
			if(r->GetBorrowerId() == user.GetBorrowerId()){
				if(r->DeleteData())
					cout << "successful! You have unreserved your book " << endl;
				else
					cout << "something goes wrong!" << endl;
			}else{
				cout << "this book is not in you reservation list, you cannot unreserve it" << endl;
}
			delete r;
		}
		cout << "input 1 to continue unreservng, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}
void UI::addTitle(){
	char option;
	char option1;
	if(user.GetIsManager()){
		string titleName;
		string author;
		do{
			system("clear");
			cout << "input the title's Name: " << endl;
			cin >> titleName;
			cout << "input the title's author: " << endl;
			cin >> author;
			Title t = Title(titleName,author);
			if(t.ExistData()){
				cout << "the title has existed!" << endl;
			}else{
				cout << "do you have some items to add to this title?" << endl;
				cout << "input y(yes) or n(no): " << endl;
				cin >> option;
				while(option == 'y'){
					cout << "please input the itemid"  << endl;
					string itemid;
					cin >> itemid;
					Item * i = new Item(titleName,itemid);
					t.AddItem(i);
					cout << "do you have another item to add to this title?" << endl;
					cout << "input y(yes) or n(no): " << endl;
					cin >> option;
				}
				if(t.StoreData())
					cout << "successful!" << endl;
				else
					cout << "some error happen" << endl;
				list<Item *> itemList;
				t.GetItemList(itemList);
				list<Item *>::iterator iter;
				//free dynamic storage
				//for(iter = itemList.begin();iter != itemList.end();++iter)
				//	delete (*iter);
			}
			cout << "input 1 to continue adding, other to return to the main user interface. " << endl;
			cin >> option1;
		}while(option1 == '1');
	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
		cout << "input any key to return to the main user interface" << endl;
		cin.get();
		cin.get();
	}
}

void UI::deleteTitle(){
	string option;
	if(user.GetIsManager()){
		string titleName;
		do{
			system("clear");
			cout << "please input the titleName you want to delete" << endl;
			cin >> titleName;
			Title t = Title(titleName);
			if(t.ExistData()){
				t.LoadData();
				if(t.DeleteData())
					cout << "successful!" << endl;
				else
					cout << " some error happen" << endl;

			}else{
				cout << "the title doesn't exist, you cannot delete a title which doesn't exist!" << endl;
			}
			cout << "input 1 to continue deleting, other to return to the main user interface. " << endl;
			cin >> option;
		}while(option == "1");
	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
		cout << "input any key to return to the main user interface" << endl;
		cin.get();
		cin.get();
       	}
}

void UI::addItem(){
	string option;
	if(user.GetIsManager()){
		string titleName;
		string itemid;
		do{
			system("clear");
			cout << "please input the titleName to which you want to add item " << endl;
			cin >> titleName;
			Title t = Title(titleName);
			//check whether the title has existed
			if(t.ExistData()){
				cout << "please input the itemid you want to add" << endl;
				cin >> itemid;
				Item *i = new Item(titleName,itemid);
				if(i->ExistData()){
					cout << "this item has existed,you cannot add the same item" << endl;
				}else{
					if(i->StoreData())
						cout << "successful!" << endl;
					else
						cout << "some error happen" << endl;
				}
				delete i;
			}else{
				cout << "the titleName doesn't exist,you cannot add item to a title that doesn't exist" << endl;
			}
			cout << "input 1 to continue adding item,other character to return to the main user interface" << endl;
			cin >> option;
		}while(option == "1");
	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
		cout << "input any key to return to the main user interface" << endl;
		cin.get();
		cin.get();
       	}
}

void UI::deleteItem(){
	string option;
	if(user.GetIsManager()){
		string titleName;
		string itemid;
		do{
			system("clear");
			cout << "please input the titleName to which you want to delete item " << endl;
			cin >> titleName;
			Title t = Title(titleName);
			//check whether the title has existed
			if(t.ExistData()){
				cout << "please input the itemid which u want to delete" << endl;
				cin >> itemid;
				Item *i = new Item(titleName,itemid);
				if(!(i->ExistData())){
					cout << "this item doesn't exist,you cannot delete the item" << endl;
				}else{
					if(i->DeleteData())
						cout << "successful!" << endl;
					else
						cout << "some error happen" << endl;
				}
				delete i;
			}else{
				cout << "the titleName doesn't exist,you cannot delete item to a title that doesn't exist" << endl;
			}
			cout << "input 1 to continue deleting item,other character to return to the main user interface" << endl;
			cin >> option;
		}while(option == "1");

	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
		cout << "input any key to return to the main user interface" << endl;
		cin.get();
		cin.get();
       	}
}

void UI::checkInfo(){
	system("clear");
	user.LoadData();
	list<Loan *> loanList;
	list<Loan *>::iterator loanIter;
	list<Reservation *> reservationList;
	list<Reservation *>::iterator reseIter;
	user.GetLoanList(loanList);
	user.GetReservationList(reservationList);
	cout << "borrowerid: " << user.GetBorrowerId() << endl;
	cout << "name: " << user.GetName() << endl;
	cout << "sex: " << user.GetSex() << endl;
	cout << "address: " << user.GetAddress() << endl;
	cout << "city: " << user.GetCity() << endl;
	cout << "here is your borrow list :" << endl;
	cout << "\ttitleName\titemid" << endl;
	for(loanIter = loanList.begin();loanIter != loanList.end();++loanIter){
		string itemid = (*loanIter)->GetItemId();
		Item *i = new Item("",itemid);
		i->LoadData();
		cout <<"\t" << i->GetTitleName() <<"\t" << i->GetItemId() << endl; 
		delete i;
	}
	cout << endl << "here is your reservation list :" << endl;
	for(reseIter = reservationList.begin();reseIter != reservationList.end();++reseIter){
		cout <<"\t" << (*reseIter)->GetTitleName() << endl; 
	}
	cout << endl;
	cout << "input any key to return to the main user interface" << endl;
	cin.get();
	cin.get();
}
