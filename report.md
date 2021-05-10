# The Report for the DSA mini project

--------------------------------------------------------

## 1) The Data structures used are as follows:

- Priority queue (Minheap)  : for Dijkstra
- Dynamic array (Vector)    : for all kinds of adjacency lists 
- Structures (Coder defined) 
- Graphs (Using above structures) : used for storing info regarding stations 

--------------------------------------------------------

## 2) Algorithms used and their complexity are as follows:

- Task-1 -> O(n^3) (Because First iterating through positive people, then their meet list to find primary contacts, and then their corresponding meet lists to find secondary contacts)
- Dijkstra's algorithm -> O(E logV)
- Calculating length of path -> O(n^2)
- Calculating danger value -> O(1)
- Task-3 query-1 (status) -> O(1)
- Task-3 query-2 (Current station) -> O(1)
- Task-3 query-3 (List of primary and secondary contacts) -> O(n)

--------------------------------------------------------

## 3) Division of work:

- Lakshmanan  --> coded  dynamicheaps , vectors , maintaining git repo
- Radheshyam  --> coded stations ADT and implementations , Dijkstra for task2
- Pranjal     --> coded task1 , code for taking inputs for connections between stations
- Sree Harsha --> coded task3 , modified task1 
- Romaharshan --> coded task3 , code for taking inputs 


NOTE: And everyone contributed in debugging together, we were in VC

Link to the repo: 
```
https://github.com/KarthikL1729/Group_10_DSA_project.git
```
--------------------------------------------------------