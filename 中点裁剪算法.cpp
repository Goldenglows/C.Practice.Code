#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// 定义点的结构体
struct Point {
    int x, y;
};

void midpoint_clip(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax) {
    // 计算线段的增量和裁剪窗口的边界增量
    int dx = x2 - x1, dy = y2 - y1;
    int p[4], q[4];
    float t1 = 0, t2 = 1;

    // 初始化增量和裁剪窗口的边界增量
    p[0] = -dx;
    p[1] = dx;
    p[2] = -dy;
    p[3] = dy;

    q[0] = x1 - xmin;
    q[1] = xmax - x1;
    q[2] = y1 - ymin;
    q[3] = ymax - y1;

    // 计算 t1 和 t2
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            cout << "线段在裁剪窗口外部，不可见" << endl;
            return;
        }

        float t = (float)q[i] / p[i];

        if (p[i] < 0) {
            if (t > t2) {
                cout << "线段在裁剪窗口外部，不可见" << endl;
                return;
            }
            else if (t > t1) {
                t1 = t;
            }
        }
        else if (p[i] > 0) {
            if (t < t1) {
                cout << "线段在裁剪窗口外部，不可见" << endl;
                return;
            }
            else if (t < t2) {
                t2 = t;
            }
        }
    }

    // 根据 t1 和 t2 计算裁剪后的端点坐标
    int clippedx1 = x1 + t1 * dx;
    int clippedy1 = y1 + t1 * dy;
    int clippedx2 = x1 + t2 * dx;
    int clippedy2 = y1 + t2 * dy;

    // 输出裁剪后的端点坐标
    cout << "裁剪后的端点：" << endl;
    cout << "起点:  (" << clippedx1 << ", " << clippedy1 << ")" << endl;
    cout << "终点:  (" << clippedx2 << ", " << clippedy2 << ")" << endl;
}

int main() {
    int xmin, ymin, xmax, ymax;
    int x1, y1, x2, y2;

    cout << "请输入裁剪窗口的左下角坐标（xmin, ymin）：";
    cin >> xmin >> ymin;
    cout << "请输入裁剪窗口的右上角坐标（xmax, ymax）：";
    cin >> xmax >> ymax;

    // 输入端点和窗口大小
    cout << "请输入端点1 (x y): ";
    cin >> x1 >> y1;
    cout << "请输入端点2 (x y): ";
    cin >> x1 >> y2;

    // 调用中点分割算法进行裁剪
    midpoint_clip(x1, y1, x2, y2, xmin, ymin, xmax, ymax);

    return 0;
}