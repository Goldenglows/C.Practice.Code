#include <iostream>
#include <vector>

void bresenham(int x0, int y0, int x1, int y1) {
	//�����ռ��ŵ�����
	std::vector < std::pair <int, int>> points;

	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
	//���
	int e = dx - dy;

	//��ӵ�һ���������
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
		//ѡ��������أ�һ��ѡ�������ѡ���뵱ǰ������ӽ�����һ�����ء�
		//���磬�����ǰ���ص�λ��ֱ���ϲ��� e == dx��
		//��ô��һ������Ӧ������x�᷽���ƶ�һ����
		//��� e == dy����Ӧ������y�᷽���ƶ�һ����
		//ѡ������������һ��ѡ������ǿ���ֱ�ߵ����巽��
		//���磬���ֱ�ߵ�б�ʴ���1�������������y�����ƶ���
		//���б��С��1�������������x�����ƶ���
		//���ַ������ܻ������һЩ����Ϊ����Ҫ����ֱ�ߵ�б�ʡ�
		else if (e == dx) { 
			e -= dy;
			x0 += sx;
		}
		else if (e == dy) { 
			e += dx;
			y0 += sy;
		}
		//����µ�����
		points.push_back(std::make_pair(x0, y0));
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
	bresenham(x1, y1, x2, y2);

	return 0;
}