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
#include <CstringArray.hpp>


namespace irc {

	class ManageServer {
		public:

		static std::string connectServer(int socket, std::string ip, std::string port);
		static int getFileDescriptorSocket();

		static std::string readServer(int socket, bool = false);
		static CstringArray readGameServer(int socket, bool = false);
		static int writeOnServer(int socket, std::string msg);

		protected:


		private:
		ManageServer() = default;
	};

}

#endif //CLIENT_MANAGESERVER_HPP
