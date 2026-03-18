#pragma once
#include <vector>
#include "PuzzleMove.h"
using namespace std;
class Hash {
public:
	size_t operator()(const PuzzleMove& p) const;
	size_t operator()(const PuzzleState& p) const;
	size_t operator()(PuzzleMove& p) const;

};