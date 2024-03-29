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
# include "CstringArray.hpp"

namespace zap {

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
		int level = 0;
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
		std::pair<int, int> _pos = {-1, -1};
		ressources_t ressources = {0, 0, 0, 0, 0, 0, 0};
		int player_on = 0;
	} shack_data_t;

	enum TYPE_ENQUEUE {
		T_UNKNOWN,
		T_GUI,
		T_MAP,
		T_BOTH
	};

	class Communication {
		public:
		Communication(int socket, bool &endClient);
		~Communication() = default;

		int getSocket() const;
		void setSocket(int socket);

		std::vector<CstringArray> &getEnqueueMap();
		void setEnqueueMap(std::vector<CstringArray> &newEnqueue);
		void enqueueMap(const CstringArray &command);

		std::vector<CstringArray> &getEnqueueGui();
		void enqueueGui(const CstringArray &msg);

		void loopRead();
		int writeOnServer(const std::string &msg);

		void lockGui();
		void unlockGui();

		void lockMap();
		void unlockMap();

		void lockDisplay();
		void unlockDisplay();

		void setFreq(int freq);
		int getFreq() const;

		std::vector<int> _listId;
		player_data_t _player;
		server_data_t _server;
		shack_data_t _shack;

		std::vector<std::string> _teamName;

		protected:
		void addMsgToQueue(const CstringArray command);

		private:
		int _socket = 0;
		bool &_read;

		int _freq = 1;

		std::mutex _write;

		std::mutex _display;
		std::mutex _mutexGui;
		std::mutex _mutexMap;

		std::vector<CstringArray> _enqueueMap = {};
		std::vector<CstringArray> _enqueueGui = {};

		const std::map<std::string, zap::TYPE_ENQUEUE> _forWho = {
			{"msz", zap::TYPE_ENQUEUE::T_MAP},
			{"bct", zap::TYPE_ENQUEUE::T_BOTH},
			{"pdi", zap::TYPE_ENQUEUE::T_MAP},
			{"pnw", zap::TYPE_ENQUEUE::T_MAP},
			{"pbc", zap::TYPE_ENQUEUE::T_MAP}, // broadcast
			{"tna", zap::TYPE_ENQUEUE::T_MAP}, // team number
			{"pfk", zap::TYPE_ENQUEUE::T_BOTH}, // egg dropped
			{"ebo", zap::TYPE_ENQUEUE::T_MAP}, // egg eclosion
			{"eht", zap::TYPE_ENQUEUE::T_MAP}, // egg eclosion
			{"endtna", zap::TYPE_ENQUEUE::T_MAP}, // team finish
			{"pie", zap::TYPE_ENQUEUE::T_MAP}, // end incantation
			{"pin", zap::TYPE_ENQUEUE::T_GUI},
			{"nbu", zap::TYPE_ENQUEUE::T_GUI},
			{"edi", zap::TYPE_ENQUEUE::T_GUI},
			{"nbt", zap::TYPE_ENQUEUE::T_GUI},
			{"enw", zap::TYPE_ENQUEUE::T_GUI},
			{"eht", zap::TYPE_ENQUEUE::T_GUI},
			{"pmv", zap::TYPE_ENQUEUE::T_MAP}, // move joueur
			{"pic", zap::TYPE_ENQUEUE::T_MAP}, // incantation
			{"sgt", zap::TYPE_ENQUEUE::T_MAP},
			{"ptu", zap::TYPE_ENQUEUE::T_MAP}, // change orientation joueur
			{"pdr", zap::TYPE_ENQUEUE::T_MAP}, // resource droppping
			{"pgt", zap::TYPE_ENQUEUE::T_MAP}, // resource collecting
			{"sgr", zap::TYPE_ENQUEUE::T_MAP}, // resource random generate
			{"", zap::TYPE_ENQUEUE::T_UNKNOWN}
		};
	};
}

#endif //CLIENT_COMMUNICATION_HPP
