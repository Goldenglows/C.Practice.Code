#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// �����Ľṹ��
struct Point {
    double x, y;
};

// Liang-Barsky�㷨����
void LiangBarsky(Point p1, Point p2, double xmin, double xmax, double ymin, double ymax) {
    // �����ֵ
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double p[4] = { -dx, dx, -dy, dy };
    double q[4] = { p1.x - xmin, xmax - p1.x, p1.y - ymin, ymax - p1.y };
    double u1 = 0.0, u2 = 1.0;

    // �������u1��u2
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

    // �ж��Ƿ���Ҫ�ü�
    if (u1 > u2) {
        return;
    }

    // ����ü���Ķ˵�
    Point clippedP1, clippedP2;
    clippedP1.x = p1.x + u1 * dx;
    clippedP1.y = p1.y + u1 * dy;
    clippedP2.x = p1.x + u2 * dx;
    clippedP2.y = p1.y + u2 * dy;

    // ����ü���Ķ˵�
    cout << "�ü�����߶ζ˵㣺" << endl;
    cout << "���: (" << clippedP1.x << ", " << clippedP1.y << ")" << endl;
    cout << "�յ�: (" << clippedP2.x << ", " << clippedP2.y << ")" << endl;

}

int main() {
    Point p1, p2;
    double xmin, xmax, ymin, ymax;

    cout << "������ü����ڵ����½����꣨xmin, ymin����";
    cin >> xmin >> ymin;
    cout << "������ü����ڵ����Ͻ����꣨xmax, ymax����";
    cin >> xmax >> ymax;

    // ����˵�ʹ��ڴ�С
    cout << "������˵�1 (x y): ";
    cin >> p1.x >> p1.y;
    cout << "������˵�2 (x y): ";
    cin >> p2.x >> p2.y;

    // ����Liang-Barsky�㷨
    LiangBarsky(p1, p2, xmin, xmax, ymin, ymax);

    return 0;
}