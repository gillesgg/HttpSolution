#include "pch.h"
#include "Logger.h"
#include "CHttpServer.h"

CHttpServer::CHttpServer(utility::string_t str_url) : http_listener_(str_url)
{
	http_listener_.support(web::http::methods::GET, std::bind(&CHttpServer::handle_get, this, std::placeholders::_1));
	http_listener_.support(web::http::methods::PUT, std::bind(&CHttpServer::handle_put, this, std::placeholders::_1));
	http_listener_.support(web::http::methods::POST, std::bind(&CHttpServer::handle_post, this, std::placeholders::_1));
	http_listener_.support(web::http::methods::DEL, std::bind(&CHttpServer::handle_delete, this, std::placeholders::_1));
}
/// <summary>
/// Http handler get
/// </summary>
/// <param name="message"></param>
void CHttpServer::handle_get(const web::http::http_request message)
{
	LOG_DEBUG << message.to_string();
	message.reply(web::http::status_codes::NotFound);
}
/// <summary>
/// Http handler post
/// </summary>
/// <param name="message"></param>
void CHttpServer::handle_post(web::http::http_request message)
{
	LOG_DEBUG << message.to_string();
	auto str = message.to_string();
	try
	{
		web::json::value httpJson;
		message.extract_json()
			.then([&httpJson](pplx::task<web::json::value> task)
				{
					httpJson = task.get();
				})
			.then([&httpJson]()
				{
					web::json::object operation = httpJson.as_object();


					for (auto item : operation)
					{
						std::wcout << L"item=" << item.second.as_string() << std::endl;
					}
				})
					.wait();
				pplx::task_from_result();
				message.reply(web::http::status_codes::OK, web::json::value::string(utility::conversions::to_string_t(L"Operation OK")));
				
	}
	catch (const web::json::json_exception& e)
	{
		message.reply(web::http::status_codes::InternalError, web::json::value::string(utility::conversions::to_string_t(e.what())));
	}
	catch (const std::exception& e)
	{
		message.reply(web::http::status_codes::InternalError, web::json::value::string(utility::conversions::to_string_t(e.what())));
	}
	catch (...)
	{
		message._reply_if_not_already(web::http::status_codes::InternalError);
	}
}
/// <summary>
/// Http Delete handler
/// </summary>
/// <param name="message"></param>
void CHttpServer::handle_delete(web::http::http_request message)
{
	LOG_DEBUG << message.to_string();
	message.reply(web::http::status_codes::NotFound);
}
/// <summary>
/// Http Put Handler
/// </summary>
/// <param name="message"></param>
void CHttpServer::handle_put(web::http::http_request message)
{
	LOG_DEBUG << message.to_string();
	message.reply(web::http::status_codes::NotFound);
}

