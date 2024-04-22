#include <iostream>
#include <cmath>

void dda(int x0,int y0,int x1,int y1) {
    //���һ����͵�һ����Ĳ�ֵ
    int dx = x1 - x0,dy = y1 - y0,step;
    float n, m, x = x0, y = y0;

    if (abs(dx) > abs(dy)) step = abs(dx);
    else step = abs(dy);

    n = float(dx) / float(step);
    m = float(dy) / float(step);
    
    //���Ƶ�һ����
    for (int j = 0; j < y0; ++j)
        std::cout << std::endl;
    std::cout << "(" << round(x) << "," << round(y) << ")" << std::endl;
    for (int j = 0; j < x0; ++j)
        std::cout << " ";
    std::cout << "��\n";

    for (int i = 0; i < step; i++) {
        x += n;
        y += m;
        std::cout << "(" << round(x) << "," << round(y) << ")" << std::endl;
        //���ƺ���ĵ�
        int X = round(x);
        int Y = round(y);
        for (int j = 0; j < X; ++j)
            std::cout << " ";
        std::cout << "��\n";
    }
}

int main() {
    // ���������������
    int x1, y1, x2, y2;
    std::cout << "�������һ���ڵ�(x1 y1): ";
    std::cin >> x1 >> y1;
    std::cout << "������ڶ����ڵ�(x2 y2): ";
    std::cin >> x2 >> y2;

    dda(x1, y1, x2, y2);

    return 0;
}