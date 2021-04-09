#pragma once

class CHttpServer
{
public:
	CHttpServer() {}
	CHttpServer(utility::string_t str_url);

	pplx::task<void> open() { return http_listener_.open(); }
	pplx::task<void> close() { return http_listener_.close(); }

private:

	void handle_get(web::http::http_request message);
	void handle_put(web::http::http_request message);
	void handle_post(web::http::http_request message);
	void handle_delete(web::http::http_request message);

	web::http::experimental::listener::http_listener http_listener_;
};