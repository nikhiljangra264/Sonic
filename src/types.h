#pragma once

#include <cmath>
#include <string>

namespace sonic {

constexpr int MAX_MOVES = 256;
constexpr int MAX_DEPTH = 128;

using Value = int;

constexpr Value VALUE_ZERO = 0;
constexpr Value VALUE_DRAW = 0;
constexpr Value VALUE_NONE = 32002;
constexpr Value VALUE_INF = 32001;
constexpr Value VALUE_MATE = 32000;

constexpr bool is_mate_value(Value score) { return VALUE_MATE - std::abs(score) <= MAX_DEPTH; }
constexpr Value mate_in(int ply) { return VALUE_MATE - ply; }
constexpr Value mated_in(int ply) { return -VALUE_MATE + ply; }

enum Direction : int {
	NORTH = 8,
	EAST = 1,
	SOUTH = -NORTH,
	WEST = -EAST,

	NORTH_EAST = NORTH + EAST,
	SOUTH_EAST = SOUTH + EAST,
	NORTH_WEST = NORTH + WEST,
	SOUTH_WEST = SOUTH + WEST
};

constexpr Direction operator+(Direction a, Direction b) { return Direction(int(a) + int(b)); }
constexpr Direction operator*(Direction d, int i) { return Direction(i * int(d)); }
constexpr Direction operator*(int i, Direction d) { return Direction(i * int(d)); }

} // namespace sonic
