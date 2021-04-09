// HttpClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "http_client.h"

int main(int argc, char* argv[])
{
	http_client httpclient;

	if (argc == 2)
	{
		auto count = atoi(argv[1]);

		for (auto x = 0; x < count; x++)
		{
			httpclient.Initialize();
		}
	}
	else
	{
		httpclient.Initialize();
	}
}
