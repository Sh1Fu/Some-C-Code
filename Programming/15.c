#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

struct node
{
    int tiles[N][N];
    int zero_cords[2][2]; // The array with zeroes coordinates
    int f, g, h;
    struct node *next;
    struct node *parent; // Using to build solve path
};

int matrix[N][N];
struct node *start, *goal;                // nodes with start and final values of matrix
struct node *open = NULL, *closed = NULL; // List of checked and non-checked nodes. Important to A*
struct node *succ_nodes[8];               // Generated new nodes
int zero_rows = 0, zero_cols = 0;

void print_a_node(struct node *pnode) // Print matrix
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%2d ", pnode->tiles[i][j]);
        printf("\n");
    }
    printf("\n");
}

struct node *initialize() // Init start and goal nodes
{
    int j, k, index, tile;
    struct node *pnode;

    pnode = (struct node *)malloc(sizeof(struct node));
    index = 1;
    zero_rows = 0, zero_cols = 0;
    for (j = 0; j < N; j++)
        for (k = 0; k < N; k++)
        {
            tile = matrix[j][k];
            pnode->tiles[j][k] = tile;
            if (tile == 0)
            {
                pnode->zero_cords[zero_rows][zero_cols] = j;
                zero_cols++;
                pnode->zero_cords[zero_rows][zero_cols] = k;
                zero_rows++;
                zero_cols = 0;
            }
        }
    pnode->f = 0;
    pnode->g = 0;
    pnode->h = 0;
    pnode->next = NULL;
    pnode->parent = NULL;
    start = pnode;
    printf("=========Start matrix=========\n");
    print_a_node(start);
    pnode = (struct node *)malloc(sizeof(struct node));

    int num = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            pnode->tiles[i][j] = num;
            num++;
        }
    }
    pnode->tiles[N - 1][N - 2] = 0;
    pnode->tiles[N - 1][N - 1] = 0;
    pnode->f = 0;
    pnode->g = 0;
    pnode->h = 0;
    pnode->next = NULL;
    goal = pnode;
    printf("\n=========Goal  matrix=========\n");
    print_a_node(goal);
    return start;
}

void swap(int row1, int column1, int row2, int column2, struct node *pnode)
{
    pnode->tiles[row1][column1] += pnode->tiles[row2][column2];
    pnode->tiles[row2][column2] = pnode->tiles[row1][column1] - pnode->tiles[row2][column2];
    pnode->tiles[row1][column1] -= pnode->tiles[row2][column2];
}

void move_down(struct node *pnode, int zr, int zc)
{
    if (pnode->zero_cords[zr][zc] + 1 < N)
    {
        swap(pnode->zero_cords[zr][zc], pnode->zero_cords[zr][zc + 1], pnode->zero_cords[zr][zc] + 1, pnode->zero_cords[zr][zc + 1], pnode);
        pnode->zero_cords[zr][zc]++;
    }
    else
    {
        pnode = NULL;
    }
}

void move_right(struct node *pnode, int zr, int zc)
{
    if (pnode->zero_cords[zr][zc + 1] + 1 < N)
    {
        swap(pnode->zero_cords[zr][zc], pnode->zero_cords[zr][zc + 1], pnode->zero_cords[zr][zc], pnode->zero_cords[zr][zc + 1] + 1, pnode);
        pnode->zero_cords[zr][zc + 1]++;
    }
    else
    {
        pnode = NULL;
    }
}

void move_up(struct node *pnode, int zr, int zc)
{
    if (pnode->zero_cords[zr][zc] - 1 > -1)
    {
        swap(pnode->zero_cords[zr][zc], pnode->zero_cords[zr][zc + 1], pnode->zero_cords[zr][zc] - 1, pnode->zero_cords[zr][zc + 1], pnode);
        pnode->zero_cords[zr][zc]--;
    }
    else
    {
        pnode = NULL;
    }
}

