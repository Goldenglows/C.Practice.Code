#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 表示一条边的结构体
struct Edge {
    int y_min; // 边的起始纵坐标
    int y_max; // 边的结束纵坐标
    float x;   // 边与扫描线的交点的横坐标
    float dx;  // 边在纵坐标上的变化率

    // 自定义输出边的信息的函数
    void printEdgeInfo() {
        cout << "P" << y_min << "P" << y_max << " (" << x << ", " << dx << ", " << y_max << ")";
    }
};

// 边的比较函数，用于排序
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.x < e2.x;
}

// 插入边到ET表中
void insertEdge(vector<vector<Edge>>& ET, Edge& edge) {
    // 确保y_min和y_max在ET向量的有效范围内
    edge.y_min = max(0, min(edge.y_min, static_cast<int>(ET.size()) - 1));
    edge.y_max = max(0, min(edge.y_max, static_cast<int>(ET.size()) - 1));
    // 插入边到ET表中
    for (int y = edge.y_min; y <= edge.y_max; ++y) {
        ET[y].push_back(edge);
    }
}

// 将ET表中的边插入到AET表中
void insertETtoAET(vector<vector<Edge>>& ET, vector<Edge>& AET, int y) {
    // 确保y在ET向量的有效范围内
    if (y >= 0 && y < static_cast<int>(ET.size())) {
        for (Edge& edge : ET[y]) {
            AET.push_back(edge);
        }
        sort(AET.begin(), AET.end(), compareEdges);
    }
}
// 扫描线填充算法的主函数
void scanLine(vector<vector<Edge>>& ET, vector<Edge>& AET) {
    int y = 0;
    cout << "ET:" << endl;
    while (y < static_cast<int>(ET.size()) || !AET.empty()) {
        if (y < static_cast<int>(ET.size()) && !ET[y].empty()) {
            // 输出ET表中的边信息
            cout << "y=" << y << ": ";
            for (Edge& edge : ET[y]) {
                edge.printEdgeInfo();
                cout << "→";
            }
            cout << endl;
            insertETtoAET(ET, AET, y);
        }
        if (!AET.empty() && AET.size() % 2 == 0) {
            // 处理AET中的边
            for (size_t i = 0; i < AET.size(); i += 2) {
                int x_start = (int)ceil(AET[i].x);
                int x_end = (int)floor(AET[i + 1].x);
                // 输出有效填充区段
                for (int x = x_start; x <= x_end; ++x) {
                    cout << "交点在： (" << x << ", " << y << ")" << endl;
                }
            }
        }
        else {
            // AET表中的边数量不是偶数，处理错误情况
        }
        y++;
        // 删除AET中y_max等于y的边
        AET.erase(remove_if(AET.begin(), AET.end(), [y](const Edge& e) { return e.y_max == y; }), AET.end());
        // 更新AET中边的x坐标
        for (Edge& edge : AET) {
            edge.x += edge.dx;
        }
    }
}
int main() {
    // 创建ET表和AET表
    vector<vector<Edge>> ET(9); // 假设纵坐标范围为0-8
    vector<Edge> AET;

    // 测试数据，向ET表中插入一些边
    Edge edge1 = { 1, 6, 5, -0.5 }; // 示例边1
    Edge edge2 = { 5, 4, 6, 0.4 };  // 示例边2
    Edge edge3 = { 1, 6, 7, -0.4 }; // 示例边3
    Edge edge4 = { 1, 2, 8, 2/3}; // 示例边4
    Edge edge5 = { 6, 8, 8, -3 }; // 示例边5
    Edge edge6 = { 2, 3, 2, 2 }; // 示例边6

    insertEdge(ET, edge1);
    insertEdge(ET, edge2);
    insertEdge(ET, edge3);
    insertEdge(ET, edge4);
    insertEdge(ET, edge5);
    insertEdge(ET, edge6);

    // 执行扫描线算法
    scanLine(ET, AET);

    return 0;
}