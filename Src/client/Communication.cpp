/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "ManageServer.hpp"
#include "Communication.hpp"

irc::Communication::Communication(int socket, bool &endClient) : _socket(socket), _read(endClient)
{
}

int irc::Communication::getSocket() const
{
	return _socket;
}

void irc::Communication::setSocket(int socket)
{
	_socket = socket;
}

void irc::Communication::enqueueGui(const std::string &msg)
{
	lockGui();
	_enqueueGui.push_back(msg);
	unlockGui();
}

void irc::Communication::enqueueMap(const std::string &msg)
{
	lockMap();
	_enqueueMap.push_back(msg);
	unlockMap();
}

std::vector<std::string>& irc::Communication::getEnqueueGui()
{
	return _enqueueGui;
}

std::vector<std::string>& irc::Communication::getEnqueueMap()
{
	return _enqueueMap;
}

int irc::Communication::writeOnServer(const std::string &msg)
{
	_write.lock();
	int ret = irc::ManageServer::writeOnServer(_socket, msg);
	_write.unlock();
	return ret;
}

void irc::Communication::loopRead()
{
	std::string msg;

	while (!_read) {
		msg = irc::ManageServer::readServer(_socket, true);
		addMsgToQueue(msg);
	}
}

void irc::Communication::addMsgToQueue(const std::string &msg)
{
	std::cout << "add: " << msg << std::endl;
	// Todo: Create a parser for msg needed by gui and map, don't forget to lock / unlock
}

void irc::Communication::lockGui()
{
	_mutexGui.lock();
}

void irc::Communication::unlockGui()
{
	_mutexGui.unlock();
}

void irc::Communication::lockMap()
{
	_mutexMap.lock();
}

void irc::Communication::unlockMap()
{
	_mutexMap.unlock();
}

void irc::Communication::lockDisplay()
{
	_display.lock();
}

void irc::Communication::unlockDisplay()
{
	_display.unlock();
}