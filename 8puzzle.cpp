#include <bits/stdc++.h>
using namespace std;
#define N 3

// on considère que le puzzle peut être résolu

class Noeud
{
    public:
    // permet de faire le backtracking
    Noeud* parent;

    // etat actuel du puzzle
    int puzzle[N][N];

    // stores blank tile coordinates
    int x, y;

    // stores the number of misplaced tiles
    int cout;

    // stores the number of moves so far
    int level;
};

// affichage de l'état du puzzle
void printPuzzle(int puzzle[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", puzzle[i][j]);
        printf("\n");
    }
}

// Création d'un noeud
Noeud* newNoeud(int puzzle[N][N], int x, int y, int newX,
              int newY, int level, Noeud* parent)
{
    Noeud* noeud = new Noeud;

    noeud->parent = parent;

    memcpy(noeud->puzzle, puzzle, sizeof noeud->puzzle);

    swap(noeud->puzzle[x][y], noeud->puzzle[newX][newY]);

    noeud->cout = INT_MAX;

    noeud->level = level;

    noeud->x = newX;
    noeud->y = newY;

    return noeud;
}

// bottom, left, top, right
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

int getCout(int initial[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        if (initial[i][j] && initial[i][j] != final[i][j])
           count++;
    return count;
}

int isMatrixIndexesOutOfBounds(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void afficherSolution(Noeud* root)
{
    if (root == NULL)
        return;
    afficherSolution(root->parent);
    printPuzzle(root->puzzle);

    printf("\n");
}

struct comp
{
    bool operator()(const Noeud* lhs, const Noeud* rhs) const
    {
        return (lhs->cout + lhs->level) > (rhs->cout + rhs->level);
    }
};

// x et y sont les coordonnées de la case vide
void solve(int initial[N][N], int x, int y,
           int final[N][N])
{
    priority_queue<Noeud*, std::vector<Noeud*>, comp> pq;

    Noeud* root = newNoeud(initial, x, y, x, y, 0, NULL);
    root->cout = getCout(initial, final);

    // Add root to list of live nodes;
    pq.push(root);

    while (!pq.empty())
    {
        Noeud* min = pq.top();

        pq.pop();

        if (min->cout == 0)
        {
            afficherSolution(min);
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isMatrixIndexesOutOfBounds(min->x + row[i], min->y + col[i]))
            {
                Noeud* child = newNoeud(min->puzzle, min->x,
                              min->y, min->x + row[i],
                              min->y + col[i],
                              min->level + 1, min);
                child->cout = getCout(child->puzzle, final);

                pq.push(child);
            }
        }
    }
}

int main()
{
    int initial[N][N] =
    {
        {2, 1, 4},
        {5, 6, 8},
        {7, 0, 3}
    };

    int final[N][N] =
    {
        {2, 1, 4},
        {5, 8, 0},
        {7, 6, 3}
    };

    // L'espace vide se trouve à la position (0, 0)
    int x = 2, y = 1;

    solve(initial, x, y, final);

    return 0;
}
