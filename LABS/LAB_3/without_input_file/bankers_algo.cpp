#include <iostream>

using namespace std;

const int P = 5; // Number of processes
const int R = 3; // Number of resource types

// Function to check if a process can be allocated resources
bool canAllocate(int process, int need[P][R], int available[R])
{
    for (int j = 0; j < R; j++)
    {
        if (need[process][j] > available[j])
            return false;
    }
    return true;
}

// Function to implement the safety algorithm
bool isSafe(int allocation[P][R], int max[P][R], int available[R])
{
    int need[P][R], safeSeq[P], work[R];
    bool finish[P] = {false};

    // Calculate the Need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Copy available resources to work array
    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P)
    {
        bool found = false;

        for (int i = 0; i < P; i++)
        {
            if (!finish[i] && canAllocate(i, need, work))
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

    // Print the Safe Sequence
    cout << "System is in a SAFE state." << endl;
    cout << "Safe Sequence: ";
    for (int i = 0; i < P; i++)
        cout << "T" << safeSeq[i] << " ";
    cout << endl;
    return true;
}

int main()
{
    int allocation[P][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[P][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int available[R] = {3, 3, 2};

    isSafe(allocation, max, available);
    return 0;
}
