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

namespace irc {

	class Communication {
		public:
		Communication(int socket, bool &endClient);
		~Communication() = default;

		int getSocket() const;
		void setSocket(int socket);

		std::vector<std::string> &getEnqueueMap();
		void enqueueMap(const std::string &msg);

		std::vector<std::string> &getEnqueueGui();
		void enqueueGui(const std::string &msg);

		void loopRead();
		int writeOnServer(const std::string &msg);

		void lockGui();
		void unlockGui();

		void lockMap();
		void unlockMap();

		protected:
		void addMsgToQueue(const std::string &msg);

		private:
		int _socket = 0;
		bool &_read;

		std::mutex _write;

		std::mutex _mutexGui;
		std::mutex _mutexMap;

		std::vector<std::string> _enqueueMap;
		std::vector<std::string> _enqueueGui;
	};
}

#endif //CLIENT_COMMUNICATION_HPP
