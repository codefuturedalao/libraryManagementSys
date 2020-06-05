#ifndef LIBRARY_MANAGE_H
#define LIBRARY_MANAGE_H
#define SQLERROR();  std::cout<<"Query Error: " << mysql_error(&mysql) << std::endl; exit(-1);
#include <iostream>
#include <mysql/mysql.h>	//-lmysqlclient
#include <list>
#include <iterator>
using std::list;
using std::string;
using std::to_string;
class DBObject{
protected:
	static const string m_hostString;
	static const string m_userString;
	static string m_passwordString;
	static string m_DBNameString;
	static int m_port;
	static MYSQL mysql;
public:
	DBObject(string DBNameString = "Library",string passwordString="root",int port = 3306);
	static void SetPassword(string passwordString);
	static void SetDBName(string DBNameString);
	static void SetPort(int port);
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	virtual bool ExistData();
	virtual bool LoadData();
	~DBObject();
};
	
class Item : public DBObject{
	string m_titleName;
	string m_itemid;
public:
	Item(string titleName,string itemid);
	bool IsBorrowed() const;
	string GetTitleName() const;
	void SetTitleName(string titleName);
	string GetItemId() const;
	void SetItemId(string itemid);
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	virtual bool ExistData();
	virtual bool LoadData(); //load data according to the itemid
	~Item();
};
class Title : public DBObject{
	string m_name;
	string m_author;
	list<Item *> m_item;
public:
	Title(string name,string author = "");
	bool IsReserved();
	void AddItem(Item * item);
	void RemoveItem(Item * item);
	void GetItemList(list<Item *> &itemList) const;
	Item * GetItemWithId(string itemId) const;
	void SetName(string name);
	string GetName() const;
	void SetAuthor(string author);
	string GetAuthor() const;
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	virtual bool ExistData();
	virtual bool LoadData(); //load data according to the titlename
	~Title();
};

class Loan : public DBObject{
	string m_itemid;
	string m_borrowerid;
public:
	Loan(string itemid,string borrowerid);
	string GetItemId() const;
	void SetItemId(string itemid);
	string GetBorrowerId() const;
	void SetBorrowerId(string borrowerid);
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	virtual bool ExistData();//use itemid to check
	virtual bool LoadData(); //load data according to the itemid
};

class Reservation : public DBObject{
	string m_titleName;
	string m_borrowerid;
public:
	Reservation(string titleName,string borrowerid);
	string GetTitleName() const;
	void SetTitleName(string titleName);
	string GetBorrowerId() const;
	void SetBorrowerId(string borrowerid);
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	virtual bool ExistData();//use borrowerid to check
	virtual bool LoadData();//use borrowerid to check
};

class Borrower : public DBObject{
	string m_borrowerid;
	string m_password;
	string m_name;
	string m_sex;
	string m_address;
	string m_city;
	list<Loan *> m_loans;
	list<Reservation *> m_reservations;
	bool m_isManager;
public:
	Borrower(string borrowerid = "",string password = "",string name = "",string sex="male",string address = "LuoJia",string city = "WuHan");
	bool LoginCheck();
	void AddLoan(Loan * loan);
	void RemoveLoan(Loan * loan);
	void GetLoanList(list<Loan *> &loanList) const;
	void AddReservation(Reservation * reservation);
	void RemoveReservation(Reservation * reservation);
	void GetReservationList(list<Reservation *> &reservationList) const;
	void SetBorrowerId(string borrowerid);
	string GetBorrowerId() const;
	void SetPassword(string password);
	string GetPassword() const;
	void SetName(string name);
	string GetName() const;
	void SetSex(string sex);
     	string GetSex() const;
	void SetAddress(string address);
	string GetAddress() const;
      	void SetCity(string city);
	string GetCity() const;
	void SetIsManager(bool isManager);
	bool GetIsManager() const;
	virtual bool StoreData();
	virtual bool DeleteData();
	virtual bool UpdateData();
	virtual bool ExistData();
	virtual bool LoadData();//load Data according to the borrowerid
	~Borrower();
};
	
	



#endif
