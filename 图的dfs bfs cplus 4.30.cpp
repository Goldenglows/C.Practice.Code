#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph {
	int V;
	list<int>* adj;

public:
	Graph(int V);
	void addEdge(int v, int w);
	void DFS(int v);
	void BFS(int v);

private:
	// ˽�и�������
	void DFSUtil(int v, bool visited[]);

};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void Graph::DFS(int v) {
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	DFSUtil(v, visited);
	
}

void Graph::DFSUtil(int v, bool visited[]) {
	visited[v] = true;
	cout << v << " ";

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		if (!visited[*i])
			DFSUtil(*i, visited);
	}
}

void Graph::BFS(int v) {
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	queue<int> queue;

	visited[v] = true;
	queue.push(v);

	while (!queue.empty()) {
		v = queue.front();
		cout << v << " ";
		queue.pop();

		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i) {
			if (!visited[*i]) {
				visited[*i] = true;
				queue.push(*i);
			}
		}
	}
}

int main() {
	/*int n;
	int v, m;*/

	Graph g(4); // ����һ���� 4 �������ͼ

	// ��ӱ�
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "������ȱ��� (DFS) �Ӷ��� 2 ��ʼ��\n";
	g.DFS(2);
	cout << "\n\n������ȱ��� (BFS) �Ӷ��� 2 ��ʼ��\n";
	g.BFS(2);

	return 0;

}