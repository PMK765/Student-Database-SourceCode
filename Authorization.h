/*
Peter Kemper
003740618
9/10/17
CS 311
Lab Assignment 1
Authorization.h
*/
#ifndef AUTHORIZATION
#define AUTHORIZATION
#include "stdafx.h"
#include<string>
using namespace std;
//typedef node* nodePtr;

class node
{
public:
	int stId;
	string userid;
	string password;
	node* next;
	node() { next = NULL; }
};

class Authorization
{
private:
	node* top;
public:
	Authorization();
	~Authorization();
	bool destroy(node* head);
	bool AddMember(int studentId, string user, string  pass);
	bool RemoveMember(int studentId);
	bool SearchId(int StudentId);
	bool ChangePassword(int userId, string newPass);
	bool PrintAll();
	bool PrintRecord(int StudentId);;
	bool ProcessTransaction();
	bool SaveConfiguration();
	bool LoadConfiguration();
	int promptUser();
};

#endif