#include <stdio.h>
#define V 6

int graph[V][V] = {
    {0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}};

int visited[V], entry[V], finish[V], time = 0;

void dfs(int u)
{
    visited[u] = 1;
    entry[u] = ++time;

    for (int v = 0; v < V; v++)
    {
        if (graph[u][v])
        {
            if (!visited[v])
            {
                printf("Tree Edge: %d -> %d\n", u, v);
                dfs(v);
            }
            else if (!finish[v])
            {
                printf("Back Edge: %d -> %d\n", u, v);
            }
            else if (entry[u] < entry[v])
            {
                printf("Forward Edge: %d -> %d\n", u, v);
            }
            else
            {
                printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    finish[u] = ++time;
}

void classifyEdges()
{
    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfs(i);
}

int main()
{
    classifyEdges();
    return 0;
}