void move_left(struct node *pnode, int zr, int zc)
{
    if (pnode->zero_cords[zr][zc + 1] - 1 > -1)
    {
        swap(pnode->zero_cords[zr][zc], pnode->zero_cords[zr][zc + 1], pnode->zero_cords[zr][zc], pnode->zero_cords[zr][zc + 1] - 1, pnode);
        pnode->zero_cords[zr][zc + 1]--;
    }
    else
    {
        pnode = NULL;
    }
}

// Used for h2
int manhattanDist(int entry, int row, int col)
{
    // Ignore 0 (Of course)
    if (entry == 0)
    {
        return 0;
    }
    // Find entry in goal
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (goal->tiles[i][j] == entry)
            {
                // Goal destination is i, j
                return abs(row - i) + abs(col - j);
            }
        }
    }
}
/* A* parameters counting  */
void update_fgh(struct node *pnode)
{
    // g is amount of steps from top. Глубина рекурсии
    if (pnode->parent != NULL)
    {
        pnode->g = pnode->parent->g + 1;
    }
    else
    {
        pnode->g = 1;
    }

    // h is the max of h1 or h2
    int h1 = 0, h2 = 0;
    int i, j;
    int correct = 0;
    // h1 is number of misplaced tiles, h2 is how far the tile is from desired location
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            correct++;
            if (pnode->tiles[i][j] != correct)
            {
                h1++;
            }
            h2 += manhattanDist(pnode->tiles[i][j], i, j);
        }
    }
    pnode->h = (h1 > h2 ? h1 : h2);
    pnode->f = pnode->g + pnode->h;
}

/* expand a node, get its children nodes, and organize the children nodes using
 * array succ_nodes.
 */
void expand(struct node *selected)
{
    zero_rows = 0, zero_cols = 0;
    for (int i = 0; i < 8; i++)
    {
        succ_nodes[i] = (struct node *)malloc(sizeof(struct node));
        memcpy(succ_nodes[i]->tiles, selected->tiles, N * N * sizeof(int));
        memcpy(succ_nodes[i]->zero_cords, selected->zero_cords, 4 * sizeof(int));
        succ_nodes[i]->parent = selected;
    }
    // Move the first zero to all possible positions
    if (succ_nodes[0]->tiles[succ_nodes[0]->zero_cords[zero_rows][zero_cols] + 1][succ_nodes[0]->zero_cords[zero_rows][zero_cols + 1]] != 0)
        move_down(succ_nodes[0], zero_rows, zero_cols);
    if (succ_nodes[1]->tiles[succ_nodes[1]->zero_cords[zero_rows][zero_cols]][succ_nodes[1]->zero_cords[zero_rows][zero_cols + 1] + 1] != 0)
        move_right(succ_nodes[1], zero_rows, zero_cols);
    if (succ_nodes[2]->tiles[succ_nodes[2]->zero_cords[zero_rows][zero_cols] - 1][succ_nodes[2]->zero_cords[zero_rows][zero_cols + 1]] != 0)
        move_up(succ_nodes[2], zero_rows, zero_cols);
    if (succ_nodes[3]->tiles[succ_nodes[3]->zero_cords[zero_rows][zero_cols]][succ_nodes[3]->zero_cords[zero_rows][zero_cols + 1] - 1] != 0)
        move_left(succ_nodes[3], zero_rows, zero_cols);

    zero_rows++; // Change focus to second zero
    // Move the second zero to all possible positions
    if (succ_nodes[4]->tiles[succ_nodes[4]->zero_cords[zero_rows][zero_cols] + 1][succ_nodes[4]->zero_cords[zero_rows][zero_cols + 1]] != 0)
        move_down(succ_nodes[4], zero_rows, zero_cols);
    if (succ_nodes[5]->tiles[succ_nodes[5]->zero_cords[zero_rows][zero_cols]][succ_nodes[5]->zero_cords[zero_rows][zero_cols + 1] + 1] != 0)
        move_right(succ_nodes[5], zero_rows, zero_cols);
    if (succ_nodes[6]->tiles[succ_nodes[6]->zero_cords[zero_rows][zero_cols] - 1][succ_nodes[6]->zero_cords[zero_rows][zero_cols + 1]] != 0)
        move_up(succ_nodes[6], zero_rows, zero_cols);
    if (succ_nodes[7]->tiles[succ_nodes[7]->zero_cords[zero_rows][zero_cols]][succ_nodes[7]->zero_cords[zero_rows][zero_cols + 1] - 1] != 0)
        move_left(succ_nodes[7], zero_rows, zero_cols);

    zero_rows = 0;

    for (int i = 0; i < 8; i++)
    {
        update_fgh(succ_nodes[i]);
    }
}

