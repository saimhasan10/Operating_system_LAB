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

    int burst_time[n], waiting_time[n], turnaround_time[n], start_time[n], end_time[n], process[n];
    double total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
    {
        input_file >> burst_time[i];
        process[i] = i + 1;
    }
    input_file.close();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (burst_time[i] > burst_time[j])
            {
                swap(burst_time[i], burst_time[j]);
                swap(process[i], process[j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            start_time[i] = 0;
        }
        else
        {
            start_time[i] = end_time[i - 1];
        }
        end_time[i] = start_time[i] + burst_time[i];
        waiting_time[i] = start_time[i];
        turnaround_time[i] = end_time[i];

        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    cout << fixed << setprecision(2);
    cout << "\nProcess\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << process[i] << "\t" << burst_time[i] << "\t\t" << start_time[i] << "\t\t" << end_time[i]
             << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

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

    cout << "\nAverage Waiting Time: " << total_waiting_time / n;
    cout << "\nAverage Turnaround Time: " << total_turnaround_time / n << endl;

    return 0;
}
