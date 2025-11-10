#include <iostream>
#include <vector>
#include <algorithm>
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
    vector<int> recent; // Stores last used index of each frame
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int current = pages[i];
        bool found = false;

        // Check if page is already present
        for (int j = 0; j < frames.size(); j++) {
            if (frames[j] == current) {
                found = true;
                recent[j] = i; // Update recent usage
                break;
            }
        }

        // If page not found -> Page Fault
        if (!found) {
            pageFaults++;

            // If frame is full, remove Least Recently Used
            if (frames.size() == f) {
                int lruIndex = min_element(recent.begin(), recent.end()) - recent.begin();
                frames[lruIndex] = current;
                recent[lruIndex] = i;
            } else {
                // If frame not full yet
                frames.push_back(current);
                recent.push_back(i);
            }
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
