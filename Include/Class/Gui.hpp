/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/
#ifndef CLIENT_GUI_HPP
#define CLIENT_GUI_HPP

namespace irc {

	class Gui {
		public:
		Gui(const pid_t &);
		~Gui() = default;

		void loopDisplay();

		protected:

		private:
		pid_t _pidMap;
	};
}

#endif //CLIENT_GUI_HPP
