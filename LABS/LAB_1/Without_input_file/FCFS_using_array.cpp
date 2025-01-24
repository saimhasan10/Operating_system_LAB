#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of Process: ";
    cin >> n;

    // array for all times
    int burst_time[n], waiting_time[n], turnaround_time[n], start_time[n], end_time[n];

    // take the burst time
    cout << "Enter the burst time for each process: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << ": ";
        cin >> burst_time[i];
    }

    //  calculate each time frame for first process
    start_time[0] = 0;
    end_time[0] = burst_time[0];
    waiting_time[0] = 0;

    // calculate each time for rest of processes
    for (int i = 1; i < n; i++)
    {
        start_time[i] = end_time[i - 1];             // start time is the previous process finish time
        end_time[i] = start_time[i] + burst_time[i]; // end time is the start time + burst time
        waiting_time[i] = start_time[i];             // the time waiting to start the process
    }

    // calculate the turnaround time
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = end_time[i]; // waiting time + burst time
    }

    // display the result
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\tStart Time\tEnd Time\n";
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t" << burst_time[i] << "\t\t"
             << waiting_time[i] << "\t\t" << turnaround_time[i] << "\t\t"
             << start_time[i] << "\t\t" << end_time[i] << "\n";
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // calculate the average time
    cout << fixed << setprecision(2);
    cout << "\nAverage waiting time: " << total_waiting_time / n << endl;
    cout << "Average turnaround time: " << total_turnaround_time / n << endl;

    // display the Gantt chart
    cout << "\nGantt chart: " << endl;
    cout << "|";
    for (int i = 0; i < n; i++)
    {
        cout << " P" << i + 1 << " |";
    }
    cout << "\n0";
    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << end_time[i];
    }
    cout << endl;

    return 0;
}