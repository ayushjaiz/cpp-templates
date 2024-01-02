#include <bits/stdc++.h>
using namespace std;

class segment_tree
{
    // *endpoints:
    //
    // seg.query(left, right);
    // seg.updatePoint(point, value);
    // seg.get_frequency(left, right, x);

    vector<pair<int, int>> tree;
    vector<int> a;
    int n;
    pair<int, int> identity = {-1, 0};

    unordered_map<int, vector<int>> mp;

    pair<int, int> merge(pair<int, int> a, pair<int, int> b)
    {
        if (a.first == b.first)
            return {a.first, a.second + b.second};

        if (a.second < b.second)
            return {b.first, b.second - a.second};
        else
            return {a.first, a.second - b.second};
    }
    void build_util(int start, int end, int index)
    {
        if (start == end)
        {
            tree[index] = {a[start], 1};
            return;
        }
        int mid = (start + end) / 2;

        build_util(start, mid, 2 * index);
        build_util(mid + 1, end, 2 * index + 1);

        tree[index] = merge(tree[2 * index], tree[2 * index + 1]);
    }
    pair<int, int> query_util(int qs, int qe, int index, int start, int end)
    {
        if (qs <= start and end <= qe)
            return tree[index];

        if (end < qs or qe < start)
            return identity;

        int mid = (start + end) / 2;
        pair<int, int> op1 = query_util(qs, qe, 2 * index, start, mid);
        pair<int, int> op2 = query_util(qs, qe, 2 * index + 1, mid + 1, end);

        return merge(op1, op2);
    }
    void updatePoint_util(int index, int start, int end, pair<int, int> value, int point)
    {
        if (point < start or end < point)
            return;

        if (start == end)
        {
            tree[index] = value;
            return;
        }

        int mid = (start + end) / 2;
        updatePoint_util(2 * index, start, mid, value, point);
        updatePoint_util(2 * index + 1, mid + 1, end, value, point);

        tree[index] = merge(tree[2 * index], tree[2 * index + 1]);
    }

public:
    segment_tree(vector<int> &a)
    {
        this->a = a;
        this->n = a.size();

        for (int i = 0; i < n; i++)
            mp[a[i]].push_back(i);

        tree.resize(4 * n + 1, identity);

        build_util(0, a.size() - 1, 1);
    }
    int get_frequency(int left, int right, int x)
    {
        auto it1 = upper_bound(mp[x].begin(), mp[x].end(), right);
        auto it2 = lower_bound(mp[x].begin(), mp[x].end(), left);
        return it1 - it2;
    }
    pair<int, int> query(int left, int right)
    {
        return query_util(left, right, 1, 0, n - 1);
    }
    void updatePoint(int point, pair<int, int> value)
    {
        updatePoint_util(1, 0, n - 1, value, point);
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    segment_tree seg(a);

    int q;
    cin >> q;
    while (q--)
    {
        int left, right;
        cin >> left >> right;
        left--, right--;

        pair<int, int> it = seg.query(left, right);

        if (it.second == 0) // or it.first == -1;
            cout << "no" << endl;
        else
        {
            int frequency = seg.get_frequency(left, right, it.first);

            if (frequency * 2 > (right - left + 1))
                cout << "yes " << it.first << endl;
            else
                cout << "no" << endl;
        }
    }

    return 0;
}