/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_COMMUNICATION_HPP
# define CLIENT_COMMUNICATION_HPP

# include <vector>
# include <string>
# include <mutex>
#include <CstringArray.hpp>

namespace irc {

	class Communication {
		public:
		Communication(int socket, bool &endClient);
		~Communication() = default;

		int getSocket() const;
		void setSocket(int socket);

		std::vector<CstringArray> &getEnqueueMap();
		void enqueueMap(const std::vector<uint> &command);

		std::vector<std::string> &getEnqueueGui();
		void enqueueGui(const std::string &msg);

		void loopRead();
		int writeOnServer(const std::string &msg);

		void lockGui();
		void unlockGui();

		void lockMap();
		void unlockMap();

		void lockDisplay();
		void unlockDisplay();

		protected:
		void addMsgToQueue(const std::string &msg);

		private:
		int _socket = 0;
		bool &_read;

		std::mutex _write;

		std::mutex _display;
		std::mutex _mutexGui;
		std::mutex _mutexMap;

		std::vector<CstringArray> _enqueueMap;
		std::vector<std::string> _enqueueGui;
	};
}

#endif //CLIENT_COMMUNICATION_HPP
