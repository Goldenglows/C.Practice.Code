#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

// ����һЩ����
const int SIMULATION_TIME = 100; // ģ��ʱ��
const int DIFS = 2; // �ֲ�ʽ֡���
const int SIFS = 1; // ��֡���
const int SLOT_TIME = 1; // ʱ϶ʱ��
const int CWmin = 31; // ��С��������
const int CWmax = 1024; // ���������
const int PACKET_SIZE = 1; // ���ݰ���С

// �� User ���ⲿ���� users ����
std::vector<class User> users(3);

// �û���
class User {
public:
    int packets_sent = 0; // ���͵����ݰ�����
    int cw = CWmin; // ��������
    int backoff_count = -1; // ���˼�������-1��ʾ���ں��˹�����

    // ���Է������ݰ�
    bool attemptToSend(int time, bool& channel_idle) {
        if (backoff_count == -1 && channel_idle) {
            // ������ں��˹��������ŵ����У���ʼ���˹���
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, cw - 1);
            backoff_count = dis(gen);
            std::cout << "User " << this - &users[0] << " �� time " << time << ": ����Backoff " << backoff_count << std::endl;
        }

        if (backoff_count >= 0) {
            // ������ں��ˣ����ٺ��˼�����
            if (channel_idle) {
                backoff_count--;
                if (backoff_count == 0) {
                    // ����ŵ�����������
                    packets_sent++;
                    std::cout << "User " << this - &users[0] << " �� time " << time << ": ��ʼ������Ϣ" << std::endl;
                    cw = CWmin; // ���þ�������
                    backoff_count = -1; // ���ú��˼�����
                    channel_idle = false; // ����ŵ�æ
                    return true;
                }
            }
            else {
                // �ŵ�æ�����ú��˼�����
                backoff_count = -1;
            }
        }

        return false;
    }
};

int main() {
    std::vector<User> users(3); // ���������û�
    bool channel_idle = true; // �ŵ�����״̬

    for (int time = 1; time <= SIMULATION_TIME; ++time) {
        // ģ��DIFSʱ��
        for (int i = 0; i < DIFS; ++i) {
            if (!channel_idle) {
                // ����ŵ�æ���ȴ�
                std::cout << "��ʱ��� Time" << time << ":��⵽�ŵ����ڱ�ռ�ã���ȴ�" << std::endl;
                break;
            }
            time++; // ģ��ʱ������
        }

        if (channel_idle) {
            // ����ŵ����У������û����Է���
            for (auto& user : users) {
                user.attemptToSend(time, channel_idle);
            }
        }

        // ģ��SIFSʱ��
        for (int i = 0; i < SIFS; ++i) {
            time++; // ģ��ʱ������
        }

        // ģ��ACKȷ�Ϲ���
        channel_idle = true; // ����ACK���ǳɹ�����

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // ģ��ʱ������
    }

    // ��������������
    int total_packets_sent = 0;
    for (const auto& user : users) {
        total_packets_sent += user.packets_sent;
    }
    double throughput = (double)total_packets_sent * PACKET_SIZE / SIMULATION_TIME;
    std::cout << "����������" << throughput << " packets/time unit." << std::endl;

    return 0;
}
//
//#include <iostream>
//#include <vector>
//#include <random>
//#include <chrono>
//#include <thread>
//
//// ����һЩ����
//const int SIMULATION_TIME = 100; // ģ��ʱ��
//const int DIFS = 2; // �ֲ�ʽ֡���
//const int SIFS = 1; // ��֡���
//const int SLOT_TIME = 1; // ʱ϶ʱ��
//const int CWmin = 31; // ��С��������
//const int CWmax = 1024; // ���������
//const int PACKET_SIZE = 1; // ���ݰ���С
//
//// �û���
//class User {
//public:
//    int packets_sent = 0; // ���͵����ݰ�����
//    int cw = CWmin; // ��������
//    int backoff_count = -1; // ���˼�������-1��ʾ���ں��˹�����
//    int channel_time = -1; // �����ŵ���ʱ���
//
//    // ���Է������ݰ�
//    bool attemptToSend(int time, bool& channel_idle) {
//        if (backoff_count == -1 && channel_idle) {
//            // ������ں��˹��������ŵ����У���ʼ���˹���
//            std::random_device rd;
//            std::mt19937 gen(rd());
//            std::uniform_int_distribution<> dis(0, cw - 1);
//            backoff_count = dis(gen);
//            std::cout << "��ʱ��� Time" << time << ": �û�����backoff " << backoff_count << std::endl;
//        }
//
//        if (backoff_count >= 0) {
//            // ������ں��ˣ����ٺ��˼�����
//            if (channel_idle) {
//                backoff_count--;
//                if (backoff_count == 0) {
//                    // ����ŵ�����������
//                    packets_sent++;
//                    channel_time = time; // ��¼�����ŵ���ʱ���
//                    std::cout << "��ʱ��� Time" << time << ":�û���ʼ��������" << std::endl;
//                    cw = CWmin; // ���þ�������
//                    backoff_count = -1; // ���ú��˼�����
//                    channel_idle = false; // ����ŵ�æ
//                    return true;
//                }
//            }
//            else {
//                // �ŵ�æ�����ú��˼�����
//                backoff_count = -1;
//            }
//        }
//
//        return false;
//    }
//};
//
//int main() {
//    // ���������û�
//    std::vector<User> users(3);
//    bool channel_idle = true; // �ŵ�����״̬
//
//    // ģ��ʱ��
//    for (int time = 1; time <= SIMULATION_TIME; ++time) {
//        // ģ��DIFSʱ��
//        for (int i = 0; i < DIFS; ++i) {
//            if (!channel_idle) {
//                // ����ŵ�æ���ȴ�
//                std::cout << "��ʱ��� Time" << time << ":��⵽�ŵ����ڱ�ռ�ã���ȴ�" << std::endl;
//                break;
//            }
//            time++; // ģ��ʱ������
//        }
//
//        if (channel_idle) {
//            // ����ŵ����У������û����Է���
//            for (auto& user : users) {
//                user.attemptToSend(time, channel_idle);
//            }
//        }
//
//        // ģ��SIFSʱ��
//        for (int i = 0; i < SIFS; ++i) {
//            time++; // ģ��ʱ������
//        }
//
//        // ģ��ACKȷ�Ϲ���
//        channel_idle = true; // ����ACK���ǳɹ�����
//
//        // ����ĸ��û����ĸ�ʱ��������ŵ�
//        for (const auto& user : users) {
//            if (user.channel_time != -1) {
//                std::cout << "�û� " << user.packets_sent << " ��ʱ��� Time " << user.channel_time << " �����ŵ����������ݡ�" << std::endl;
//                //user.channel_time = -1; // ���������ŵ���ʱ���
//            }
//        }
//
//        // ģ��ʱ������
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//
//    // ��������������
//    int total_packets_sent = 0;
//    for (const auto& user : users) {
//        total_packets_sent += user.packets_sent;
//    }
//    double throughput = (double)total_packets_sent * PACKET_SIZE / SIMULATION_TIME;
//    std::cout << "����������" << throughput << " packets/time unit." << std::endl;
//
//    return 0;
//}
