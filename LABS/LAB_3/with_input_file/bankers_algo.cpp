#include <bits/stdc++.h>

using namespace std;

const int MAX_P = 10;
const int MAX_R = 10;

int P, R;
int allocation[MAX_P][MAX_R], maxRes[MAX_P][MAX_R], need[MAX_P][MAX_R], available[MAX_R];

bool canAllocate(int process, int available[])
{
    for (int j = 0; j < R; j++)
    {
        if (need[process][j] > available[j])
            return false;
    }
    return true;
}

bool isSafe()
{
    int work[MAX_R];
    bool finish[MAX_P] = {false};
    int safeSeq[MAX_P];

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P)
    {
        bool found = false;

        for (int i = 0; i < P; i++)
        {
            if (!finish[i] && canAllocate(i, work))
            {
                // Allocate resources
                for (int j = 0; j < R; j++)
                    work[j] += allocation[i][j];

                safeSeq[count++] = i;
                finish[i] = true;
                found = true;
            }
        }

        if (!found)
        {
            cout << "System is in an UNSAFE state!" << endl;
            return false;
        }
    }

    cout << "System is in a SAFE state." << endl;
    cout << "Safe Sequence: ";
    for (int i = 0; i < P; i++)
        cout << "T" << safeSeq[i] << " ";
    cout << endl;
    return true;
}

// Function to read input from a file
void readInputFromFile(string filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    // Read P (Processes) and R (Resources)
    infile >> P >> R;

    // Read Available resources
    for (int i = 0; i < R; i++)
        infile >> available[i];

    // Read Allocation and Max matrices
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
            infile >> allocation[i][j];
        for (int j = 0; j < R; j++)
            infile >> maxRes[i][j];
    }

    infile.close();

    // Compute Need matrix: Need = Max - Allocation
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxRes[i][j] - allocation[i][j];
}

int main()
{
    // Read input from file
    readInputFromFile("input.txt");

    // Run the safety algorithm
    isSafe();

    return 0;
}
