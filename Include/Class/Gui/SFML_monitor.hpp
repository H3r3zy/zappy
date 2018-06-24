/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_SFML_MONITOR_HPP
# define PSU_ZAPPY_2017_SFML_MONITOR_HPP

# include <string>
# include <vector>
# include <map>
# include <SFML/Graphics.hpp>
# include <functional>
# include "Communication.hpp"

namespace zap {

	class IObjectSFML;
	class Gui;

	class SFML_monitor {
		public:
		SFML_monitor(const std::string &window_name, std::size_t width, std::size_t height);
		~SFML_monitor();

		void loopWindow(zap::Communication *comm);
		void closeWindow();

		void addObjectToDraw(const std::string &name, IObjectSFML *object, int scene = 0, int layer = 1);
		IObjectSFML *getObjectByName(std::string name, int scene = 0);
		void deleteObjectByName(std::string name, int scene = 0);
		void deleteObjectByScene(int scene);

		void setPostionWindow(const sf::Vector2i &pos);
		void setNameWindow(std::string name);
		bool isWindowOpen();

		void setScene(int scene);
		int getCurrentScene() const;
		bool isSceneCreated(int scene);

		sf::Vector2f getWindowSize() const;

		template<class Callable, class... Args>
		void addFuncLoop(int scene, Callable &&func, Args &&... args) {
			auto f = std::bind(
				std::forward<Callable>(func),
				std::forward<Args>(args)...);

			_listFunc[scene].emplace_back([f] {
				f();
			});
		};

		protected:
		std::string _windowName;
		sf::Vector2f _windowSize;

		std::map<int, std::map<std::string, zap::IObjectSFML *>> _listObject;
		std::map<int, std::vector<std::function<void(void)>>> _listFunc;

		private:
		void manageEvent(sf::Event &event);
		void drawObject();
		void callFuncLoop();
		void deleteObjects();

		sf::RenderWindow _window;
		int _scene;
	};
}

#endif //PSU_ZAPPY_2017_SFML_MONITOR_HPP
