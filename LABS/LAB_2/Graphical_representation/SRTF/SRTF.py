import matplotlib.pyplot as plt

def main():
    try:
        with open("input.txt", "r") as file:
            lines = file.readlines()
    except FileNotFoundError:
        print("Unable to open input file.")
        return

    # Read number of processes
    n = int(lines[0].strip())

    arrival_time = []
    burst_time = []
    remaining_time = []
    start_time = [-1] * n  # -1 indicates that the process has not started yet
    process = []

    # Read process details
    for line in lines[1:n + 1]:
        p, at, bt = line.strip().split()
        process.append(p)
        arrival_time.append(int(at))
        burst_time.append(int(bt))
        remaining_time.append(int(bt))

    current_time = 0
    completed = 0
    end_time = [0] * n
    turnaround_time = [0] * n
    waiting_time = [0] * n
    total_tat = 0
    total_wt = 0
    gantt_chart = []  # Stores the sequence of process execution for the Gantt Chart
    gantt_times = []  # Stores the time at each stage of the Gantt Chart

    while completed < n:
        shortest = -1
        min_remaining = float("inf")

        # Find process with the shortest remaining time at the current time
        for i in range(n):
            if arrival_time[i] <= current_time and remaining_time[i] > 0:
                if remaining_time[i] < min_remaining:
                    min_remaining = remaining_time[i]
                    shortest = i

        if shortest == -1:
            # No process is ready to execute; idle time
            gantt_chart.append("Idle")
            gantt_times.append(current_time)
            current_time += 1
            continue

        # Update start time if it's the first execution
        if start_time[shortest] == -1:
            start_time[shortest] = current_time

        # Execute the process for 1 unit of time
        gantt_chart.append(process[shortest])
        gantt_times.append(current_time)
        remaining_time[shortest] -= 1
        current_time += 1

        # If the process is completed
        if remaining_time[shortest] == 0:
            completed += 1
            end_time[shortest] = current_time
            turnaround_time[shortest] = end_time[shortest] - arrival_time[shortest]
            waiting_time[shortest] = turnaround_time[shortest] - burst_time[shortest]

            total_tat += turnaround_time[shortest]
            total_wt += waiting_time[shortest]

    gantt_times.append(current_time)

    # Print outputs
    print("\nProcess\tArrival Time\tBurst Time\tStart Time\tEnd Time\tTAT\tWT")
    for i in range(n):
        print(f"{process[i]}\t{arrival_time[i]}\t\t{burst_time[i]}\t\t"
              f"{start_time[i]}\t\t{end_time[i]}\t\t"
              f"{turnaround_time[i]}\t{waiting_time[i]}")

    print(f"\nAverage Turnaround Time: {total_tat / n:.2f}")
    print(f"Average Waiting Time: {total_wt / n:.2f}")

    # Gantt Chart Representation
    print("\nGantt Chart:")
    for p in gantt_chart:
        print(f"| {p} ", end="")
    print("|")

    # Graphical Representation of Gantt Chart
    fig, ax = plt.subplots(figsize=(10, 2))
    colors = plt.cm.Paired(range(len(set(gantt_chart))))

    unique_processes = list(set(gantt_chart))
    color_map = {unique_processes[i]: colors[i] for i in range(len(unique_processes))}

    current_position = 0
    for i in range(len(gantt_chart)):
        process_name = gantt_chart[i]
        start = gantt_times[i]
        end = gantt_times[i + 1]
        ax.barh(0, end - start, left=start, color=color_map[process_name], edgecolor="black")
        ax.text((start + end) / 2, 0, process_name, ha="center", va="center", fontsize=10, color="white")

    ax.set_yticks([])
    ax.set_xticks(range(0, gantt_times[-1] + 1))
    ax.set_xlabel("Time Units")
    ax.set_title("Gantt Chart")
    plt.show()


if __name__ == "__main__":
    main()
