#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    // Array for all times and processes
    int burst_time[n], waiting_time[n], turnaround_time[n], start_time[n], end_time[n], process[n];
    double total_waiting_time = 0, total_turnaround_time = 0;

    // Input burst times and provide process IDs
    cout << "Enter the burst times for the processes:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> burst_time[i];
        process[i] = i + 1; // Assign process IDs
    }

    // Sorting processes by burst time (SJF Scheduling)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (burst_time[i] > burst_time[j])
            {
                swap(burst_time[i], burst_time[j]);
                swap(process[i], process[j]); // ID swapping
            }
        }
    }

    // Calculating Start Time, End Time, Waiting Time, and Turnaround Time
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            start_time[i] = 0; // First process starts at 0
        }
        else
        {
            start_time[i] = end_time[i - 1]; // Start after previous process ends
        }
        end_time[i] = start_time[i] + burst_time[i]; // Calculate end time for current process
        waiting_time[i] = start_time[i];             // Waiting time is equivalent to start time
        turnaround_time[i] = end_time[i];            // TAT = End time (since Arrival Time is 0)

        // Accumulate totals
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Display Results
    cout << fixed << setprecision(2);
    cout << "\nProcess\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << process[i] << "\t" << burst_time[i] << "\t\t" << start_time[i] << "\t\t" << end_time[i]
             << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "| P" << process[i] << " ";
    }
    cout << "|\n";
    for (int i = 0; i < n; i++)
    {
        cout << start_time[i] << "\t";
    }
    cout << end_time[n - 1] << endl;

    // Averages
    cout << "\nAverage Waiting Time: " << total_waiting_time / n;
    cout << "\nAverage Turnaround Time: " << total_turnaround_time / n << endl;

    return 0;
}
