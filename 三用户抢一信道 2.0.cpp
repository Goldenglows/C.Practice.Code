#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// 定义常量
const int DIFS = 2; // DIFS时间
const int SIFS = 1; // SIFS时间
const int DATA = 5; // DATA
const int SLOT_TIME = 1; // 每个slot的时间
const int CW_INITIAL = 31; // 初始竞争窗口大小
const int PAYLOAD_SIZE = 512; // 每次传输的数据大小（字节）

// 定义节点结构体
struct Station {
    int backoff; // 倒计时器
};

// 初始化节点
void inituser(vector<Station>& stations) {
    for (int i = 0; i < stations.size(); ++i) {
        stations[i].backoff = -1; // -1表示未抢到信道，需要重新选择倒计时器
    }
}

// 选择随机倒计时器
int BackoffCounter() {
    return rand() % CW_INITIAL;
}

// 检查信道状态
bool Channelidle() {
    // 模拟信道是否空闲，这里简单地返回true表示一直空闲
    return true;
}

// 执行CSMA/CA过程
void csmaca(vector<Station>& users, int& channel_idle, int& success,int& time_tr) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].backoff == -1) { // 未抢到信道，重新选择倒计时器
            users[i].backoff = BackoffCounter();
        }
        else if (users[i].backoff > 0) { // 倒计时器递减
            users[i].backoff -= 1;
        }
        else { // 倒计时器归零，抢占信道
            if (Channelidle()) {
                // 信道空闲，节点抢占信道
                cout << "user " << i + 1 << "抢占了信道" << endl;
                channel_idle = i + 1;
                success++;
                // 重置倒计时器
                users[i].backoff = -1;
                // 发送数据后等待ACK
                cout << "user " << i + 1 << "开始发送信息" << endl;
                cout << "等待SIFS时间" << endl;
                cout << "接收到ACK确认帧" << endl;
                // 传输完成后等待DIFS时间重新开始CSMA/CA过程
                cout << "传输完成，等待DIFS时间" << endl;
                time_tr += DATA;
            }
            else {
                // 信道忙，等待下一次重试
                cout << "user " << i + 1 << "检测到信道忙，等待下一次重试" << endl;
                // 重置倒计时器
                users[i].backoff = -1;
            }
        }
    }
}

int main() {
    srand(time(0)); // 设置随机种子

    // 初始化节点
    vector<Station> users(3);
    inituser(users);

    int channel_idle = 0; // 记录当前占用信道的节点编号，0表示无节点占用
    int success = 0; // 成功传输次数

    // 模拟100个时间单位
    for (int time = 0; time < 100; ++time) {
        cout << "时间：" << time << endl;
        csmaca(users, channel_idle, success, time);
    }

    // 计算吞吐量
    double sum_data = success * PAYLOAD_SIZE; // 成功传输的总数据量（字节）
    double time_s = 100 * 0.001; // 模拟的时间单位转换为秒
    double tr_bps = sum_data / time_s;
    double tr_Bps = tr_bps / 8;

    // 输出吞吐量和其他信息
    cout << "吞吐量：" << tr_Bps << " 字节/秒" << endl;

    return 0;
}