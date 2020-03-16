#include <iostream>
#include <map>
#include "../headers/STOER_WAGNER_ALGORITHM.h"

STOER_WAGNER_ALGORITHM::STOER_WAGNER_ALGORITHM() = default;

double STOER_WAGNER_ALGORITHM::min_cut(graph &g,
                                       std::vector<std::pair<int, int>> &min_cut_edges,
                                       clock_t maxWorkTimeInSeconds,
                                       double MAX_WEIGHT) {

    int n = g.size();
    double min_cost = MAX_WEIGHT * (n * n);

    INT_GRAPH compressed(n);
    std::map<std::pair<int, int>, bool> zero_edges;
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g.size(); ++j) {
            if (g.getValue(i, j) == 0) zero_edges[{i, j}] = true;
        }
    }

    std::chrono::time_point<std::chrono::system_clock> beginTime = std::chrono::system_clock::now();

    std::vector<int> min_cut;
    for (int i = 0; i < n; ++i) compressed[i].push_back(i);

    std::vector<double> w(n);
    std::vector<int> isCompressed(n, false);
    std::vector<int> used_in_sub_graph(n);

    for (int iteration = 0; iteration < n - 1; ++iteration) {

        if (!checkTime(beginTime, maxWorkTimeInSeconds)) break;

        used_in_sub_graph.assign(n, false);
        w.assign(n, 0);
        for (int it = 0, prev = -1; it < n - iteration; ++it) {

            if (!checkTime(beginTime, maxWorkTimeInSeconds)) break;

            int s = -1;

            // TODO: Update with Fibonacci-heap
            for (int i = 0; i < n; ++i)
                if (!isCompressed[i] && !used_in_sub_graph[i] && (s == -1 || w[i] > w[s]))
                    s = i;

            if (it == n - iteration - 1) {
                if (w[s] < min_cost) {
                    min_cost = w[s];
                    min_cut = compressed[s];
                }
                compress_vertex(compressed, prev, s);
                for (int i = 0; i < n; ++i) {
                    g.setValue(prev, i, g.getValue(prev, i) + g.getValue(s, i));
                    g.setValue(i, prev, g.getValue(i, prev) + g.getValue(s, i));
                }
                isCompressed[s] = true;
            } else {
                used_in_sub_graph[s] = true;
                for (int i = 0; i < n; ++i) {
                    w[i] += g.getValue(s, i);
                }
                prev = s;
            }
        }
    }

    std::vector<int> used_in_min_cut(n, false);
    for (int v: min_cut) used_in_min_cut[v] = true;
    for (int i = 0; i < n; ++i) {

        if (!checkTime(beginTime, maxWorkTimeInSeconds)) break;

        for (int j = 0; j < n; ++j) {

            if (!checkTime(beginTime, maxWorkTimeInSeconds)) break;

            if (!zero_edges[{i, j}] && used_in_min_cut[i] && !used_in_min_cut[j])
                min_cut_edges.emplace_back(i, j);
        }
    }

    return min_cost;
}

void STOER_WAGNER_ALGORITHM::compress_vertex(INT_GRAPH &compressed, int root, int to_compress) {
    compressed[root].insert(
            compressed[root].end(),
            compressed[to_compress].begin(), compressed[to_compress].end());
}

bool STOER_WAGNER_ALGORITHM::checkTime(std::chrono::time_point<std::chrono::system_clock> beginTime,
                                       int maxWorkTimeInSeconds) {
    std::chrono::time_point<std::chrono::system_clock> thisTime = std::chrono::system_clock::now();
    std::cout << (thisTime - beginTime).count();
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - beginTime).count()
           < maxWorkTimeInSeconds;
}
