#include "Hash.h"

size_t Hash::operator()(const PuzzleMove& p) const{
    vector<int> v = p.getState().getTiles();
    size_t result = 0;
    for (const auto& i : v) {
        result = result * 7 + i; 
    }
    return result;
}

size_t Hash::operator()(const PuzzleState& p) const {
    vector<int> v = p.getTiles();
    size_t result = 0;
    for (const auto& i : v) {
        result = result * 7 + i;
    }
    return result;
}


size_t Hash::operator()(PuzzleMove& p) const {
    vector<int> v = p.getState().getTiles();
    size_t result = 0;
    for (const auto& i : v) {
        result = result * 7 + i;
    }
    return result;
}