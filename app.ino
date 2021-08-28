/*
    도어락 인터페이스 수행평가

    MiniCom 상속받는 DoorLock 클래스 구현
*/

#include "DoorLock.h"

DoorLock doorlock;

void setup()
{
    doorlock.Init();
}

void loop()
{
    doorlock.Run();
}
