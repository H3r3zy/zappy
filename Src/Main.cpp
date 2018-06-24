/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Auth.hpp"

int main()
{
	try {
		zap::Auth auth(1200, 800);
	} catch (const std::exception &e) {
		std::cout << "Error occured" << std::endl;
		return 84;
	}
	return 0;
}