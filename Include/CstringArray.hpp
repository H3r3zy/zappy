//
// EPITECH PROJECT, 2018
// CstringArray
// File description:
// CstringArray
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
	void setTeamName(const std::string &command);
	void setCommand(const std::vector<uint> &commandInfo);
	void clearAll();

	const std::string &getCommandName() const;
	const std::string &getTeamName() const;
	const std::vector<uint> &getCommand() const;

	private:
	std::string _commandName;
	std::string _teamName;
	std::vector<uint> _command;
};

#endif //CLIENT_CSTRING_HPP
