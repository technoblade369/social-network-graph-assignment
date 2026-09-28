# Analysis Details

## 1. Graph properties

The graph contains six vertices and six undirected edges.

\[
V = 6,\quad E = 6
\]

A complete undirected graph with six vertices would contain:

\[
E_{max} = \frac{V(V-1)}{2} = \frac{6(5)}{2}=15
\]

The given graph has only 6 of those 15 possible edges, so it is considerably less connected than a complete graph.

## 2. Storage comparison

### Matrix

The matrix requires:

\[
V^2 = 6^2 = 36
\]

entries.

### List

For an undirected graph, every edge occurs in two adjacency lists:

\[
V + 2E = 6 + 2(6)=18
\]

logical storage positions before counting pointer/object overhead.

The list therefore stores only information associated with actual connections.

## 3. Traversal comparison

For the supplied program execution:

| Operation | Matrix | List |
|---|---:|---:|
| BFS from A — neighbor inspections | 36 matrix cells | 12 adjacency nodes |
| DFS from A | Scans all V neighbor positions at each vertex | Scans only stored neighbors |
| BFS order | A B C D E F | A B C D E F |
| DFS order | A B D E F C | A B D E F C |

The orders match because the program uses the same vertex order and preserves the same neighbor order in the two representations.

## 4. Search comparison

The assignment's vertex-search operation locates the **label** `F`.

The labels are sequentially examined:

```text
A, B, C, D, E, F
```

This requires 6 comparisons for target `F`.

Both implementations therefore have:

\[
T_{search}=O(V)
\]

in this experiment.

This is different from edge checking. A graph representation does not automatically make arbitrary label lookup constant-time unless an additional indexing structure is provided.

## 5. Edge-checking comparison

For matrix:

\[
T_{edge}=O(1)
\]

because one matrix cell identifies whether the edge exists.

For list:

\[
T_{edge}=O(deg(u))
\]

because the adjacency list of the source vertex may need to be scanned.

In the execution, checking `B-E` inspects:

```text
B -> A
B -> D
B -> E
```

so 3 adjacency-node comparisons are performed.

## 6. Sparse-network conclusion

For sparse graphs:

\[
E \ll V^2
\]

The adjacency list usually avoids the large unused area present in a matrix and gives traversal complexity of:

\[
O(V+E)
\]

instead of:

\[
O(V^2)
\]

For a social network that has many users but relatively fewer connections than the number of all possible user pairs, this makes the adjacency-list representation appropriate from a storage and traversal perspective.

The matrix is still preferable for workloads dominated by repeated constant-time edge-existence queries.
