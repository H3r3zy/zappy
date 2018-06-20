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
	char buffer[4096];

	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	if (select(socket + 1, &readfds, NULL, NULL, (!blockRead) ? &t : NULL) == -1) {
		result = "select error\n";

	} else if (FD_ISSET(socket, &readfds)) {
		int len = 0;
		do {
			len = (int)read(socket, buffer, 4095);
			if (len <= 0) {
				std::cout << "Manage server" << "je throw" << std::endl;
				throw std::exception();
			}
			buffer[len] = '\0';
			result += buffer;
		} while (len == 4095);
	}
	std::stringstream ss(result);
	std::string command;
	ss >> command;

	std::cout << "COMMAND: " << command << std::endl;
	std::cout << "result: " << result << std::endl;
	return result;
}
CstringArray irc::ManageServer::readGameServer(int socket, bool blockRead)
{
//	std::cout << "je vais read sur mon serveur" << std::endl;

	std::string result;
	CstringArray finalCommand;
	fd_set readfds;
	struct timeval t = {0, 300};

	//	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	if (select(socket + 1, &readfds, NULL, NULL, (!blockRead) ? &t : NULL) == -1) {
		result = "select error\n";
		std::cout << "ca a fail bordel" << std::endl;

	} else if (FD_ISSET(socket, &readfds)) {


		std::vector<char> test;
		char c[1];
		int rc;

		while ((rc = read(socket, c, 1)) > 0) {
			if (c[0] != '\n') {
				test.push_back(*c);
			} else {
				break;
			}
		}
	//	sleep(1);
		//std::cout << "Ma chaine :" << std::endl;
		for (const auto &it : test) {
			std::cout << it;
		}
		std::cout << std::endl;

		char buffer[4096];
		int i = 0;
		for (const auto &it : test) {
			buffer[i] = test[i];
			i++;
		}
		buffer[i] = '\0';

		if (strncmp(buffer, "msz", 3) == 0) {

			std::vector<uint> bag;
			for (int i = 0; i < 8; i++)
				bag.emplace_back(0);
			for (size_t i = 0; i < 8; i++) {
				memcpy(&bag[i], buffer + 4 + i * (sizeof(uint) + 1), sizeof(uint));
			//	printf("bag %d\n", bag[i]);
			}
			finalCommand.setCommand(bag);

			//exit(1);
		}
		if (strncmp(buffer, "bct", 3) == 0) {
			std::vector<uint> bag;
			for (int i = 0; i < 8; i++)
				bag.emplace_back(0);
			for (size_t i = 0; i < 8; i++) {
				memcpy(&bag[i], buffer + 4 + i * (sizeof(uint) + 1), sizeof(uint));
		//		printf("expeted %d\n", bag[i]);

			}
			finalCommand.setCommand(bag);

			//exit(1);
		}
		std::string commandName;
		for (const auto &it : buffer) {
			if (it == ' ')
				break;
			commandName.push_back(it);
		}
		std::cout << "Nom de ma commande : " << commandName << std::endl;
		finalCommand.setCommandName(commandName);


	} else {
	//	std::cout << "NTM gros con" << std::endl;

	}
	return finalCommand;
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
	if (write(socket, msg.c_str(), msg.size()) == -1) {
		std::cout << "excpetion ici" << std::endl;
		throw std::exception();
	}
	return 0;
}