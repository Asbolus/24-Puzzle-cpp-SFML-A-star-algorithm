#include <random>
#include "A_star.h"
#include "Game.h"
using namespace sf;

constexpr unsigned int perGridWidth = 120;

bool clickPuzzle(RenderWindow &window)
{
	return Mouse::getPosition(window).x < 600;
}
bool clickNewRoundButton(RenderWindow &window)
{
	return Mouse::getPosition(window).x > 600 && Mouse::getPosition(window).x < 720 && Mouse::getPosition(window).y > 0 && Mouse::getPosition(window).y < 60;
}
bool clickShowPathButton(RenderWindow &window)
{
	return Mouse::getPosition(window).x > 600 && Mouse::getPosition(window).x < 720 && Mouse::getPosition(window).y > 60 && Mouse::getPosition(window).y < 120;
}
string intToUpperAlphabet(int num)
{
	string s;
	// ASCII @ = 40, A = 41, B = 42 ...... X = 58
	if (num != 0)
	{
		s = '@' + num;
	}
	else
		s = "0";

	return s;
}
void drawSeparationLine(RenderWindow &window)
{
	RectangleShape verticalLine[4];
	RectangleShape horizontalLine[4];
	RectangleShape middleLine;
	middleLine.setSize(Vector2f(4, 600));
	middleLine.setFillColor(Color::Blue);
	middleLine.setPosition(600, 0);

	for (size_t i = 0; i < 4; ++i)
	{
		verticalLine[i].setSize(Vector2f(2, 600));
		verticalLine[i].setFillColor(Color::Red);
		verticalLine[i].setPosition(perGridWidth * (i + 1), 0);

		horizontalLine[i].setSize(Vector2f(600, 2));
		horizontalLine[i].setFillColor(Color::Red);
		horizontalLine[i].setPosition(0, perGridWidth * (i + 1));

		window.draw(verticalLine[i]);
		window.draw(horizontalLine[i]);
		window.draw(middleLine);
	}
}
void movePuzzle(const RenderWindow &window, int grid[][7])
{

	Vector2i pos = Mouse::getPosition(window);
	int x = pos.y / perGridWidth + 1;
	int y = pos.x / perGridWidth + 1;
	/*      ^^^^^
	because SFML is UV coordinates, so change x and y is more easier to code
	*/
	int dx = 0;
	int dy = 0;

	if (grid[x + 1][y] == 0) { dx = 1; }
	if (grid[x - 1][y] == 0) { dx = -1; }
	if (grid[x][y + 1] == 0) { dy = 1; }
	if (grid[x][y - 1] == 0) { dy = -1; }

	// exchange blank and grid
	int n = grid[x][y];
	grid[x][y] = 0;
	grid[x + dx][y + dy] = n;
}
void randomizePuzzle(int grid[][7])
{
	std::uniform_int_distribution<unsigned> random(1, 4);
	std::default_random_engine e(time(0));

	int x;
	int y;
	int dx, dy;
	// start by 0
	for (size_t i = 0; i < 6; ++i)
		for (size_t j = 0; j < 6; ++j)
			if (grid[i][j] == 0)
			{
				x = i;
				y = j;
			}

	// Warning! loop too many times may cause the puzzle very complex
	// that needs to spend VERY LONG TIME to solve the puzzle
	for (size_t i = 0; i < 55; ++i)
	{
		int direction = random(e);
		switch (direction)
		{
		case 1:
			if (grid[x + 1][y] != 0 && grid[x + 1][y] != -1 && x < 5)
			{
				dx = 1;
				int n = grid[x + dx][y];
				grid[x][y] = n;
				grid[x + dx][y] = 0;
				++x;
			}
			break;
		case 2:
			if (grid[x - 1][y] != 0 && grid[x - 1][y] != -1 && x > 1)
			{
				dx = -1;
				int n = grid[x + dx][y];
				grid[x][y] = n;
				grid[x + dx][y] = 0;
				--x;
			}
			break;
		case 3:
			if (grid[x][y + 1] != 0 && grid[x][y + 1] != -1 && y < 5)
			{
				dy = 1;
				int n = grid[x][y + dy];
				grid[x][y] = n;
				grid[x][y + dy] = 0;
				++y;
			}
			break;
		case 4:
			if (grid[x][y - 1] != 0 && grid[x][y - 1] != -1 && y > 1)
			{
				dy = -1;
				int n = grid[x][y + dy];
				grid[x][y] = n;
				grid[x][y + dy] = 0;
				--y;
			}
			break;
		}
	}
}
string getPuzzleString(int grid[][7])
{
	string s;
	for (int i = 1; i < 6; i++)
		for (int j = 1; j < 6; j++)
		{
			s += intToUpperAlphabet(grid[i][j]);
		}

	return s;
}

Game::Game()
{
}
Game::~Game()
{
}
void Game::run()
{
	RenderWindow window(VideoMode(1430, 600), "24-Puzzle!", sf::Style::Close); // can't resize;
	window.setFramerateLimit(60);

	Texture puzzle;
	puzzle.loadFromFile("images/puzzle.png");
	Sprite puzzleSolution(puzzle);
	puzzleSolution.setPosition(600, 0);

	Texture buttonNewRoundTexture;
	buttonNewRoundTexture.loadFromFile("images/button_new_round.png");
	Sprite buttonNewRound(buttonNewRoundTexture);
	buttonNewRound.setPosition(600, 0);

	Texture buttonShowPathTexture;
	buttonShowPathTexture.loadFromFile("images/button_show_path.png");
	Sprite buttonShowPath(buttonShowPathTexture);
	buttonShowPath.setPosition(600, 60);

	Font font;
	font.loadFromFile("font/arial.ttf");
	Text solutionText;
	solutionText.setFont(font);
	solutionText.setCharacterSize(19);
	solutionText.setFillColor(sf::Color::Red);

	int grid[7][7];
	Sprite sprite[25];
	memset(grid, -1, sizeof(int) * 7 * 7); // initialize array to -1

	// initialize puzzle
	int n = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			sprite[n].setTexture(puzzle);
			sprite[n].setTextureRect(IntRect(j * perGridWidth, i * perGridWidth, perGridWidth, perGridWidth));
			grid[i + 1][j + 1] = n;
			n++;
		}
	randomizePuzzle(grid);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					if (clickPuzzle(window))
						movePuzzle(window, grid);
					if (clickNewRoundButton(window))
					{
						randomizePuzzle(grid);
					}

					if (clickShowPathButton(window))
					{
						string puzzleString = getPuzzleString(grid);
						Puzzle myPuzzle(puzzleString);
						solutionText.setString(myPuzzle.solvePuzzleAndGetPathString());
						solutionText.setPosition(1210, 0);											
					}
				}
		}

		// show puzzle
		window.clear(Color::White);
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
			{
				int n = grid[i + 1][j + 1];
				sprite[n].setPosition(j * perGridWidth, i * perGridWidth);
				window.draw(sprite[n]);
			}

		window.draw(solutionText);
		window.draw(puzzleSolution);
		window.draw(buttonNewRound);
		window.draw(buttonShowPath);
		drawSeparationLine(window);
		window.display();
	}
}