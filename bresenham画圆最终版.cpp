#include <iostream>
#include <vector>
#include <cmath>

// �����Ľṹ��
struct Point {
    int x;
    int y;
    // ���캯��,�򻯲���
    Point(int circle_X, int circle_Y) : x(circle_X), y(circle_Y) {}
};

// ���Ƶ�ĺ���
void print_circle(int x, int y) {
    std::cout << "(" << x << ", " << y << ")\n";
}

void bresenhamcircle(int circle_x, int circle_y, int R) {
    int x = 0;
    int y = R;
    int p = 3 - 2 * R;

    //����Բ�ϵ����е�
    std::vector<Point> points;

    //���Ƴ�ʼ��
    print_circle(circle_x, circle_y + R);

    while (x < y) {
        if (p < 0) {
            p += 4 * x + 6;
        }
        else {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;

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
    bresenhamcircle(0, 0, R);

    return 0;
}