#pragma once

#include <MiniCom.h>
#include <storage.h>
#include <Keypad.h>
#include <Button.h>
#include <Led.h>
#include <Servo.h>
#include "Keymap.h"

const int servo_pin = 3;
const int button_pin = 2;
const int led_pin = 12;

/*
    평소에는 LCD off 상태
    시작 : '*' 입력
        숫자 입력 시 마다 LCD에 * 출력
        3초간 입력 없을 경우 리셋
    종료 : '#' 입력, LCD 클리어
        외부 버튼 한 번 누르면 비밀번호 변경 모드, 한 번 더 누르면 저장
    3회 틀린 경우 10분간 작동 정지
*/
class DoorLock : public MiniCom
{
public:

    void Init();
    void Run();
    void Process(char key);
    void Check();
    void StartGetInput();
    void ResetInput();
    void EndChangePassword();
    boolean IsSetMode();
    void SwitchSetMode();

    void Tick();
    void Tick(int n);

    static DoorLock* GetInstance(long serial_bps=115200, int lcd_addr=0x27);

protected:
    static DoorLock* instance;
    String password_ = "";
    Servo servo_lock_;
    Button btn_{button_pin};

    Keypad keypad_{makeKeymap(keys_4x4), row_pins, col_pins, KEY_ROWS, KEY_COLS};
    String input_ = "";
    String inputStar_ = "";
    boolean b_input_ = false;
    boolean b_set_password_ = false;

    Led beep_{led_pin};
    int timer_id_ = -1;
    int wrong_time_ = 0;

private:
    DoorLock(long serial_bps=115200, int lcd_addr=0x27);
    ~DoorLock();
};

void SwitchBSetPassword();
void SetResetFlag();
