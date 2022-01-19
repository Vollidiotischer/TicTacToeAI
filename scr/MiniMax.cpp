#include <iostream>
#include <cmath>
#include "Vars.h"

extern int player; 

int solver(Tile(&)[3][3], int, bool); 
int determineWinner(Tile(&)[3][3]); 

void miniMax(Tile (&field)[3][3]) {

	int maxScore = -100000000;

	int pos[2] = { 0, 0 };

	for (int i = 0; i < 3; i++) {
		for (int i2 = 0; i2 < 3; i2++) {
			if (field[i][i2].used == 0) {

				field[i][i2].used = player; 
				int score = solver(field, 0, false);
				field[i][i2].used = 0;

				if (score > maxScore) {
					maxScore = score;
					pos[0] = i;
					pos[1] = i2;
				}
				std::cout << i << "-" << i2 << "-" << score << "   ";
			}
			else {
				std::cout << i << "-" << i2 << "-xxx   "; 
			}
		}
		std::cout << std::endl; 
	}

	if (field[pos[0]][pos[1]].used == 0) {
		field[pos[0]][pos[1]].used = player;
	}

	player *= -1; 
	std::cout << std::endl << std::endl; 
}

int solver(Tile(&field)[3][3], int depth, bool isMaximizing) {
	int ret = determineWinner(field);

	if (ret != 0) {
		return ret * 100;// -depth;
	}


	if (isMaximizing) {
		long bestScore = -100000000;
		for (int i2 = 0; i2 < 3; i2++) {
			for (int i = 0; i < 3; i++) {
				if (field[i][i2].used == 0) {

					field[i][i2].used = player;
					


					int score = solver(field, depth+1, false);

					if (score > bestScore) {
						bestScore = score;
					}

					bestScore -= (int)((double)bestScore / (double)abs(bestScore));

					field[i][i2].used = 0;



				}
			}
		}
		return bestScore; 
	}
	else{
		long bestScore = 100000000;
		for (int i = 0; i < 3; i++) {
			for (int i2 = 0; i2 < 3; i2++) {
				if (field[i][i2].used == 0) {


					field[i][i2].used = (player * -1);
					

					int score = solver(field, depth+1, true);

					if (score < bestScore) {
						bestScore = score;
					}

					bestScore -= (int)((double)bestScore / (double)abs(bestScore));

					field[i][i2].used = 0;



					
				}
			}
		}
		return bestScore;
	}

}

int determineWinner(Tile(&field)[3][3]) {

	for (int i = 0; i < 3; i++) {
		if (field[i][0].used == field[i][1].used && field[i][1].used == field[i][2].used && field[i][0].used != 0) {
			return field[i][0].used; 
		}

		if (field[0][i].used == field[1][i].used && field[1][i].used == field[2][i].used && field[0][i].used != 0) {
			return field[0][i].used;
		}
	}

	if (field[0][0].used == field[1][1].used && field[1][1].used == field[2][2].used && field[0][0].used != 0) {
		return field[0][0].used;
	}

	if (field[0][2].used == field[1][1].used && field[1][1].used == field[2][0].used && field[0][2].used != 0) {
		return field[0][2].used;
	}
	
	int openSpots = 0; 

	for (int i = 0; i < 3; i++) {
		for (int i2 = 0; i2 < 3; i2++) {
			if (field[i][i2].used == 0) {
				openSpots++; 
			}
		}
	}

	if (openSpots == 0) {
		return -1; 
	}

	return 0; 
}


/*

1 -> AI
-1 -> Human 

*/