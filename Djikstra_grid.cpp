#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minCost(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> minDistance(n, vector<int>(m, 1e9));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

        int source_r = 0, source_c = 0;
        int des_r = n - 1, des_c = m - 1;

        pq.push({0, 0, 0});
        minDistance[source_c][source_r] = 0;

        vector<int> dx = {0, 0, 1, -1};
        vector<int> dy = {1, -1, 0, 0};
        while (!pq.empty())
        {
            int dis, row, col;
            tie(dis, row, col) = pq.top();
            pq.pop();

            for (int i = 0; i < 4; i++)
            {
                int nrow = row + dx[i];
                int ncol = col + dy[i];

                if (row == des_r and col == des_c)
                    break;

                if (nrow < 0 or nrow >= n or ncol < 0 or ncol >= m)
                    continue;

                int weight = (grid[row][col] == (i + 1)) ? 0 : 1;

                if (dis + weight < minDistance[nrow][ncol]) // old+weight < new
                {
                    minDistance[nrow][ncol] = dis + weight;
                    pq.push({minDistance[nrow][ncol], nrow, ncol});
                }
            }
        }
        return minDistance[n - 1][m - 1];
    }
};