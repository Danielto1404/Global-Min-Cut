#include <cstring>
#include <iostream>
#include "../headers/graph.h"

graph::graph(int size) {
    mSize = size;
    mData = new double *[size];
    for (int i = 0; i < size; ++i) {
        mData[i] = static_cast<double *>(calloc(size, sizeof(double)));
    }
}

graph::graph(const graph &copy) {
    mSize = copy.mSize;
    mData = copy.mData;
    memcpy(mData, copy.mData, sizeof(double) * mSize * mSize);
}

graph::~graph() {
    for (int i = 0; i < size(); ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}

void graph::setValue(int i, int j, double value) {
    mData[i][j] = value;
}

double graph::getValue(int i, int j) const {
    return mData[i][j];
}

int graph::size() const {
    return mSize;
}

std::ostream &operator<<(std::ostream &out, const graph &g) {
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g.size(); ++j) {
            out << g.getValue(i, j) << ' ';
        }
        out << '\n';
    }
    return out;
}
