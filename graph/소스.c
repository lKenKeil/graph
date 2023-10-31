#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// �׷��� ����ü ����
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// ��� ����ü ����
struct Node {
    int vertex;
    struct Node* next;
};

// ���� ����ü ���� �� ��� ����
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

// ť ����ü ���� �� ��� ����
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

// ���� �켱 Ž�� �˰���
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
            printf("\n��ǥ�� ã�ҽ��ϴ�!\n");
            printf("�湮�� ����� ��: %d\n", visitedCount);
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

// �ʺ� �켱 Ž�� �˰���
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
            printf("\n��ǥ�� ã�ҽ��ϴ�!\n");
            printf("�湮�� ����� ��: %d\n", visitedCount);
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

// ���� �Լ�
int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = 11;
    graph->adjLists = (struct Node**)malloc(graph->numVertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    // �׷��� �ʱ�ȭ
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

    // �޴� ����
    int choice = 0;
    while (choice != 3) {
        printf("\n1: ���� �켱 Ž��\n2: �ʺ� �켱 Ž��\n3: ����\n");
        printf("�޴� �Է�: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int start, goal;
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf("%d %d", &start, &goal);
            DFS(graph, start, goal);
            for (int i = 0; i < graph->numVertices; i++) {
                graph->visited[i] = 0;
            }
            break;
        }
        case 2: {
            int start, goal;
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf("%d %d", &start, &goal);
            BFS(graph, start, goal);
            for (int i = 0; i < graph->numVertices; i++) {
                graph->visited[i] = 0;
            }
            break;
        }
        case 3:
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �����ϼ���.\n");
        }
    }

    return 0;
}
