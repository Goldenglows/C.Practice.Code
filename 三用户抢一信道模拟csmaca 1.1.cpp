#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// �û���
class User {
private:
    int id;             // �û�ID
    int cw;             // �������ڴ�С
    int backoff;        // ����ʱ
    bool channel_idle;  // �ŵ��Ƿ����
    bool transmitting;  // �Ƿ����ڷ�������
public:
    // ���캯��
    User(int _id) : id(_id), cw(31), backoff(0), channel_idle(true), transmitting(false) {}

    // ��ȡ�û�ID
    int get_id() { return id; }

    // ����û��Ƿ����ڷ�������
    bool is_transmitting() { return transmitting; }

    // ��С����ʱ
    void decrease_backoff() {
        if (backoff > 0) {
            backoff--;
        }
    }

    // ��ʼ��������
    void start_transmitting() {
        transmitting = true;
        backoff = rand() % (cw + 1);
        cout << "�û� " << id << " ��ʼ�������ݣ�����ʱΪ " << backoff << endl;
    }

    // ����ŵ�״̬
    void check_channel() {
        if (channel_idle) {
            decrease_backoff();
            if (backoff == 0) {
                start_transmitting();
            }
        }
    }

    // ���յ�ACKȷ��֡
    void receive_ack() {
        cout << "�û� " << id << " ���յ�ACKȷ��֡��" << endl;
        transmitting = false;
    }

    // �����ŵ�״̬
    void set_channel_idle(bool idle) {
        channel_idle = idle;
    }
};

// CSMA/CA��
class CSMA_CA {
private:
    vector<User> users;  // �û�����
    bool channel_idle;   // �ŵ��Ƿ����
public:
    // ���캯��
    CSMA_CA(int num_users) : channel_idle(true) {
        // ��ʼ���û�
        for (int i = 0; i < num_users; i++) {
            users.push_back(User(i + 1));
        }
    }

    // ģ��CSMA/CA����
    void simulate() {
        srand(time(NULL));
        int total_transmitted = 0;
        // ѭ��ֱ�������û�������������
        while (total_transmitted < users.size()) {
            channel_idle = true;
            // ���ÿ���û����ŵ�״̬
            for (auto& user : users) {
                user.check_channel();
                user.set_channel_idle(channel_idle);
            }

            // ����ŵ������У����¼����ѷ������ݵ��û���
            if (!channel_idle) {
                total_transmitted = 0;
                for (auto& user : users) {
                    if (user.is_transmitting()) {
                        total_transmitted++;
                    }
                }
            }

            // ���յ�ACKȷ��֡���û���������
            for (auto& user : users) {
                if (user.is_transmitting()) {
                    user.receive_ack();
                }
            }
        }
    }
};

int main() {
    // ����CSMA/CA���󲢽��з���
    CSMA_CA csma_ca(3);
    csma_ca.simulate();

    return 0;
}