#
# makefile for LibraryManage
# CPP Version
# JacksonSang 5/30/2020 
#

CC = g++

CFLAGS =  

OBJNAME = -o libM 

OBJS = main.o libraryManage.o utility.o -lmysqlclient

tiny.exe: $(OBJS)
	$(CC) $(OBJNAME) $(OBJS)

main.o: main.cpp utility.h utility.cpp libraryManage.h libraryManage.cpp
	$(CC) $(CFLAGS) -c main.cpp

libraryManage.o: libraryManage.cpp libraryManage.h 
	$(CC) $(CFLAGS) -c libraryManage.cpp

utility.o: utility.cpp utility.h libraryManage.h
	$(CC) $(CFLAGS) -c utility.cpp

