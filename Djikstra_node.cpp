#include <bits/stdc++.h>
using namespace std;

vector<int> djikstra(vector<vector<int>> &adj, int n, int k)
{
    vector<vector<pair<int, int>>> edges(n + 1, vector<pair<int, int>>());

    for (int i = 0; i < adj.size(); i++)
    {
        int u, v, weight;

        u = adj[i][0], v = adj[i][1], weight = adj[i][2];

        edges[u].push_back({v, weight});
        edges[v].push_back({u, weight});
    }

    int inf = 1e9;                   
    int source = 1, destination = n; //

    priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;
    vector<int> minDistance(n + 1, inf);

    pq.push({0, source});
    minDistance[source] = 0;

    while (!pq.empty())
    {
        int dis, curr;
        tie(dis, curr) = pq.top();
        pq.pop();

        // if (curr == destination)
        // continue;

        if (minDistance[curr] < dis)
            continue;

        for (auto it : edges[curr])
        {
            int child = it.first, weight = it.second;
            if (dis + weight < minDistance[child])
            {
                minDistance[child] = dis + weight;
                pq.push({minDistance[child], child});
            }
        }
    }
    return minDistance;
}



vector<int> dijkstra_with_parent(vector<vector<int>> &times, int n, int source)
{
    vector<vector<pair<int, int>>> edges(n, vector<pair<int, int>>());

    for (int i = 0; i < times.size(); i++)
    {
        int u, v, weight;
        u = times[i][0], v = times[i][1], weight = times[i][2];

        edges[u].push_back({v, weight});
        edges[v].push_back({u, weight});
    }

    int inf = 1e9;                   // 
    int source = 1, destination = n; //

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // vector<int> parent(n, -1);
    vector<int> minDistance(n, inf);

    pq.push({0, source});

    while (!pq.empty())
    {
        int dis = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        // if (curr == destination)
        // continue;

        for (auto it : edges[curr])
        {
            int child = it.first, weight = it.second;

            if (minDistance[curr] + weight < minDistance[child])
            {
                minDistance[child] = minDistance[curr] + weight;
                // parent[child] = curr;
                pq.push({minDistance[curr] + weight, child});
            }
        }
    }
    //return minDistance[destination] == inf ? -1 : minDistance[destination];
    return minDistance;
}


// 0 indexing
vector<int> djikstra(int source, vector<vector<pair<int, int>>> &edges, int n)
{
    int inf = 1e18;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> minDistance(n, inf);

    pq.push({0, source});
    minDistance[source] = 0;

    while (!pq.empty())
    {
        int dis = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if (minDistance[curr] < dis)
            continue;

        for (auto it : edges[curr])
        {
            int child = it.first, weight = it.second;

            if (minDistance[curr] + weight < minDistance[child])
            {
                minDistance[child] = minDistance[curr] + weight;
                pq.push({minDistance[curr] + weight, child});
            }
        }
    }
    return minDistance;
}