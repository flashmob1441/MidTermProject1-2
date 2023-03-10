#include <iostream>
#include <future>
#include <windows.h>
#include <conio.h>
#include <queue>
#include "cls.h"

using namespace std;

const unsigned int width = 16;
const unsigned int hight = 4;
char window[hight][width];

int enemySpeedMillSec = 1000;
unsigned int enemySpawnPos = width - 1;
unsigned int enemyPos[2] = { 3, enemySpawnPos };
const unsigned enemySpeedChange = 200;
const unsigned int enemySpawnDelay = 10;

bool playerLife = true;
unsigned int playerFlightTimeSec = 3;
unsigned int playerPos[2] = { 3, 3 };

void spawnEnemy() {
	Sleep(enemySpeedMillSec);
	enemyPos[1]--;
}

void playerJump() {
	int key;
	bool playerOnGround = true;

	if (playerOnGround) {
		key = _getch();

		if (key == 32) {
			playerPos[0] = 2;
			playerOnGround = false;
			Sleep(playerFlightTimeSec * 1000);
			playerPos[0] = 3;
			playerOnGround = true;
		}
	}
}

void fill() {
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			window[i][j] = '.';
		}
	}

	window[enemyPos[0]][enemyPos[1]] = '#';
	window[playerPos[0]][playerPos[1]] = '@';
}

void output() {
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			cout << window[i][j];
		}
		cout << endl;
	}
}

int randomDelay(int min, int max) {
	srand(time(NULL));
	return (min + rand() % (max - min + 1));
}

void start() {
	queue<future<void>> playerActions;

	bool haveEnemy = false;

	while (playerLife) {
		playerActions.push(async(playerJump));

		fill();
		output();

		if (haveEnemy) {
			spawnEnemy();

			if (enemyPos[0] == playerPos[0] && enemyPos[1] == playerPos[1]) {
				playerLife = false;
			}
			if (enemyPos[1] == 0) {
				if (enemySpeedMillSec <= 0) {
					break;
				}
				enemySpeedMillSec -= enemySpeedChange;
				enemyPos[1] = enemySpawnPos;
				haveEnemy = false;
			}
		}
		else {
			if (randomDelay(1, 100) < enemySpawnDelay) {
				Sleep(randomDelay(1, 5) * 1000);
			}
			else {
				haveEnemy = true;
			}
		}
		cls();
	}
	cls();

	if (playerLife) {
		cout << "You win!";
	}
	else {
		cout << "You Died";
	}
	exit(1);
}

int main() {
	start();
}