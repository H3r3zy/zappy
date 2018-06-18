//
// Created by wisenoa on 17/06/18.
//


#ifndef PSU_ZAPPY_2017_SFMLTOOL_HPP
#define PSU_ZAPPY_2017_SFMLTOOL_HPP

#include <SFML/Graphics/Font.hpp>

class SfmlTool {
	public:
	static sf::Font arialFont;
	static bool InitAllFont();
	static const sf::Font &getArialFont();
};

#endif //PSU_ZAPPY_2017_SFMLTOOL_HPP
