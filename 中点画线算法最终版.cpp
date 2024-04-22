#include <iostream>
#include <vector>

void middleline(int x0, int y0, int x1, int y1) {
	//建立空间存放点坐标
	std::vector < std::pair <int, int>> points;

	int dx = x1 - x0; 
	int dy = y1 - y0; 
	//决策变量
	int d = 2 * dy - dx; 
	int ea = 2 * dy;
	int eb = 2 * (dy - dx);
	//起点
	int x = x0;
	int y = y0; 

	points.push_back(std::make_pair(x, y)); // 添加起点坐标

	while (x < x1) {
		if (d <= 0) { 
			d += ea; 
			x++; 
		}
		else { 
			d += eb; 
			x++; 
			y++;
		}
		points.push_back(std::make_pair(x, y)); 
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
	middleline(x1, y1, x2, y2);

	return 0;
}