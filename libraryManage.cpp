#include "libraryManage.h"
const string DBObject::m_hostString = "localhost";
const string DBObject::m_userString = "root";
string DBObject::m_DBNameString;
string DBObject::m_passwordString;
int DBObject::m_port;
MYSQL DBObject::mysql;


DBObject::DBObject(string DBNameString,string passwordString,int port){
	m_DBNameString = DBNameString;
	m_passwordString = passwordString;
	m_port = port;
	mysql_init(&mysql);
	if(NULL == mysql_real_connect(
			&mysql,
			m_hostString.c_str(),
			m_userString.c_str(),
			m_passwordString.c_str(),
			m_DBNameString.c_str(),
			m_port,
			NULL,
			0
		)){
		SQLERROR();
	}
	std::cout << "the database is " << DBNameString << std::endl;
	//to do 
	//write the connect func in Constructor function is not a good idea
	
}

void DBObject::SetPassword(string passwordString){
	m_passwordString = passwordString;
}

void DBObject::SetDBName(string DBNameString){
	m_DBNameString = DBNameString;
}

void DBObject::SetPort(int port){
	m_port = port;
}

bool DBObject::StoreData(){return true;}
bool DBObject::DeleteData(){return true;}
bool DBObject::UpdateData(){return true;}
bool DBObject::ExistData(){return true;}
bool DBObject::LoadData(){return true;}

DBObject::~DBObject(){
	mysql_close(&mysql);
}

//Item-------------------------------------------------------------
Item::Item(string titleName,int itemid):m_titleName(titleName),m_itemid(itemid){

}

