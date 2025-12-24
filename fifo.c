#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

// Function to display frames
void displayFrames(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
}

// Function to check page hit
int isHit(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

/* ---------------- FIFO ALGORITHM ---------------- */
void fifo(int pages[], int n, int f) {
    int frames[MAX_FRAMES], index = 0, faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement\n");
    printf("Page\tFrames\t\tStatus\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", pages[i]);

        if (!isHit(frames, f, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;

            displayFrames(frames, f);
            printf("\tFault");
        } else {
            displayFrames(frames, f);
            printf("\tHit");
        }
        printf("\n");
    }

    printf("----------------------------------------\n");
    printf("Total Page Faults (FIFO) = %d\n", faults);
}

/* ---------------- LRU ALGORITHM ---------------- */
void lru(int pages[], int n, int f) {
    int frames[MAX_FRAMES], time[MAX_FRAMES];
    int faults = 0, counter = 0;

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement\n");
    printf("Page\tFrames\t\tStatus\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", pages[i]);
        counter++;
        int hit = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                time[j] = counter;
                hit = 1;
                break;
            }
        }

        if (!hit) {
            int min = time[0], pos = 0;
            for (int j = 1; j < f; j++) {
                if (time[j] < min) {
                    min = time[j];
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            time[pos] = counter;
            faults++;

            displayFrames(frames, f);
            printf("\tFault");
        } else {
            displayFrames(frames, f);
            printf("\tHit");
        }
        printf("\n");
    }

    printf("----------------------------------------\n");
    printf("Total Page Faults (LRU) = %d\n", faults);
}

/* ---------------- OPTIMAL ALGORITHM ---------------- */
void optimal(int pages[], int n, int f) {
    int frames[MAX_FRAMES], faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement\n");
    printf("Page\tFrames\t\tStatus\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", pages[i]);

        if (isHit(frames, f, pages[i])) {
            displayFrames(frames, f);
            printf("\tHit\n");
            continue;
        }

        int pos = -1, farthest = i + 1;

        for (int j = 0; j < f; j++) {
            int k;
            for (k = i + 1; k < n; k++) {
                if (frames[j] == pages[k])
                    break;
            }
            if (k == n) {
                pos = j;
                break;
            }
            if (k > farthest) {
                farthest = k;
                pos = j;
            }
        }

        if (pos == -1)
            pos = 0;

        frames[pos] = pages[i];
        faults++;

        displayFrames(frames, f);
        printf("\tFault\n");
    }

    printf("----------------------------------------\n");
    printf("Total Page Faults (Optimal) = %d\n", faults);
}

/* ---------------- MAIN FUNCTION ---------------- */
int main() {
    int pages[MAX_PAGES];
    int n, f, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    do {
        printf("\n===== Virtual Memory Management =====\n");
        printf("1. FIFO Page Replacement\n");
        printf("2. LRU Page Replacement\n");
        printf("3. Optimal Page Replacement\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: fifo(pages, n, f); break;
            case 2: lru(pages, n, f); break;
            case 3: optimal(pages, n, f); break;
            case 4: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
