//For DBMS Coursework
//Sergeev Ilya, EMA-18-2

#include <iostream>
#include <string>
#include "windows.h"
#include <wininet.h>
#pragma comment(lib,"wininet")

#include "MD5\md5.h"

std::string SendGet(const char* url, const char* query);

int main()
{
	while (true) // Зациклим выполнение программы
	{
		std::cout << "Enter command, reg or log" << std::endl;

		std::string cmd;
		std::cin >> cmd;

		if (cmd == "reg")
		{
			//Запрашиваем данные для регистрации
			std::string name, pass;

			std::cout << "Enter name" << std::endl;
			std::cin >> name;

			std::cout << "Enter password" << std::endl;
			std::cin >> pass;

			//Создаем запрос, хешируем пароль
			std::string answer; std::string query = "cw1//registration.php?name=" + name
				+ "&pass=" + MD5().operator()(pass);
			answer = SendGet("bk-usue.space", query.c_str());

			//Выводим ответ
			switch (std::stoi(answer))
			{
			case 0:
				std::cout << "User successfully registered! Now you can log in." << std::endl;
				break;

			case 2:
				std::cout << "Username already in use." << std::endl;;
				break;

			case 1:
			default:
				std::cout << "Some error occured. Try later" << std::endl;
				break;
			}
		}
		else if (cmd == "log")
		{
			std::string name, pass;

			std::cout << "Enter name" << std::endl;
			std::cin >> name;

			std::cout << "Enter password" << std::endl;
			std::cin >> pass;

			std::string answer; std::string query = "cw1//login.php?name=" + name
				+ "&pass=" + MD5().operator()(pass);
			answer = SendGet("bk-usue.space", query.c_str());

			switch (std::stoi(answer))
			{
			case 0:
				std::cout << "Successfully log in! Hello, " << name << '!' << std::endl;
				break;

			case 2:
				std::cout << "Wrong name or password" << std::endl;;
				break;

			case 1:
			default:
				std::cout << "Some error occured. Try later" << std::endl;
				break;
			}
		}
		else
			std::cout << "Wrong command" << std::endl;
	}

	return 0;
}

std::string SendGet(const char* url, const char* query)
{
	HINTERNET hIntSession;
	HINTERNET hHttpSession;
	HINTERNET hHttpRequest;

	hIntSession = InternetOpenA("cw1", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	hHttpSession = InternetConnectA(hIntSession, url, 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
	hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", query, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	const char* szHeaders = "Content-Type: text/html\nMyHeader: Check text"; CHAR szReq[1024] = "";
	HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq));
	CHAR szBuffer[1025]; DWORD dwRead = 0;
	while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
	{
		szBuffer[dwRead] = 0;
		dwRead = 0;
	}

	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hIntSession);

	return szBuffer;
}