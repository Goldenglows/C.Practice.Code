#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// �����Ľṹ��
struct Point {
    int x, y;
};

void midpoint_clip(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax) {
    // �����߶ε������Ͳü����ڵı߽�����
    int dx = x2 - x1, dy = y2 - y1;
    int p[4], q[4];
    float t1 = 0, t2 = 1;

    // ��ʼ�������Ͳü����ڵı߽�����
    p[0] = -dx;
    p[1] = dx;
    p[2] = -dy;
    p[3] = dy;

    q[0] = x1 - xmin;
    q[1] = xmax - x1;
    q[2] = y1 - ymin;
    q[3] = ymax - y1;

    // ���� t1 �� t2
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            cout << "�߶��ڲü������ⲿ�����ɼ�" << endl;
            return;
        }

        float t = (float)q[i] / p[i];

        if (p[i] < 0) {
            if (t > t2) {
                cout << "�߶��ڲü������ⲿ�����ɼ�" << endl;
                return;
            }
            else if (t > t1) {
                t1 = t;
            }
        }
        else if (p[i] > 0) {
            if (t < t1) {
                cout << "�߶��ڲü������ⲿ�����ɼ�" << endl;
                return;
            }
            else if (t < t2) {
                t2 = t;
            }
        }
    }

    // ���� t1 �� t2 ����ü���Ķ˵�����
    int clippedx1 = x1 + t1 * dx;
    int clippedy1 = y1 + t1 * dy;
    int clippedx2 = x1 + t2 * dx;
    int clippedy2 = y1 + t2 * dy;

    // ����ü���Ķ˵�����
    cout << "�ü���Ķ˵㣺" << endl;
    cout << "���:  (" << clippedx1 << ", " << clippedy1 << ")" << endl;
    cout << "�յ�:  (" << clippedx2 << ", " << clippedy2 << ")" << endl;
}

int main() {
    int xmin, ymin, xmax, ymax;
    int x1, y1, x2, y2;

    cout << "������ü����ڵ����½����꣨xmin, ymin����";
    cin >> xmin >> ymin;
    cout << "������ü����ڵ����Ͻ����꣨xmax, ymax����";
    cin >> xmax >> ymax;

    // ����˵�ʹ��ڴ�С
    cout << "������˵�1 (x y): ";
    cin >> x1 >> y1;
    cout << "������˵�2 (x y): ";
    cin >> x1 >> y2;

    // �����е�ָ��㷨���вü�
    midpoint_clip(x1, y1, x2, y2, xmin, ymin, xmax, ymax);

    return 0;
}