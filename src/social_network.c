#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V 6
#define MAX_QUEUE 100

const char vertices[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

/* Convert a vertex label to its array index. */
int indexOf(char label) {
    for (int i = 0; i < V; i++) {
        if (vertices[i] == label)
            return i;
    }
    return -1;
}

/* Add an undirected edge to the adjacency matrix. */
void addMatrixEdge(int matrix[V][V], char a, char b) {
    int u = indexOf(a);
    int v = indexOf(b);
    matrix[u][v] = 1;
    matrix[v][u] = 1;
}

/* Add an undirected edge to the adjacency list. */
void addListEdge(Node *list[V], char a, char b) {
    int u = indexOf(a);
    int v = indexOf(b);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;

    if (list[u] == NULL) {
        list[u] = newNode;
    } else {
        Node *temp = list[u];
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void printMatrix(int matrix[V][V]) {
    printf("\n--- Adjacency Matrix ---\n");
    printf("    ");
    for (int i = 0; i < V; i++)
        printf("%c ", vertices[i]);
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%c | ", vertices[i]);
        for (int j = 0; j < V; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void printList(Node *list[V]) {
    printf("\n--- Adjacency List ---\n");
    for (int i = 0; i < V; i++) {
        printf("%c -> ", vertices[i]);
        Node *temp = list[i];
        while (temp != NULL) {
            printf("%c", vertices[temp->vertex]);
            if (temp->next != NULL)
                printf(" -> ");
            temp = temp->next;
        }
        printf("\n");
    }
}

/* BFS using adjacency matrix. Returns number of matrix cell checks. */
void bfsMatrix(int matrix[V][V], char start) {
    int startIndex = indexOf(start);
    if (startIndex == -1) {
        printf("Invalid start vertex.\n");
        return;
    }

    int visited[V] = {0};
    int queue[MAX_QUEUE];
    int front = 0, rear = 0;
    long long checks = 0;

    visited[startIndex] = 1;
    queue[rear++] = startIndex;

    printf("\nBFS using Adjacency Matrix: ");

    while (front < rear) {
        int u = queue[front++];
        printf("%c ", vertices[u]);

        for (int v = 0; v < V; v++) {
            checks++;
            if (matrix[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }

    printf("\nMatrix neighbor-cell checks during BFS: %lld\n", checks);
}

/* BFS using adjacency list. Returns number of adjacency nodes inspected. */
void bfsList(Node *list[V], char start) {
    int startIndex = indexOf(start);
    if (startIndex == -1) {
        printf("Invalid start vertex.\n");
        return;
    }

    int visited[V] = {0};
    int queue[MAX_QUEUE];
    int front = 0, rear = 0;
    long long checks = 0;

    visited[startIndex] = 1;
    queue[rear++] = startIndex;

    printf("\nBFS using Adjacency List: ");

    while (front < rear) {
        int u = queue[front++];
        printf("%c ", vertices[u]);

        Node *temp = list[u];
        while (temp != NULL) {
            checks++;
            int v = temp->vertex;
            if (!visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }

    printf("\nList neighbor-node inspections during BFS: %lld\n", checks);
}

/* DFS using adjacency matrix. */
void dfsMatrixRecursive(int matrix[V][V], int u, int visited[V]) {
    visited[u] = 1;
    printf("%c ", vertices[u]);

    for (int v = 0; v < V; v++) {
        if (matrix[u][v] && !visited[v])
            dfsMatrixRecursive(matrix, v, visited);
    }
}

void dfsMatrix(int matrix[V][V], char start) {
    int startIndex = indexOf(start);
    int visited[V] = {0};

    if (startIndex == -1) {
        printf("Invalid start vertex.\n");
        return;
    }

    printf("\nDFS using Adjacency Matrix: ");
    dfsMatrixRecursive(matrix, startIndex, visited);
    printf("\n");
}

/* DFS using adjacency list. */
void dfsListRecursive(Node *list[V], int u, int visited[V]) {
    visited[u] = 1;
    printf("%c ", vertices[u]);

    Node *temp = list[u];
    while (temp != NULL) {
        int v = temp->vertex;
        if (!visited[v])
            dfsListRecursive(list, v, visited);
        temp = temp->next;
    }
}

void dfsList(Node *list[V], char start) {
    int startIndex = indexOf(start);
    int visited[V] = {0};

    if (startIndex == -1) {
        printf("Invalid start vertex.\n");
        return;
    }

    printf("\nDFS using Adjacency List: ");
    dfsListRecursive(list, startIndex, visited);
    printf("\n");
}

/* Search for a vertex label by scanning the vertex-header representation.
   Returns the number of label comparisons. */
int searchVertexMatrix(const char labels[V], char target) {
    int operations = 0;

    for (int i = 0; i < V; i++) {
        operations++;
        if (labels[i] == target) {
            printf("\nMatrix representation search: Vertex %c found at index %d.\n",
                   target, i);
            printf("Label comparisons required: %d\n", operations);
            return operations;
        }
    }

    printf("\nMatrix representation search: Vertex %c not found.\n", target);
    printf("Label comparisons required: %d\n", operations);
    return operations;
}

int searchVertexList(Node *list[V], const char labels[V], char target) {
    int operations = 0;

    for (int i = 0; i < V; i++) {
        operations++;
        if (labels[i] == target) {
            printf("\nAdjacency list search: Vertex %c found at list header %d.\n",
                   target, i);
            printf("Header-label comparisons required: %d\n", operations);
            return operations;
        }
    }

    printf("\nAdjacency list search: Vertex %c not found.\n", target);
    printf("Header-label comparisons required: %d\n", operations);
    return operations;
}

/* Check whether an edge exists. Matrix: one cell access. List: scan degree(u). */
void checkEdgeMatrix(int matrix[V][V], char a, char b) {
    int u = indexOf(a);
    int v = indexOf(b);

    if (u == -1 || v == -1) {
        printf("\nInvalid vertex label in matrix edge check.\n");
        return;
    }

    printf("\nMatrix edge check %c-%c: %s (1 matrix-cell access)\n",
           a, b, matrix[u][v] ? "Edge exists" : "Edge does not exist");
}

void checkEdgeList(Node *list[V], char a, char b) {
    int u = indexOf(a);
    int v = indexOf(b);

    if (u == -1 || v == -1) {
        printf("\nInvalid vertex label in list edge check.\n");
        return;
    }

    int operations = 0;
    Node *temp = list[u];
    while (temp != NULL) {
        operations++;
        if (temp->vertex == v) {
            printf("\nList edge check %c-%c: Edge exists (%d adjacency-node inspections)\n",
                   a, b, operations);
            return;
        }
        temp = temp->next;
    }

    printf("\nList edge check %c-%c: Edge does not exist (%d adjacency-node inspections)\n",
           a, b, operations);
}

void freeList(Node *list[V]) {
    for (int i = 0; i < V; i++) {
        Node *temp = list[i];
        while (temp != NULL) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
}

int main(void) {
    int matrix[V][V] = {0};
    Node *list[V] = {NULL};

    /*
       Given undirected social-network connections:
       A-B, A-C, B-D, B-E, C-F, E-F
    */
    const char edges[][2] = {
        {'A', 'B'},
        {'A', 'C'},
        {'B', 'D'},
        {'B', 'E'},
        {'C', 'F'},
        {'E', 'F'}
    };

    int edgeCount = sizeof(edges) / sizeof(edges[0]);

    for (int i = 0; i < edgeCount; i++) {
        addMatrixEdge(matrix, edges[i][0], edges[i][1]);
        addListEdge(list, edges[i][0], edges[i][1]);
        addListEdge(list, edges[i][1], edges[i][0]);
    }

    printf("SOCIAL NETWORK GRAPH REPRESENTATION\n");
    printf("Vertices: A B C D E F\n");
    printf("Edges: A-B, A-C, B-D, B-E, C-F, E-F\n");

    printMatrix(matrix);
    printList(list);

    bfsMatrix(matrix, 'A');
    bfsList(list, 'A');

    dfsMatrix(matrix, 'A');
    dfsList(list, 'A');

    /*
       For the assignment experiment, search for vertex F.
       The function works for any single-character vertex label.
    */
    char target = 'F';
    searchVertexMatrix(vertices, target);
    searchVertexList(list, vertices, target);

    /* Edge-checking experiment using the existing edge B-E. */
    checkEdgeMatrix(matrix, 'B', 'E');
    checkEdgeList(list, 'B', 'E');

    printf("\n--- Complexity Summary ---\n");
    printf("Adjacency Matrix space: O(V^2)\n");
    printf("Adjacency List space:   O(V + E)\n");
    printf("BFS/DFS with Matrix:    O(V^2)\n");
    printf("BFS/DFS with List:      O(V + E)\n");
    printf("Vertex-label search:    O(V) in this implementation for both\n");
    printf("Edge check Matrix:      O(1)\n");
    printf("Edge check List:        O(deg(u)), worst case O(V)\n");

    freeList(list);
    return 0;
}
