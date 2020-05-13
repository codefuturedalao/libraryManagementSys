#ifndef UTILITY_H
#define UTILITY_H
#include "libraryManage.h"
class UI{
	static Borrower user;
	static void searchBook();
	static void borrowBook();
	static void returnBook();
	static void reserveBook();
	static void unreserveBook();
	static void addTitle();
	static void deleteTitle();
	static void addItem();
	static void deleteItem();
	static void checkInfo();
	//static void SeeAllBooks();
public:
	static void PrintMainUI();
	static void PrintStartUI();
	static void PrintLoginUI();
	static void PrintRegisterUI();
	static void PrintLeaveUI();
	static void GetBorrower();
};

#endif
