#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    if (!input_file)
    {
        cout << "Unable to open input file." << endl;
        return 1;
    }

    int n, time_quantum;
    input_file >> n >> time_quantum;

    string process[n];
    int burst_time[n], remaining_time[n], start_time[n], end_time[n];
    int turnaround_time[n], waiting_time[n];
    int completed = 0, current_time = 0;

    // Reading input
    for (int i = 0; i < n; i++)
    {
        input_file >> process[i] >> burst_time[i];
        remaining_time[i] = burst_time[i];
        start_time[i] = -1; // -1 indicates the process has not started yet
    }
    input_file.close();

    vector<pair<string, int>> gantt_chart; // To store the Gantt chart (process ID and execution duration)

    // Round Robin scheduling
    while (completed < n)
    {
        bool all_idle = true;

        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0)
            {
                all_idle = false;

                // Update start time for the first execution
                if (start_time[i] == -1)
                {
                    start_time[i] = current_time;
                }

                // Execute the process for either the time quantum or remaining time
                int exec_time = min(time_quantum, remaining_time[i]);
                gantt_chart.push_back({process[i], exec_time});
                current_time += exec_time;
                remaining_time[i] -= exec_time;

                // If the process is completed
                if (remaining_time[i] == 0)
                {
                    completed++;
                    end_time[i] = current_time;
                    turnaround_time[i] = end_time[i]; // Arrival time is 0
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                }
            }
        }

        // If no process is ready to execute, CPU is idle
        if (all_idle)
        {
            gantt_chart.push_back({"Idle", 1});
            current_time++;
        }
    }

    // Calculate averages
    double total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++)
    {
        total_tat += turnaround_time[i];
        total_wt += waiting_time[i];
    }

    // Display results
    cout << "\nProcess\tBurst Time\tStart Time\tEnd Time\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "\t" << burst_time[i] << "\t\t"
             << start_time[i] << "\t\t" << end_time[i] << "\t\t"
             << turnaround_time[i] << "\t" << waiting_time[i] << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time: " << total_wt / n << endl;

    cout << "\nGantt Chart:\n";
    for (const auto &entry : gantt_chart)
    {
        cout << "| " << entry.first << " ";
    }
    cout << "|\n";

    return 0;
}
