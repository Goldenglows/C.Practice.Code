#include <iostream>
#include <vector>
#include <cmath>
#include <graphics.h>

//�е�Բ�㷨������뾶��Բ��Ĭ����ԭ�㣬�������Բ�ϵ����е�

// �����Ľṹ��
struct Point {
    int x;
    int y;
    // ���캯��,�򻯲���
    Point(int xc, int yc) : x(xc), y(yc) {}
};

// ���Ƶ�ĺ���
void print_circle(int x, int y) {
    std::cout << "(" << x << ", " << y << ")\n";
}

void mid_circle(int circle_x, int circle_y, int R) {
    int x = R;
    int y = 0;
    int p = 1 - R;

    //����Բ�ϵ����е�
    std::vector<Point> points;

    //���Ƴ�ʼ��
    print_circle(circle_x + x, circle_y + y);

    while (x > y) {
        y++;
        if (p <= 0)
            p = p + 2 * y + 1;
        else {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }

        // Check if the x and y are inside the window, then print
        // their symmetric points
        if (x < y)
            break;

        //���Ƶ�ǰ��İ˶ԳƵ㣬�����浽������
        points.push_back(Point(circle_x + x, circle_y + y));
        points.push_back(Point(circle_x - x, circle_y + y));
        points.push_back(Point(circle_x + x, circle_y - y));
        points.push_back(Point(circle_x - x, circle_y - y));
        points.push_back(Point(circle_x + y, circle_y + x));
        points.push_back(Point(circle_x - y, circle_y + x));
        points.push_back(Point(circle_x + y, circle_y - x));
        points.push_back(Point(circle_x - y, circle_y - x));
    }

    std::cout << "��ӡ�����е��������£�" << std::endl;

    //���Բ�ϵ����е�
    for (const auto& point : points) {
        print_circle(point.x, point.y);
    }
}

int main() {
    int R;

    std::cout << "����뾶: ";
    std::cin >> R;

    //Բ������Ĭ��Ϊ (0, 0)
    mid_circle(0, 0, R);

    return 0;
}