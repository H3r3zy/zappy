/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <cstring>
#include <regex>
#include "ManageServer.hpp"
#include "Communication.hpp"

irc::Communication::Communication(int socket, bool &endClient) : _socket(socket), _read(endClient)
{
	writeOnServer("sgt");
	CstringArray msg = irc::ManageServer::readGameServer(_socket, true);
	if (msg.getCommandName() == "sgt")
		_freq = msg.getCommand()[0];
}

int irc::Communication::getSocket() const
{
	return _socket;
}

void irc::Communication::setSocket(int socket)
{
	_socket = socket;
}

void irc::Communication::enqueueGui(const CstringArray &msg)
{
	lockGui();
	_enqueueGui.emplace_back(msg);
	unlockGui();
}


void irc::Communication::enqueueMap(const CstringArray &command)
{
	lockMap();
	_enqueueMap.emplace_back(command);
	unlockMap();
}

std::vector<CstringArray> &irc::Communication::getEnqueueGui()
{
	return _enqueueGui;
}

std::vector<CstringArray> &irc::Communication::getEnqueueMap()
{
	return _enqueueMap;
}

int irc::Communication::writeOnServer(const std::string &msg)
{
	_write.lock();
	//std::cout << "jecris ["  << msg << "] au serveur" << std::endl;
	int ret = irc::ManageServer::writeOnServer(_socket, msg + "\n");
	_write.unlock();
	return ret;
}

void irc::Communication::loopRead()
{
	CstringArray msg;

	while (!_read) {
		msg = irc::ManageServer::readGameServer(_socket, true);
		addMsgToQueue(msg);
	}
}

void irc::Communication::addMsgToQueue(const CstringArray &command)
{
	auto tmpPrint = command.getCommand();
/*	if (tmpPrint.size() == 9) {
		//std::cout << "J'arrive à la fin du parsing, le nom de la commande est [" << command.getCommandName() << "]" << std::endl;
		//std::cout << "Et son message est :" << tmpPrint[0] << " "
			<< tmpPrint[1] << " " << tmpPrint[2] << " "
			<< tmpPrint[3] << " " << tmpPrint[4] << " "
			<< tmpPrint[5] << " " << tmpPrint[6] << " "
			<< tmpPrint[7] << std::endl;
	}
 */
	if (!command.getCommandName().empty()) {
		for (auto &&comm : _forWho) {
			if (comm.first == command.getCommandName()) {
				if (comm.second == irc::TYPE_ENQUEUE::T_MAP || comm.second == irc::TYPE_ENQUEUE::T_BOTH)
					enqueueMap(command);
				if (comm.second == irc::TYPE_ENQUEUE::T_GUI || comm.second == irc::TYPE_ENQUEUE::T_BOTH)
					enqueueGui(command);
				return;
			}
		}
	}
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

void irc::Communication::setEnqueueMap(std::vector<CstringArray> &newEnqueue)
{
	_enqueueMap = newEnqueue;
}

void irc::Communication::setFreq(int freq)
{
	_freq = freq;
}

int irc::Communication::getFreq() const
{
	return _freq;
}