/*
    도어락 인터페이스 수행평가

    MiniCom 상속받는 DoorLock 클래스 구현
    멤버함수의 콜백함수 등록을 위해 싱글톤 패턴 사용
*/

#include "DoorLock.h"

auto& doorlock = *DoorLock::GetInstance();

void setup()
{
    doorlock.Init();
}

void loop()
{
    doorlock.Run();
}
