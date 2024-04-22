#include <iostream>
#include <vector>
#include <cmath>
#include <graphics.h>

//中点圆算法，输入半径，圆心默认在原点，输出画的圆上的所有点

// 定义点的结构体
struct Point {
    int x;
    int y;
    // 构造函数,简化操作
    Point(int xc, int yc) : x(xc), y(yc) {}
};

// 绘制点的函数
void print_circle(int x, int y) {
    std::cout << "(" << x << ", " << y << ")\n";
}

void mid_circle(int circle_x, int circle_y, int R) {
    int x = R;
    int y = 0;
    int p = 1 - R;

    //保存圆上的所有点
    std::vector<Point> points;

    //绘制初始点
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
    mid_circle(0, 0, R);

    return 0;
}