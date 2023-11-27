#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX 100

typedef struct node {
    int vertex;
    struct node* next;
} node;

node* createNode(int);
node* addEdge(node* list, int);
void bridgeUtil(int, int visited[], int disc[], int low[], int parent[]);
void bridge();
void isBridge(int, int);

node* adj[MAX];
int vertices;

int main() {
    int i, src, dest;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    for (i = 0; i < vertices; i++)
        adj[i] = NULL;

        while (1) {
            printf("Enter edges (src dest) or (-1 -1) to finish: ");
            scanf("%d %d", &src, &dest);
            if (src == -1 && dest == -1)
                break;
            adj[src] = addEdge(adj[src], dest);
            adj[dest] = addEdge(adj[dest], src);
        }

    bridge();

    printf("\nEnter a specific edge (src dest) to check: ");
    scanf("%d %d", &src, &dest);
    isBridge(src, dest);

    return 0;
}

node* createNode(int v) {
    node* newNode = malloc(sizeof(node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

node* addEdge(node* list, int v) {
    node* newNode = createNode(v);
    newNode->next = list;
    return newNode;
}

void bridgeUtil(int u, int visited[], int disc[], int low[], int parent[]) {
    static int time = 0;
    int children = 0;
    node* p;
    visited[u] = 1;
    disc[u] = low[u] = ++time;

    for (p = adj[u]; p; p = p->next) {
        int v = p->vertex;
        if (!visited[v]) {
            children++;
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            if (low[v] > disc[u])
                printf("%d %d is a bridge", u, v);
        }
        else if (v != parent[u])
                    low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
    }
}

void bridge() {
    int i, visited[MAX] = { 0 }, disc[MAX], low[MAX], parent[MAX];
    for (i = 0; i < vertices; i++)
        parent[i] = -1;
    for (i = 0; i < vertices; i++)
        if (!visited[i])
            bridgeUtil(i, visited, disc, low, parent);
}

void isBridge(int src, int dest) {
    int i, visited[MAX] = { 0 }, disc[MAX], low[MAX], parent[MAX];
    for (i = 0; i < vertices; i++)
        parent[i] = -1;
    bridgeUtil(src, visited, disc, low, parent);
    if (low[dest] > disc[src])
        printf("%d %d is a bridge", src, dest);
    else
            printf("%d %d is not a bridge", src, dest);
}
