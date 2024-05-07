#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// 用户类
class User {
private:
    int id;             // 用户ID
    int cw;             // 竞争窗口大小
    int backoff;        // 倒计时
    bool channel_idle;  // 信道是否空闲
    bool transmitting;  // 是否正在发送数据
public:
    // 构造函数
    User(int _id) : id(_id), cw(31), backoff(0), channel_idle(true), transmitting(false) {}

    // 获取用户ID
    int get_id() { return id; }

    // 检查用户是否正在发送数据
    bool is_transmitting() { return transmitting; }

    // 减小倒计时
    void decrease_backoff() {
        if (backoff > 0) {
            backoff--;
        }
    }

    // 开始发送数据
    void start_transmitting() {
        transmitting = true;
        backoff = rand() % (cw + 1);
        cout << "用户 " << id << " 开始发送数据，倒计时为 " << backoff << endl;
    }

    // 检查信道状态
    void check_channel() {
        if (channel_idle) {
            decrease_backoff();
            if (backoff == 0) {
                start_transmitting();
            }
        }
    }

    // 接收到ACK确认帧
    void receive_ack() {
        cout << "用户 " << id << " 接收到ACK确认帧。" << endl;
        transmitting = false;
    }

    // 设置信道状态
    void set_channel_idle(bool idle) {
        channel_idle = idle;
    }
};

// CSMA/CA类
class CSMA_CA {
private:
    vector<User> users;  // 用户数组
    bool channel_idle;   // 信道是否空闲
public:
    // 构造函数
    CSMA_CA(int num_users) : channel_idle(true) {
        // 初始化用户
        for (int i = 0; i < num_users; i++) {
            users.push_back(User(i + 1));
        }
    }

    // 模拟CSMA/CA过程
    void simulate() {
        srand(time(NULL));
        int total_transmitted = 0;
        // 循环直到所有用户都发送完数据
        while (total_transmitted < users.size()) {
            channel_idle = true;
            // 检查每个用户的信道状态
            for (auto& user : users) {
                user.check_channel();
                user.set_channel_idle(channel_idle);
            }

            // 如果信道不空闲，重新计数已发送数据的用户数
            if (!channel_idle) {
                total_transmitted = 0;
                for (auto& user : users) {
                    if (user.is_transmitting()) {
                        total_transmitted++;
                    }
                }
            }

            // 接收到ACK确认帧的用户结束发送
            for (auto& user : users) {
                if (user.is_transmitting()) {
                    user.receive_ack();
                }
            }
        }
    }
};

int main() {
    // 创建CSMA/CA对象并进行仿真
    CSMA_CA csma_ca(3);
    csma_ca.simulate();

    return 0;
}