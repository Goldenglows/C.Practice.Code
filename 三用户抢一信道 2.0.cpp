#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// ���峣��
const int DIFS = 2; // DIFSʱ��
const int SIFS = 1; // SIFSʱ��
const int DATA = 5; // DATA
const int SLOT_TIME = 1; // ÿ��slot��ʱ��
const int CW_INITIAL = 31; // ��ʼ�������ڴ�С
const int PAYLOAD_SIZE = 512; // ÿ�δ�������ݴ�С���ֽڣ�

// ����ڵ�ṹ��
struct Station {
    int backoff; // ����ʱ��
};

// ��ʼ���ڵ�
void inituser(vector<Station>& stations) {
    for (int i = 0; i < stations.size(); ++i) {
        stations[i].backoff = -1; // -1��ʾδ�����ŵ�����Ҫ����ѡ�񵹼�ʱ��
    }
}

// ѡ���������ʱ��
int BackoffCounter() {
    return rand() % CW_INITIAL;
}

// ����ŵ�״̬
bool Channelidle() {
    // ģ���ŵ��Ƿ���У�����򵥵ط���true��ʾһֱ����
    return true;
}

// ִ��CSMA/CA����
void csmaca(vector<Station>& users, int& channel_idle, int& success,int& time_tr) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].backoff == -1) { // δ�����ŵ�������ѡ�񵹼�ʱ��
            users[i].backoff = BackoffCounter();
        }
        else if (users[i].backoff > 0) { // ����ʱ���ݼ�
            users[i].backoff -= 1;
        }
        else { // ����ʱ�����㣬��ռ�ŵ�
            if (Channelidle()) {
                // �ŵ����У��ڵ���ռ�ŵ�
                cout << "user " << i + 1 << "��ռ���ŵ�" << endl;
                channel_idle = i + 1;
                success++;
                // ���õ���ʱ��
                users[i].backoff = -1;
                // �������ݺ�ȴ�ACK
                cout << "user " << i + 1 << "��ʼ������Ϣ" << endl;
                cout << "�ȴ�SIFSʱ��" << endl;
                cout << "���յ�ACKȷ��֡" << endl;
                // ������ɺ�ȴ�DIFSʱ�����¿�ʼCSMA/CA����
                cout << "������ɣ��ȴ�DIFSʱ��" << endl;
                time_tr += DATA;
            }
            else {
                // �ŵ�æ���ȴ���һ������
                cout << "user " << i + 1 << "��⵽�ŵ�æ���ȴ���һ������" << endl;
                // ���õ���ʱ��
                users[i].backoff = -1;
            }
        }
    }
}

int main() {
    srand(time(0)); // �����������

    // ��ʼ���ڵ�
    vector<Station> users(3);
    inituser(users);

    int channel_idle = 0; // ��¼��ǰռ���ŵ��Ľڵ��ţ�0��ʾ�޽ڵ�ռ��
    int success = 0; // �ɹ��������

    // ģ��100��ʱ�䵥λ
    for (int time = 0; time < 100; ++time) {
        cout << "ʱ�䣺" << time << endl;
        csmaca(users, channel_idle, success, time);
    }

    // ����������
    double sum_data = success * PAYLOAD_SIZE; // �ɹ�����������������ֽڣ�
    double time_s = 100 * 0.001; // ģ���ʱ�䵥λת��Ϊ��
    double tr_bps = sum_data / time_s;
    double tr_Bps = tr_bps / 8;

    // �����������������Ϣ
    cout << "��������" << tr_Bps << " �ֽ�/��" << endl;

    return 0;
}