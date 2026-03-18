#include "Heuristic.h"
#include "PuzzleMove.h"

Heuristic::Heuristic(PuzzleState g) : goal(g) {

    // set N
    N = g.getTiles().size();

	vector<int> table(g.getTiles().size());
	for (int i = 0; i < table.size(); i++) {
		table[g.getTiles()[i]] = i;
	}
    // build a reverse lookup table so we can quickly 
    // find distances in tiles.
    inverseTable = table;
}

bool Heuristic::operator()(const PuzzleMove& s1, const PuzzleMove& s2){

	return s1.getFValue() > s2.getFValue();
		
}

int Heuristic::operator()(const PuzzleState& s1) const {

    vector<int> tiles = s1.getTiles();
    int sum = 0;

    int N = sqrt(tiles.size());

    for (int i = 0; i < tiles.size(); i++) {

        int tile = tiles[i];
        if (tile == 0) continue;

        int goalIndex = inverseTable[tile];

        int startRow = i / N;
        int startCol = i % N;

        int goalRow = goalIndex / N;
        int goalCol = goalIndex % N;

        sum += abs(startRow - goalRow) + abs(startCol - goalCol);
    }

    return sum;
}