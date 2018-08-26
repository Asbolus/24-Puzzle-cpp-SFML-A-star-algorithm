#include "A_star.h"
#include <queue>

struct cmp
{
	bool operator() (const Puzzle &lhs, const Puzzle &rhs)
	{
		return lhs.get_cost() > rhs.get_cost();
	}
};
priority_queue<Puzzle, vector<Puzzle>, cmp > p_functors;
Puzzle myPuzzle;

int ManhattanDistance(const string &stateRps)
{
	size_t i;
	int posX, posY, goalX, goalY, sumOfDistance = 0;
	int num[25]; // string to int
	for (i = 0; i < stateRps.size(); i++)
	{
		if ((int)stateRps[i] == 48)         // ASCII '0' = 48
			num[i] = 0;
		else
			num[i] = (int)stateRps[i] - 64; // ASCII 'A' = 65
	}

	for (i = 0; i < 25; ++i)
	{
		if (num[i] != 0)
		{
			posX = i % 5;
			posY = i / 5;

			goalX = num[i] % 5;
			goalY = num[i] / 5;

			sumOfDistance += abs(posX - goalX);
			sumOfDistance += abs(posY - goalY);
		}
	}

	return sumOfDistance;
}
void Successor(const string &stateRps, const int lastG, const string &last_acq)
{
	string nextStateRps;
	char temp;
	size_t i;
	int posX, posY;
	bool UP = false, DOWN = false, LEFT = false, RIGHT = false;

	// find 0
	for (i = 0; i < stateRps.size(); ++i)
		if (stateRps[i] == '0')
		{
			posX = i % 5;
			posY = i / 5;
			break;
		}

	if (posX > 0) LEFT  = true;
	if (posX < 4) RIGHT = true;
	if (posY > 0) UP    = true;
	if (posY < 4) DOWN  = true;

	if (UP)
	{
		nextStateRps = stateRps; 
		
		// exchange tile
		temp = nextStateRps[i];
		nextStateRps[i] = nextStateRps[i - 5];
		nextStateRps[i - 5] = temp;

		myPuzzle.set(nextStateRps, lastG + 1);
		myPuzzle.set_actionSequence(last_acq + "u");
		p_functors.push(myPuzzle);
	}

	if (DOWN)
	{
		nextStateRps = stateRps;
		temp = nextStateRps[i];
		nextStateRps[i] = nextStateRps[i + 5];
		nextStateRps[i + 5] = temp;

		myPuzzle.set(nextStateRps, lastG + 1);
		myPuzzle.set_actionSequence(last_acq + "d");
		p_functors.push(myPuzzle);
	}

	if (LEFT)
	{
		nextStateRps = stateRps;
		temp = nextStateRps[i];
		nextStateRps[i] = nextStateRps[i - 1];
		nextStateRps[i - 1] = temp;

		myPuzzle.set(nextStateRps, lastG + 1);
		myPuzzle.set_actionSequence(last_acq + "l");
		p_functors.push(myPuzzle);
	}

	if (RIGHT)
	{
		nextStateRps = stateRps;
		temp = nextStateRps[i];
		nextStateRps[i] = nextStateRps[i + 1];
		nextStateRps[i + 1] = temp;

		myPuzzle.set(nextStateRps, lastG + 1);
		myPuzzle.set_actionSequence(last_acq + "r");
		p_functors.push(myPuzzle);
	}
}
string getPathString(const string &state,const string &path)
{
	string s;
	for (size_t i = 0; i < path.size(); ++i)
	{
		if      (path[i] == 'u') { s += "Step " + to_string(i) + ": Move 0 to up"    + "\n"; }
		else if (path[i] == 'd') { s += "Step " + to_string(i) + ": Move 0 to down"  + "\n"; }
		else if (path[i] == 'l') { s += "Step " + to_string(i) + ": Move 0 to left"  + "\n"; }
		else if (path[i] == 'r') { s += "Step " + to_string(i) + ": Move 0 to right" + "\n"; }
	}
	return s;
}

Puzzle::Puzzle()
{
}
Puzzle::Puzzle(string &stateRps)
{
	this->stateRps = stateRps;
}
Puzzle::~Puzzle()
{
}
void Puzzle::set(string &stateRps, int cost_g)
{
	this->stateRps = stateRps;
	this->cost_g = cost_g;
	this->cost_h = ManhattanDistance(stateRps);
	this->cost_f = this->cost_g + this->cost_h;
}
void Puzzle::set_actionSequence(const string &last_acq)
{
	this->actionSequence = last_acq;
}
int Puzzle::get_cost() const
{
	return cost_f;
}
int Puzzle::get_cost_g() const
{
	return cost_g;
}
string Puzzle::get_stateRps() const
{
	return stateRps;
}
string Puzzle::get_actionSequence() const
{
	return this->actionSequence;
}

template <class Q>
void clearQueue(Q & q)
{
	q = Q();
}

string Puzzle::solvePuzzleAndGetPathString()
{
	clearQueue(p_functors);

	string s;
	string tempStr;
	string actionSequence;
	int tempG;

	Successor(stateRps, 0, "");
	while (tempStr != "0ABCDEFGHIJKLMNOPQRSTUVWX")
	{
		tempStr = p_functors.top().get_stateRps();
		tempG = p_functors.top().get_cost_g();
		actionSequence = p_functors.top().get_actionSequence();
		p_functors.pop();

		Successor(tempStr, tempG, actionSequence);   // push the smallest cost into Successor
	}
	return getPathString(stateRps, actionSequence);
}