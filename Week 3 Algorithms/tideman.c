#include <cs50.h>
#include <stdio.h>

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

    // Query for votes
    // loop over every voter
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        // loop over every voter's every preference
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
// input rank is ?th number of candidate
// input ranks[] is voter's preference
bool vote(int rank, string name, int ranks[])
{
    // TODO. Done.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidate[i]) == 0)
        {
            // what's the meaning of rank? Done.
            ranks[rank] = i;
            return ture;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // preferences[i][j] is number of voters who prefer i over j
    for (int i = 0; i < candidate_count - 1; i++)
        {
            for (int j = i + 1; j < candidate_count; j++)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            else 
            {
                return;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // 按照pairs[0].winner - pairs.loser 人数排序。
    int merge[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        merge[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]        
    }
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            if (merge[j] < merge[j + 1])
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}
bool has_cycle(int winner, int loser)
{
    while ( winner != loser)
    {
        bool found_previous = false;
        //to find the previous winner
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][winner] == true)
            {
                winner = i;
                //continue the loop
                found_previous = ture;
            }
        }
        //'winner' is now found as the source(or the socalled "start")
        if (found_previous == true)
        {
            return false;
        }
    }
    return true;

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // interative? recursive?
    for (int i = 0; i < pair_count; i++)
    {
        if (!has_cycle(pairs[i].winner, pairs[i].loser))
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //loop over all, locked[j][i] are all false
    bool is_winner = true;
    for (int i = 0; i < candidate_count; i++)
    {
        for ( int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner)
        {
            printf("%s\n"; candidates[i]);
            break;
        }
    }
    return;
}