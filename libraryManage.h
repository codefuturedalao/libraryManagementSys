#ifndef LIBRARY_MANAGE_H
#define LIBRARY_MANAGE_H
#define SQLERROR();  std::cout<<"Query Error: " << mysql_error(&mysql) << std::endl; exit(-1);
#include <iostream>
#include <mysql/mysql.h>	//-lmysqlclient
using std::string;
class DBObject{
	static MYSQL mysql;
	static const string m_hostString = "localhost";
	static const string m_userString = "root";
	static string m_passwordString;
	static string m_DBNameString;
	static int m_port;
public:
	DBObject(string DBNameString = "Library",string passwordString="",int port = 3306);
	static void SetPassword(string passwordString);
	static void setDBName(string DBNameString);
	static void setPort(int port);
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	~DBObject();
};
	
class Item : public DBObject{
	string m_titleName;
	int m_itemid;
public:
	Item(string titleName,int itemid);
	bool isBorrowed() const;
	string GetTitleName() const;
	void SetTitleName(string titleName);
	int GetItemId() const;
	void SetItemId(int itemid);
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	~Item();
};
class Title : public DBObject{
	string m_name;
	string m_author;
	list<Item *> m_item;
public:
	Title(string name,string author = "");
	void AddItem(Item * item);
	void RemoveItem(Item * item);
	void GetItemList(list<Item *> &itemList) const;
	Item * GetItemWithId(int itemId) const;
	void SetName(string name);
	string GetName() const;
	void SetAuthor(string author);
	string GetAuthor() const;
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	~Title();
};
