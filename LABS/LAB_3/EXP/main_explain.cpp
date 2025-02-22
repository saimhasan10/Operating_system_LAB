#include <bits/stdc++.h> // Include all standard libraries
using namespace std;

const int MAX_P = 10; // Max number of processes
const int MAX_R = 10; // Max number of resource types

int P, R; // Number of processes and resources
int allocation[MAX_P][MAX_R], maxRes[MAX_P][MAX_R], need[MAX_P][MAX_R], available[MAX_R];

// Function to check if a process can be allocated resources safely
bool canAllocate(int process, int available[])
{
    for (int j = 0; j < R; j++)
    {
        if (need[process][j] > available[j]) // If needed resources exceed available resources
            return false;                    // Process cannot execute now
    }
    return true; // Process can execute
}

// Function to check if the system is in a safe state
bool isSafe()
{
    int work[MAX_R];              // Work array to track available resources
    bool finish[MAX_P] = {false}; // Track if a process has finished
    int safeSeq[MAX_P];           // Store the safe sequence

    // Copy available resources to work array (temporary storage)
    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;    // Count of processes that have executed
    while (count < P) // Try to execute all processes
    {
        bool found = false; // Check if any process can execute in this iteration

        for (int i = 0; i < P; i++)
        {
            if (!finish[i] && canAllocate(i, work)) // If process can execute
            {
                // Allocate resources and update available (work)
                for (int j = 0; j < R; j++)
                    work[j] += allocation[i][j]; // Resources are released back after execution

                safeSeq[count++] = i; // Store process in safe sequence
                finish[i] = true;     // Mark process as finished
                found = true;
            }
        }

        if (!found) // If no process can execute, system is in an unsafe state
        {
            cout << "System is in an UNSAFE state!" << endl;
            return false;
        }
    }

    // Print the Safe Sequence if system is safe
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

    // Read number of processes (P) and resources (R)
    infile >> P >> R;

    // Read Available resources
    for (int i = 0; i < R; i++)
        infile >> available[i];

    // Read Allocation and Max matrices
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
            infile >> allocation[i][j]; // Read Allocation matrix
        for (int j = 0; j < R; j++)
            infile >> maxRes[i][j]; // Read Max matrix
    }

    infile.close(); // Close the file after reading

    // Compute Need matrix: Need = Max - Allocation
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxRes[i][j] - allocation[i][j];
}

int main()
{
    // Read input data from file
    readInputFromFile("input.txt");

    // Run the Banker's Algorithm to check system safety
    isSafe();

    return 0;
}
