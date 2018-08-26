#ifndef A_STAR_H
#define A_STAR_H
#include <string>
using namespace std;

int ManhattanDistance(const string &stateRps);
void Successor(const string &stateRps, const int lastG, const string &last_acq);
string getPathString(const string &state, const string &path);
template <class Q>
void clearQueue(Q & q);

class Puzzle
{
public:
	Puzzle();
	Puzzle(string &stateRps);
	~Puzzle();

	void set(string &stateRps, int cost_g);
	void set_actionSequence(const string &last_acq);
	int get_cost() const;
	int get_cost_g() const;
	string get_stateRps() const;
	string get_actionSequence() const;
	string solvePuzzleAndGetPathString();
private:
	string stateRps;
	string actionSequence;
	int cost_g;
	int cost_h;
	int cost_f;
};

#endif