
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STR_TO_INT(b, i) (buff[i]) | (buff[i + 1] << 8) | \
	(buff[i + 2] << 16) | (buff[i + 3] << 24)

int main(int ac, char **av)
{
////////////////////////// SENDER PART
	char buff[55] = "nbr line dera sibu mend phir thys food eggs\n";
	uint stock[8] = {
		2, 434, 6, 8, 100, 77, 789, 3
	};

	for (size_t i = 0; i < 8; i++) {
		memcpy(buff + 4 + i * (sizeof(uint) + 1),
		       &stock[i], sizeof(uint));

	}
	printf("[%s]\n", buff);

////////////////////////// RECEIVER PART
	uint bag[8] = {0};
	for (size_t i = 0; i < 8; i++) {
		memcpy(&bag[i],
		       buff + 4 + i * (sizeof(uint) + 1), sizeof(uint));
		printf("expeted %d : %d\n", stock[i], bag[i]);

	}
	// otherwise
	uint var = 0;
//	memcpy(&var, buff[offset], sizeof(uint));
	return 0;
}
