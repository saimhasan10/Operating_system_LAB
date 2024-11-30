import matplotlib.pyplot as plt

# Input the number of processes
n = int(input("Enter the number of processes: "))

# Input burst times and process IDs
burst_time = []
process = []
for i in range(n):
    bt = int(input(f"Enter the burst time for Process {i + 1}: "))
    burst_time.append(bt)
    process.append(i + 1)  # Process IDs start from 1

# Sorting processes by burst time (SJF Scheduling)
for i in range(n - 1):
    for j in range(i + 1, n):
        if burst_time[i] > burst_time[j]:
            burst_time[i], burst_time[j] = burst_time[j], burst_time[i]
            process[i], process[j] = process[j], process[i]

# Calculating Start Time, End Time, Waiting Time, and Turnaround Time
start_time = [0] * n
end_time = [0] * n
waiting_time = [0] * n
turnaround_time = [0] * n
total_waiting_time = 0
total_turnaround_time = 0

for i in range(n):
    if i == 0:
        start_time[i] = 0  # First process starts at 0
    else:
        start_time[i] = end_time[i - 1]  # Start after previous process ends
    end_time[i] = start_time[i] + burst_time[i]  # Calculate end time
    waiting_time[i] = start_time[i]  # Waiting time is equivalent to start time
    turnaround_time[i] = end_time[i]  # TAT = End time (since Arrival Time is 0)
    
    # Accumulate totals
    total_waiting_time += waiting_time[i]
    total_turnaround_time += turnaround_time[i]

# Display Results
print("\nProcess\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tTurnaround Time")
for i in range(n):
    print(f"P{process[i]}\t{burst_time[i]}\t\t{start_time[i]}\t\t{end_time[i]}\t\t{waiting_time[i]}\t\t{turnaround_time[i]}")

# Gantt Chart Data Preparation
fig, ax = plt.subplots(figsize=(10, 2))
colors = ['skyblue', 'orange', 'green', 'pink', 'purple', 'yellow', 'red', 'brown', 'cyan', 'magenta']
for i in range(n):
    ax.broken_barh([(start_time[i], burst_time[i])], (10, 5), facecolors=colors[i % len(colors)], label=f"P{process[i]}")

ax.set_ylim(5, 20)
ax.set_xlim(0, end_time[-1] + 1)
ax.set_xlabel("Time")
ax.set_yticks([])
ax.set_xticks(range(0, end_time[-1] + 1))
ax.legend(loc='upper right', title="Processes")
plt.title("Gantt Chart")
plt.grid(True, axis='x')
plt.show()

# Averages
print(f"\nAverage Waiting Time: {total_waiting_time / n:.2f}")
print(f"Average Turnaround Time: {total_turnaround_time / n:.2f}")
