#include <iostream>
#include <vector>
#include <cmath>

// 定义点的结构体
struct Point {
    int x;
    int y;
    // 构造函数,简化操作
    Point(int circle_X, int circle_Y) : x(circle_X), y(circle_Y) {}
};

// 绘制点的函数
void print_circle(int x, int y) {
    std::cout << "(" << x << ", " << y << ")\n";
}

void bresenhamcircle(int circle_x, int circle_y, int R) {
    int x = 0;
    int y = R;
    int p = 3 - 2 * R;

    //保存圆上的所有点
    std::vector<Point> points;

    //绘制初始点
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

        //绘制当前点的八对称点，并保存到数组中
        points.push_back(Point(circle_x + x, circle_y + y));
        points.push_back(Point(circle_x - x, circle_y + y));
        points.push_back(Point(circle_x + x, circle_y - y));
        points.push_back(Point(circle_x - x, circle_y - y));
        points.push_back(Point(circle_x + y, circle_y + x));
        points.push_back(Point(circle_x - y, circle_y + x));
        points.push_back(Point(circle_x + y, circle_y - x));
        points.push_back(Point(circle_x - y, circle_y - x));
    }

    std::cout << "打印出所有点坐标如下：" << std::endl;

    //输出圆上的所有点
    for (const auto& point : points) {
        print_circle(point.x, point.y);
    }
}

int main() {
    int R;

    std::cout << "输入半径: ";
    std::cin >> R;

    //圆心坐标默认为 (0, 0)
    bresenhamcircle(0, 0, R);

    return 0;
}