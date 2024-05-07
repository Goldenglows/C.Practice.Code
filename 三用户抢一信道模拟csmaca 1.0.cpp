#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

// 定义一些常量
const int SIMULATION_TIME = 100; // 模拟时间
const int DIFS = 2; // 分布式帧间隔
const int SIFS = 1; // 短帧间隔
const int SLOT_TIME = 1; // 时隙时间
const int CWmin = 31; // 最小竞争窗口
const int CWmax = 1024; // 最大竞争窗口
const int PACKET_SIZE = 1; // 数据包大小

// 在 User 类外部声明 users 数组
std::vector<class User> users(3);

// 用户类
class User {
public:
    int packets_sent = 0; // 发送的数据包数量
    int cw = CWmin; // 竞争窗口
    int backoff_count = -1; // 后退计数器，-1表示不在后退过程中

    // 尝试发送数据包
    bool attemptToSend(int time, bool& channel_idle) {
        if (backoff_count == -1 && channel_idle) {
            // 如果不在后退过程中且信道空闲，开始后退过程
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, cw - 1);
            backoff_count = dis(gen);
            std::cout << "User " << this - &users[0] << " 在 time " << time << ": 进行Backoff " << backoff_count << std::endl;
        }

        if (backoff_count >= 0) {
            // 如果正在后退，减少后退计数器
            if (channel_idle) {
                backoff_count--;
                if (backoff_count == 0) {
                    // 获得信道，发送数据
                    packets_sent++;
                    std::cout << "User " << this - &users[0] << " 在 time " << time << ": 开始发送信息" << std::endl;
                    cw = CWmin; // 重置竞争窗口
                    backoff_count = -1; // 重置后退计数器
                    channel_idle = false; // 标记信道忙
                    return true;
                }
            }
            else {
                // 信道忙，重置后退计数器
                backoff_count = -1;
            }
        }

        return false;
    }
};

int main() {
    std::vector<User> users(3); // 创建三个用户
    bool channel_idle = true; // 信道空闲状态

    for (int time = 1; time <= SIMULATION_TIME; ++time) {
        // 模拟DIFS时间
        for (int i = 0; i < DIFS; ++i) {
            if (!channel_idle) {
                // 如果信道忙，等待
                std::cout << "在时间点 Time" << time << ":检测到信道正在被占用，请等待" << std::endl;
                break;
            }
            time++; // 模拟时间流逝
        }

        if (channel_idle) {
            // 如果信道空闲，所有用户尝试发送
            for (auto& user : users) {
                user.attemptToSend(time, channel_idle);
            }
        }

        // 模拟SIFS时间
        for (int i = 0; i < SIFS; ++i) {
            time++; // 模拟时间流逝
        }

        // 模拟ACK确认过程
        channel_idle = true; // 假设ACK总是成功接收

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟时间流逝
    }

    // 计算和输出吞吐量
    int total_packets_sent = 0;
    for (const auto& user : users) {
        total_packets_sent += user.packets_sent;
    }
    double throughput = (double)total_packets_sent * PACKET_SIZE / SIMULATION_TIME;
    std::cout << "总吞吐量：" << throughput << " packets/time unit." << std::endl;

    return 0;
}
//
//#include <iostream>
//#include <vector>
//#include <random>
//#include <chrono>
//#include <thread>
//
//// 定义一些常量
//const int SIMULATION_TIME = 100; // 模拟时间
//const int DIFS = 2; // 分布式帧间隔
//const int SIFS = 1; // 短帧间隔
//const int SLOT_TIME = 1; // 时隙时间
//const int CWmin = 31; // 最小竞争窗口
//const int CWmax = 1024; // 最大竞争窗口
//const int PACKET_SIZE = 1; // 数据包大小
//
//// 用户类
//class User {
//public:
//    int packets_sent = 0; // 发送的数据包数量
//    int cw = CWmin; // 竞争窗口
//    int backoff_count = -1; // 后退计数器，-1表示不在后退过程中
//    int channel_time = -1; // 抢到信道的时间点
//
//    // 尝试发送数据包
//    bool attemptToSend(int time, bool& channel_idle) {
//        if (backoff_count == -1 && channel_idle) {
//            // 如果不在后退过程中且信道空闲，开始后退过程
//            std::random_device rd;
//            std::mt19937 gen(rd());
//            std::uniform_int_distribution<> dis(0, cw - 1);
//            backoff_count = dis(gen);
//            std::cout << "在时间点 Time" << time << ": 用户进行backoff " << backoff_count << std::endl;
//        }
//
//        if (backoff_count >= 0) {
//            // 如果正在后退，减少后退计数器
//            if (channel_idle) {
//                backoff_count--;
//                if (backoff_count == 0) {
//                    // 获得信道，发送数据
//                    packets_sent++;
//                    channel_time = time; // 记录抢到信道的时间点
//                    std::cout << "在时间点 Time" << time << ":用户开始发送数据" << std::endl;
//                    cw = CWmin; // 重置竞争窗口
//                    backoff_count = -1; // 重置后退计数器
//                    channel_idle = false; // 标记信道忙
//                    return true;
//                }
//            }
//            else {
//                // 信道忙，重置后退计数器
//                backoff_count = -1;
//            }
//        }
//
//        return false;
//    }
//};
//
//int main() {
//    // 创建三个用户
//    std::vector<User> users(3);
//    bool channel_idle = true; // 信道空闲状态
//
//    // 模拟时间
//    for (int time = 1; time <= SIMULATION_TIME; ++time) {
//        // 模拟DIFS时间
//        for (int i = 0; i < DIFS; ++i) {
//            if (!channel_idle) {
//                // 如果信道忙，等待
//                std::cout << "在时间点 Time" << time << ":检测到信道正在被占用，请等待" << std::endl;
//                break;
//            }
//            time++; // 模拟时间流逝
//        }
//
//        if (channel_idle) {
//            // 如果信道空闲，所有用户尝试发送
//            for (auto& user : users) {
//                user.attemptToSend(time, channel_idle);
//            }
//        }
//
//        // 模拟SIFS时间
//        for (int i = 0; i < SIFS; ++i) {
//            time++; // 模拟时间流逝
//        }
//
//        // 模拟ACK确认过程
//        channel_idle = true; // 假设ACK总是成功接收
//
//        // 输出哪个用户在哪个时间点抢到信道
//        for (const auto& user : users) {
//            if (user.channel_time != -1) {
//                std::cout << "用户 " << user.packets_sent << " 在时间点 Time " << user.channel_time << " 抢到信道并发送数据。" << std::endl;
//                //user.channel_time = -1; // 重置抢到信道的时间点
//            }
//        }
//
//        // 模拟时间流逝
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//
//    // 计算和输出吞吐量
//    int total_packets_sent = 0;
//    for (const auto& user : users) {
//        total_packets_sent += user.packets_sent;
//    }
//    double throughput = (double)total_packets_sent * PACKET_SIZE / SIMULATION_TIME;
//    std::cout << "总吞吐量：" << throughput << " packets/time unit." << std::endl;
//
//    return 0;
//}
