#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sort(int *track, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (track[j] > track[j + 1])
            {
                int temp = track[j];
                track[j] = track[j + 1];
                track[j + 1] = temp;
            }
        }
    }
}

int scan(int *track, int n, int head, int dir)
{
    int overhead = 0;
    int index = -1;

    track[n + 1] = head;
    sort(track, n + 2);
    for (int i = 0; i < n + 2; i++)
    {
        if (track[i] == head)
        {
            index = i;
            break;
        }
    }

    for (int i = index; i >= 0 && i < n + 2; i += dir)
    {
        overhead += abs(track[i] - head);
        head = track[i];
        printf("%d\t", head);
    }

    dir *= -1;

    for (int i = index + dir; i >= 0 && i < n + 2; i += dir)
    {
        overhead += abs(track[i] - head);
        head = track[i];
        printf("%d\t", head);
    }

    return overhead;
}

int main()
{
    int n, head;
    printf("Enter the number of tracks to be checked: ");
    scanf("%d", &n);
    getchar();

    int *track = (int *)malloc((n + 1) * sizeof(int));
    printf("Enter the current head position: ");
    scanf("%d", &head);
    getchar();

    printf("Enter the tracks to be checked:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Track %d: ", i + 1);
        scanf("%d", &track[i]);
        getchar();
    }

    printf("Enter the initial direction of movement (-1 for left, 1 for right): ");
    int dir;
    scanf("%d", &dir);

    if (dir == -1)
    {
        track[n] = 0; // taking 0 as lowerbound
    }
    if (dir == 1)
    {
        track[n] = 199; // taking 0 as upperbound
    }

    int overhead = scan(track, n, head, dir);
    printf("\nOverhead: %d\n", overhead);

    free(track);
    return 0;
}