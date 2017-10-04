/*
Peter Kemper
003740618
9/10/17
CS 311
Lab Assignment 1
Main.cpp
*/

#include "stdafx.h"	//VS2017 needs this for some reason
#include<iostream>
#include "Authorization.h"

int main()
{
	Authorization StudentList;
	
	StudentList.LoadConfiguration();
	StudentList.promptUser();

	return 0;
}