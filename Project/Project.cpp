#include <iostream>
#include <windows.h>

using namespace std;

const unsigned int width = 16;
const unsigned int hight = 4;
string window[hight][width];

int playerPos[2] = { 3, 3 };
bool playerLife = true;

void startFill() {
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			window[i][j] = '.';
		}
	}

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

int spawnDelay(int min, int max) {


	return (min + rand() % (max - min + 1)) * 1000;
}

void spawnEnemy() {
	unsigned int enemyPos[2] = { 3, 15 };

	for (int i = enemyPos[1]; i > 0; i--) {
		Sleep(1000);
		window[enemyPos[0]][i] = '#';
	}
}

void game() {
	while (playerLife) {
		spawnEnemy();
		output();
	}
}

int main() {
	startFill();

	game();
}