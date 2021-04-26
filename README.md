### DSA Mini project - Group 10

## General idea

# Declare a struct person array, consisting of a vector of pairs(defined by us) of people he/she meets and the day they meet, current station, current status.

# If a person in the meet array has a meet date that is > 14 days before the current day, that entry will be dleted, as that person's status will not change.

# Update status, station and meet vector depending on the day and data given.

# Maintain stations as a graph (Mainly for q2, to calculate the safety values (take top three) and implement Dijkstra to find shortest path).

## Q1 specific 

# List L has people who TESTED positive on that day D.

# We have to check the primary and secondary contacts of that person for the past X days.

# People on list L have no MOVEMENT from their station for 14 days. (They stay in their current station, i.e. where they tested positive).

# In list L for task 1, we need

- The day D

- X value (Number of days we need to look back for)

- Number of people who tested positive on that day

- Indices of the people who tested positive

# We are considering the people who tested positive to become negative after 14 days of quarantine. The primary and secondary contacts, on the other hand, will remain as they are, because they could be asymptomatic carriers.

## Q2 specific

# We will use the danger values as weights for the edges to find the safest paths using Dijkstra's algorithm.

# The first run will give us the safest path, for the second run, we remove the HEAVIEST edge in path 1 (which is the most dangerous) and run dijkstra again.

# This continues, till we find 3 paths (if exists).

# We are using directed edges between stations to account for the different danger values. For example, an edge FROM A TO B has the danger value of B as a weight, and FROM B TO A has the danger value of A as the weight.

# Once we find the three safest paths, we calculate their distances and rank them accordingly (Highest safety first, in case of same safety, sort by distance).

# We then take input for the user's choice, 0 for not going, 1 for path 1, 2 for path 2 (If exists) and so on.

# We update the person's status and current station accordingly. We also keep adding the people he meets on the way to the meet vector. His/her previous station struct and all the stations he/she encounters on his/her chosen path will also be updated (because the danger value and number of residents will change as well). (The stations on the path will only have to be updated if the person is a primary contact, all other cases will not make a difference).

## Q3 specific

# We will create a menu driven code for this, which accepts a person's index and the query, and fucntions accordingly

## q3 p1 (status)

## Pseudocode p1

# access index of that person, in array
# cout<<status<<;

# q3 p2

## Pseudocode p2

# access index of person
# cout<<cur_station;

# q3 p3

## Pseudocode p3

# for(in person array)
# {
#    if(in the station)
#    {
#        if(stat == 1/2(primary/secondary))
#        {
#            cout<<that guy/girl;
#        }
#        else
#            continue;
#    }
# }