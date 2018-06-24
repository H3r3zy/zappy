/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_MANAGESERVER_HPP
# define CLIENT_MANAGESERVER_HPP

# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <sys/select.h>
# include <fstream>
# include <functional>
# include <map>
# include "CstringArray.hpp"

namespace zap {

	class ManageServer {
		public:

		static std::string connectServer(int socket, std::string ip, std::string port);
		static int getFileDescriptorSocket();

		static std::string readServer(int socket, bool = false);
		static CstringArray readGameServer(int socket, bool = false);
		static int writeOnServer(int socket, std::string msg);

		static void parseLine8Input(char *buffer, CstringArray &command);
		static void parseLine1Input(char *buffer, CstringArray &command);

		protected:

		private:
		ManageServer() = default;
	};

	const std::map<std::string, std::function<void(char *, CstringArray &)>> _pattern = {
		{"msz", &zap::ManageServer::parseLine8Input},
		{"pnw", &zap::ManageServer::parseLine8Input},
		{"tna", &zap::ManageServer::parseLine8Input}, // team number
		{"endtna", &zap::ManageServer::parseLine8Input}, // team finish
		{"bct", &zap::ManageServer::parseLine8Input},
		{"enw", &zap::ManageServer::parseLine8Input},
		{"eht", &zap::ManageServer::parseLine8Input},
		{"pic", &zap::ManageServer::parseLine8Input}, // start incantation
		{"pie", &zap::ManageServer::parseLine8Input}, // end incantation
		{"pbc", &zap::ManageServer::parseLine8Input}, // broadcast
		{"pfk", &zap::ManageServer::parseLine8Input}, // egg dropped
		{"ebo", &zap::ManageServer::parseLine8Input}, // egg eclosion
		{"eht", &zap::ManageServer::parseLine8Input}, // egg eclosion
		{"pdi", &zap::ManageServer::parseLine8Input},
		{"edi", &zap::ManageServer::parseLine8Input},
		{"pin", &zap::ManageServer::parseLine8Input},
		{"nbt", &zap::ManageServer::parseLine1Input},
		{"nbu", &zap::ManageServer::parseLine1Input},
		{"pmv", &zap::ManageServer::parseLine8Input}, // move
		{"sgt", &zap::ManageServer::parseLine1Input},
		{"ptu", &zap::ManageServer::parseLine8Input}, // move 2 ?
		{"pdr", &zap::ManageServer::parseLine8Input}, // resource dropping
		{"pgt", &zap::ManageServer::parseLine8Input}, // resource collecting
		{"sgr", &zap::ManageServer::parseLine8Input}, // resource random generate
	};

}

#endif //CLIENT_MANAGESERVER_HPP
