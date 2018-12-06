/**
* 1.int main | a simple terminal wher an usser can defiend a server port
* 2. int initServer  | Create the server listining connection
* statics void ev_handler | Serve stactimal html files
*/

// Include Mongoose 

#include "pentoa.h";
#include <string>
#include <iostream>


//stuct containgn setting for how to server http with mongoose
static struct mg_serve_http_opts s_http_server_opts;

int initServer(int port);

//event handler
static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	//if event is http reqst
	if (ev == MG_EV_HTTP_REQUEST) {
		//serve static html files
		mg_serve_http(nc,( struct http_message *) p, s_http_server_opts);
	}
}


int initServer(int port) {
	//Monagoose evenet manager
	struct mg_mgr mgr;
	//Mangoose connection
	struct mg_connection *nc;

	//Convert port to char	
	std::string portToChar = std::to_string(port);
	static char const *sPort = portToChar.c_str();

	//Init Mangoose
	mg_mgr_init(&mgr, NULL);
	std::cout << "Starting Fucking Web Server on port" << sPort << std::endl;

	nc = mg_bind(&mgr, sPort, ev_handler);

	//if connnection failds
	if (nc == NULL) {
		std::cout << "Faild to create listiner" << std::endl;
		return 1;
	}


	// set up htpp server option 
	mg_set_protocol_http_websocket(nc);

	s_http_server_opts.document_root = ".";

	s_http_server_opts.enable_directory_listing = "yes";
	
	

	for (;;) {
		mg_mgr_poll(&mgr, 1000);

	}

	//Freeup up all data
	mg_mgr_free(&mgr);




}

int main(void) {
	int port;
	std::cout << "Select errr.fucking server port" << std::endl;
	std::cin >> port;

	//fail case
		if (std::cin.fail()) {
			port = 1000;

		}

		initServer(port);

	return 0;

}