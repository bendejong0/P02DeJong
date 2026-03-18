#ifndef _PUZZLEMOVE_
#define _PUZZLEMOVE_

#include "PuzzleState.h"
using namespace std;

enum MoveType { down, left, right, up, nullMove };

class PuzzleMove {
public:
	PuzzleMove() { }

	PuzzleMove(PuzzleState s, PuzzleState p, MoveType m) : state(s),parent(p),move(m) { }

	PuzzleMove(PuzzleState s, PuzzleState p, MoveType m, int c, int h) : state(s), parent(p), move(m), cost(c), heuristicValue(h), fValue(c + h) {}

    PuzzleState & getState() { return state; }

	PuzzleState & getParent() { return parent; }

	MoveType getMoveName() { return move; }

	int getCost() const { return cost; }

	int getHeuristicValue() const { return heuristicValue; }

	int getFValue() const { return fValue; }

private:
	PuzzleState state;
	PuzzleState parent;
	MoveType move;
	int cost;
	int heuristicValue;
	int fValue;
};
#endif
