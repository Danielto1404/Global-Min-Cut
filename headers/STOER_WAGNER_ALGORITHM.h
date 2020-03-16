#include <vector>
#include <queue>
#include "graph.h"

#ifndef GLOBAL_MIN_CUT_STOER_WAGNER_ALGORITHM_H
#define GLOBAL_MIN_CUT_STOER_WAGNER_ALGORITHM_H

#endif //GLOBAL_MIN_CUT_STOER_WAGNER_ALGORITHM_H

using INT_GRAPH = std::vector<std::vector<int>>;

class STOER_WAGNER_ALGORITHM {

public:
    STOER_WAGNER_ALGORITHM();

// MAX WEIGHT SHOULD BE LESS THEN LONG_LONG_MAX_VALUE / (n * n)
    static double
    min_cut(graph &g, std::vector<std::pair<int, int>> &min_cut_edges, clock_t maxWorkTimeInSeconds,
            double MAX_WEIGHT = 1000000000);

private:
    static void compress_vertex(INT_GRAPH &compressed, int root, int to_compress);

    static bool checkTime(std::chrono::time_point<std::chrono::system_clock> beginTime, int maxWorkTimeInSeconds);
};