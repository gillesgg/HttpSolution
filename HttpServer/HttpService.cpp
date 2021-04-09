#include "pch.h"
#include "Logger.h"
#include "CHttpServer.h"
#include "HttpService.h"

HRESULT HttpService::on_initialize(const utility::string_t& str_address)
{
	LOG_TRACE << __FUNCTION__;
	web::uri_builder uri(str_address);
	uri.append_path(U("Operation/"));

	try
	{

		LOG_INFO << utility::string_t(U("Start http server"));
		auto addr = uri.to_uri().to_string();
		http_ = std::make_unique<CHttpServer>(addr);
		LOG_INFO << utility::string_t(U("Listening for requests at: ")) << addr;
		http_->open().wait();
	}
	catch (web::http::http_exception& e)
	{
		LOG_ERROR << e.what();
		if (e.error_code().value() == 183)
		{
			return E_FAIL;
		}
	}
	return (S_OK);
}


HRESULT HttpService::InitWebServer()
{
	LOG_TRACE << __FUNCTION__;
	HRESULT hr = S_OK;

	LOG_DEBUG << utility::string_t(U("Init file setting"));

	utility::string_t str_port = L"34568";
	utility::string_t str_address = L"http://localhost:";
	str_address.append(str_port);
	on_initialize(str_address);

	return (hr);
}