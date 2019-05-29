// Logger_Version2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "Logger.h"
using namespace std;
int main()
{
	string message1 = "logg message 1 ...";
	string message2 = "logg message 2 ...";

	CLogger::GetLogger();

	LOGGER->Log(INFO,"Binary string of number %c = %b!", 'a', 20);

	LOGGER->Log(INFO, "Binary string of number %s = %h!", "Tested Value:", 56);
	return 0;
}

