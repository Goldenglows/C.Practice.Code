#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// ����ü����ڵ�������
const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

// ������������
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

// Cohen-Sutherland �ü��㷨
void Cohen_Sutherland(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax) {
    int code0 = code_area(x0, y0, xmin, xmax, ymin, ymax);
    int code1 = code_area(x1, y1, xmin, xmax, ymin, ymax);
    bool accept = false;

    while (true) {
        if (!(code0 | code1)) { // ������㶼�ڲü�������
            accept = true;
            break;
        }
        else if (code0 & code1) { // ������㶼�ڲü�������
            break;
        }
        else {
            double x, y;
            int codeOut = code0 ? code0 : code1;

            // �����ཻ�ı߽�����µĶ˵�
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
        cout << "�ü�����߶ζ˵㣺" << endl;
        cout << "���: (" << x0 << ", " << y0 << ")" << endl;
        cout << "�յ�: (" << x1 << ", " << y1 << ")" << endl;
    }
    else {
        cout << "�߶���ȫ�ڲü�������" << endl;
    }
}

int main() {
    // �����û�����ü����ڵĴ�С
    double xmin, xmax, ymin, ymax;
    cout << "������ü����ڵ����½����꣨xmin, ymin����";
    cin >> xmin >> ymin;
    cout << "������ü����ڵ����Ͻ����꣨xmax, ymax����";
    cin >> xmax >> ymax;

    // �����û�������ü����߶ζ˵�
    double x0, y0, x1, y1;
    cout << "��������ü��߶ε�������꣨x0, y0����";
    cin >> x0 >> y0;
    cout << "��������ü��߶ε��յ����꣨x1, y1����";
    cin >> x1 >> y1;

    // ִ�� Cohen-Sutherland �ü��㷨
    Cohen_Sutherland(x0, y0, x1, y1, xmin, xmax, ymin, ymax);

    return 0;
}