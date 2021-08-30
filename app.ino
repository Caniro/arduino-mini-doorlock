/*
    도어락 인터페이스 수행평가

    MiniCom 클래스를 상속받는 DoorLock 클래스 구현
    멤버 함수를 콜백 함수에 깔끔하게 등록하는 방법을 찾지 못해서
    싱글톤 패턴 사용
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
