#include <bits/stdc++.h>
using namespace std;

int maxRec(int pieces[], int i, int j, int sum)
{
    if (j == i + 1)
        return max(pieces[i], pieces[j]);

    return max((sum - maxRec(pieces, i + 1, j, sum - pieces[i])),
               (sum - maxRec(pieces, i, j - 1, sum - pieces[j])));
}

int findOptimalStrategy(int* pieces, int n)
{
    int sum = 0;
    sum = accumulate(pieces, pieces + n, sum);
    return maxRec(pieces, 0, n - 1, sum);
}

int main()
{
    int test1[] = { 12, 11, 5, 4 };
    printf("%d\n", findOptimalStrategy(test1, 4));

    int test2[] = { 1, 0, 3, 9 };
    printf("%d\n", findOptimalStrategy(test2, 4));

    int test3[] = { 40, 10, 1, 4, 3, 9 };
    printf("%d\n", findOptimalStrategy(test3, 6));

    return 0;
}
