#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// 定义常量
const int DIFS = 2; // DIFS时间
const int SIFS = 1; // SIFS时间
const int SLOT_TIME = 1; // 每个slot的时间
const int CW_INITIAL = 31; // 初始竞争窗口大小
const int PAYLOAD_SIZE = 512; // 每次传输的数据大小（字节）

// 定义节点结构体
struct Station {
    int backoff_counter; // 倒计时器
};

// 初始化节点
void initializeStations(vector<Station>& stations) {
    for (int i = 0; i < stations.size(); ++i) {
        stations[i].backoff_counter = -1; // -1表示未抢到信道，需要重新选择倒计时器
    }
}

// 选择随机倒计时器
int selectBackoffCounter() {
    return rand() % CW_INITIAL;
}

// 检查信道状态
bool isChannelIdle() {
    // 模拟信道是否空闲，这里简单地返回true表示一直空闲
    return true;
}

// 执行CSMA/CA过程
void csmaCa(vector<Station>& stations, int& channel_busy, int& successful_transmissions) {
    for (int i = 0; i < stations.size(); ++i) {
        if (stations[i].backoff_counter == -1) { // 未抢到信道，重新选择倒计时器
            stations[i].backoff_counter = selectBackoffCounter();
        }
        else if (stations[i].backoff_counter > 0) { // 倒计时器递减
            stations[i].backoff_counter -= 1;
        }
        else { // 倒计时器归零，抢占信道
            if (isChannelIdle()) {
                // 信道空闲，节点抢占信道
                cout << "Station " << i + 1 << "抢占了信道" << endl;
                channel_busy = i + 1;
                successful_transmissions++;
                // 重置倒计时器
                stations[i].backoff_counter = -1;
                // 发送数据后等待ACK
                cout << "Station " << i + 1 << "开始发送信息" << endl;
                cout << "等待SIFS时间" << endl;
                cout << "接收到ACK确认帧" << endl;
                // 传输完成后等待DIFS时间重新开始CSMA/CA过程
                cout << "传输完成，等待DIFS时间" << endl;
            }
            else {
                // 信道忙，等待下一次重试
                cout << "Station " << i + 1 << "检测到信道忙，等待下一次重试" << endl;
                // 重置倒计时器
                stations[i].backoff_counter = -1;
            }
        }
    }
}

int main() {
    srand(time(0)); // 设置随机种子

    // 初始化节点
    vector<Station> stations(3);
    initializeStations(stations);

    int channel_busy = 0; // 记录当前占用信道的节点编号，0表示无节点占用
    int successful_transmissions = 0; // 成功传输次数

    // 模拟100个时间单位
    for (int time = 0; time < 100; ++time) {
        cout << "时间：" << time << endl;
        csmaCa(stations, channel_busy, successful_transmissions);
    }

    // 计算吞吐量
    double total_data_transferred = successful_transmissions * PAYLOAD_SIZE; // 成功传输的总数据量（字节）
    double simulation_time_seconds = 100 * 0.001; // 模拟的时间单位转换为秒
    double throughput_bps = total_data_transferred / simulation_time_seconds; // 吞吐量（比特/秒）
    double throughput_Bps = throughput_bps / 8; // 吞吐量（字节/秒）

    // 输出吞吐量和其他信息
    cout << "吞吐量：" << throughput_Bps << " 字节/秒" << endl;

    return 0;
}