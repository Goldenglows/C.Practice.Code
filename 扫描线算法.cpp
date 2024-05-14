#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// ��ʾһ���ߵĽṹ��
struct Edge {
    int y_min; // �ߵ���ʼ������
    int y_max; // �ߵĽ���������
    float x;   // ����ɨ���ߵĽ���ĺ�����
    float dx;  // �����������ϵı仯��

    // �Զ�������ߵ���Ϣ�ĺ���
    void printEdgeInfo() {
        cout << "P" << y_min << "P" << y_max << " (" << x << ", " << dx << ", " << y_max << ")";
    }
};

// �ߵıȽϺ�������������
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.x < e2.x;
}

// ����ߵ�ET����
void insertEdge(vector<vector<Edge>>& ET, Edge& edge) {
    // ȷ��y_min��y_max��ET��������Ч��Χ��
    edge.y_min = max(0, min(edge.y_min, static_cast<int>(ET.size()) - 1));
    edge.y_max = max(0, min(edge.y_max, static_cast<int>(ET.size()) - 1));
    // ����ߵ�ET����
    for (int y = edge.y_min; y <= edge.y_max; ++y) {
        ET[y].push_back(edge);
    }
}

// ��ET���еı߲��뵽AET����
void insertETtoAET(vector<vector<Edge>>& ET, vector<Edge>& AET, int y) {
    // ȷ��y��ET��������Ч��Χ��
    if (y >= 0 && y < static_cast<int>(ET.size())) {
        for (Edge& edge : ET[y]) {
            AET.push_back(edge);
        }
        sort(AET.begin(), AET.end(), compareEdges);
    }
}
// ɨ��������㷨��������
void scanLine(vector<vector<Edge>>& ET, vector<Edge>& AET) {
    int y = 0;
    cout << "ET:" << endl;
    while (y < static_cast<int>(ET.size()) || !AET.empty()) {
        if (y < static_cast<int>(ET.size()) && !ET[y].empty()) {
            // ���ET���еı���Ϣ
            cout << "y=" << y << ": ";
            for (Edge& edge : ET[y]) {
                edge.printEdgeInfo();
                cout << "��";
            }
            cout << endl;
            insertETtoAET(ET, AET, y);
        }
        if (!AET.empty() && AET.size() % 2 == 0) {
            // ����AET�еı�
            for (size_t i = 0; i < AET.size(); i += 2) {
                int x_start = (int)ceil(AET[i].x);
                int x_end = (int)floor(AET[i + 1].x);
                // �����Ч�������
                for (int x = x_start; x <= x_end; ++x) {
                    cout << "�����ڣ� (" << x << ", " << y << ")" << endl;
                }
            }
        }
        else {
            // AET���еı���������ż��������������
        }
        y++;
        // ɾ��AET��y_max����y�ı�
        AET.erase(remove_if(AET.begin(), AET.end(), [y](const Edge& e) { return e.y_max == y; }), AET.end());
        // ����AET�бߵ�x����
        for (Edge& edge : AET) {
            edge.x += edge.dx;
        }
    }
}
int main() {
    // ����ET���AET��
    vector<vector<Edge>> ET(9); // ���������귶ΧΪ0-8
    vector<Edge> AET;

    // �������ݣ���ET���в���һЩ��
    Edge edge1 = { 1, 6, 5, -0.5 }; // ʾ����1
    Edge edge2 = { 5, 4, 6, 0.4 };  // ʾ����2
    Edge edge3 = { 1, 6, 7, -0.4 }; // ʾ����3
    Edge edge4 = { 1, 2, 8, 2/3}; // ʾ����4
    Edge edge5 = { 6, 8, 8, -3 }; // ʾ����5
    Edge edge6 = { 2, 3, 2, 2 }; // ʾ����6

    insertEdge(ET, edge1);
    insertEdge(ET, edge2);
    insertEdge(ET, edge3);
    insertEdge(ET, edge4);
    insertEdge(ET, edge5);
    insertEdge(ET, edge6);

    // ִ��ɨ�����㷨
    scanLine(ET, AET);

    return 0;
}