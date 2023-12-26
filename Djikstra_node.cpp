#include <bits/stdc++.h>
using namespace std;

int networkDelayTime(vector<vector<int>> &times, int n, int k)
{
    vector<vector<pair<int, int>>> edges(n + 1, vector<pair<int, int>>());

    for (int i = 0; i < times.size(); i++)
    {
        int u = times[i][0], v = times[i][1], weight = times[i][2];

        edges[u].push_back({v, weight});
    }

    int inf = 1e9;
    priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;
    vector<int> minDistance(n + 1, inf);

    pq.push({0, k});
    minDistance[k] = 0;

    while (!pq.empty())
    {
        int dis, node;
        tie(dis, node) = pq.top();
        pq.pop();

        // if (node == destination)
        // continue;

        if (minDistance[node] < dis)
            continue;

        for (auto it : edges[node])
        {
            int adjNode = it.first, weight = it.second;
            if (dis + weight < minDistance[adjNode])
            {
                minDistance[adjNode] = dis + weight;
                pq.push({minDistance[adjNode], adjNode});
            }
        }
    }
    int ans = *max_element(minDistance.begin() + 1, minDistance.end());
    return ans == 1e9 ? -1 : ans;
}




vector<int> dijkstra_with_parent(vector<vector<int>> &times, int n, int source)
{
    vector<vector<pair<int, int>>> edges(n, vector<pair<int, int>>());
    int inf = 1e9;

    for (int i = 0; i < times.size(); i++)
    {
        int u = times[i][0], v = times[i][1], weight = times[i][2];

        edges[u].push_back({v, weight});
        edges[v].push_back({u, weight});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // vector<int> parent(n, -1);
    vector<int> minDistance(n, inf);

    pq.push({0, source});

    while (!pq.empty())
    {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // if (node == destination)
        // continue;

        for (auto it : edges[node])
        {
            int child = it.first, weight = it.second;

            if (minDistance[node] + weight < minDistance[child])
            {
                minDistance[child] = minDistance[node] + weight;
                // parent[child] = node;
                pq.push({minDistance[node] + weight, child});
            }
        }
    }
    return minDistance;
}