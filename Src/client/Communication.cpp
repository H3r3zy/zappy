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

zap::Communication::Communication(int socket, bool &endClient) : _socket(socket), _read(endClient)
{
	writeOnServer("sgt");
}

int zap::Communication::getSocket() const
{
	return _socket;
}

void zap::Communication::setSocket(int socket)
{
	_socket = socket;
}

void zap::Communication::enqueueGui(const CstringArray &msg)
{
	lockGui();
	_enqueueGui.emplace_back(msg);
	unlockGui();
}


void zap::Communication::enqueueMap(const CstringArray &command)
{
	lockMap();
	_enqueueMap.emplace_back(command);
	unlockMap();
}

std::vector<CstringArray> &zap::Communication::getEnqueueGui()
{
	return _enqueueGui;
}

std::vector<CstringArray> &zap::Communication::getEnqueueMap()
{
	return _enqueueMap;
}

int zap::Communication::writeOnServer(const std::string &msg)
{
	_write.lock();
	int ret = zap::ManageServer::writeOnServer(_socket, msg + "\n");
	_write.unlock();
	return ret;
}

void zap::Communication::loopRead()
{
	while (!_read) {
		addMsgToQueue(zap::ManageServer::readGameServer(_socket, true));
	}
}

void zap::Communication::addMsgToQueue(const CstringArray command)
{
	if (!command.getCommandName().empty()) {
		for (auto &&comm : _forWho) {
			if (comm.first == command.getCommandName()) {
				if (comm.second == zap::TYPE_ENQUEUE::T_MAP || comm.second == zap::TYPE_ENQUEUE::T_BOTH) {
					enqueueMap(command);
				}
				if (comm.second == zap::TYPE_ENQUEUE::T_GUI || comm.second == zap::TYPE_ENQUEUE::T_BOTH)
					enqueueGui(command);
				return;
			}
		}
	}
}

void zap::Communication::lockGui()
{
	_mutexGui.lock();
}

void zap::Communication::unlockGui()
{
	_mutexGui.unlock();
}

void zap::Communication::lockMap()
{
	_mutexMap.lock();
}

void zap::Communication::unlockMap()
{
	_mutexMap.unlock();
}

void zap::Communication::lockDisplay()
{
	_display.lock();
}

void zap::Communication::unlockDisplay()
{
	_display.unlock();
}

void zap::Communication::setEnqueueMap(std::vector<CstringArray> &newEnqueue)
{
	_enqueueMap = newEnqueue;
}

void zap::Communication::setFreq(int freq)
{
	_freq = freq;
}

int zap::Communication::getFreq() const
{
	return _freq;
}