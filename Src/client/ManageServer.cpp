/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "ManageServer.hpp"

std::string irc::ManageServer::readServer(int socket, bool blockRead, bool first)
{
	static std::string result = "";
	fd_set readfds;
	struct timeval t = {0, 1000};

	if (!first)
		result = "";
	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	if (result.size() >= 2 && result.substr(result.size() - 2, result.size()) == "\r\n") {
		result.erase(result.size() - 2, 2);
		std::string tmp = result;
		result = "";
		return tmp;
	}
	if (select(socket + 1, &readfds, NULL, NULL, (!blockRead) ? &t : NULL) == -1)
		result = "select error";
	else if (FD_ISSET(socket, &readfds)) {
		char buffer[2];
		int len = (int)read(socket, buffer, 1);
		if (len <= 0)
			throw std::exception();
		buffer[len] = '\0';
		result += buffer;
		return readServer(blockRead, true);
	}
	return result;
}

std::string irc::ManageServer::connectServer(int socket, std::string ip, std::string port)
{
	struct sockaddr_in s_in;
	struct timeval t = {10, 0};

	if (socket < 0)
		return "Can't create the socket";
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons((uint16_t)std::stoi(port));
	s_in.sin_addr.s_addr = inet_addr(ip.c_str());
	setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &t, sizeof(t));
	if (connect(socket, (struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		close(socket);
		return "Can't connect to the server";
	}
	return "";
}

int irc::ManageServer::getFileDescriptorSocket()
{
	struct protoent *pe;

	pe = getprotobyname("TCP");
	if (!pe)
		return -1;
	return socket(AF_INET, SOCK_STREAM, pe->p_proto);
}

int irc::ManageServer::writeOnServer(int socket, std::string msg)
{
	if (write(socket, msg.c_str(), msg.size()) == -1)
		throw std::exception();
	return 0;
}