bool Item::IsBorrowed() const{
	string sql = "select * from loanTable where itemid = '";
	sql = sql + to_string(m_itemid) + "';";
	if(!mysql_query(&mysql,sql.c_str())){
		MYSQL_RES *result = mysql_use_result(&mysql);
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{	//an error occur
		SQLERROR();
	}
}

string Item::GetTitleName() const{
	return m_titleName;
}

void Item::SetTitleName(string titleName){
	m_titleName = titleName;
}

int Item::GetItemId() const{
	return m_itemid;
}

void Item::SetItemId(int itemid){
	m_itemid = itemid;
}

bool Item::StoreData(){
	string sql = "insert into itemTable(titleName,itemid) values('" + m_titleName + "','"+ to_string(m_itemid) + "');";
	std::cout<< "in the itemTable" << std::endl;
	
	if(mysql_query(&mysql,sql.c_str())){ //a query error occur
		SQLERROR();
	}
	return true;
}

bool Item::DeleteData(){
	string sql = "delete from itemTable where itemid = '" + to_string(m_itemid) + "';";
	if(ExistData()){ 
		//now delete the record
		if(IsBorrowed()){
			std::cout << "this item has been borrowed, so u cann't delete this item" << std::endl;
			return false;
		}else if(!mysql_query(&mysql,sql.c_str())){
			return true;
		}else{
			SQLERROR();
		}
	}else{
		std::cout<<"there doesn't exist item which id is " << m_itemid << std::endl;
		return false;
	}
}

bool Item::UpdateData(){
	string sqlUpdate = "update itemTable set titleName = '" + m_titleName + "',itemId = '" + to_string(m_itemid) + "' where itemid = '" + to_string(m_itemid) + "';";
	if(ExistData()){ 
		if(!mysql_query(&mysql,sqlUpdate.c_str())){
			return true;
		}else{
			SQLERROR();
		}
	}
	else{ //can't find this item
		std::cout << "there is not such a item in the database " << std::endl;
		return false;
	}
}	

bool Item::ExistData(){
	string sqlSearch = "select * from itemTable where itemid = '" + to_string(m_itemid) + "';";
	if(!mysql_query(&mysql,sqlSearch.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}
}

bool Item::LoadData(){
	if(!ExistData()){
		std::cout<<"you cann't load this item,this item doesn't exist" << std::endl;
		return false;
	}else{
		//load Data in  loanTable
		string sql = "select * from  itemTable where itemid = '" + to_string(m_itemid) + "';";
		if(!mysql_query(&mysql,sql.c_str())){ 
			MYSQL_RES * result = mysql_use_result(&mysql);		
			MYSQL_ROW row;
			if((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
				m_titleName = row[0]; 
				mysql_free_result(result);
				return true;
			}else{
				mysql_free_result(result);
				return false;
			}
		}else{
			SQLERROR();
		}
	}
	
}


Item::~Item(){

}

//Title------------------------------------------------------------
Title::Title(string name,string author):m_name(name),m_author(author){
			
}

bool Title::IsReserved(){
	string sqlSearch = "select * from reservationTable where titleName = '" + m_name + "';";
	if(!mysql_query(&mysql,sqlSearch.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}
}


void Title::AddItem(Item * item){
	//to do
	//check whether the m_item already have the item in the list
	m_item.push_back(item);
}

void Title::RemoveItem(Item * item){
	//delete the item from the database
	m_item.remove(item);
}

void Title::GetItemList(list<Item *> &itemList) const{
	itemList = m_item;
}

Item * Title::GetItemWithId(int itemId) const{
	list<Item *>::const_iterator iter;
	for(iter = m_item.begin();iter != m_item.end(); ++iter){
		if((*iter)->GetItemId() == itemId)
			return (Item *)(*iter);
	}
	return NULL;
}

void Title::SetName(string name){
	m_name = name;
}

string Title::GetName() const{
	return m_name;
}

void Title::SetAuthor(string author){
	m_author = author;
}

string Title::GetAuthor() const{
	return m_author;
}

bool Title::StoreData(){
	if(ExistData()){
		std::cout<<"you cann't restore this title, may be you need to update this data" << std::endl;
		return false;
	}else{
		//store data in titleTable
		string sql = "insert into titleTable(titleName,author) values('" + m_name + "','"+ m_author + "');";
		std::cout << "start insert into titleTable" << std::endl;
		if(mysql_query(&mysql,sql.c_str())){ //a query error occur
			SQLERROR();
		}
	//store data in itemTable
		std::cout << "start insert into itemTable" << std::endl;
		list<Item *>::iterator iter;
		for(iter = m_item.begin();iter != m_item.end(); ++iter){
			(*iter)->StoreData();	
		}
		return true;			
	}
}

bool Title::DeleteData(){
	if(ExistData()){
		std::cout << "there is no title name " << m_name << ", can not delete a title which doesn't exist" << std::endl;
		return false;
	}else{
		//first check whether this book has been reserved
		if(IsReserved()){
			std::cout << "the title " << m_name << " has been reserved, so can't delete this book" << std::endl;	
			return false;
		}
		string sql = "delete from titleTable where titleName = '" + m_name + "';";
		//second delete the item 
		list<Item *>::iterator iter;
		for(iter = m_item.begin();iter != m_item.end(); ++iter){
			if(!(*iter)->DeleteData()){
				std::cout << "can not delete item " << (*iter)->GetItemId() << " when delete title " << m_name << std::endl;	
				return false;
			}
		}
		//last delete the title
		if(!mysql_query(&mysql,sql.c_str())){
			return true;
		}else{
			SQLERROR();
		}
	}
		
}

bool Title::UpdateData(){
	//to do
	//this operation can not update the title's name 
	//because when i change its name, the update statement's condition must be false
	string sqlUpdate = "update titleTable set titleName = '" + m_name + "',author = '" + m_author + "' where titleName = '" + m_name + "';";
	if(ExistData()){
		if(!mysql_query(&mysql,sqlUpdate.c_str())){
			list<Item *>::iterator iter;
			for(iter = m_item.begin();iter != m_item.end(); ++iter){
				if((*iter)->ExistData())
					(*iter)->UpdateData();
				else
					(*iter)->StoreData();
			}
			
			return true;
		}else{
			SQLERROR();
		}
	}else{
		std::cout << "this book doesn't exist, so u cann't update it, maybe u want to store that" << std::endl;
		return false;
	}
}

bool Title::ExistData(){
	string sqlSearch = "select * from titleTable where titleName = '" + m_name + "';";
	std::cout <<sqlSearch << std::endl;
	if(!mysql_query(&mysql,sqlSearch.c_str())){ 
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}
	
}

bool Title::LoadData(){
	m_item.clear();
	if(!ExistData()){
		std::cout<<"you cann't load this title,this title doesn't exist" << std::endl;
		return false;
	}else{
		//load Data in  titleTable
		string sql = "select * from  titleTable where titleName = '" + m_name + "';";
		if(!mysql_query(&mysql,sql.c_str())){ 
			MYSQL_RES * result = mysql_use_result(&mysql);		
			MYSQL_ROW row;
			if((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
				m_author = row[1]; 
				mysql_free_result(result);
				return true;
			}else{
				mysql_free_result(result);
				return false;
			}
		}else{
			SQLERROR();
		}
		//load Data in  ItemTable
		sql = "select * from  itemTable where titleName = '" + m_name + "';";
		if(!mysql_query(&mysql,sql.c_str())){ 
			MYSQL_RES * result = mysql_use_result(&mysql);		
			MYSQL_ROW row;
			while((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
				std::cout << "row[0]: " << row[0] << "row[1]: " << row[1] << std::endl;
				//to do
				//may cause memory linkage 
				Item * i = new Item(row[0],atoi(row[1])); 
				m_item.push_back(i);
			}
				mysql_free_result(result);
				return true;
		}else{
			SQLERROR();
		}
	}

}
Title::~Title(){
	list<Item *>::iterator iter;
	for(iter = m_item.begin();iter != m_item.end(); ++iter){
		delete (*iter);
	}
}

//Loan--------------------------------------------------------------
Loan::Loan(int itemid,string borrowerid):m_itemid(itemid),m_borrowerid(borrowerid){

}

int Loan::GetItemId() const{
	return m_itemid;
}

void Loan::SetItemId(int itemid){
	m_itemid = itemid;
}

string Loan::GetBorrowerId() const{
	return m_borrowerid;
}

void Loan::SetBorrowerId(string borrowerid){
	m_borrowerid = borrowerid;
}

bool Loan::StoreData(){
	if(ExistData()){
		std::cout<<"you cann't restore this loan, may be you need to update this data" << std::endl;
		return false;
	}else{
		//store data in titleTable
		string sql = "insert into loanTable(itemid,borrowerid) values('" + to_string(m_itemid) + "','"+ m_borrowerid + "');";
		if(mysql_query(&mysql,sql.c_str())){ //a query error occur
			SQLERROR();
		}
		return true;
	}
}

bool Loan::DeleteData(){
	string sql = "delete from loanTable where itemid = '" + to_string(m_itemid) + "';";
	if(ExistData()){ 
		//now delete the record
		if(!mysql_query(&mysql,sql.c_str())){
			return true;
		}else{
			SQLERROR();
		}
	}else{
		std::cout<<"there doesn't exist item which id is " << m_itemid << std::endl;
		return false;
	}

	
}
bool Loan::UpdateData(){
	//todo
	return true;
}
bool Loan::ExistData(){
	string sqlSearch = "select * from loanTable where itemid = '" + to_string(m_itemid) + "';";
	if(!mysql_query(&mysql,sqlSearch.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}
}

bool Loan::LoadData(){
	if(!ExistData()){
		std::cout<<"you cann't load this loan,this loan doesn't exist" << std::endl;
		return false;
	}else{
		//load Data in  loanTable
		string sql = "select * from  loanTable where itemid = '" + to_string(m_itemid) + "';";
		if(!mysql_query(&mysql,sql.c_str())){ 
			MYSQL_RES * result = mysql_use_result(&mysql);		
			MYSQL_ROW row;
			if((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
				m_borrowerid = row[1]; 
				mysql_free_result(result);
				return true;
			}else{
				mysql_free_result(result);
				return false;
			}
		}else{
			SQLERROR();
		}
	}
	
}

//Reservation------------------------------------------------------------------
Reservation::Reservation(string titleName,string borrowerid): m_titleName(titleName),m_borrowerid(borrowerid){

}

string Reservation::GetTitleName() const{
	return m_titleName;
}

void Reservation::SetTitleName(string titleName){
	m_titleName = titleName;
}

string Reservation::GetBorrowerId() const{
	return m_borrowerid;
}

void Reservation::SetBorrowerId(string borrowerid){
	m_borrowerid = borrowerid;
}

bool Reservation::StoreData(){
	if(ExistData()){
		std::cout<<"you cann't restore this reservation, may be you need to update this data" << std::endl;
		return false;
	}else{
		//store data in titleTable
		string sql = "insert into reservationTable(titleName,borrowerid) values('" + m_titleName + "','"+ m_borrowerid + "');";
		if(mysql_query(&mysql,sql.c_str())){ //a query error occur
			SQLERROR();
		}
		return true;			
	}
	
}
bool Reservation::DeleteData(){
	string sql = "delete from loanTable where borrowerid = '" + m_borrowerid + "';";
	if(ExistData()){ 
		//now delete the record
		if(!mysql_query(&mysql,sql.c_str())){
			return true;
		}else{
			SQLERROR();
		}
	}else{
		std::cout<<"there doesn't exist reservation which borrowerid is " << m_borrowerid << ",titleName is " << m_titleName << std::endl;
		return false;
	}

}
bool Reservation::UpdateData(){
	//todo
	return true;
}
bool Reservation::ExistData(){
	string sqlSearch = "select * from reservationTable where borrowerid = '" + m_borrowerid + "';";
	if(!mysql_query(&mysql,sqlSearch.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}

}

bool Reservation::LoadData(){
	if(!ExistData()){
		std::cout<<"you cann't load this reservation,this reservation doesn't exist" << std::endl;
		return false;
	}else{
		//load Data in  loanTable
		string sql = "select * from  reservationTable where borrowerid = '" + m_borrowerid + "';";
		if(!mysql_query(&mysql,sql.c_str())){ 
			MYSQL_RES * result = mysql_use_result(&mysql);		
			MYSQL_ROW row;
			if((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
				m_titleName = row[1]; 
				mysql_free_result(result);
				return true;
			}else{
				mysql_free_result(result);
				return false;
			}
		}else{
			SQLERROR();
		}
	}
}

//Borrower----------------------------------------------------------------------
Borrower::Borrower(string borrowerid,string password,string name,string sex,string address,string city):m_borrowerid(borrowerid),m_password(password),m_name(name),m_sex(sex),m_address(address),m_city(city){

}

bool Borrower::LoginCheck(){
	string sqlSearch = "select * from borrowerTable where borrowerid = '" + m_borrowerid + "' and password = sha1('" + m_password + "');";
	if(!mysql_query(&mysql,sqlSearch.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			LoadData();
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}
}

void Borrower::AddLoan(Loan * loan){
	m_loans.push_back(loan);
}

void Borrower::RemoveLoan(Loan * loan){
	m_loans.remove(loan);
}

void Borrower::GetLoanList(list<Loan *> &loanList) const{
	loanList = m_loans;
}

void Borrower::AddReservation(Reservation * reservation){
	m_reservations.push_back(reservation);
}

void Borrower::RemoveReservation(Reservation * reservation){
	m_reservations.remove(reservation);
}

void Borrower::GetReservationList(list<Reservation *> &reservationList) const{
	reservationList = m_reservations;
}

void Borrower::SetBorrowerId(string borrowerid){
	m_borrowerid = borrowerid;
}

string Borrower::GetBorrowerId() const{
	return m_borrowerid;
}

void Borrower::SetPassword(string password){
	m_password = password;
}

string Borrower::GetPassword() const{
	return m_password;
}

void Borrower::SetName(string name){
	m_name = name;
}

string Borrower::GetName() const{
	return m_name;
}

void Borrower::SetSex(string sex){
	m_sex = sex;
}

string Borrower::GetSex() const{
	return m_sex;
}

void Borrower::SetAddress(string address){
	m_address = address;
}

string Borrower::GetAddress() const{
	return m_address;
}

void Borrower::SetCity(string city){
	m_city = city;
}

string Borrower::GetCity() const{
	return m_city;
}

void Borrower::SetIsManager(bool isManager){
	m_isManager = isManager;
}

bool Borrower::GetIsManager() const{
	return m_isManager;
}

bool Borrower::StoreData(){
	if(ExistData()){
		std::cout<<"you cann't restore this user, may be you need to update this data" << std::endl;
		return false;
	}else{
		//store data in titleTable
		string sql = "insert into borrowerTable(borrowerid,password,name,sex,address,city) values('" + m_borrowerid + "',sha1(''"+ m_password + "'),'"  + m_name + "','" + m_sex + "','" + m_address + "','" + m_city + "');";
		if(mysql_query(&mysql,sql.c_str())){ //a query error occur
			SQLERROR();
		}
	}
	//no need to store the m_loans and m_reservations
	//because in addLoan and addReservation func
	//i just store the loan and reservation instead of addLoan and addReservation
				
	return true;
}
bool Borrower::DeleteData(){
	//todo	
	return true;
}
bool Borrower::UpdateData(){
	//todo
	return true;
}
bool Borrower::ExistData(){
	string sql = "update borrowerTable set password = sha1('" + m_password + "',name = '" + m_name + "',sex = '" + m_sex + "',address = " + m_address + "',city = '" + m_city + "';";
	if(!mysql_query(&mysql,sql.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row(result) != NULL){ //there is a record in loan table
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}
}
bool Borrower::LoadData(){
	m_loans.clear();
	m_reservations.clear();	
	string sql = "select name,sex,address,city from borrowerTable where borrowerid = '" + m_borrowerid + "';";
	if(!mysql_query(&mysql,sql.c_str())){ 
		MYSQL_RES * result = mysql_use_result(&mysql);		
		MYSQL_ROW row;
		if((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
			m_name = row[0]; 
			m_sex = row[1];
			m_address = row[2];
			m_city = row[3];
			mysql_free_result(result);
			return true;
		}else{
			mysql_free_result(result);
			return false;
		}
	}else{
		SQLERROR();
	}
	sql = "select itemid from loanTable where borrowerid = '" + m_borrowerid + "';";
	if(!mysql_query(&mysql,sql.c_str())){
		MYSQL_RES * result = mysql_use_result(&mysql);		
		MYSQL_ROW row;
		while((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
			std::cout << "row[0]: " << row[0] << std::endl;
			//to do
			//may cause memory linkage 
			Loan * i = new Loan(atoi(row[0]),GetBorrowerId()); 
			m_loans.push_back(i);
		}
		mysql_free_result(result);
		return true;
	}else{
		SQLERROR();
	}
	sql = "select titleName from reservationTable where borrowerid = '" + m_borrowerid + "';";
	if(!mysql_query(&mysql,sql.c_str())){
		MYSQL_RES * result = mysql_use_result(&mysql);		
		MYSQL_ROW row;
		while((row = mysql_fetch_row(result)) != NULL){ //there is a record in loan table
			std::cout << "row[0]: " << row[0] << std::endl;
			//to do
			//may cause memory linkage 
			Reservation * r = new Reservation(row[0],GetBorrowerId()); 
			m_reservations.push_back(r);
		}
		mysql_free_result(result);
		return true;
	}else{
		SQLERROR();
	}
	


	
	return true;
}	

Borrower::~Borrower(){
	list<Loan *>::iterator loanIter;
	list<Reservation *>::iterator reseIter;
	for(loanIter = m_loans.begin();loanIter != m_loans.end(); ++loanIter){
		delete (*loanIter);
	}	
	for(reseIter = m_reservations.begin();reseIter != m_reservations.end(); ++reseIter){
		delete (*reseIter);
	}
}
