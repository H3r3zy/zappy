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
# include <map>

namespace irc {

	typedef struct {
		int q0;
		int q1;
		int q2;
		int q3;
		int q4;
		int q5;
		int q6;
	} ressources_t;

	typedef struct {
		int id = 1;
		std::string team = "Unknown";
		std::string status = "Unknown";
		ressources_t ressources = {0, 0, 0, 0, 0, 0, 0};
		std::pair<double, double> _pos = {0, 0};
	} player_data_t;

	typedef struct {
		int team_number = 0;
		int user = 1;
		ressources_t ressources = {0, 0, 0, 0, 0, 0, 0};
		int eggs = 0;
	} server_data_t;

	typedef struct {
		std::pair<int, int> _pos = {0, 0};
		ressources_t ressources = {0, 0, 0, 0, 0, 0, 0};
		int player_on = 0;
	} shack_data_t;

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

		void lockDisplay();
		void unlockDisplay();

		std::vector<int> _listId;
		player_data_t _player;
		server_data_t _server;
		shack_data_t _shack;

		protected:
		void addMsgToQueue(const std::string &msg);

		private:
		int _socket = 0;
		bool &_read;

		std::mutex _write;

		std::mutex _display;
		std::mutex _mutexGui;
		std::mutex _mutexMap;

		std::vector<std::string> _enqueueMap;
		std::vector<std::string> _enqueueGui;
	};
}

#endif //CLIENT_COMMUNICATION_HPP
