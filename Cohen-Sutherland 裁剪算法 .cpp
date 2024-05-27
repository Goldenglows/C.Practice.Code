#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// 定义裁剪窗口的区域码
const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

// 计算点的区域码
int code_area(double x, double y, double xmin, double xmax, double ymin, double ymax) {
    int code = INSIDE;

    if (x < xmin) {
        code |= LEFT;
    }
    else if (x > xmax) {
        code |= RIGHT;
    }
    if (y < ymin) {
        code |= BOTTOM;
    }
    else if (y > ymax) {
        code |= TOP;
    }

    return code;
}

// Cohen-Sutherland 裁剪算法
void Cohen_Sutherland(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax) {
    int code0 = code_area(x0, y0, xmin, xmax, ymin, ymax);
    int code1 = code_area(x1, y1, xmin, xmax, ymin, ymax);
    bool accept = false;

    while (true) {
        if (!(code0 | code1)) { // 如果两点都在裁剪窗口内
            accept = true;
            break;
        }
        else if (code0 & code1) { // 如果两点都在裁剪窗口外
            break;
        }
        else {
            double x, y;
            int codeOut = code0 ? code0 : code1;

            // 根据相交的边界计算新的端点
            if (codeOut & TOP) {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            }
            else if (codeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            }
            else if (codeOut & RIGHT) {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            }
            else {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            if (codeOut == code0) {
                x0 = x;
                y0 = y;
                code0 = code_area(x0, y0, xmin, xmax, ymin, ymax);
            }
            else {
                x1 = x;
                y1 = y;
                code1 = code_area(x1, y1, xmin, xmax, ymin, ymax);
            }
        }
    }

    if (accept) {
        cout << "裁剪后的线段端点：" << endl;
        cout << "起点: (" << x0 << ", " << y0 << ")" << endl;
        cout << "终点: (" << x1 << ", " << y1 << ")" << endl;
    }
    else {
        cout << "线段完全在裁剪窗口外" << endl;
    }
}

int main() {
    // 接受用户输入裁剪窗口的大小
    double xmin, xmax, ymin, ymax;
    cout << "请输入裁剪窗口的左下角坐标（xmin, ymin）：";
    cin >> xmin >> ymin;
    cout << "请输入裁剪窗口的右上角坐标（xmax, ymax）：";
    cin >> xmax >> ymax;

    // 接受用户输入待裁剪的线段端点
    double x0, y0, x1, y1;
    cout << "请输入待裁剪线段的起点坐标（x0, y0）：";
    cin >> x0 >> y0;
    cout << "请输入待裁剪线段的终点坐标（x1, y1）：";
    cin >> x1 >> y1;

    // 执行 Cohen-Sutherland 裁剪算法
    Cohen_Sutherland(x0, y0, x1, y1, xmin, xmax, ymin, ymax);

    return 0;
}