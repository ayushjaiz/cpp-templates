#include <bits/stdc++.h>
using namespace std;
class Tree
{
    vector<vector<int>> parents;
    vector<int> height;

    void findHeight(int current, int currParent, int currHeight, vector<vector<int>> &edges, vector<int> &height)
    {
        height[current] = currHeight;
        for (auto neighbour : edges[current])
        {
            if (neighbour != currParent)
                findHeight(neighbour, current, currHeight + 1, edges, height);
        }
    }

    void findFirstParent(int current, int currParent, vector<vector<int>> &edges, vector<int> &firstParent)
    {
        firstParent[current] = currParent;
        for (auto neighbour : edges[current])
        {
            if (neighbour != currParent)
                findFirstParent(neighbour, current, edges, firstParent);
        }
    }

    void precompute(vector<vector<int>> &edges, vector<vector<int>> &parents)
    {
        findFirstParent(0, -1, edges, parents[0]);

        int n = parents[0].size();
        for (int k = 1; k <= log2(n); k++)
        {
            for (int curr = 0; curr < n; curr++)
            {
                int intermediate = parents[k - 1][curr];
                if (intermediate == -1)
                    parents[k][curr] = -1;
                else
                    parents[k][curr] = parents[k - 1][intermediate];
            }
        };
    }

    int kthParent(int x, int k, vector<vector<int>> &parents)
    {
        int n = parents[0].size();
        for (int i = log2(n); i >= 0; i--)
        {
            if (k & (1 << i))
                x = parents[i][x];
            if (x == -1)
                break;
        }
        return x;
    }

    int lca(int x, int y, vector<vector<int>> &parents, vector<int> &height)
    {
        int n = parents[0].size();

        if (height[x] > height[y])
            x = kthParent(x, height[x] - height[y], parents);
        else
            y = kthParent(y, height[y] - height[x], parents);

        if (x == y)
            return x;

        for (int i = log2(n); i >= 0; i--)
        {
            int parent_x = parents[i][x];
            int parent_y = parents[i][y];

            if (parent_x != parent_y)
                x = parent_x, y = parent_y;
        }
        return parents[0][x];
    }

    int distance(int x, int y, vector<vector<int>> &parents, vector<int> &height)
    {
        return (height[x] + height[y]) - (2 * height[lca(x, y, parents, height)]);
    }

public:
    // zero based indexing
    Tree(vector<vector<int>> &edges)
    {
        int n = edges.size();

        parents.resize(log2(n) + 1, vector<int>(n));
        precompute(edges, parents);

        height.resize(n);
        findHeight(0, -1, 0, edges, height);
    }

    int KthParent(int x, int k) { return kthParent(x, k, parents); }
    int Height(int x) { return height[x]; }
    int Lca(int x, int y) { return lca(x, y, parents, height); }
    int Distance(int x, int y) { return distance(x, y, parents, height); }
};
