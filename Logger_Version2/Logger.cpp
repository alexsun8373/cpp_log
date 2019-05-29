#include "stdafx.h"
#include "Logger.h"
#include "Utilities.h"
const std::string CLogger::m_sFileName = "Log.txt";
CLogger* CLogger::m_pThis = NULL;
std::ofstream CLogger::m_Logfile;
CLogger::CLogger()
{

}
CLogger* CLogger::GetLogger() {
	if (m_pThis == NULL) {
		m_pThis = new CLogger();
		m_Logfile.open(m_sFileName.c_str(), std::ios::out | std::ios::app);
	}
	return m_pThis;
}

void CLogger::Log(Level s,const char * pszFmt, ...)
{
	va_list pArgs = NULL;
	va_start(pArgs, pszFmt);
	m_Logfile << "[" << Util::CurrentDateTime() << "]" << levels[static_cast<int>(s)] << ":";
	for (; *pszFmt != '\0'; ++pszFmt) {
		if (*pszFmt != '%') {//Ouput the original character if not contorl 
			putchar(*pszFmt);
			m_Logfile << *pszFmt;
			continue;
		}
		switch (*++pszFmt) {//check the next character if it is contorol
		case '%': //for two consecutive %,just output 1
			putchar('%');
			m_Logfile << "%";
			break;
		case 'd': //decimalism
			m_Logfile << va_arg(pArgs, int);
			break;
		case 'c': //char
			char c;
			c = (char)va_arg(pArgs, int);
			m_Logfile << c;
			printf("char %c\n", c);
			break;
		case 's'://string
			m_Logfile << va_arg(pArgs, char *);;
			break;
		case 'b': {//Binary
			char aucStr[sizeof(int) * 8 + 1] = { 0 };
			m_Logfile << "0b" << Util::MyItoa(va_arg(pArgs, int), aucStr, 2);
			break;
		}
		case 'h': {//hex
			char aucStr[sizeof(int) * 8 + 1] = { 0 };
			m_Logfile << "0x" << Util::MyItoa(va_arg(pArgs, int), aucStr, 16);
			break;
		}
		default:
			m_Logfile << "The format is not support";
			return;
		}
	}
	va_end(pArgs);
	m_Logfile << std::endl;
}

void CLogger::Log(const std::string& sMessage)
{
	m_Logfile << Util::CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
}