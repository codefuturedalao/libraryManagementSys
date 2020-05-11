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

DBObject::~DBObject(){
	mysql_close(&mysql);
}

//Item-------------------------------------------------------------
Item::Item(string titleName,int itemid):m_titleName(titleName),m_itemid(itemid){

}

bool Item::IsBorrowed() const{
	string sql = "select * from loadTable where item_id = '";
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
	string sql = "insert into itemTable(titleName,itemId) values('" + m_titleName + "','"+ to_string(m_itemid) + "');";
	std::cout<< "in the itemTable" << std::endl;
	
	if(mysql_query(&mysql,sql.c_str())){ //a query error occur
		SQLERROR();
	}
	return true;
}

bool Item::DeleteData(){
	string sql = "delete from itemTable where itemId = '" + to_string(m_itemid) + "';";
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
	string sqlUpdate = "update itemTable set titleName = '" + m_titleName + "',itemId = '" + to_string(m_itemid) + "' where itemId = '" + to_string(m_itemid) + "';";
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

Title::~Title(){
}

//Loan--------------------------------------------------------------
Loan::Loan(int itemid,int borrowerid):m_itemid(itemid),m_borrowerid(borrowerid){

}

int Loan::GetItemId() const{
	return m_itemid;
}

void Loan::SetItemId(int itemid){
	m_itemid = itemid;
}

int Loan::GetBorrowerId() const{
	return m_borrowerid;
}

void Loan::SetItemId(int borrowerid){
	m_borrowerid = borrowerid;
}

bool Loan::StoreData(){
	if(ExistData()){
		std::cout<<"you cann't restore this loan, may be you need to update this data" << std::endl;
		return false;
	}else{
		//store data in titleTable
		string sql = "insert into loanTable(itemid,borrowerid) values('" + to_string(m_itemid) + "','"+ to_string(m_borrowerid) + "');";
		if(mysql_query(&mysql,sql.c_str())){ //a query error occur
			SQLERROR();
		}
		return true;
	}
}

bool Loan::DeleteData(){
	
}
bool Loan::UpdateData(){}
bool Loan::ExistData(){
	string sqlSearch = "select * from loanTable where loanid = '" + to_string(m_loanid) + "';";
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

