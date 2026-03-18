// Contains definitions for hashing functions.

#include "Hash.h"

// Hashes a PuzzleMove
// input: const PuzzleMove reference
// output: size_t because I'm assuming this will get huge.
size_t Hash::operator()(const PuzzleMove& p) const{
    vector<int> v = p.getState().getTiles();
    size_t result = 0;
    for (const auto& i : v) {
        result = result * 17 + i; 
    }
    return result;
}

// Hashes a PuzzleState
// input: const PuzzleState reference
// output: size_t because I'm assuming this will get huge.
size_t Hash::operator()(const PuzzleState& p) const {
    vector<int> v = p.getTiles();
    size_t result = 0;
    for (const auto& i : v) {
        result = result * 17 + i;
    }
    return result;
}

// Hashes a PuzzleState
// input: PuzzleState reference
// output: size_t because I'm assuming this will get huge.
size_t Hash::operator()(PuzzleMove& p) const {
    vector<int> v = p.getState().getTiles();
    size_t result = 0;
    for (const auto& i : v) {
        result = result * 17 + i;
    }
    return result;
}