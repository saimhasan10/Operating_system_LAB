#include <bits/stdc++.h>
using namespace std;

int main()
{

    ifstream input_file("input.txt");
    if (!input_file)
    {
        cout << "Error: Could not open input file" << endl;
        return 1;
    }

    int n;
    input_file >> n;

    int burst_time[n], waiting_time[n], turnaround_time[n], start_time[n], end_time[n];

    for (int i = 0; i < n; i++)
    {
        input_file >> burst_time[i];
    }
    input_file.close();

    start_time[0] = 0;
    end_time[0] = burst_time[0];
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++)
    {
        start_time[i] = end_time[i - 1];
        end_time[i] = start_time[i] + burst_time[i];
        waiting_time[i] = start_time[i];
    }

    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = end_time[i];
    }

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

    cout << fixed << setprecision(2);
    cout << "\nAverage waiting time: " << total_waiting_time / n << endl;
    cout << "Average turnaround time: " << total_turnaround_time / n << endl;

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