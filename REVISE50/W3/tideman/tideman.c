#include <cs50.h>
#include <stdio.h>
#include <string.h> // for strcmp

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes for each voter i
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        // declaring a 1D matrix of preference, which vote will populate based on string input
        int ranks[candidate_count];
        // ranks contains the ranked candidates by index
        // ranks array is created and destroyed per loop?

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        //for each voter i, update global array from ranked


        //PRINTCHECK ranks
        for (int r = 0; r < candidate_count; r++)
        {
            printf("Rank %i:%i\n", r ,ranks[r]);
        }

        record_preferences(ranks);

        //PRINTCHECK preferences
        for (int x = 0; x < candidate_count; x++)
        {
            for (int y = 0; y < candidate_count; y++)
            {
                printf("|%i", preferences[x][y]);
            }
            printf("|\n");
        }
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //checks user input of name against global candidates array, and update the vote index's particular ranked list for the rank j
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name,candidates[i])) //strcmp returns zero if match
        {
            ranks[rank] = i; //rank contains int of candidate IDs i.e. i = 0  is the first candidate
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
// Assume that every voter will rank each of the candidates.
void record_preferences(int ranks[])
{
    for(int r = 0; r < candidate_count; r++)
    {
        for (int c = r + 1; c < candidate_count; c++)
        {
            // if (r == c) not required, since c will lead r (i.e. preferred candidate already avaluated)
            preferences[ranks[c]][ranks[r]]++; //[i][j] = [c][r], where r is the higher ranked candidate over c (further right of r)
            //note that i is row index and j is column index?
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
/*
typedef struct
{
    int winner;
    int loser;
}
*/
    int p = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > 0) //for i = j, will always be 0
            {
                pairs[p].winner = i;
                pairs[p].loser = j;
                p++; //is it best practice to keep the loop counter seperate?
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max_pair;
    for (int p = 0; p < pair_count; p++)
    {
        //PRINTCHECK pairs
        printf("--Pair Array--\n");
        for (int i = 0; i < pair_count; i++)
        {
            printf("Win:%i Lose:%i Margin:%i\n ", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
        }

        max_pair = 0;
        for (int m = p ; m < pair_count; m++)
        {
            if(preferences[pairs[m].winner][pairs[m].loser] > max_pair)
            {
                //If multiple pairs have the same strength of victory, you may assume that the order does not matter.
                max_pair = m;
            }
        }
        pair temp = {.winner = 0, .loser = 0}; //note, pair is a typedef struct, rather than explicit struct
        temp.winner = pairs[p].winner;
        temp.loser = pairs[p].loser;

        pairs[p].winner = pairs[max_pair].winner;
        pairs[p].loser = pairs[max_pair].loser;

        pairs[max_pair].winner = temp.winner;
        pairs[max_pair].loser = temp.loser;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i; j >= 0; j--)
        {

            if (pairs[i].winner == pairs[j].loser)
            {
                printf("Arrow from pair.winner %d -> pair.loser %d ", i, j);
            }

            if (pairs[j].loser == pairs[i].winner)
            {
                printf("Arrow from pair.loser %d -> pair.winner %d ", j, i);
            }
        }
        printf("Pair Locked: W:%d L:%d",pairs[i].winner, pairs[i].loser);
    }





    return;
}

// Print the winner of the election
// You may assume there will not be more than one source.
void print_winner(void)
{
    // TODO
    return;
}

/*
the Tideman voting method consists of three parts:

Tally: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
Sort: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.
Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.
Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner!


First, notice the two-dimensional array preferences. The integer preferences[i][j] will represent the number of voters who prefer candidate i over candidate j.

The file also defines another two-dimensional array, called locked, which will represent the candidate graph. locked is a boolean array, so locked[i][j] being true represents the existence of an edge pointing from candidate i to candidate j; false means there is no edge. (If curious, this representation of a graph is known as an “adjacency matrix”).

Next up is a struct called pair, used to represent a pair of candidates: each pair includes the winner’s candidate index and the loser’s candidate index.

The candidates themselves are stored in the array candidates, which is an array of strings representing the names of each of the candidates. There’s also an array of pairs, which will represent all of the pairs of candidates (for which one is preferred over the other) in the election.

The program also has two global variables: pair_count and candidate_count, representing the number of pairs and number of candidates in the arrays pairs and candidates, respectively.

Now onto main. Notice that after determining the number of candidates, the program loops through the locked graph and initially sets all of the values to false, which means our initial graph will have no edges in it.

Next, the program loops over all of the voters and collects their preferences in an array called ranks (via a call to vote), where ranks[i] is the index of the candidate who is the ith preference for the voter. These ranks are passed into the record_preference function, whose job it is to take those ranks and update the global preferences variable.

Once all of the votes are in, the pairs of candidates are added to the pairs array via a called to add_pairs, sorted via a call to sort_pairs, and locked into the graph via a call to lock_pairs. Finally, print_winner is called to print out the name of the election’s winner!


Complete the vote function.
The function takes arguments rank, name, and ranks. If name is a match for the name of a valid candidate, then you should update the ranks array to indicate that the voter has the candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.)
Recall that ranks[i] here represents the user’s ith preference.
The function should return true if the rank was successfully recorded, and false otherwise (if, for instance, name is not the name of one of the candidates).
You may assume that no two candidates will have the same name.
Complete the record_preferences function.
The function is called once for each voter, and takes as argument the ranks array, (recall that ranks[i] is the voter’s ith preference, where ranks[0] is the first preference).
The function should update the global preferences array to add the current voter’s preferences. Recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j.
You may assume that every voter will rank each of the candidates.
Complete the add_pairs function.
The function should add all pairs of candidates where one candidate is preferred to the pairs array. A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
The function should update the global variable pair_count to be the number of pairs of candidates. (The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).
Complete the sort_pairs function.
The function should sort the pairs array in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate. If multiple pairs have the same strength of victory, you may assume that the order does not matter.
Complete the lock_pairs function.
The function should create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.
Complete the print_winner function.
The function should print out the name of the candidate who is the source of the graph. You may assume there will not be more than one source.

Be sure to test your code to make sure it handles…

An election with any number of candidate (up to the MAX of 9)
Voting for a candidate by name
Invalid votes for candidates who are not on the ballot
Printing the winner of the election

*/
