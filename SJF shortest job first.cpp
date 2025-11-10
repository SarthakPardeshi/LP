#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;   // Process ID
    int bt;   // Burst Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << i + 1 << ": ";
        cin >> p[i].bt;
    }

    // Sort processes according to Burst Time (Shortest Job First)
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.bt < b.bt;
    });

    // Calculate Waiting Time
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = 0;
        for (int j = 0; j < i; j++)
            p[i].wt += p[j].bt;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++)
        p[i].tat = p[i].bt + p[i].wt;

    // Display results
    float totalWT = 0, totalTAT = 0;
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].bt << "\t\t"
             << p[i].wt << "\t\t" << p[i].tat << endl;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << endl;

    return 0;
}
