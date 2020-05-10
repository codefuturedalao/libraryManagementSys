#include "libraryManage.h"

DBObject::DBObject(string DBNameString,string passwordString="",int port = 3306){
	mysql_init(&mysql);
	mysql_real_connect(
			&mysql,
			m_hostString.c_str(),
			m_userString.c_str(),
			m_passwordString.c_str(),
			m_DBNameString.c_str(),
			m_port,
			NULL,
			0
		);
	//to do 
	//write the connect func in Constructor function is not a good idea
	
}

void DBObject::SetPassword(string passwordString){
	m_passwordString = passwordString;
}

void DBObject::SetDBName(string DBNameString){
	m_DBNameString = DBNamestring;
}

void DBObject::SetPort(int port){
	m_port = port;
}

bool DBObject::StoreData(){}
bool DBObject::DeleteData(){}
bool DBObject::UpdateData(){}

DBObject::~DBObject(){
	mysql_close(&mysql);
}

//Item-------------------------------------------------------------
Item::Item(string titleName,int itemid):m_titleName(titleName),m_itemid(itemid){

}

bool Item::isBorrowed(){
	string sql = "select * from loadTable where item_id = ";
	sql = sql + string(m_itemid) + ";";
	if(mysql_query(&mysql,sql.c_str())){
		MYSQL_RES *result = mysql_use_result(&mysql);
		if(mysql_fetch_row() != NULL){ //there is a record in loan table
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

inline string Item::GetTitleName() const{
	return m_titleName;
}

inline void Item::SetTitleName(string titleName){
	m_titleName = titleName;
}

inline int Item::GetItemId() const{
	return m_itemid;
}

inline void Item::SetItemId(int itemid){
	m_itemid = itemid;
}

bool Item::StoreData(){
	string sql = "insert into itemTable(titleName,itemId) values(" + m_titleName + ","+ string(m_itemid) + ");";
	if(!mysql_query(&mysql,sql.c_str())) //a query error occur
		SQLERROR();
	return true;
}

bool Item::DeleteData(){
	string sqlSearch = "select * from itemTable where itemId = " + string(m_itemid) + ";";
	string sqlDelete = "delete from itemTable where itemId = " + string(m_itemid) + ";";
	if(mysql_query(&mysql,sqlSearch.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row() != NULL){ //there is a record in loan table
			mysql_free_result(result);
			//now delete the record
			if(mysql_query(&mysql,sqlDelete.c_str())){
				return true;
			}else{
				SQLERROR();
			}
		}else{
			mysql_free_result(result);
			std::cout << "there is not such a item in the database " << std::endl;
			return false;
		}
	}else{
		SQLERROR();
	}
}	

bool Item::UpdateData(){
	string sqlSearch = "select * from itemTable where itemId = " + string(m_itemid) + ";";
	string sqlUpdate = "update itemTable set titleName = " + m_titleName + ",itemId = " + string(m_itemid) + "where itemId = " + string(m_itemid) + ";";
	if(mysql_query(&mysql,sqlSearch.c_str())){ //a query error occur
		MYSQL_RES * result = mysql_use_result(&mysql);		
		if(mysql_fetch_row() != NULL){ //there is a record in loan table
			mysql_free_result(result);
			//now delete the record
			if(mysql_query(&mysql,sqlUpdate.c_str())){
				return true;
			}else{
				SQLERROR();
			}
		}else{
			mysql_free_result(result);
			std::cout << "there is not such a item in the database " << std::endl;
			return false;
		}
	}else{
		SQLERROR();
	}
}	

Item::~Item(){

}

//Title------------------------------------------------------------
Title::Title(string name,string author = ""):m_name(name),m_author(author){

}

inline void Title::AddItem(Item * item){
	//to do
	//check whether the m_item already have the item in the list
	m_item.push_back(item);
}

inline void Title::RemoveItem(Item * item){
	m_item.remove(item);
}

inline void Title::GetItemList(list<Item *> &itemList) const{
	itemList = m_item;
}

inline Item * Title::GetItemWithId(int itemId) const{
	list<Item *>::iterator iter;
	for(iter = m_item.begin();iter != m_item.end(); ++iter){
		if(iter->GetItemId() == itemId)
			return (Item *)iter;
	}
	return NULL:
}

inline void Title::SetName(string name){
	m_name = name;
}

inline string Title::GetName() const{
	return m_name;
}

inline void Title::SetAuthor(string author){
	m_author = author;
}

inline string Title::GetAUthor() const{
	return m_author;
}

bool Title::StoreData(){
	//todo
}

bool Title::DeleteData(){
	//todo
}

bool Title::UpdateData(){
	//todo
}
