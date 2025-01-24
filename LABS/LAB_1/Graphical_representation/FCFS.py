import matplotlib.pyplot as plt

def main():
    n = int(input("Enter the number of Processes: "))

    # arrays for all times
    burst_time = []
    waiting_time = []
    turnaround_time = []
    start_time = []
    end_time = []

    # take the burst time input
    print("Enter the burst time for each process: ")
    for i in range(n):
        bt = int(input(f"P{i+1}: "))
        burst_time.append(bt)

    # calculate the times for the first process
    start_time.append(0)
    end_time.append(burst_time[0])
    waiting_time.append(0)

    # calculate times for the rest of the processes
    for i in range(1, n):
        start_time.append(end_time[i - 1])  # start time is the previous process finish time
        end_time.append(start_time[i] + burst_time[i])  # end time is the start time + burst time
        waiting_time.append(start_time[i])  # the time waiting to start the process

    # calculate the turnaround time
    for i in range(n):
        turnaround_time.append(end_time[i])  # turnaround time is end time

    # Display the result
    print("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\tStart Time\tEnd Time")
    total_waiting_time = 0
    total_turnaround_time = 0
    for i in range(n):
        print(f"P{i+1}\t{burst_time[i]}\t\t{waiting_time[i]}\t\t{turnaround_time[i]}\t\t{start_time[i]}\t\t{end_time[i]}")
        total_waiting_time += waiting_time[i]
        total_turnaround_time += turnaround_time[i]

    # Calculate the average times
    print(f"\nAverage waiting time: {total_waiting_time / n:.2f}")
    print(f"Average turnaround time: {total_turnaround_time / n:.2f}")

    # Display the Gantt chart
    print("\nGantt chart: ")
    fig, ax = plt.subplots(figsize=(10, 5))
    
    for i in range(n):
        ax.barh(0, burst_time[i], left=start_time[i], height=0.5, align='center', label=f"P{i+1}")

    ax.set_yticks([0])
    ax.set_yticklabels(["Processes"])
    ax.set_xlabel("Time")
    ax.set_title("Gantt Chart")

    # Add labels for each process
    for i in range(n):
        ax.text((start_time[i] + end_time[i]) / 2, 0, f"P{i+1}", ha='center', va='center', color='white')

    plt.show()

if __name__ == "__main__":
    main()
