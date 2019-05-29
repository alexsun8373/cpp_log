#pragma once
#include <iostream>
#include <string>
#include <time.h>

namespace Util
{
	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	const std::string CurrentDateTime()
	{
		time_t     now = time(NULL);
		struct tm  tstruct;
		char       buf[80];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}
	char * MyItoa(int iValue, char *pszResBuf, unsigned int uiRadix) {
		//If pszResBuf is NULL, string "Nil" is returned.
		if (NULL == pszResBuf) {
			//May add more trace/log output here
			return "Nil";
		}

		//If uiRadix(Base of Number) is out of range[2,36],
		//empty resulting string is returned.
		if ((uiRadix < 2) || (uiRadix > 36)) {
			//May add more trace/log output here
			*pszResBuf = '\0';
			return pszResBuf;
		}

		char *pStr = pszResBuf; //Pointer to traverse string
		char *pFirstDig = pszResBuf; //Pointer to first digit
		if ((10 == uiRadix) && (iValue < 0)) { //Negative decimal number
			iValue = (unsigned int)-iValue;
			*pStr++ = '-';
			pFirstDig++;  //Skip negative sign
		}

		int iTmpValue = 0;
		do {
			iTmpValue = iValue;
			iValue /= uiRadix;
			//Calculating the modulus operator(%) by hand saving a division
			*pStr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[iTmpValue - iValue * uiRadix];
		} while (iValue);
		*pStr-- = '\0';  //Terminate string, pStr points to last digit(or negative sign)
						 //Now have a string of number in reverse order

						 //Swap *pStr and *pFirstDig for reversing the string of number
		while (pFirstDig < pStr) { //Repeat until halfway
			char cTmpChar = *pStr;
			*pStr-- = *pFirstDig;
			*pFirstDig++ = cTmpChar;
		}
		return pszResBuf;
	}
}