#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int arrival_time[n], burst_time[n], remaining_time[n], start_time[n], end_time[n];
    int turnaround_time[n], waiting_time[n];
    double total_tat = 0, total_wt = 0;
    string process[n];

    cout << "Enter process details (Name ArrivalTime BurstTime):\n";
    for (int i = 0; i < n; i++)
    {
        cin >> process[i] >> arrival_time[i] >> burst_time[i];
        remaining_time[i] = burst_time[i];
        start_time[i] = -1; // -1 indicates that the process has not started yet
    }

    int current_time = 0, completed = 0;
    vector<string> gantt_chart; // Stores the sequence of process execution for the Gantt Chart.

    while (completed < n)
    {
        int shortest = -1, min_remaining = INT_MAX;

        // Find process with the shortest remaining time at the current time
        for (int i = 0; i < n; i++)
        {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0)
            {
                if (remaining_time[i] < min_remaining)
                {
                    min_remaining = remaining_time[i];
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            // No process is ready to execute; idle time
            gantt_chart.push_back("Idle");
            current_time++; // increasing the timestamp
            continue;
        }

        // Update start time if it's the first execution
        if (start_time[shortest] == -1)
        {
            start_time[shortest] = current_time;
        }

        // Execute the process for 1 unit of time
        gantt_chart.push_back(process[shortest]);
        remaining_time[shortest]--;
        current_time++;

        // If the process is completed
        if (remaining_time[shortest] == 0)
        {
            completed++;
            end_time[shortest] = current_time;
            turnaround_time[shortest] = end_time[shortest] - arrival_time[shortest];
            waiting_time[shortest] = turnaround_time[shortest] - burst_time[shortest];

            total_tat += turnaround_time[shortest];
            total_wt += waiting_time[shortest];
        }
    }

    // Print the outputs
    cout << "\nProcess\tArrival Time\tBurst Time\tStart Time\tEnd Time\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t"
             << start_time[i] << "\t\t" << end_time[i] << "\t\t"
             << turnaround_time[i] << "\t" << waiting_time[i] << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time: " << total_wt / n << endl;

    cout << "\nGantt Chart:\n";
    for (const string &p : gantt_chart)
    {
        cout << "| " << p << " ";
    }
    cout << "|\n";
    return 0;
}
