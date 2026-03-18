#pragma once
#include "PuzzleState.h"
#include "PuzzleMove.h"

using namespace std;
class Heuristic {
public:
	
	Heuristic(PuzzleState g);
	Heuristic() {}

	bool operator()(const PuzzleMove& s1, const PuzzleMove& s2);
	int operator()(const PuzzleState& s1) const;
private:
	PuzzleState goal;
	vector<int> inverseTable;
	int N;
};