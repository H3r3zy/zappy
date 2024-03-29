/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_zappy_2017_AUTH_HPP
# define PSU_zappy_2017_AUTH_HPP

# include <vector>
# include <SFML/Audio.hpp>
# include "SFML_monitor.hpp"

namespace zap {

	class Gui;

	class Auth {
		public:
		Auth(int width, int height);
		~Auth();

		protected:
		void modalError(std::string error);
		void loopErrorDisplay();

		private:
		void initBck();
		void initPlaceHolder();
		void initTextInput();
		void initSubmit();
		void initSounds();

		void inputTextWrite(IObjectSFML *placeholder, IObjectSFML *input, bool layer);
		void GoToTheNextInput(IObjectSFML *from, IObjectSFML *to, int step);
		void setLayer(IObjectSFML *placeholder, const std::size_t &layer);

		void sendForm();
		void tryToConnect(bool error);
		bool checkConnection();


		zap::SFML_monitor _base;
		int _height = 800;
		int _width = 1200;

		std::string _nick;
		std::string _ip;
		std::string _port;

		std::vector<std::string> _listError;
		int _socketServer = 0;

		sf::Music _music;
	};
}

#endif //PSU_zappy_2017_AUTH_HPP
