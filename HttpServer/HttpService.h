#pragma once

#include "CHttpServer.h"

class HttpService
{
public:
	HRESULT on_initialize(const utility::string_t& str_address);
	HRESULT InitWebServer();

private:
	std::unique_ptr<CHttpServer> http_;

};

