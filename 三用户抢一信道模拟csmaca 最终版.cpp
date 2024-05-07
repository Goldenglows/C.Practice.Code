#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// ���峣��
const int DIFS = 2; // DIFSʱ��
const int SIFS = 1; // SIFSʱ��
const int SLOT_TIME = 1; // ÿ��slot��ʱ��
const int CW_INITIAL = 31; // ��ʼ�������ڴ�С
const int PAYLOAD_SIZE = 512; // ÿ�δ�������ݴ�С���ֽڣ�

// ����ڵ�ṹ��
struct Station {
    int backoff_counter; // ����ʱ��
};

// ��ʼ���ڵ�
void initializeStations(vector<Station>& stations) {
    for (int i = 0; i < stations.size(); ++i) {
        stations[i].backoff_counter = -1; // -1��ʾδ�����ŵ�����Ҫ����ѡ�񵹼�ʱ��
    }
}

// ѡ���������ʱ��
int selectBackoffCounter() {
    return rand() % CW_INITIAL;
}

// ����ŵ�״̬
bool isChannelIdle() {
    // ģ���ŵ��Ƿ���У�����򵥵ط���true��ʾһֱ����
    return true;
}

// ִ��CSMA/CA����
void csmaCa(vector<Station>& stations, int& channel_busy, int& successful_transmissions) {
    for (int i = 0; i < stations.size(); ++i) {
        if (stations[i].backoff_counter == -1) { // δ�����ŵ�������ѡ�񵹼�ʱ��
            stations[i].backoff_counter = selectBackoffCounter();
        }
        else if (stations[i].backoff_counter > 0) { // ����ʱ���ݼ�
            stations[i].backoff_counter -= 1;
        }
        else { // ����ʱ�����㣬��ռ�ŵ�
            if (isChannelIdle()) {
                // �ŵ����У��ڵ���ռ�ŵ�
                cout << "Station " << i + 1 << "��ռ���ŵ�" << endl;
                channel_busy = i + 1;
                successful_transmissions++;
                // ���õ���ʱ��
                stations[i].backoff_counter = -1;
                // �������ݺ�ȴ�ACK
                cout << "Station " << i + 1 << "��ʼ������Ϣ" << endl;
                cout << "�ȴ�SIFSʱ��" << endl;
                cout << "���յ�ACKȷ��֡" << endl;
                // ������ɺ�ȴ�DIFSʱ�����¿�ʼCSMA/CA����
                cout << "������ɣ��ȴ�DIFSʱ��" << endl;
            }
            else {
                // �ŵ�æ���ȴ���һ������
                cout << "Station " << i + 1 << "��⵽�ŵ�æ���ȴ���һ������" << endl;
                // ���õ���ʱ��
                stations[i].backoff_counter = -1;
            }
        }
    }
}

int main() {
    srand(time(0)); // �����������

    // ��ʼ���ڵ�
    vector<Station> stations(3);
    initializeStations(stations);

    int channel_busy = 0; // ��¼��ǰռ���ŵ��Ľڵ��ţ�0��ʾ�޽ڵ�ռ��
    int successful_transmissions = 0; // �ɹ��������

    // ģ��100��ʱ�䵥λ
    for (int time = 0; time < 100; ++time) {
        cout << "ʱ�䣺" << time << endl;
        csmaCa(stations, channel_busy, successful_transmissions);
    }

    // ����������
    double total_data_transferred = successful_transmissions * PAYLOAD_SIZE; // �ɹ�����������������ֽڣ�
    double simulation_time_seconds = 100 * 0.001; // ģ���ʱ�䵥λת��Ϊ��
    double throughput_bps = total_data_transferred / simulation_time_seconds; // ������������/�룩
    double throughput_Bps = throughput_bps / 8; // ���������ֽ�/�룩

    // �����������������Ϣ
    cout << "��������" << throughput_Bps << " �ֽ�/��" << endl;

    return 0;
}