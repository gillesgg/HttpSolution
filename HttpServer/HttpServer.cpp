// HttpServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "HttpService.h"
#include "CHttpServer.h"




int main()
{
	HttpService http;

	http.InitWebServer();

	std::wcout << L"Press a key to stop" << std::endl;
	getchar();
}
