#include "PuzzleMove.h"
#include "Heuristic.h"
#include "PuzzleState.h"
#include <algorithm>
#include <queue>   // for std::priority_queue
#include <utility> // for std::pair
#include "Hash.h"
#include <unordered_set>

bool findSolution(const PuzzleState& start, const PuzzleState& goal);
void printSolution(unordered_set<PuzzleMove, Hash>& closed, PuzzleMove& goal);
void expandState(PuzzleMove& current, priority_queue<PuzzleMove, vector<PuzzleMove>, Heuristic>& open, unordered_set<PuzzleMove, Hash>& closed, Heuristic& h);
vector<PuzzleMove> buildSolutionList(unordered_set<PuzzleMove, Hash>& closed, PuzzleMove& goal);

int main() {
	cout << "*** P01 Puzzle Uninformed Search - A* ***" << endl;
	cout << "<======================================================>" << endl;
	cout << "Enter number of rows and columns: ";
	size_t N;
	cin >> N;

	cout << "\nEnter Start State row by row:" << endl;
	PuzzleState start = PuzzleState(N, N);
	cin >> start;
	cout << "\nEnter Goal State row by row: " << endl;
	PuzzleState goal = PuzzleState(N, N);
	cin >> goal;
	cout << endl << endl;

	if (start == goal) {
		cout << "*** Solution found immediately: start state is the goal state. ***\n\n";
	}
	else {
		findSolution(start, goal);
	}
}

// takes in the start state and goal state.
bool findSolution(const PuzzleState& start, const PuzzleState& goal) {
	Heuristic h(goal);
	priority_queue<PuzzleMove, vector<PuzzleMove>, Heuristic> open(h);
	unordered_set<PuzzleMove, Hash> closed;
	open.push(PuzzleMove(start, PuzzleState::NullState, MoveType::nullMove));


	while (!open.empty()) {
		PuzzleMove current = open.top();
		open.pop();
		if (current.getState() == goal) {
			closed.insert(current);
			printSolution(closed, current);
			return true;
		}
		else {
			closed.insert(current);
			expandState(current, open, closed, h);
		}
	}
	// something really bad happened
	return false;
}

// takes in the current state, a priority queue, an unordered set, and a heuristic function which contains the goal state.
void expandState(PuzzleMove& current, priority_queue<PuzzleMove, vector<PuzzleMove>, Heuristic>& open, unordered_set<PuzzleMove, Hash>& closed, Heuristic& h) {
	// Down, Left, Up, Right

	auto moveBlank = [&current](MoveType direction) {
		switch (direction) {
		case MoveType::down:
			return current.getState().moveBlankDown();
			break;
		case MoveType::left:
			return current.getState().moveBlankLeft();
			break;
		case MoveType::up:
			return current.getState().moveBlankUp();
			break;
		case MoveType::right:
			return current.getState().moveBlankRight();
			break;
		}
	};

	if (current.getState().canMoveDown()) {
		PuzzleState temp = moveBlank(MoveType::down);
		// if it's not in the closed list,
		PuzzleMove key(temp, PuzzleState(), nullMove);
		if (closed.find(key) == closed.end()) {
			// add it to the open list
			open.push(PuzzleMove(temp, current.getState(), MoveType::down, current.getCost()+1, h(temp)));
		}
	}
	if (current.getState().canMoveLeft()) {
		PuzzleState temp = moveBlank(MoveType::left);
		// if it's not in the closed list,
		PuzzleMove key(temp, PuzzleState(), nullMove);
		if (closed.find(key) == closed.end()) {
			// add it to the open list
			open.push(PuzzleMove(temp, current.getState(), MoveType::left, current.getCost() + 1, h(temp)));
		}
	}
	if (current.getState().canMoveUp()) {
		PuzzleState temp = moveBlank(MoveType::up);
		// if it's not in the closed list,
		PuzzleMove key(temp, PuzzleState(), nullMove);
		if (closed.find(key) == closed.end()) {
			// add it to the open list
			open.push(PuzzleMove(temp, current.getState(), MoveType::up, current.getCost() + 1, h(temp)));
		}
	}
	if (current.getState().canMoveRight()) {
		PuzzleState temp = moveBlank(MoveType::right);
		// if it's not in the closed list,
		PuzzleMove key(temp, PuzzleState(), nullMove);
		if (closed.find(key) == closed.end()) {
			// compute the heuristic value of the state
			PuzzleMove tempMove(temp, current.getState(), MoveType::right, current.getCost() + 1, h(temp));
			// add it to the open list
			open.push(tempMove);
		}
	}
}

// takes in an unordered_set and goal state
// takes in the goal state because otherwise we dont know where to start
// because unordered_set does not have a "first" or "last" element.
vector<PuzzleMove> buildSolutionList(unordered_set<PuzzleMove, Hash>& closed, PuzzleMove& goal) {
	vector<PuzzleMove> solutionList;

	PuzzleMove current = goal;

	// find the previous node by hashing the parent
	while (current.getMoveName() != nullMove) {
		solutionList.push_back(current);

		PuzzleState parentState = current.getParent();

		// dummy key, only state matters
		PuzzleMove key(parentState, PuzzleState(), nullMove);

		auto it = closed.find(key);
		if (it == closed.end()) break; // safety

		current = *it;
	}
	solutionList.push_back(current); // add the start state

	return solutionList;
}

// takes in an unordered_set, goal state
// needs the goal state because it has to pass it to buildSolutionList
void printSolution(unordered_set<PuzzleMove, Hash>& closed, PuzzleMove& goal) {
	vector<PuzzleMove> solution;
	int nodesExpanded = closed.size()-1;

	solution = buildSolutionList(closed, goal);
	int pathLength = solution.size()-1;

	cout << "*** Solution Found ***\n\n";

	for (auto it = solution.rbegin(); it != solution.rend(); it++)
	{
		switch (it->getMoveName())
		{
		case MoveType::down:
			cout << "down\n\n";
			break;
		case MoveType::left:
			cout << "left\n\n";
			break;
		case MoveType::right:
			cout << "right\n\n";
			break;
		case MoveType::up:
			cout << "up\n\n";
			break;
		}

		it->getState().print(cout);
		cout << "\n";

	}

	cout << "\nNumber of nodes expanded: " << nodesExpanded;
	cout << "\nPath length to Goal: " << pathLength;
	cout << "\n\n";
}