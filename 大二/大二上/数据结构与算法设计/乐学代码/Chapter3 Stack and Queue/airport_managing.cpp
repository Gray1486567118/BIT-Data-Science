#include <iostream>
#include <cstdio>
#include <cstdlib>

// 跑道结构
struct RunwayType {
    int freetime;
    int totaltime;
};
RunwayType runway[105];

// 飞机结构
struct AirplaneType {
    int airplaneID;
    int time;
    AirplaneType *next;
};

// 降落队列
AirplaneType *landhead = nullptr;
AirplaneType *landtail = nullptr;

void createlandqueue() {
    AirplaneType *p = (AirplaneType *)malloc(sizeof(AirplaneType));
    p->next = nullptr;
    p->airplaneID = -1;
    p->time = -1;
    landhead = p;
    landtail = p;
}

void addlandqueue(int number, int time) {
    AirplaneType *p = (AirplaneType *)malloc(sizeof(AirplaneType));
    p->next = nullptr;
    p->airplaneID = number;
    p->time = time;
    landtail->next = p;
    landtail = landtail->next;
}

AirplaneType outlandqueue() {
    AirplaneType *p = landhead->next;
    landhead->next = p->next;
    if (landhead->next == nullptr)
        landtail = landhead;
    return *p;
}

// 起飞队列
AirplaneType *offhead = nullptr;
AirplaneType *offtail = nullptr;

void createoffqueue() {
    AirplaneType *p = (AirplaneType *)malloc(sizeof(AirplaneType));
    p->next = nullptr;
    p->time = -1;
    p->airplaneID = -1;
    offhead = p;
    offtail = p;
}

void addoffqueue(int number, int time) {
    AirplaneType *p = (AirplaneType *)malloc(sizeof(AirplaneType));
    p->next = nullptr;
    p->time = time;
    p->airplaneID = number;
    offtail->next = p;
    offtail = offtail->next;
}

AirplaneType outoffqueue() {
    AirplaneType *p = offhead->next;
    offhead->next = p->next;
    if (offhead->next == nullptr)
        offtail = offhead;
    return *p;
}

// 判断队列是否为空
bool isempty(AirplaneType *p) {
    return p->next == nullptr;
}

int main() {
    int totalrunway, landcost, offcost;
    int currenttime = 0;
    int landnumber, offnumber, finish = 0;
    int landstartnumber = 5001, offstartnumber = 1;
    int allrunwayfree = 1;
    int landwait = 0, offwait = 0;
    int land_number = 0, off_number = 0;
    int runway_totaltime = 0;

    std::cin >> totalrunway >> landcost >> offcost;

    for (int i = 1; i <= totalrunway; ++i) {
        runway[i].freetime = 0;
        runway[i].totaltime = 0;
    }

    createlandqueue();
    createoffqueue();

    std::printf("Current Time: %4d\n", currenttime++);

    while (true) {
        if (finish != 1) {
            std::cin >> landnumber >> offnumber;
            if (landnumber < 0 && offnumber < 0) {
                finish = 1;
            }
        }

        for (int i = 0; i < landnumber; ++i) {
            addlandqueue(landstartnumber++, currenttime);
            land_number++;
        }

        for (int i = 0; i < offnumber; ++i) {
            addoffqueue(offstartnumber++, currenttime);
            off_number++;
        }

        for (int i = 1; i <= totalrunway; ++i) {
            if (runway[i].freetime == 0) {
                if (!isempty(landhead)) {
                    AirplaneType airplane = outlandqueue();
                    runway[i].freetime = landcost;
                    std::printf("airplane %04d is ready to land on runway %02d\n", airplane.airplaneID, i);
                    landwait += currenttime - airplane.time;
                    runway[i].totaltime += landcost;
                } else if (!isempty(offhead)) {
                    AirplaneType airplane = outoffqueue();
                    runway[i].freetime = offcost;
                    std::printf("airplane %04d is ready to takeoff on runway %02d\n", airplane.airplaneID, i);
                    offwait += currenttime - airplane.time;
                    runway[i].totaltime += offcost;
                }
            }
        }

        std::printf("Current Time: %4d\n", currenttime++);
        allrunwayfree = 1;

        for (int i = 1; i <= totalrunway; ++i) {
            if (runway[i].freetime != 0) {
                if (!(--runway[i].freetime)) {
                    std::printf("runway %02d is free\n", i);
                } else {
                    allrunwayfree = 0;
                }
            }
        }

        if (finish && isempty(landhead) && isempty(offhead) && allrunwayfree)
            break;
    }

    // 输出最终结果
    std::printf("simulation finished\n");
    std::printf("simulation time: %4d\n", --currenttime);

    double land_average = (double)landwait / land_number;
    std::printf("average waiting time of landing: %4.1f\n", land_average);

    double off_average = (double)offwait / off_number;
    std::printf("average waiting time of takeoff: %4.1f\n", off_average);

    for (int i = 1; i <= totalrunway; ++i) {
        std::printf("runway %02d busy time: %4d\n", i, runway[i].totaltime);
        runway_totaltime += runway[i].totaltime;
    }

    float pertime = ((float)runway_totaltime / totalrunway) * 100 / currenttime;
    std::printf("runway average busy time percentage: %4.1f%%\n", pertime);

    return 0;
}
