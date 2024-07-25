#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <limits>
#include <sstream>
#include <string>
#include <thread>

#include "chess/all.h"
#include "utils/timer.h"
#include "book.h"
#include "types.h"

namespace sonic {

struct SearchInfo {
    // Total nodes searched.
    std::uint64_t nodes = 0;
    std::uint64_t max_nodes = std::numeric_limits<std::uint64_t>::max() / 2;

    // Start time of the search.
    TimePoint start_time;
    std::uint64_t max_time = std::numeric_limits<std::uint64_t>::max() / 2;

    // Current search depth.
    int depth = 0;
    int seldepth = 0;
    int max_depth = MAX_DEPTH;

    bool stop = false;
    bool time_out() const { return stop || (max_time < time_elapsed(start_time)); }

    std::array<std::uint64_t, MAX_DEPTH> history_keys;

    void store_history(std::uint64_t key) { history_keys[depth] = key; }

    bool is_repetition(std::uint64_t key) const {
        for(int i = depth - 1; i >= 0; i--) {
            if(history_keys[i] == key) {
                return true;
            }
        }
        return false;
    }

    std::array<std::array<Move, MAX_DEPTH>, MAX_DEPTH> pv;
    std::array<int, MAX_DEPTH> pv_length = {};

    void insert_pv(int ply, Move move) {
        pv[ply][0] = move;
        std::copy(pv[ply + 1].begin(), pv[ply + 1].begin() + pv_length[ply + 1], pv[ply].begin() + 1);
        pv_length[ply] = pv_length[ply + 1] + 1;
    }

    std::string pv_to_string() const {
        std::ostringstream os;
        for(std::size_t i = 0; i < pv_length[0]; i++) {
            os << pv[0][i].to_string();
            if(i != pv_length[0] - 1) {
                os << " ";
            }
        }
        return os.str();
    }
};

void search(Position& pos, SearchInfo& search_info, const Book& book);

} // namespace sonic