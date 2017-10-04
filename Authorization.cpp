/*
Peter Kemper
003740618
9/10/17
CS 311
Lab Assignment 1
Authorization.cpp
*/
#include "stdafx.h"
#include "Authorization.h"
#include<iostream>
#include<fstream>
#include<sstream>
Authorization::Authorization()
{
	top = NULL;
}
Authorization::~Authorization()
{
	destroy(top);
}
bool Authorization::destroy(node* topp)
{
	node* current;
	node* tmp;
	current = topp;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		delete tmp;
	}
	topp = NULL;
	return true;
}
bool Authorization::AddMember(int studentId, string user, string pass)
{
	if (top == NULL)
	{
		top = new node();
		top->stId = studentId;
		top->userid = user;
		top->password = pass;
		return true;
	}
	else
	{
		node *curr = top;
		node *prev = NULL;
		node *newnode;
		bool found = false;
		newnode = new node;
		newnode->stId = studentId;

		while ((curr != NULL) && (!found))
		{
			if (studentId > curr->stId)
			{
				prev = curr;
				curr = curr->next;
			}
			else
			{
				found = true;
			}
		}

		newnode->next = curr;
		newnode->stId = studentId;
		newnode->userid = user;
		newnode->password = pass;
		if (prev == NULL)
		{
			top = newnode;
		}
		else
		{
			prev->next = newnode;
		}
	}
	return true;
}
bool Authorization::RemoveMember(int studentId)
{
	if (top == NULL)
	{
		cout << "No student was deleted" << endl;
		return false;
	}
	node *p = top;
	while (p->next->stId != studentId)
	{
		p = p->next;
		if (p->next == NULL)
		{
			cout << "No student was deleted" << endl;
			return false;
		}
	}
	node *delPtr = p->next;
	p->next = p->next->next;
	delete delPtr;
	cout << "Student " << studentId << " deleted." << endl;
	return true;
}
bool Authorization::SearchId(int StudentId)
{
	node *p = top;
	while (p->next->stId != StudentId)
	{
		p = p->next;
		if (p->next == NULL)
		{
			cout << "Student not found" << endl;
			return false;
		}
	}
	cout << "Student Found" << endl;
	return true;
}
bool Authorization::ChangePassword(int userId, string newPass)
{
	node *p = top;
	while (p != NULL)
	{
		if (p->stId == userId)
		{
			p->password = newPass;
			cout << "Password for " << userId << " changed." << endl;
			return true;
		}
		else
		{
			p = p->next;
		}
	}
}
bool Authorization::PrintAll()
{
	node *p = top;
	while (p != NULL)
	{
		std::cout << p->stId << "\t" << p->userid << "\t" << p->password << endl;
		p = p->next;
	}
	return true;
}
bool Authorization::PrintRecord(int StudentId)
{
	node *p = top;
	while (p != NULL)
	{
		if ((p->stId != StudentId) && p->next == NULL)
		{
			cout << "Record Not Found" << endl;
			return false;
		}
		else if (p->stId == StudentId)
		{
			cout << p->stId << "\t" << p->userid << "\t" << p->password << endl;
			return true;
		}
		else 
		{
			p = p->next;
		}
	}
}
bool Authorization::ProcessTransaction()
{
	string filename, keyword, s1 = " ",s2 = " ",s3 = " ", rawline;
	filename = "Trans.txt";
	ifstream infile;

	infile.open(filename);

	while (getline(infile, rawline))
	{
		stringstream stream(rawline);
		if (rawline.find("Insert") == 0)
		{
			stream >> keyword >> s1 >> s2 >> s3;
			AddMember(stoi(s1), s2, s3);
		}
		else if (rawline.find("Delete") == 0)
		{
			stream >> keyword >> s1;
			RemoveMember(stoi(s1));
		}
		else if (rawline.find("Find") == 0)
		{
			stream >> keyword >> s1;
			SearchId(stoi(s1));
		}
		else if (rawline.find("PrintRecord") == 0)
		{
			stream >> keyword >> s1;
			PrintRecord(stoi(s1));
		}
		else if (rawline.find("Print") == 0)
		{
			PrintAll();
		}
		else if (rawline.find("ChangePassword") == 0)
		{
			stream >> keyword >> s1 >> s2;
			ChangePassword(stoi(s1), s2);
		}
		else
		{
			cout << endl;
		}
	}
	return true;
}
bool Authorization::SaveConfiguration()
{
	ofstream fout;
	fout.open("config.txt");
	node *p = top;
	while (p != NULL)
	{
		fout << p->stId << "\t";
		fout << p->userid << "\t";
		fout << p->password << "\t";
		fout << endl;
		p = p->next;
	}
	fout.close();
	return true;
}
bool Authorization::LoadConfiguration()
{
	ifstream infile;
	infile.open("config.txt");
	int SID;
	string User, Pass;

	while (infile >> SID >> User >> Pass)
	{
		AddMember(SID, User, Pass);
	}
	infile.close();

	return true;
}
int Authorization::promptUser()
{
	string choice = " ";
	cout << "Enter one of the following 3 commands:\n1)Process a Transaction File\n2)Save the Information to a Configuration File\n3)Quit/Exit\n";
	cin >> choice;
	while ((choice != "1") || (choice != "2") || (choice != "3"))
	{
	if (choice == "1")
	{
		ProcessTransaction();
	}
	if (choice == "2")
	{
		SaveConfiguration();
	}
	if (choice == "3")
	{
		return 0;
	}
	else
	{
		cout << "Enter just a '1', '2', or '3'" << endl<<endl;
	}
	cout << "Enter one of the following 3 commands:\n1)Process a Transaction File\n2)Save the Information to a Configuration File\n3)Quit/Exit\n";
	cin >> choice;
	}
	return stoi(choice);
}