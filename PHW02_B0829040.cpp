#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<cmath>
using namespace std;
class Queue{
    private:
        int v;
        int front, back;
        int *queue;

    public:
        Queue(int V);
        bool IsEmpty();
        void enqueue(int j);
        void dequeue();
        int getFront();
};

Queue::Queue(int V){
    v = V;
    queue = new int[v];
    front = -1;
    back = -1;
}

bool Queue::IsEmpty(){
    return (front == back);
}

void Queue::enqueue(int j){
    queue[++back] = j;
}

void Queue::dequeue(){
    front++;
}

int Queue::getFront(){
    return queue[front + 1];
}


struct AdjListNode{
    int v;
    struct AdjListNode *pNext;
};

struct AdjList{
    struct AdjListNode *head;
};

class AdjacencyList{
    private:
        int v;
        struct AdjList *array;
    public:
        AdjacencyList(int v);
        AdjListNode *newAdjListNode(int j){
            AdjListNode *newNode = new AdjListNode;
            newNode->v = j;
            newNode->pNext = NULL;
            return newNode;
        }
        void AddEdge(int i, int j);
        void PrintList();
};

AdjacencyList::AdjacencyList(int v){
    this->v = v;
    array = new AdjList[v];
    for (int i = 0; i < v; i++){
        array[i].head = NULL;
    }
}

void AdjacencyList::AddEdge(int i, int j){
    AdjListNode *newNode = newAdjListNode(j);
    newNode->pNext = array[i].head;
    array[i].head = newNode;
    /*AdjListNode *newNode = newAdjListNode(i);
    newNode->pNext = array[j].head;
    array[j].head = newNode;*/
}

void AdjacencyList::PrintList(){
    cout << "Adjacency Lists: " << endl;
    for (int i = 0; i < v; ++i){
        AdjListNode *List = array[i].head;
        cout << i << "-->";
        while(List){
            cout << List->v << "->";
            List = List->pNext;
        }
        cout << "NULL" << endl;
    }
}

class DFSBFS{
    private:
        int v;
        bool *visited;
        int **a;
    public:
        DFSBFS(int V);
        void AddEdge(int i, int j);
        void DFSvisit(int k);
        void DFS();
        void BFS();
        void Print();
};

DFSBFS::DFSBFS(int V){
    v = V;
    visited = new bool[v];
    for (int i = 0; i < v; i++){
        visited[i] = false;
    }

    a = new int *[v];
    for (int i = 0; i < v; i++){
        a[i] = new int[v];
    }
    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            a[i][j] = 0;
        }
    }
}

void DFSBFS::AddEdge(int i, int j){
    a[i][j] = 1;
}

void DFSBFS::DFSvisit(int k){
    visited[k] = true;
    for(int i=0;i<v; i++){
        if(a[k][i]==1 && visited[i]==false){
            a[k][i] = 2;
            a[i][k] = 2;
            DFSvisit(i);
        }
    }
}

void DFSBFS::DFS(){
    for (int i = 0; i < v; i++){
        if (visited[i] == false){
            DFSvisit(i);
        }
    }
    cout << "DFS Adjacency Matrix:" << endl;
    Print();
}

void DFSBFS::BFS(){
    Queue queue(v);
    for (int i = 0; i < v; i++)
    {
        if(visited[i]==false){
            queue.enqueue(i);
            visited[i] = true;
        }
        while (!queue.IsEmpty())
        {
            int vis = queue.getFront();
            queue.dequeue();
            for (int i = 0; i < v; i++)
            {
                if (a[vis][i] == 1 && (visited[i] == false))
                {
                    queue.enqueue(i);
                    visited[i] = true;
                    a[vis][i] = 2;
                    a[i][vis] = 2;
                }
            }
        }
    }
    cout << "BFS Adjacency Matrix:" << endl;
    Print();
}

void DFSBFS::Print(){
    for(int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            if(a[i][j]==2){
                a[i][j] = 1;
            }
            else if(a[i][j]==1){
                a[i][j] = 0;
            }
        }
    }
    cout << "    ";
    for (int i = 0; i < v; i++){
        cout << i << " ";
        }
        cout << endl;

        cout << "    ";
        for (int i = 0; i < v; i++){
            cout << "- ";
        }
        cout << endl;

    for (int i = 0; i < v; i++){
        cout << i << " | ";
        for (int j = 0; j < v; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int v, e;
    cout << "The number of nodes: "; cin >> v;
    cout << "The number of edges: "; cin >> e;
    cout << endl;

    srand(time(0));
    int **matrix;
    matrix = new int *[v];
    for (int i = 0; i < v; i++){
        matrix[i] = new int[v];
    }

    if (0 <= e && e <= (v * v - v) / 2){
        for (int i = 0; i < v; i++){ //初始都assign 0
            for (int j = 0; j < v; j++){
                matrix[i][j] = 0;
            }
        }
        for (int k = 0; k < e; k++){ //assign 1
            int i = rand() % v + 0;
            int j = rand() % v + 0;
            if (matrix[i][j] == 1 || i == j){
                e++;
            }
            else{
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }

        //Adjacency Matrix
        cout << "Adjacency Matrix :" << endl;
        cout << "    ";
        for (int i = 0; i < v; i++){
            cout << i << " ";
        }
        cout << endl;

        cout << "    ";
        for (int i = 0; i < v; i++){
            cout << "- ";
        }
        cout << endl;

        for (int i = 0; i < v; i++)
        {
            cout << i << " | ";
            for (int j = 0; j < v; j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        //Adjacency List
        AdjacencyList AdjacencyList(v);
        for (int i = 0; i < v; i++){
            for(int j = 0; j < v; j++){
                if(matrix[i][j]==1){
                    AdjacencyList.AddEdge(i, j);
                }
            }
        }
        AdjacencyList.PrintList();
        cout << endl;

        //DFS
        DFSBFS dfs(v);
        for (int i = 0; i < v; i++){
            for(int j = 0; j < v; j++){
                if(matrix[i][j]==1){
                    dfs.AddEdge(i, j);
                }
            }
        }
        dfs.DFS();
        cout << endl;

        //BFS
        DFSBFS bfs(v);
        for (int i = 0; i < v; i++){
            for (int j = 0; j < v; j++){
                if(matrix[i][j]==1){
                    bfs.AddEdge(i, j);
                }
            }
        }
        bfs.BFS();
    }
    else{
        cout << "The number of edges are illegal." << endl;
    }
}