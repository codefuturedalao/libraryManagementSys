#include "utility.h"
using std::cout;
using std::endl;
Borrower UI::user;

void UI::PrintStartUI(){
	system("cls");
	cout << "\t\t\tWelcome to the library Management created by jacksonSang!" << endl;
	cout<< endl << endl;
	cout <<"if u have regiseted, please input 1 select log in." << endl;
	cout <<"if u haven't registed, please input 2 select register." << endl;
	cout << "if u want to leave now, please input q" << endl;
	cout << endl << endl;
}

void UI::PrintLoginUI(){
	string borrowerid;
	string password;
	string option;
	do{
		system("cls");
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
			cout << "\t\t\tlog in successful" << endl;
			cout << "\t\t\tWelcome to Library Management System" << "Mr./Mrs " << user.GetName() << endl;
			return;
		}
	}while(option == "1");
	//option != 1 && !user.LoginCheck() user want to leave
	printLeaveUI();
}

void UI::PrintRegisterUI(){
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
	cout << "\t\t\tRegister Success!" << endl;
}

void UI::PrintLeaveUI(){
	cout << "--------------------------------------------"<< endl;
	cout << "--------------------------------------------" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "----------------------Bye-------------------" << endl;
	cout << "--------------------------------------------"<< endl;
	cout << "--------------------------------------------" << endl;
	cout << "--------------------------------------------" << endl;
	
}

void UI::PrintMainUI(){
	string option;
	do{
		system("cls");
		cout << "\t\t\tUser : " << user.GetName() << endl;
		cout <<"\t\t\tthere are some operation you can do:" << endl;
		cout <<"\t1. search book \t2. borrow book \t3. return book " << endl;
		cout << "\t4. reserve book \t5. add title(m) \t6. delete Title(m) " << endl;
		cout << "\t7. add item \t8. delete item(m) \9. checkInfo" << endl;
		cout << "\t10. quit" << endl;
		cout << " caution: (m) means only manager can do this operation! " << endl;
		cout << "please input number between 0 and 10 " << endl;
		cin >> option;
		switch(option){
			case "1": 
			    searchBook();	
			    break;
			case "2":
			    borrowBook();
			    break;
			case "3":
			    returnBook();
			    break;
			case "4":
			    reserveBook();
			    break;
			case "5":
			    addTitle();
			    break;
			case "6":
			    deleteTitle();
			    break;
			case "7":
			    addItem();
			    break;
			case "8":
			    deleteItem();
			    break;
			case "9":
			    break;
			default:	
			    cout << "please input number between 1 and 10 " << endl;
			    break;
				
		}
	}while(option != "10")
}

