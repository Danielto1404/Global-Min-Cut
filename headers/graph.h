#ifndef GLOBAL_MIN_CUT_GRAPH_H
#define GLOBAL_MIN_CUT_GRAPH_H

#endif //GLOBAL_MIN_CUT_GRAPH_H

class graph {
public:
    explicit graph(int size);

    graph(const graph &copy);

    ~graph();

    void setValue(int i, int j, double value);

    double getValue(int i, int j) const;

    int size() const;

    friend std::ostream& operator<<(std::ostream& out, const graph& g);

private:
    int mSize;
    double **mData;
};
