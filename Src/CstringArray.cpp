//
// Created by wisenoa on 19/06/18.
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
