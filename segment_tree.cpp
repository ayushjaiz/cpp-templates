#include <bits/stdc++.h>
using namespace std;

class segment_tree
{
    //*endpoints:
    // segment_tree seg(a, IDENTITY_ELEMENT);
    // seg.query(left, right);

    vector<int> a, tree;
    int n, identity;
    int purpose(int a, int b)
    {
        return a + b; // only changes here
    }
    void build_util(int start, int end, int index)
    {
        if (start == end)
        {
            tree[index] = a[start];
            return;
        }
        int mid = (start + end) / 2;

        build_util(start, mid, 2 * index);
        build_util(mid + 1, end, 2 * index + 1);

        tree[index] = purpose(tree[2 * index], tree[2 * index + 1]);
    }
    int query_util(int qs, int qe, int index, int start, int end)
    {
        if (qs <= start and end <= qe)
            return tree[index];

        if (end < qs or qe < start)
            return identity;

        int mid = (start + end) / 2;
        int op1 = query_util(qs, qe, 2 * index, start, mid);
        int op2 = query_util(qs, qe, 2 * index + 1, mid + 1, end);

        return purpose(op1, op2);
    }
    void updatePoint_util(int index, int start, int end, int value, int point)
    {
        if (point < start or end < point)
            return;

        if (start == end)
        {
            tree[index] += value;
            return;
        }

        int mid = (start + end) / 2;
        updatePoint_util(2 * index, start, mid, value, point);
        updatePoint_util(2 * index + 1, mid + 1, end, value, point);

        tree[index] = purpose(tree[2 * index], tree[2 * index + 1]);
    }

public:
    segment_tree(vector<int> &a, int identity)
    {
        this->a = a;
        this->n = a.size();
        this->identity = identity;

        tree.resize(4 * n + 1, identity);

        build_util(0, a.size() - 1, 1);
    }
    int query(int left, int right)
    {
        return query_util(left, right, 1, 0, n - 1);
    }
    void updatePoint(int point, int value)
    {
        updatePoint_util(1, 0, n - 1, value, point);
    }
};