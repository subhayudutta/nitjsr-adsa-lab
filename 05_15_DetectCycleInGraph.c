#include <stdio.h>
#define V 6
#define INF 9999

int graph[V][V] = {
    {0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}};

int visited[V], path[V], minCycle = INF, maxCycle = 0;

void dfs(int u, int depth)
{
    visited[u] = 1;
    path[u] = depth;

    for (int v = 0; v < V; v++)
    {
        if (graph[u][v])
        {
            if (!visited[v])
                dfs(v, depth + 1);
            else if (path[v])
            {
                int len = depth - path[v] + 1;
                if (len < minCycle)
                    minCycle = len;
                if (len > maxCycle)
                    maxCycle = len;
            }
        }
    }

    path[u] = 0;
    visited[u] = 0;
}

void findCycles()
{
    for (int i = 0; i < V; i++)
        dfs(i, 1);

    if (minCycle == INF)
        printf("No cycles found.\n");
    else
    {
        printf("Smallest cycle length: %d\n", minCycle);
        printf("Largest cycle length: %d\n", maxCycle);
    }
}

int main()
{
    findCycles();
    return 0;
}
