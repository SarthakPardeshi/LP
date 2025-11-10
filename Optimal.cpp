#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to find the page to be replaced
int predict(vector<int>& pages, vector<int>& frames, int n, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames.size(); i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // If the page is never used again
        if (j == n)
            return i;
    }
    // If all pages will be used again, replace the farthest one
    return (res == -1) ? 0 : res;
}

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
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int current = pages[i];
        bool found = false;

        // Check if page already exists
        for (int j = 0; j < frames.size(); j++) {
            if (frames[j] == current) {
                found = true;
                break;
            }
        }

        // If not found, Page Fault
        if (!found) {
            pageFaults++;

            if (frames.size() < f)
                frames.push_back(current);
            else {
                int pos = predict(pages, frames, n, i + 1);
                frames[pos] = current;
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
