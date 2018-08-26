#ifndef GAME_H
#define GAME_H
#include <string>
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;

bool clickPuzzle(RenderWindow &window);
bool clickNewRoundButton(RenderWindow &window);
bool clickShowPathButton(RenderWindow &window);
string intToUpperAlphabet(int num);
void drawSeparationLine(RenderWindow &window);
void movePuzzle(const RenderWindow &window, int grid[][7]);
void randomizePuzzle(int grid[][7]);
string getPuzzleString(int grid[][7]);

class Game
{
public:
	Game();
	~Game();
	void run();
};

#endif