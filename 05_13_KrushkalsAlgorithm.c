#include <stdio.h>
#include <stdlib.h>

#define V 5
#define E 7

struct Edge
{
    int src, dest, weight;
} edges[E] = {
    {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}, {1, 2, 25}, {3, 4, 2}};

int parent[V];

int find(int i)
{
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

void unionSet(int x, int y)
{
    parent[find(x)] = find(y);
}

int cmp(const void *a, const void *b)
{
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

void kruskal()
{
    int cost = 0;
    qsort(edges, E, sizeof(edges[0]), cmp);
    for (int i = 0; i < V; i++)
        parent[i] = i;

    printf("Edge \tWeight\n");
    for (int i = 0, e = 0; e < V - 1 && i < E; i++)
    {
        int u = edges[i].src, v = edges[i].dest;
        if (find(u) != find(v))
        {
            printf("%d - %d \t%d\n", u, v, edges[i].weight);
            cost += edges[i].weight;
            unionSet(u, v);
            e++;
        }
    }
    printf("Total cost: %d\n", cost);
}

int main()
{
    kruskal();
    return 0;
}
