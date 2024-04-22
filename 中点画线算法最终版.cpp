#include <iostream>
#include <vector>

void middleline(int x0, int y0, int x1, int y1) {
	//�����ռ��ŵ�����
	std::vector < std::pair <int, int>> points;

	int dx = x1 - x0; 
	int dy = y1 - y0; 
	//���߱���
	int d = 2 * dy - dx; 
	int ea = 2 * dy;
	int eb = 2 * (dy - dx);
	//���
	int x = x0;
	int y = y0; 

	points.push_back(std::make_pair(x, y)); // ����������

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

	// ������е�����
	std::cout << "���е�����꣺" << std::endl;
	for (const auto& point : points) {
		std::cout << "(" << point.first << ", " << point.second << ")" << std::endl;
	}

}

int main() {
	// ���������������
	int x1, y1, x2, y2;
	std::cout << "�������һ���ڵ�(x1 y1): ";
	std::cin >> x1 >> y1;
	std::cout << "������ڶ����ڵ�(x2 y2): ";
	std::cin >> x2 >> y2;

	// �����е㻭���㷨��������е�����
	middleline(x1, y1, x2, y2);

	return 0;
}