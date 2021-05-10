## DSA Mini project - Group 10

### General idea

 Declare a struct person array, consisting of a vector of pairs(defined by us) of people he/she meets and the day they meet, current station, current status, and the day he/she tested positive (If applicable. By default, would be initialised to -1).

 If a person in the meet array has a meet date that is > 14 days before the current day, that entry will be deleted, as that person's status will not change.

 Update status, station and meet vector depending on the day and data given.

 Maintain stations as a graph (Mainly for q2, to calculate the safety values (take top three) and implement Dijkstra to find shortest path).

 Indexing starts from zero (for the person indices) (info for the user giving the inputs).

### Q1 specific 

List L has people who TESTED positive on that day D.

We have to check the primary and secondary contacts of that person for the past X days.

People on list L have no MOVEMENT from their station for 14 days. (They stay in their current station, i.e. where they tested positive). (In q2, run a check : If the person asked to travel is currently quarantined, display an error message.)

 In list L for task 1, we need

- The day D

- X value (Number of days we need to look back for)

- Number of people who tested positive on that day

- Indices of the people who tested positive

We are considering the people who tested positive to become negative after 14 days of quarantine. The primary and secondary contacts, on the other hand, will remain as they are, because they could be asymptomatic carriers.

In task 1, while we're printing all the primary contacts and their respective secondary contacts of the list L one by one, there's a possibility of clashes:

For example, let's say, people 1, 2 and 3 are at the same station, and 1 tested positive. Then, for the primary contact 2, 3 is a secondary contact, and for the primary contact 3, 2 is a secondary contact. In this case, our code will output the same, but at the end, it'll update the status of both 2 and 3 as primary contacts.

### Q2 specific

 We will use the danger values as weights for the edges to find the safest paths using Dijkstra's algorithm.

 The first run will give us the safest path, for the second run, we remove the HEAVIEST edge in path 1 (which is the most dangerous) and run dijkstra again.

 This continues, till we find 3 paths (if exists).

 We are using directed edges between stations to account for the different danger values. For example, an edge FROM A TO B has the danger value of B as a weight, and FROM B TO A has the danger value of A as the weight.

 Once we find the three safest paths, we calculate their distances and rank them accordingly (Highest safety first, in case of same safety, sort by distance).

 We then take input for the user's choice, 0 for not going, 1 for path 1, 2 for path 2 (If exists) and so on.

 We update the person's status and current station accordingly. We also keep adding the people he meets on the way to the meet vector. His/her previous station struct and all the stations he/she encounters on his/her chosen path will also be updated (because the danger value and number of residents will change as well). (The stations on the path will only have to be updated if the person is a primary contact, all other cases will not make a difference).

### Q3 specific

 We will create a menu driven code for this, which accepts a person's index and the query, and fucntions accordingly



### Q3 p1 (status)
input format: 
    int DAY , int INDEX  
Output format: 
    string representing the status of the person of index "INDEX" on day "DAY"

Note: DAY should not be less than the status alloted day

### Pseudocode p1
```c++
 access index of that person, in array
 cout<<status<<;
```
### Q3 p2 (location)
Input format: 
The person's index

### Pseudocode p2
```c++
 access index of person
 cout<<cur_station;
```
### Q3 p3  (info regarding persons in a station)
Input format:
Day_number Station_number
Output format:
    List of the [positive , primaryContact , secondaryContact , Negative] persons in the station "STATION_NUM"  in order 

NOTE: DAY should not be less than the status alloted day

### Pseudocode p3
```c++
person* list;
 for(in person array)
 {
    if(in the station)
    {
        Add to list ;

    }
 }
    qsort ( list);
printf ( list ) ; 

 ```

 ### Running the program 

 A makefile has been included, so running the command

 ```
 make project
```
Compiles the entire code into an executable called project.

Now running 
```
./project
```
begins the execution.

The input format is specified by the prompts, sample graphs have been given in test.txt which has been included.

Only the files "maininput.c, Stations.c, dynamicheap.c, vec.c" and .h files are included.