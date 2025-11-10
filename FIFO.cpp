#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> f;

    vector<int> frames;
    queue<int> q;  // To keep track of order (FIFO)
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int current = pages[i];
        bool found = false;

        // Check if page is already in frame (Page Hit)
        for (int j = 0; j < frames.size(); j++) {
            if (frames[j] == current) {
                found = true;
                break;
            }
        }

        // If page not found -> Page Fault occurs
        if (!found) {
            pageFaults++;

            // If frame is full, remove oldest page (FIFO)
            if (frames.size() == f) {
                int oldest = q.front();
                q.pop();

                // Remove oldest page from frames
                for (int k = 0; k < frames.size(); k++) {
                    if (frames[k] == oldest) {
                        frames.erase(frames.begin() + k);
                        break;
                    }
                }
            }

            // Add new page
            frames.push_back(current);
            q.push(current);
        }

        // Display frames after each step
        cout << "Step " << i + 1 << ": ";
        for (int x : frames)
            cout << x << " ";
        if (found)
            cout << " (Hit)";
        else
            cout << " (Fault)";
        cout << endl;
    }

    cout << "\nTotal Page Faults = " << pageFaults << endl;
    cout << "Total Page Hits = " << n - pageFaults << endl;

    return 0;
}

