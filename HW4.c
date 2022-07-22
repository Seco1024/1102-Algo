#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define false 0
#define true 1
typedef int bool;

struct node
{
    int id, left, right, dist;
    bool known;
};
typedef struct node node;

struct adjNode
{
    int id;
    struct adjNode *next;
};
typedef struct adjNode adjNode;

struct adjList
{
    adjNode *header;
};
typedef struct adjList adjList;

struct node_q
{
    int id;
    struct node_q *prev, *next;
};
typedef struct node_q node_q;

struct queue
{
    node_q *head, *tail;
};
typedef struct queue queue;

struct graph
{
    int v; //節點數量
    adjList *array;
};
typedef struct graph graph;

node *createNode(int, int, int);
graph *createGraph(int);
void addEdge(graph *, node *, node *);
bool check_overlap(node *, node *);
node_q *createNodeq(int);
bool queue_is_empty(queue *);
void enqueue(queue *, node_q *);
node_q *dequeue(queue *);

node_q *createNodeq(int id)
{
    node_q *ptr = (node_q *)malloc(sizeof(node_q));
    ptr->id = id;
    ptr->next = NULL;
    ptr->prev = NULL;
    return ptr;
}

node *createNode(int id, int left, int right)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->id = id;
    newNode->left = left;
    newNode->right = right;
    newNode->dist = -1;
    newNode->known = false;

    return newNode;
}

graph *createGraph(int size)
{
    graph *G = (graph *)malloc(sizeof(graph));
    G->v = size;
    G->array = (adjList *)malloc(size * sizeof(adjList));
    int i;
    for (i = 0; i < size; i++)
    {
        G->array[i].header = NULL;
    }
    return G;
}

void addEdge(graph *G, node *V1, node *V2)
{
    adjNode *ptr = NULL;
    int V1_id = V1->id, V2_id = V2->id;
    if (G->array[V1_id].header == NULL)
    {
        adjNode *tmp = (adjNode *)malloc(sizeof(adjNode));
        tmp->id = V2_id;
        tmp->next = NULL;
        G->array[V1_id].header = tmp;
    }
    else
    {
        ptr = G->array[V1_id].header;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        adjNode *tmp = (adjNode *)malloc(sizeof(adjNode));
        tmp->id = V2_id;
        tmp->next = NULL;
        ptr->next = tmp;
    }
    if (G->array[V2_id].header == NULL)
    {
        adjNode *tmp = (adjNode *)malloc(sizeof(adjNode));
        tmp->id = V1_id;
        tmp->next = NULL;
        G->array[V2_id].header = tmp;
    }
    else
    {
        ptr = G->array[V2_id].header;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        adjNode *tmp = (adjNode *)malloc(sizeof(adjNode));
        tmp->id = V1_id;
        tmp->next = NULL;
        ptr->next = tmp;
    }
}

bool check_overlap(node *current, node *vertex)
{
    if (vertex->left >= current->right || vertex->right <= current->left)
        return false;
    else
        return true;
}

bool queue_is_empty(queue *self)
{
    return (self->head) ? false : true;
}

void enqueue(queue *self, node_q *node)
{
    if (!(self->head))
    {
        self->head = node;
        self->tail = node;
    }
    else
    {
        node->prev = self->tail;
        self->tail->next = node;
        self->tail = node;
    }
}

node_q *dequeue(queue *self)
{
    assert(!(queue_is_empty(self)));
    node_q *ptr = self->head;
    if (self->head == self->tail)
    {
        self->head = self->tail = NULL;
    }
    else
    {
        self->head = ptr->next;
        self->head->prev = NULL;
    }
    return ptr;
}

int main(void)
{
    int n, i, j, k, left, right;
    scanf("%d", &n);
    node *array[n];
    graph *G = createGraph(n);

    for (i = 0; i < n; i++)
    {
        scanf(" %d %d", &left, &right);
        array[i] = createNode(i, left, right);
    }

    for (k = 0; k < n - 1; k++)
    {
        for (j = k + 1; j < n; j++)
        {
            if (check_overlap(array[k], array[j]) == true)
            {
                addEdge(G, array[k], array[j]);
            }
        }
    }
    node_q *source = createNodeq(0), *ptr;
    queue *Q = (queue *)malloc(sizeof(queue));
    Q->head = NULL;
    Q->tail = NULL;
    enqueue(Q, source);
    array[0]->dist = 0;
    while (queue_is_empty(Q) == false)
    {
        ptr = dequeue(Q);
        array[ptr->id]->known = true;
        adjNode *tmp = G->array[ptr->id].header;
        while (tmp != NULL)
        {
            if (array[tmp->id]->known == true)
            {
                tmp = tmp->next;
            }
            else if (array[tmp->id]->dist == -1)
            {
                array[tmp->id]->dist = array[ptr->id]->dist + 1;
                array[tmp->id]->known = true;
                if (tmp->id == n - 1)
                {
                    printf("%d", array[tmp->id]->dist);
                    return 0;
                }
                node_q *new = createNodeq(tmp->id);
                enqueue(Q, new);
                tmp = tmp->next;
            }
        }
    }
    printf("%d", 0);
    return 0;
}
