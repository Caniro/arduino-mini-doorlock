#include "DoorLock.h"

const int base_address = 100; // 비밀번호 저장 EEPROM 주소

DoorLock::DoorLock(long serial_bps, int lcd_addr)
: MiniCom(serial_bps, lcd_addr)
{}

void DoorLock::Init()
{
    MiniCom::init();
    offLcd();
    print(0, "[[Door Lock]]");
    password_ = readRom(base_address);
    servo_lock_.attach(servo_pin);
    servo_lock_.write(0);
    btn_.setCallback(SwitchBSetPassword);
}

void DoorLock::Run()
{
    MiniCom::run();

    // 타이머 감지
    if (b_reset)
    {
        ResetInput();
        Tick(2);
        b_reset = false;
    }

    // 비밀번호 변경 모드
    btn_.check();
    if (b_set_password && b_set_password_old_ == false)
        StartGetInput();
    else if (b_set_password == false && b_set_password_old_)
        EndChangePassword();
    b_set_password_old_ = b_set_password;

    // 키패드 입력 감지
    if (char key = keypad_.getKey())
        Process(key);
}

void DoorLock::Process(char key)
{
    if (key == '*' && b_input_ == false)
    {
        StartGetInput();
        timer_id_ = timer.setTimeout(3000, SetResetFlag);
    }
    else if (key == '#' && b_input_)
    {
        if (b_set_password == false)
        {
            timer.deleteTimer(timer_id_);
            timer_id_ = -1;
            b_input_ = false;
            Check();
            offLcd();
        }
        else
            b_set_password = !b_set_password;
    }
    else if (b_input_)
    {
        if (!b_set_password)
            timer.restartTimer(timer_id_);
        input_ += key;
        inputStar_ += '*';
        Tick();
    }
    print(1, inputStar_.c_str());
}

void DoorLock::Check()
{
    if (input_ == password_)
    {
        servo_lock_.write(90);
        delay(5000);
        servo_lock_.write(0);
        wrong_time_ = 0;
        ResetInput();
    }
    else
    {
        inputStar_ = "";
        ++wrong_time_;
        onLcd();
        print(1, "wrong count: ", wrong_time_);
        Tick(3);
        delay(500);
        print(1, "wait for 10min");
        offLcd();
        if (wrong_time_ >= 3)
        {
            delay((unsigned long)10 * 60 * 1000); // 10분 정지
            wrong_time_ = 0;
        }
    }
}

void DoorLock::StartGetInput()
{
    b_input_ = true;
    input_ = "";
    inputStar_ = "";
    onLcd();
    Tick();
}

void DoorLock::ResetInput()
{
    b_input_ = false;
    input_ = "";
    inputStar_ = "";
    offLcd();
    print(1, inputStar_.c_str());
}

void DoorLock::Tick()
{
    beep_.on();
    delay(100);
    beep_.off();
    delay(50);
}

void DoorLock::Tick(int n)
{
    for (int i = 0; i < n; ++i)
        Tick();
}

void DoorLock::EndChangePassword()
{
    password_ = input_;
    writeRom(base_address, input_);
    delay(100);
    ResetInput();
}

void SwitchBSetPassword()
{
    b_set_password = !b_set_password;
}

void SetResetFlag()
{
    b_reset = true;
}
