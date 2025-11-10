#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> bt(n), rem_bt(n), wt(n, 0), tat(n, 0);

    cout << "Enter Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> bt[i];
        rem_bt[i] = bt[i]; // Remaining burst time initially same as burst time
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int t = 0; // Current time

    // Round Robin scheduling
    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false; // There is at least one process pending

                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i]; // Waiting Time = Time spent - Burst Time
                    rem_bt[i] = 0;
                }
            }
        }

        if (done)
            break;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    // Display Results
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << bt[i] << "\t\t" << wt[i]
             << "\t\t" << tat[i] << endl;
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << endl;

    return 0;
}

