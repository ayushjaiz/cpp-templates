#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
int mod = 1e9 + 7;

class segment_tree
{
    vector<pii> tree;
    int n;
    pii identity;

    pii purpose(pii &a, pii &b)
    {
        if (a.first == 0 and b.first == 0)
            return a;

        if (a.first == b.first)
            return {a.first, (a.second + b.second) % mod};
        else if (a.first > b.first)
            return a;
        else
            return b;
    }
    void build_util(int start, int end, int index)
    {
        if (start == end)
        {
            tree[index] = identity;
            return;
        }
        int mid = (start + end) / 2;

        build_util(start, mid, 2 * index);
        build_util(mid + 1, end, 2 * index + 1);

        tree[index] = purpose(tree[2 * index], tree[2 * index + 1]);
    }

    pii query_util(int qs, int qe, int index, int start, int end)
    {
        if (qs <= start and end <= qe)
            return tree[index];

        if (end < qs or qe < start)
            return identity;

        int mid = (start + end) / 2;
        pii op1 = query_util(qs, qe, 2 * index, start, mid);
        pii op2 = query_util(qs, qe, 2 * index + 1, mid + 1, end);

        return purpose(op1, op2);
    }
    void updatePoint_util(int index, int start, int end, pii value, int point)
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

        tree[index] = purpose(tree[2 * index], tree[2 * index + 1]);
    }

public:
    segment_tree(int n)
    {
        this->n = n;
        identity = {0, 1};

        tree.resize(4 * n + 1, identity);

        build_util(0, n - 1, 1);
    }
    pii query(int left, int right)
    {
        return query_util(left, right, 1, 0, n - 1);
    }
    void updatePoint(int point, pii value)
    {
        updatePoint_util(1, 0, n - 1, value, point);
    }
};

bool comp(pair<int, int> &a, pair<int, int> &b)
{
    if (a.first != b.first)
        return a.first < b.first;

    return a.second > b.second;
}

int32_t main()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<pair<int, int>> nums_map(n);
    for (int i = 0; i < n; i++)
        nums_map[i] = {nums[i], i};

    sort(nums_map.begin(), nums_map.end(), comp);

    vector<int> pos(n);
    for (int i = 0; i < n; i++)
        pos[nums_map[i].second] = i;

    segment_tree seg(n + 1);

    for (int i = 0; i < n; i++)
    {
        auto it = seg.query(0, pos[i] - 1);
        seg.updatePoint(pos[i], {it.first + 1, it.second});
    }

    auto ans = seg.query(0, n);
    cout << ans.first << " " << ans.second << endl;

    return 0;
}
