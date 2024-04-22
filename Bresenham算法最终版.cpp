#include <iostream>
#include <vector>

void bresenham(int x0, int y0, int x1, int y1) {
	//建立空间存放点坐标
	std::vector < std::pair <int, int>> points;

	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
	//误差
	int e = dx - dy;

	//添加第一个点的坐标
	points.push_back(std::make_pair(x, y));

	while (x0 != x1 || y0 != y1) {

		int e2 = 2 * e;

		if (e2 > -dy && e < dx) { 
			e -= dy;
			x0 += sx;
		}
		else if (e2 < dx && er< dy) { 
			e += dx;
			y0 += sy;
		}
		//选择最近像素：一种选择策略是选择与当前像素最接近的下一个像素。
		//例如，如果当前像素点位于直线上并且 e == dx，
		//那么下一个像素应该沿着x轴方向移动一步；
		//如果 e == dy，则应该沿着y轴方向移动一步。
		//选择向量方向：另一种选择策略是考虑直线的整体方向。
		//例如，如果直线的斜率大于1，则更倾向于在y轴上移动；
		//如果斜率小于1，则更倾向于在x轴上移动。
		//这种方法可能会更复杂一些，因为它需要计算直线的斜率。
		else if (e == dx) { 
			e -= dy;
			x0 += sx;
		}
		else if (e == dy) { 
			e += dx;
			y0 += sy;
		}
		//添加新点坐标
		points.push_back(std::make_pair(x0, y0));
	}

	// 输出所有点坐标
	std::cout << "所有点的坐标：" << std::endl;
	for (const auto& point : points) {
		std::cout << "(" << point.first << ", " << point.second << ")" << std::endl;
	}

}

int main() {
	// 输入两个点的坐标
	int x1, y1, x2, y2;
	std::cout << "请输入第一个节点(x1 y1): ";
	std::cin >> x1 >> y1;
	std::cout << "请输入第二个节点(x2 y2): ";
	std::cin >> x2 >> y2;

	// 调用中点画线算法并输出所有点坐标
	bresenham(x1, y1, x2, y2);

	return 0;
}