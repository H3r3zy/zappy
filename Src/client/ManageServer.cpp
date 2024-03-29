/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <cstring>
#include <sstream>
#include <ParseEnqueueMap.hpp>
#include "CstringArray.hpp"
#include "ManageServer.hpp"

std::string zap::ManageServer::readServer(int socket, bool blockRead)
{
	std::string result;
	fd_set readfds;
	struct timeval t = {0, 1000};
	char buffer[2];

	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	if (select(socket + 1, &readfds, NULL, NULL,
		(!blockRead) ? &t : NULL) == -1) {
		result = "select error\n";
	} else if (FD_ISSET(socket, &readfds)) {
		int len = 0;
		do {
			len = (int)read(socket, buffer, 1);
			if (len <= 0) {
				throw std::exception();
			}
			buffer[1] = '\0';
			result += buffer;
		} while (buffer[0] != -5 && buffer[0] != '\n');
	}
	std::stringstream ss(result);
	std::string command;
	ss >> command;
	return result;
}

CstringArray zap::ManageServer::readGameServer(int socket, bool blockRead)
{
	std::string result;
	fd_set readfds;
	CstringArray finalCommand;
	struct timeval t = {0, 300};

	//	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	if (select(socket + 1, &readfds, NULL, NULL,
		(!blockRead) ? &t : NULL) == -1)
		result = "select error\n";
	else if (FD_ISSET(socket, &readfds)) {
		std::vector<char> test;
		char c[1];
		long int rc;

		while ((rc = read(socket, c, 1)) > 0) {
			if (c[0] != -5)
				test.push_back(*c);
			else
				break;
		}
		char buffer[8192];
		int i = 0;
		for (const auto &it : test) {
			static_cast<void>(it);
			buffer[i] = test[i];
			i++;
		}
		buffer[i] = '\0';
		if (buffer[0] == '\0' && i > 0) {
			memmove(buffer, &buffer[1], i);
		}
		i--;
		if (!strncmp("pnw", buffer, 3) || !strncmp("tna", buffer, 3)) {
			std::string teamName;
			while (i > 0 && ((buffer[i] >= 'a' && buffer[i] <= 'z') ||
				(buffer[i] >= 'A' && buffer[i] <= 'Z') ||
				(buffer[i] >= '0' && buffer[i] <= '9'))) {
				teamName.insert(teamName.begin(), buffer[i]);
				i--;
			}
			finalCommand.setTeamName(teamName);
		}

		std::string commandName("");
		for (const auto &it : buffer) {
			if (it == ' ')
				break;
			if (it >= 'a' && it <= 'z') {
				commandName.push_back(it);
			}
		}
		finalCommand.setCommandName(commandName);

		for (auto &&item : _pattern) {
			if (!strncmp(item.first.c_str(), buffer, 3)) {
				item.second(buffer, finalCommand);
				break;
			}
		}

	}
	return finalCommand;
}

std::string zap::ManageServer::connectServer(int socket, std::string ip,
	std::string port
)
{
	struct sockaddr_in s_in;
	struct timeval t = {10, 0};

	struct hostent *he;
	struct in_addr **addr_list;

	if ((he = gethostbyname(ip.c_str())) == NULL)
		return "Can't get hostname";

	addr_list = (struct in_addr **) he->h_addr_list;
	ip.clear();

	if (!addr_list || !addr_list[0])
		return "Can't resolve ip address";
	ip = inet_ntoa(*addr_list[0]);

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

int zap::ManageServer::getFileDescriptorSocket()
{
	struct protoent *pe;

	pe = getprotobyname("TCP");
	if (!pe)
		return -1;
	return socket(AF_INET, SOCK_STREAM, pe->p_proto);
}

int zap::ManageServer::writeOnServer(int socket, std::string msg)
{
	if (write(socket, msg.c_str(), msg.size()) == -1) {
		throw std::exception();
	}
	return 0;
}
void zap::ManageServer::parseLine8Input(char *buffer, CstringArray &command)
{
	std::vector<uint> bag;
	for (int i = 0; i < 10; i++)
		bag.emplace_back(0);
	for (size_t i = 0; i < 10; i++) {
		bag[i] = 0;
		memcpy(&bag[i], buffer + 4 + i * (sizeof(uint) + 1), sizeof(uint));
		if (command.getCommandName() == "pnw")
		std::cout << bag[i] << std::endl;
	}
	command.setCommand(bag);
}

void zap::ManageServer::parseLine1Input(char *buffer, CstringArray &command)
{
	std::vector<uint> bag;
	bag.emplace_back(0);
	memcpy(&bag[0], buffer + 4, sizeof(uint));
	command.setCommand(bag);
}