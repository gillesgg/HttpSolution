#include "pch.h"
#include "http_client.h"


HRESULT http_client::Initialize()
{
	web::json::value json_return;
	web::http::status_codes status;

	web::json::value postData;
	postData[L"name"] = web::json::value::string(L"Joe Smith");
	postData[L"sport"] = web::json::value::string(L"Baseball");

	

	auto JsonMessage = postData.serialize();

	std::wstring port = L"34568";
	std::wstring address = L"http://localhost:";
	address.append(port);

	auto uri = web::http::uri(address);
	web::http::client::http_client client(web::http::uri_builder(uri).append_path(U("/Operation")).to_uri());

	const auto& content_type = utility::conversions::to_utf16string("application/json");

	client.request(web::http::methods::POST, U("/"), JsonMessage, content_type)
		.then([&status](const web::http::http_response& response)
			{
				if (response.status_code() != web::http::status_codes::OK)
				{
					return response.extract_string().then([](utility::string_t message) -> pplx::task< web::json::value >
						{
						return pplx::task_from_exception<web::json::value>
							(
								std::exception(utility::conversions::to_utf8string(message).c_str()));
						});
				}
				return response.extract_json();
			})
		.then([&json_return](const pplx::task<web::json::value>& task)
			{
				try
				{
					json_return = task.get();
				}
				catch (const web::http::http_exception& e)
				{
					if (e.error_code().value() == ERROR_WINHTTP_CANNOT_CONNECT)
					{
						std::cout << "The connection with the server could not be established" << std::endl;
					}
					else
					{
						std::cout << "error=" << e.what() << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << "error=" << ex.what() << std::endl;
				}
			})
				.wait();
			auto msg = json_return.serialize();
			std::wcout << msg << std::endl;
			return S_OK;
}
