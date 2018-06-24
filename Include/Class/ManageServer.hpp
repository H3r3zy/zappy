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

namespace irc {

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
		{"msz", &irc::ManageServer::parseLine8Input},
		{"pnw", &irc::ManageServer::parseLine8Input},
		{"tna", &irc::ManageServer::parseLine8Input}, // team number
		{"endtna", &irc::ManageServer::parseLine8Input}, // team finish
		{"bct", &irc::ManageServer::parseLine8Input},
		{"pic", &irc::ManageServer::parseLine8Input}, // start incantation
		{"pie", &irc::ManageServer::parseLine8Input}, // end incantation
		{"pbc", &irc::ManageServer::parseLine8Input}, // broadcast
		{"pdi", &irc::ManageServer::parseLine8Input},
		{"pin", &irc::ManageServer::parseLine8Input},
		{"nbt", &irc::ManageServer::parseLine1Input},
		{"nbu", &irc::ManageServer::parseLine1Input},
		{"pmv", &irc::ManageServer::parseLine8Input}, // move
		{"sgt", &irc::ManageServer::parseLine1Input},
		{"ptu", &irc::ManageServer::parseLine8Input}, // move 2 ?
		{"pdr", &irc::ManageServer::parseLine8Input}, // resource dropping
		{"pgt", &irc::ManageServer::parseLine8Input}, // resource collecting
		{"sgr", &irc::ManageServer::parseLine8Input}, // resource random generate
	};

}

#endif //CLIENT_MANAGESERVER_HPP
