#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool can_lock(int winner, int loser);

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

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

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

        record_preferences(ranks);

        printf("\n");
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int f_preference = ranks[i];

        for (int j = i + 1; j < candidate_count; j++)
        {
            int s_preference = ranks[j];
            preferences[f_preference][s_preference]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other,
// by getting all the candidates and analyzing all of them against
// all of them
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            int winner;
            int loser;

            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    winner = i;
                    loser = j;
                }
                else
                {
                    winner = j;
                    loser = i;

                }

                pair created_pair;
                created_pair.winner = winner;
                created_pair.loser = loser;

                pairs[pair_count] = created_pair;
                pair_count++;
            }


        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory,
// using bubble sort algorithm
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++) 
    {
        int moves = 0;

        for (int j = (pair_count - 2); j > -1; j--)
        {
            pair f_pair = pairs[j];
            pair s_pair = pairs[j + 1];

            int f_pair_votes = preferences[f_pair.winner][f_pair.loser];
            int s_pair_votes = preferences[s_pair.winner][s_pair.loser];

            if (f_pair_votes < s_pair_votes)
            {
                pairs[j] = s_pair;
                pairs[j + 1] = f_pair;

                moves++;
            }
        }

        if (moves == 0)
        {
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        
        if (!can_lock(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;

    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            // if the candidate analyzed has one lock, it is not the winner
            if (locked[j][i])
            {
                count++;
                break;
            }
        }

        if (count == 0)
        {
            winner = i;
            break;
        }
    }

    printf("%s\n", candidates[winner]);
    return;
}

// checks if the graph can lock by analyzing all the locks
// that were done before the pretended lock
bool can_lock(int winner, int candidate_analyzed)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[candidate_analyzed][i])
        {
            if (i == winner)
            {
                return true;
            }
            
            if (can_lock(winner, i))
            {
                return true;
            }
        }
    }
    
    return false;
}