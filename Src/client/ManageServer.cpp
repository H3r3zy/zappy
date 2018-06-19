/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <cstring>
#include "ManageServer.hpp"

std::string irc::ManageServer::readServer(int socket, bool blockRead)
{
	std::string result;
	fd_set readfds;
	struct timeval t = {0, 1000};

	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	if (select(socket + 1, &readfds, NULL, NULL, (!blockRead) ? &t : NULL) == -1)
		result = "select error\n";
	else if (FD_ISSET(socket, &readfds)) {
		char buffer[4096];
		int len = 0;
		do {
			len = (int)read(socket, buffer, 4095);
			if (len <= 0)
				throw std::exception();
			buffer[len] = '\0';
			result += buffer;
		} while (strlen(buffer) == 4096);
		if (result.size() > 1 && result[result.size() - 1] == '\n')
			result.erase(result.size() - 1, 1);
	}
	std::cout << "result: " << result << std::endl;
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