/* Boolean function to compare array with goal matrix */
int nodes_same(struct node *a, struct node *b)
{
    int flg = 0;
    if (memcmp(a->tiles, b->tiles, sizeof(int) * N * N) == 0)
        flg = 1;
    return flg;
}

/* Filtering. Some nodes in succ_nodes may already be included in either open
 * or closed list. Remove them. It is important to reduce execution time.
 * This function checks the (i)th node in succ_nodes array.
 * You must call this function in a loop to check all the nodes in succ_nodes.*/
void filter(int i, struct node *pnode_list)
{
    // pnode_list - list of all open(closed) nodes
    if (pnode_list == NULL || succ_nodes[i] == NULL)
    {
        return;
    }
    struct node *temp = pnode_list;
    while (temp != NULL)
    {
        if (nodes_same(succ_nodes[i], temp))
        {
            succ_nodes[i] = NULL;
            return;
        }
        temp = temp->next;
    }
}

void merge_to_open()
{
    /* Merge unrepeated nodes into open list after filtering */
    for (int i = 0; i < 8; i++)
    {
        if (succ_nodes[i] == NULL)
        {
            continue;
        }
        // Create a new node to insert, as succ_nodes will soon be cleared for next iteration
        struct node *toInsert = (struct node *)malloc(sizeof(struct node));
        memcpy(toInsert->tiles, succ_nodes[i]->tiles, 16 * sizeof(int));
        memcpy(toInsert->zero_cords, succ_nodes[i]->zero_cords, 4 * sizeof(int));
        toInsert->f = succ_nodes[i]->f;
        toInsert->g = succ_nodes[i]->g;
        toInsert->h = succ_nodes[i]->h;
        toInsert->parent = succ_nodes[i]->parent;

        if (open == NULL)
        {
            open = toInsert;
            continue;
        }

        struct node *temp = open;

        int hasInserted = 0;

        while (temp != NULL && temp->next != NULL)
        {
            if (toInsert->f < temp->next->f)
            {
                toInsert->next = temp->next;
                temp->next = toInsert;
                hasInserted = 1;
                break;
            }
            temp = temp->next;
        }

        // Temp should be either the last node, or the node where toInsert should be inserted
        if (hasInserted == 0)
        {
            temp->next = toInsert;
        }
    }
}

int main()
{
    int iter;
    struct node *copen, *solution_path;
    int pathlen = 0;

    solution_path = NULL;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    start = initialize();
    open = start;
    int mv_count = 0;
    while (open != NULL)
    {
        copen = open;
        open = open->next;
        if (nodes_same(copen, goal))
        {
            do
            {
                copen->next = solution_path;
                solution_path = copen;
                copen = copen->parent;
                pathlen++;
            } while (copen != NULL);
            printf("%d moves\n", pathlen - 1);
            do
            {
                printf("%d\n====================\n", mv_count);
                print_a_node(solution_path);
                solution_path = solution_path->next;
                mv_count++;
            } while (solution_path != NULL && mv_count <= pathlen);
            break;
        }
        expand(copen);
        for (int i = 0; i < 8; i++)
        {
            filter(i, open);
            filter(i, closed);
        }
        merge_to_open();
        copen->next = closed;
        closed = copen;
    }

    return 0;
}