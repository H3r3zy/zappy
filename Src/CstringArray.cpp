//
// EPITECH PROJECT, 2018
// CstringArray.cpp
// File description:
// CstringArray
//

#include "CstringArray.hpp"

CstringArray::CstringArray(const std::vector<uint> &commandInfo)
{
	_command = commandInfo;
}

void CstringArray::setCommandName(const std::string &command)
{
	_commandName = command;
}

const std::vector<uint> &CstringArray::getCommand() const
{
	return _command;
}

const std::string &CstringArray::getCommandName() const
{
	return _commandName;
}

CstringArray::CstringArray()
{
}

void CstringArray::setCommand(const std::vector<uint> &commandInfo)
{
	_command = commandInfo;
}

const std::string &CstringArray::getTeamName() const
{
	return _teamName;
}

void CstringArray::setTeamName(const std::string &command)
{
	_teamName = command;
}

void CstringArray::clearAll()
{
	_command.clear();
	_teamName.clear();
	_commandName.clear();
}
