#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 그래프 구조체 정의
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// 노드 구조체 정의
struct Node {
    int vertex;
    struct Node* next;
};

// 스택 구조체 정의 및 기능 구현
struct Stack {
    int data;
    struct Stack* next;
};

void push(struct Stack** top, int data) {
    struct Stack* new_node = (struct Stack*)malloc(sizeof(struct Stack));
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

int pop(struct Stack** top) {
    if (*top == NULL) {
        return -1;
    }
    struct Stack* temp = *top;
    *top = (*top)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

// 큐 구조체 정의 및 기능 구현
struct Queue {
    struct Node* front;
    struct Node* rear;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue* queue, int v) {
    struct Node* temp = createNode(v);
    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
}

int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return -1;
    }
    struct Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    int popped = temp->vertex;
    free(temp);
    return popped;
}

// 깊이 우선 탐색 알고리즘
void DFS(struct Graph* graph, int startVertex, int goal) {
    struct Stack* stack = NULL;
    push(&stack, startVertex);
    graph->visited[startVertex] = 1;
    int visitedCount = 0;

    while (stack != NULL) {
        int currentVertex = pop(&stack);
        printf("%d ", currentVertex);
        visitedCount++;

        if (currentVertex == goal) {
            printf("\n목표를 찾았습니다!\n");
            printf("방문한 노드의 수: %d\n", visitedCount);
            break;
        }

        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int connectedVertex = temp->vertex;
            if (!graph->visited[connectedVertex]) {
                push(&stack, connectedVertex);
                graph->visited[connectedVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// 너비 우선 탐색 알고리즘
void BFS(struct Graph* graph, int startVertex, int goal) {
    struct Queue* queue = createQueue();
    enqueue(queue, startVertex);
    graph->visited[startVertex] = 1;
    int visitedCount = 0;

    while (queue->front != NULL) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        visitedCount++;

        if (currentVertex == goal) {
            printf("\n목표를 찾았습니다!\n");
            printf("방문한 노드의 수: %d\n", visitedCount);
            break;
        }

        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int connectedVertex = temp->vertex;
            if (!graph->visited[connectedVertex]) {
                enqueue(queue, connectedVertex);
                graph->visited[connectedVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// 메인 함수
int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = 11;
    graph->adjLists = (struct Node**)malloc(graph->numVertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    // 그래프 초기화
    int edges[][2] = { {0, 5}, {0, 2}, {0, 4}, {0, 6}, {0, 9}, {1, 5}, {1, 4}, {1, 7}, {1, 10}, {2, 3}, {2, 4}, {3, 5}, {3, 4}, {4, 6}, {4, 7}, {6, 7}, {6, 8}, {9, 8}, {7, 10}, {8, 10} };
    int numEdges = 20;

    for (int i = 0; i < numEdges; i++) {
        int start = edges[i][0];
        int end = edges[i][1];

        struct Node* newNode = createNode(end);
        newNode->next = graph->adjLists[start];
        graph->adjLists[start] = newNode;

        newNode = createNode(start);
        newNode->next = graph->adjLists[end];
        graph->adjLists[end] = newNode;
    }

    // 메뉴 구현
    int choice = 0;
    while (choice != 3) {
        printf("\n1: 깊이 우선 탐색\n2: 너비 우선 탐색\n3: 종료\n");
        printf("메뉴 입력: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int start, goal;
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &goal);
            DFS(graph, start, goal);
            for (int i = 0; i < graph->numVertices; i++) {
                graph->visited[i] = 0;
            }
            break;
        }
        case 2: {
            int start, goal;
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d %d", &start, &goal);
            BFS(graph, start, goal);
            for (int i = 0; i < graph->numVertices; i++) {
                graph->visited[i] = 0;
            }
            break;
        }
        case 3:
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 선택입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}
