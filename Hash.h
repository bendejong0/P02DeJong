#pragma once
#include <vector>
#include "PuzzleMove.h"
using namespace std;
class Hash {
public:
	size_t operator()(PuzzleMove& p);
	size_t operator()(PuzzleState& p);
};