void UI::searchBook(){
	string bookName;
	string option;
	system("cls");
	do{
		cout << "please input the book's name you want to search: " << endl;
		cin >> bookName;
		Title title{bookName};
		if(!titile.ExistData()){
			cout << bookName <<  " doesn't exist" << endl;
		}else{
			title.LoadData();
			cout << "\tbookName\tbookAuthor\tbookItem\tisBorrowed" << endl;
			list<Item *> itemList;
			title.GetItemList(itemList);
			list<Item *>::iterator iter;
			for(iter = itemList.begin(); iter != itemList.end(),++iter)
				cout <<	"\t" << bookName << "\t" << title.GetAuthor() << "\t" << (*iter)->GetItemId() << "\t" << (*iter)->isBorrowed() << endl;
		}
		cout << "input 1 to continue searching, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}

void UI::borrowBook(){
	int itemid;
	string option;
	system("cls");
	do{
		cout << "please input the item's id that you want to borrow" << endl;
		cin >> itemid;
		Item item("",itemid);
		if(!item.ExistData()){
			cout << "the item doesn't exist, please confirm the itemid" << endl;
		}else if(item.IsBorrowed()){
			cout << "the item have been borrowed, please switch another book to borrow" << endl;
		}else{
			Loan l = Loan(itemid,m_borrowerid);
			if(l.StoreData()){
				cout << "successful! You have borrowed your book " << endl;
				//user.AddLoan(l);
			}
			else 
				cout << "something goes wrong!" << endl;
		}
		cout << "input 1 to continue borrowing, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}

void UI::returnBook(){
	int itemid;
	string option;
	system("cls");
	do{
		user.LoadData();
		list<Loan *> loanList;
		user.GetLoanList(loanList);
		list<Loan *>::iterator iter;
		cout << "here is your borrow list :" << endl;
		cout << "\ttitleName\titemid" << endl;
		for(iter = loanList.begin();iter != loanList.end();++iter){
			int itemid = (*iter)->GetItemId();
			Item i = Item("",itemid);
			i.LoadData();

			cout <<"\t" << i.GetTitleName() <<"\t" << i.GetItemId() << endl; 
		}

		cout << "please input the item'id that you want to return " << endl;
		cin >> itemid;
		Loan loan = Loan(itemid,m_borrowerid);
		if(!loan.ExistData()){
			cout << "the itemid is not correct! " << endl;
		}else{
			if(loan.DeleteData())
				cout << "successful! You have returned this book " << endl;
			else
				cout << "something goes wrong!" << endl;
		}
		cout << "input 1 to cotinue returning, other to return to the main user interface. " << endl;
		cin >> option;
	}while(option == "1");
}

void UI::reserveBook(){
	string titleName;
	string option;
	system("cls");
	do{
		cout << "please input the title's name that you want to reserve" << endl;
		cin >> titleName;
		Title title = Title(titleName);
		if(!title.ExistData()){
			cout << "the book doesn't exist, please confirm the title's Name" << endl;
		}else{
			Reservation r = Reservation(titleName,m_borrowerid);
			if(r.StoreData())
				cout << "successful! You have borrowed your book " << endl;
			else
				cout << "something goes wrong!" << endl;
		}
		cout << "input 1 to continue borrowing, other to return to the main user interface. " << endl;
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
			system("cls");
			cout << "input the title's Name: " << endl;
			cin >> titleName;
			cout << "input the title's author: " << endl;
			cin >> author();
			Title t = Title(titleName,author);
			if(t.ExistData()){
				cout << "the title has existed!" << endl;
			}else{
				cout << "do you have some items to add to this title?" << endl;
				cout << "input y(yes) or n(no): " << endl;
				cin >> option;
				while(option == 'y'){
					cout << "please input the itemid"  << endl;
					int itemid;
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
				for(iter = itemList.begin();iter != itemList.end();++iter)
					delete (*iter);
			}
			cout << "input 1 to continue adding, other to return to the main user interface. " << endl;
			cin >> option1;
		}while(option1 == "1");
	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
	}
}

void UI::deleteTitle(){
	string option;
	if(user.GetIsManager()){
		string titleName;
		do{
			system("cls");
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
			cin >> option1;
		}while(option == "1");
	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
       	}
}

void UI::addItem(){
	string option;
	if(user.GetIsManager()){
		string titleName;
		string itemid;
		do{
			system("cls");
			cout <<< "please input the titleName to which you want to add item " << endl;
			cin >> titleName;
			Title t = Title(titleName);
			//check whether the title has existed
			if(t.ExistData()){
				Item i = Item(titleName,itemid);
				if(i.ExistData()){
					cout << "this item has existed,you cannot add the same item" << endl;
				}else{
					if(i.StoreData())
						cout << "successful!" << endl;
					else
						cout << "some error happen" << endl;
				}
			}else{
				cout << "the titleName doesn't exist,you cannot add item to a title that doesn't exist" << endl;
			}
			cout << "input 1 to continue adding item,other character to return to the main user interface" << endl;
		}while(option = "1");
	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
       	}
}

void UI::deleteItem(){
	if(user.GetIsManager()){
		string titleName;
		string itemid;
		do{
			system("cls");
			cout <<< "please input the titleName to which you want to delete item " << endl;
			cin >> titleName;
			Title t = Title(titleName);
			//check whether the title has existed
			if(t.ExistData()){
				Item i = Item(titleName,itemid);
				if(i.ExistData()){
					cout << "this item has existed,you cannot add the same item" << endl;
				}else{
					if(i.DeleteData())
						cout << "successful!" << endl;
					else
						cout << "some error happen" << endl;
				}
			}else{
				cout << "the titleName doesn't exist,you cannot add item to a title that doesn't exist" << endl;
			}
			cout << "input 1 to continue adding item,other character to return to the main user interface" << endl;
		}while(option = "1");

	}else{
		cout << "you are not manager, you are not allowed to do this operation!" << endl;
       	}
}

void UI::checkInfo(){
	system("cls");
	user.LoadData();
	list<Loan *> loanList;
	list<Loan *>::iterator loanIter;
	list<Reservation *> reservationList;
	list<Reservation *>::iterator reseIter;
	user.GetLoanList(loanList);
	user.GetReservation(reservationList);
	cout << "borrowerid: " << user.GetBorrowerId() << endl;
	cout << "name: " << user.GetName() << endl;
	cout << "sex: " << user.GetSex() << endl;
	cout << "address: " << user.GetAddress() << endl;
	cout << "city: " << user.GetCity() << endl;
	cout << "here is your borrow list :" << endl;
	cout << "\ttitleName\titemid" << endl;
	for(loanIter = loanList.begin();loanIter != loanList.end();++loanIter){
		int itemid = (*iter)->GetItemId();
		Item i = Item("",itemid);
		i.LoadData();

		cout <<"\t" << i.GetTitleName() <<"\t" << i.GetItemId() << endl; 
	}
	cout << endl << "here is your reservation list :" << endl;
	for(reseIter = reservationList.begin();reseIter != reservationList.end();++reseIter){
		cout <<"\t" << (*reseIter)->GetTitleName() << endl; 
	}
	cout << "input any key to return to the main user interface" << endl;
}
