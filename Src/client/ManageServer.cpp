/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <cstring>
#include <sstream>
#include "ManageServer.hpp"

std::string irc::ManageServer::readServer(int socket, bool blockRead)
{
	std::cout << "je vais read sur mon serveur" << std::endl;

	std::string result;
	fd_set readfds;
	struct timeval t = {0, 1000};

	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	if (select(socket + 1, &readfds, NULL, NULL, (!blockRead) ? &t : NULL) == -1) {
		result = "select error\n";
		std::cout << "ca a fail bordel" << std::endl;

	} else if (FD_ISSET(socket, &readfds)) {
		char buffer[4096];
		int len = 0;
		std::cout << "je boucle dedans" << std::endl;

		do {
			len = (int)read(socket, buffer, 4095);
			if (len <= 0)
				throw std::exception();
			buffer[len] = '\0';
			result += buffer;
			std::cout << len << " => " << buffer << " = " << result << std::endl;
		} while (len == 4095);
		if (strncmp(buffer, "msz", 3) == 0) {
			uint32_t x = 0;
			uint32_t y = 0;
			memcpy(&x, buffer + 4, sizeof(uint32_t));
			memcpy(&y, buffer + 9, sizeof(uint32_t));
			std::cout << len << " map size: " << (int) x << " " << (int) y << std::endl;





			uint bag[8] = {0};
			for (size_t i = 0; i < 8; i++) {
				memcpy(&bag[i],
					buffer + 4 + i * (sizeof(uint) + 1), sizeof(uint));
				printf("expeted %d\n", bag[i]);

			}

			exit(1);
		}
	} else {
		std::cout << "NTM gros con" << std::endl;

	}
	sleep(2);
	std::stringstream ss(result);
	std::string command;
	ss >> command;
	std::cout << "COMMAND: " << command << std::endl;

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
	std::cout << "J'envoie [" << msg << "] a la socket " << socket << std::endl;
	if (write(socket, msg.c_str(), msg.size()) == -1)
		throw std::exception();
	return 0;
}