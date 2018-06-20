//
// Created by wisenoa on 19/06/18.
//


#ifndef CLIENT_CSTRING_HPP
#define CLIENT_CSTRING_HPP

#include <iostream>
#include <vector>

class CstringArray {
	public:
	CstringArray();
	CstringArray(const std::vector<uint> &commandInfo);
	~CstringArray() = default;
	void setCommandName(const std::string &command);
	void setCommand(const std::vector<uint> &commandInfo);
	const std::string &getCommandName() const;
	const std::vector<uint> &getCommand() const;

	private:
	std::string _commandName;
	std::vector<uint> _command;
};

#endif //CLIENT_CSTRING_HPP
