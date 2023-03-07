#include "snake.h"

extern time_t obstacleTimeStamp;


int main() {
    srand((unsigned int)time(0));      // �������������
    obstacleTimeStamp = time(NULL);
    int end = 1, result;
    while (end) {
        result = Menu();                           // ��ʾ���˵����������û�ѡ��˵�ѡ�������Ϸ��ִ��
        switch (result) {
        case 1:                                // ѡ��1��ʾ����ʼ̰������Ϸ
            InitMap();                         // ��ʼ����ͼ���ߺ�ʳ��
            while (MoveSnake());               // �������0����ֹͣ�ƶ�������1������ƶ���
            break;
        case 2:                                // ѡ��2��ʾ����ʾ������Ϣ
            Help();
            break;
        case 3:                                // ѡ��3��ʾ����ʾ������Ϣ
            About();
            break;
        case 0:                                // ѡ��4��ʾ����ʾ������Ϸ
            end = 0;
            break;
        }
    }
}