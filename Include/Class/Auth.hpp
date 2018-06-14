/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_MYIRC_2017_AUTH_HPP
# define PSU_MYIRC_2017_AUTH_HPP

# include <vector>
# include "SFML_monitor.hpp"

namespace irc {

	class Gui;

	class Auth {
		public:
		Auth(int width, int height);
		~Auth() = default;

		protected:
		void modalError(std::string error);
		void loopErrorDisplay();

		private:
		void initBck();
		void initPlaceHolder();
		void initTextInput();
		void initSubmit();

		void inputTextWrite(IObjectSFML *placeholder, IObjectSFML *input, bool layer);
		void GoToTheNextInput(IObjectSFML *from, IObjectSFML *to, int step);
		void setLayer(IObjectSFML *placeholder, const std::size_t &layer);

		void sendForm();
		void tryToConnect(bool error);


		irc::SFML_monitor _base;
		int _height = 800;
		int _width = 1200;

		std::string _nick;
		std::string _ip;
		std::string _port;

		std::vector<std::string> _listError;
		int _socketServerMap = 0;
		int _socketServerGui = 0;
	};
}

#endif //PSU_MYIRC_2017_AUTH_HPP
