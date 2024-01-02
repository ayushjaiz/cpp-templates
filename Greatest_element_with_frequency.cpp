#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pii pair<int, int>
#define ff first
#define ss second

int mod = 1e9 + 7;
int add(int a, int b) { return (a + b + mod) % mod; }

// segment tree (without lazy updates)
class segment_tree
{
    // *endpoints:
    //
    // seg.query(left, right);
    // seg.updatePoint(point, value);

    vector<pii> tree;
    vector<int> a;
    int n;
    pii identity = {0, 1};
    pii purpose(pii a, pii b)
    {
        if (a.ff > b.ff)
            return a;
        else if (a.ff < b.ff)
            return b;
        else
        {
            if (a.ff == 0)
                return {0, 1};
            else
                return {a.ff, add(a.ss, b.ss)};
        }
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
    segment_tree(vector<int> &a)
    {
        this->n = n;
        this->a = a;

        tree.resize(4 * n + 1, identity);

        build_util(0, a.size() - 1, 1);
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

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<pii> vp(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        vp[i] = {a[i], i};
    }

    vector<int> a_copy(n);

    vector<int> pos(n);
    sort(vp.begin(), vp.end());
    for (int i = 0; i < n; i++)
        pos[vp[i].ss] = i, a_copy[i] = vp[i].ff;

    vector<int> count(n + 1, 0);

    segment_tree seg(count);

    for (int i = 0; i < n; i++)
    {
        int ele = lower_bound(a_copy.begin(), a_copy.end(), a[i]) - a_copy.begin();

        pii it = seg.query(0, ele - 1);
        seg.updatePoint(pos[i], {add(it.ff, 1), it.ss});

        // cout << pos[i] << " " << it.ff + 1 << " " << it.ss << endl;
    }
    pii ans = seg.query(0, n - 1);
    cout << ans.ff << " " << ans.ss;

    return 0;
}