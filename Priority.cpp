#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a process
struct Process {
    int id;        // Process ID
    int bt;        // Burst Time
    int priority;  // Smaller value = Higher priority
    int wt;        // Waiting Time
    int tat;       // Turnaround Time
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input Burst Time and Priority for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "\nEnter Burst Time for Process P" << p[i].id << ": ";
        cin >> p[i].bt;
        cout << "Enter Priority for Process P" << p[i].id << ": ";
        cin >> p[i].priority;
    }

    // Sort processes by priority (ascending order)
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.priority < b.priority;
    });

    // Calculate Waiting Time
    p[0].wt = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        p[i].wt = 0;
        for (int j = 0; j < i; j++) {
            p[i].wt += p[j].bt;
        }
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
    }

    // Display results
    float totalWT = 0, totalTAT = 0;
    cout << "\n-------------------------------------------------------------";
    cout << "\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time";
    cout << "\n-------------------------------------------------------------";

    for (int i = 0; i < n; i++) {
        cout << "\nP" << p[i].id << "\t" << p[i].bt << "\t\t" << p[i].priority
             << "\t\t" << p[i].wt << "\t\t" << p[i].tat;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\n-------------------------------------------------------------";
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "-------------------------------------------------------------\n";

    return 0;
}
