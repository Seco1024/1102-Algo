#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define false 0
#define true 1
#define MIN_BOUND 0
typedef int bool;

struct node_q{
    int data,row,col;
    bool mark;
    struct node_q *prev,*next;
};
typedef struct node_q node_q;

struct queue{
    node_q *head,*tail;
};
typedef struct queue queue;

bool queue_is_empty(queue *);
void enqueue(queue *,node_q *);
node_q *dequeue(queue *);
int i,j,temp_data,temp_row,temp_col,max=1,row_num,col_num,bfs_number=0;
queue q;
queue *q_ptr=&q;

int main(void){
    scanf("%d %d",&row_num,&col_num);
    node_q matrix[row_num][col_num];
    for(i=0;i<row_num;i++){
        for(j=0;j<col_num;j++){
            scanf(" %d",&temp_data);
            matrix[i][j].data=temp_data;
            matrix[i][j].row=i;
            matrix[i][j].col=j;
            matrix[i][j].mark=false;
            matrix[i][j].prev,matrix[i][j].next=NULL;
        }
    }
    for(i=0;i<row_num;i++){
        for(j=0;j<col_num;j++){
            if(!(matrix[i][j].mark)){       /*BFS*/
                bfs_number=0;
                matrix[i][j].mark=true;
                enqueue(q_ptr,&matrix[i][j]);
                while(queue_is_empty(q_ptr)==false){
                    node_q *bfs_node=(node_q *)malloc(sizeof(node_q));
                    bfs_node=dequeue(q_ptr);
                    bfs_number++;
                    node_q *up=&matrix[(bfs_node->row)-1][bfs_node->col];      /*上*/
                    node_q *down=&matrix[(bfs_node->row)+1][bfs_node->col];    /*下*/
                    node_q *left=&matrix[bfs_node->row][(bfs_node->col)-1];    /*左*/
                    node_q *right=&matrix[bfs_node->row][(bfs_node->col)+1];   /*右*/
                    if((bfs_node->row)-1>=MIN_BOUND && up->data==bfs_node->data && up->mark==false){
                        up->mark=true;
                        enqueue(q_ptr,up);  
                        //printf("上");
                    }
                    if((bfs_node->row)+1<row_num && down->data==bfs_node->data && down->mark==false){
                        down->mark=true;
                        enqueue(q_ptr,down);
                        //printf("下");
                    }
                    if((bfs_node->col)-1>=MIN_BOUND && left->data==bfs_node->data && left->mark==false){
                        left->mark=true;
                        enqueue(q_ptr,left);
                        //printf("左");
                    }
                    if((bfs_node->col)+1<col_num && right->data==bfs_node->data && right->mark==false){
                        right->mark=true;
                        enqueue(q_ptr,&matrix[bfs_node->row][(bfs_node->col)+1]);
                        //printf("右");
                    }
                }
                if(bfs_number>max){
                    max=bfs_number;
                }
            }
        }
    }
    printf("%d",max);
    return 0;
}

bool queue_is_empty(queue *self){
    return (self->head)?false:true;
}

void enqueue(queue *self,node_q *node){
    if(!(self->head)){
        self->head=node;
        self->tail=node;
    }
    else{
        node->prev=self->tail;
        self->tail->next=node;
        self->tail=node;
    }
}

node_q *dequeue(queue *self){
    assert(!(queue_is_empty(self)));
    node_q *ptr=self->head;
    if(self->head==self->tail){
        self->head=self->tail=NULL;
    }
    else{
        self->head=ptr->next;
        self->head->prev=NULL;
    }
    return ptr;
    free(ptr);
}
