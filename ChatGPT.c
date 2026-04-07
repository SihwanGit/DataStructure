#include <stdio.h>
#include <stdlib.h>

#define ROWS 7
#define COLS 7

int dir[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
}; //노드의 상하좌우를 의미함.

typedef struct { //x,y좌표
    int x, y;
} Point;

typedef struct TreeNode { //트리 노드
    Point point; //좌표
    int data; //얘는 벽 or 길
    struct TreeNode* left, * right;
} TreeNode;

typedef struct { //큐
    TreeNode* nodes[ROWS * COLS];
    int front, rear;
} QueueType;

void init_queue(QueueType* q) {
    q->front = -1;
    q->rear = -1;
}

int is_empty(QueueType* q) {
    if (q->front == q->rear) return 1; //비어 있으면 1, 아니면 0
    else return 0;
}

void enqueue(QueueType* q, TreeNode* n) {
    //이 코드는 아무리 데이터가 많이 들어와도 최대 7x7개이므로 full은 굳이 검사할 필요가 없다.
    q->nodes[++q->rear] = n; //말그대로 TreeNode 삽입
}

TreeNode* dequeue(QueueType* q) {
    if (is_empty(q) == 1) {
        printf("큐가 공백상태입니다.\n");
        return NULL; //공백이면 NULL 반환
    }
    else {
        return q->nodes[++q->front];
    }
}

TreeNode* createNode(Point point, int data) { //개별적인 트리노드 생성
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    t->data = data;
    t->point = point;
    t->right = NULL;
    t->left = NULL;
    return t;
}

void printMaze(int maze[ROWS][COLS], Point current) { //출력함수: 0은 길, 1은 #, 2는 지나온 길
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == current.x && j == current.y) // 현재 위치
                printf("C ");
            else if (maze[i][j] == 2) // 지나온 길
                printf(". ");
            else if (maze[i][j] == 1) // 벽
                printf("# ");
            else
                printf("0 "); // 길
        }
        printf("\n");
    }
    printf("\n");
}

TreeNode* convertToTree(int maze[ROWS][COLS], Point start) { //반복을 이용한 트리 변환 코드
    Point s = start;
    TreeNode* root = createNode(s, 0);
//    QueueType q;
//    init_queue(&q);
//    enqueue(&q, root);
    maze[start.y][start.x] = 2; // 지나온 길
    printf("Root Node: (%d, %d)\n", start.y, start.x);

    TreeNode* current = root;
    for (int i = 0; i < 4; i++) {
        int ny = current->point.x + dir[i][0];
        int nx = current->point.y + dir[i][1];
        //위 -> 아래 -> 왼쪽 -> 오른쪽 순으로 검사
        if (nx >= 0 && ny >= 0 && nx < ROWS && ny < COLS && maze[ny][nx] == 0) {
        //x,y좌표가 행렬 안에 있고, 미로의 해당 좌표의 데이터가 0이면..
            TreeNode* newNode = createNode((Point) { ny, nx }, 0); //그 좌표를 가진 노드를 생성
            maze[ny][nx] = 2;
            if (i < 2) {
                current->left = newNode; //x좌표 변환은 왼쪽에 저장
                printf("Adding Node: (%d, %d) as a child of node: (%d, %d)\n", newNode->point.y, newNode->point.x, current->point.y, current->point.x);
                convertToTree()
            }
            else {
                current->right = newNode; //y좌표 변환은 오른쪽에 저장
                printf("Adding Node: (%d, %d) as a child of node: (%d, %d)\n", newNode->point.y, newNode->point.x, current->point.y, current->point.x);
            }

            //enqueue(&q, newNode);
        }
    }
    printf("\n");
    return root;
}

// level_order (BFS)
int level_order(TreeNode* ptr, int maze[ROWS][COLS], Point goal) { //레벨 순회
    if (!ptr) return 0;
    QueueType q;
    init_queue(&q);
    enqueue(&q, ptr);

    while (is_empty(&q) != 1) {
        TreeNode* current = dequeue(&q);
        printf("Current Position: (%d , %d)\n", current->point.y, current->point.x);
        printMaze(maze, current->point);
        if (current->point.x == goal.x && current->point.y == goal.y) //좌표가 같으면 1리턴(도착하면 1리턴)
            return 1;
        if (current->left != NULL)  //left가 널이 아니면
            enqueue(&q, current->left);
        if (current->right != NULL) //right가 널이 아니면
            enqueue(&q, current->right);
    }
    return 0; //도착하지 못하고 끝나면 0리턴
}

int main() {
    // test case (1): path를 찾는 케이스
    int maze1[ROWS][COLS] = {
        {0, 1, 0, 0, 0, 0, 1},
        {0, 0, 1, 1, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 1},
        {0, 1, 0, 0, 0, 0, 0}
    };

    Point start = { 0, 0 };
    Point goal = { 6, 6 };

    TreeNode* root1 = convertToTree(maze1, start);
    printf("Level Order Traversal:\n");
    int path_found = level_order(root1, maze1, goal);

    if (path_found == 1) {
        printf("Path found!\n");
    }
    else {
        printf("No path found\n");
    }
    printf("\n");

    // test case (2): path를 못찾는 케이스
    int maze2[ROWS][COLS] = {
       {0, 1, 0, 0, 0, 0, 1},
       {0, 0, 1, 1, 0, 1, 1},
       {1, 0, 1, 0, 0, 0, 1},
       {0, 0, 0, 0, 1, 0, 1},
       {0, 1, 0, 1, 0, 1, 1},
       {1, 1, 1, 1, 1, 0, 1},
       {0, 1, 0, 0, 0, 0, 0}
    };

    TreeNode* root2 = convertToTree(maze2, start);
    printf("Level Order Traversal:\n");
    path_found = level_order(root2, maze2, goal);
    if (path_found == 1) {
        printf("Path found!\n");
    }
    else {
        printf("No path found\n");
    }
    return 0;
}
