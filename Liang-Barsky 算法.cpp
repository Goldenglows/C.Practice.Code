#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// 定义点的结构体
struct Point {
    double x, y;
};

// Liang-Barsky算法函数
void LiangBarsky(Point p1, Point p2, double xmin, double xmax, double ymin, double ymax) {
    // 计算差值
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double p[4] = { -dx, dx, -dy, dy };
    double q[4] = { p1.x - xmin, xmax - p1.x, p1.y - ymin, ymax - p1.y };
    double u1 = 0.0, u2 = 1.0;

    // 计算参数u1和u2
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0) {
                return;
            }
        }
        else {
            double r = q[i] / p[i];
            if (p[i] < 0) {
                u1 = max(u1, r);
            }
            else {
                u2 = min(u2, r);
            }
        }
    }

    // 判断是否需要裁剪
    if (u1 > u2) {
        return;
    }

    // 计算裁剪后的端点
    Point clippedP1, clippedP2;
    clippedP1.x = p1.x + u1 * dx;
    clippedP1.y = p1.y + u1 * dy;
    clippedP2.x = p1.x + u2 * dx;
    clippedP2.y = p1.y + u2 * dy;

    // 输出裁剪后的端点
    cout << "裁剪后的线段端点：" << endl;
    cout << "起点: (" << clippedP1.x << ", " << clippedP1.y << ")" << endl;
    cout << "终点: (" << clippedP2.x << ", " << clippedP2.y << ")" << endl;

}

int main() {
    Point p1, p2;
    double xmin, xmax, ymin, ymax;

    cout << "请输入裁剪窗口的左下角坐标（xmin, ymin）：";
    cin >> xmin >> ymin;
    cout << "请输入裁剪窗口的右上角坐标（xmax, ymax）：";
    cin >> xmax >> ymax;

    // 输入端点和窗口大小
    cout << "请输入端点1 (x y): ";
    cin >> p1.x >> p1.y;
    cout << "请输入端点2 (x y): ";
    cin >> p2.x >> p2.y;

    // 调用Liang-Barsky算法
    LiangBarsky(p1, p2, xmin, xmax, ymin, ymax);

    return 0;
}