# Social Network Graph Representation — Assignment

## Problem Statement

Consider the social network with the following connections:

- A–B
- A–C
- B–D
- B–E
- C–F
- E–F

The assignment covers:

1. Implementation using an **Adjacency Matrix** and an **Adjacency List**.
2. BFS and DFS traversal starting from vertex **A**.
3. Searching for a specified vertex using both representations and recording the operations required.
4. Comparison of the representations based on space, traversal, edge checking, and time complexity.
5. Identifying the more appropriate representation for a **sparse social network** using execution results.

## Project Structure

```text
social-network-graph-assignment/
├── README.md
├── .gitignore
├── sample_output.txt
├── src/
│   └── social_network.c
└── docs/
    └── analysis.md
```

## Graph Used

The graph is undirected:

```text
        A
       / \
      B   C
     / \   \
    D   E---F
```

Vertices: **V = 6**

Edges: **E = 6**

Since the graph is undirected, each edge is represented twice in an adjacency list.

## Adjacency Matrix

Using vertex order `A B C D E F`:

```text
    A B C D E F
A | 0 1 1 0 0 0
B | 1 0 0 1 1 0
C | 1 0 0 0 0 1
D | 0 1 0 0 0 0
E | 0 1 0 0 0 1
F | 0 0 1 0 1 0
```

The matrix contains `6 × 6 = 36` cells.

## Adjacency List

The program preserves the edge-insertion order:

```text
A -> B -> C
B -> A -> D -> E
C -> A -> F
D -> B
E -> B -> F
F -> C -> E
```

There are 6 list heads and 12 adjacency nodes for the 6 undirected edges.

## BFS from A

Traversal order using both representations:

```text
A B C D E F
```

The order is the same because both representations use the same vertex order and neighbor insertion order.

### Execution observations

- Matrix BFS checks every possible neighbor cell.
- List BFS inspects only actual adjacency nodes.

For this graph:

```text
Matrix BFS neighbor-cell checks = 36
Adjacency-list BFS neighbor-node inspections = 12
```

## DFS from A

Traversal order produced by the program:

```text
A B D E F C
```

Again, both representations use the same neighbor order, so the DFS order is the same in this experiment.

## Vertex Search Experiment

The program searches for vertex **F**.

The vertex labels are stored in the common order:

```text
A B C D E F
```

A sequential search therefore requires:

```text
A → B → C → D → E → F
```

So the execution records **6 label comparisons** for both representations in the worst-case target position used here.

> Note: This experiment measures locating a vertex label, not checking whether an edge exists. Vertex-label lookup can be made faster in a real system with a hash table or direct index mapping; that is outside this assignment's representation comparison.

## Edge Checking Experiment

The program also checks whether the edge **B–E** exists.

### Matrix

One matrix cell is inspected:

```text
matrix[B][E]
```

Therefore the edge check is **O(1)**.

### Adjacency List

The list for `B` is scanned:

```text
B -> A -> D -> E
```

Three adjacency nodes are inspected before finding `E`.

Therefore this particular execution uses **3 adjacency-node inspections**, and the general complexity is **O(deg(B))**, with worst case **O(V)**.

## Comparison

| Feature | Adjacency Matrix | Adjacency List |
|---|---|---|
| Space | O(V²) | O(V + E) |
| Graph storage for this case | 36 cells | 6 heads + 12 adjacency nodes |
| BFS | O(V²) | O(V + E) |
| DFS | O(V²) | O(V + E) |
| Vertex-label search in this implementation | O(V) | O(V) |
| Edge existence check | O(1) | O(deg(u)), worst O(V) |
| Best suited for | Dense graphs / frequent edge checks | Sparse graphs |

## Time Complexity Analysis

Let:

- `V` = number of vertices
- `E` = number of edges

### Adjacency Matrix

The matrix stores all possible vertex pairs, so traversal scans `V` possible neighbors for every visited vertex.

```text
BFS = O(V²)
DFS = O(V²)
Space = O(V²)
Edge check = O(1)
```

### Adjacency List

The list stores only existing edges.

```text
BFS = O(V + E)
DFS = O(V + E)
Space = O(V + E)
Edge check = O(deg(u))   // worst case O(V)
```

## Result and Justification

For a **sparse social network**, an adjacency list is generally more space-efficient because it stores only existing connections rather than all possible vertex pairs.

The execution results also show the difference clearly for this graph:

- Matrix BFS inspected **36** possible neighbor cells.
- List BFS inspected **12** actual adjacency nodes.

Thus, for sparse graphs where `E` is much smaller than `V²`, the adjacency-list representation provides a more compact storage model and traversal work proportional to the existing connections.

The adjacency matrix remains useful when the application frequently asks whether a particular edge exists and constant-time edge checking is important.

## How to Compile and Run

### GCC

From the project root:

```bash
gcc src/social_network.c -o social_network
./social_network
```

### Windows MinGW

```powershell
gcc src/social_network.c -o social_network.exe
.\social_network.exe
```

## Expected Output

See [`sample_output.txt`](sample_output.txt).

## Learning Outcome

This project demonstrates how the same social-network graph can be represented in two different ways and how the representation affects:

- memory usage,
- BFS/DFS traversal work,
- vertex searching,
- edge checking,
- and overall time complexity.

## Submission

Upload this folder as a GitHub repository and submit the repository URL in the assignment portal.
