/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Auth.hpp"

int main(void)
{
	try {
		irc::Auth auth(1200, 800);
	} catch (const std::exception &e) {
		//std::cout << "Error occured" << std::endl;
		return 84;
	}
	return 0;
}