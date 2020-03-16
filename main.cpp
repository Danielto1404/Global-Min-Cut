#include <iostream>
#include <fstream>
#include <map>
#include "headers/STOER_WAGNER_ALGORITHM.h"

using namespace std;

void parseInputLine(const string &s, int &from, int &to, double &w) {
    string tmp;
    int cnt = 0;
    for (char c: s) {
        if (c == ',') {
            if (cnt == 0) {
                cnt++;
                from = stoi(tmp);
            } else to = stoi(tmp);
            tmp = string();
        } else {
            tmp += c;
        }
    }
    if (cnt == 0)
        return;
    w = stod(tmp);
}

int main() {
    ifstream ip("/Users/daniilkorolev/Documents/Global-Min-Cut/main_test.csv");
    string data;
    map<int, int> vertexes;
    map<pair<int, int>, double> weights;
    int elementCnt = 0;
    int skip_lines = 1;
    cout << "Start reading data..\n";
    while (ip.good()) {
        int from, to;
        double w;
        getline(ip, data);
        if (skip_lines) {
            --skip_lines;
            continue;
        }
        parseInputLine(data, from, to, w);
        if (vertexes.find(from) == vertexes.end())
            vertexes[from] = elementCnt++;

        if (vertexes.find(to) == vertexes.end())
            vertexes[to] = elementCnt++;

        weights[{vertexes[from], vertexes[to]}] = w;
    }

    graph g = graph(elementCnt);
    for (const auto edge: weights) {
        int from = edge.first.first, to = edge.first.second;
        double w = edge.second;
        g.setValue(from, to, w);
        g.setValue(to, from, w);
    }
    cout << "Data successfully read.\n\n";
    cout << "Start computing data..\n";
    std::vector<std::pair<int, int>> min_cur_edges;
    double min_cut = STOER_WAGNER_ALGORITHM::min_cut(g, min_cur_edges, 1);
    cout << "min-cut value = " << min_cut << "\nEdges in min-cut:\n";
    for (auto e: min_cur_edges)
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
}
