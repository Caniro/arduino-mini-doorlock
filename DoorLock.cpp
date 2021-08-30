#include "DoorLock.h"

const int kBaseAddress = 100; // 비밀번호 저장 EEPROM 주소

DoorLock* DoorLock::instance_ = NULL;

DoorLock::DoorLock(long serial_bps, int lcd_addr)
: MiniCom(serial_bps, lcd_addr)
{}

DoorLock::~DoorLock()
{
    delete instance_;
}

DoorLock* DoorLock::GetInstance(long serial_bps, int lcd_addr)
{
    if (instance_ == NULL)
        instance_ = new DoorLock(serial_bps, lcd_addr);
    return instance_;
}

void DoorLock::Init()
{
    MiniCom::init();
    offLcd();
    print(0, "[[Door Lock]]");
    password_ = readRom(kBaseAddress);
    servo_lock_.attach(kServoPin);
    servo_lock_.write(0);
    btn_.setCallback(SetPassword);
}

void DoorLock::Run()
{
    MiniCom::run();
    btn_.check();

    if (char key = keypad_.getKey())
        Process(key);
}

void DoorLock::Process(char key)
{
    if (key == '*' && input_mode_ == false)
    {
        StartGetInput();
        timer_id_ = timer.setTimeout(3000, DoReset);
    }
    else if (key == '#' && input_mode_)
    {
        if (!IsSetMode())
        {
            timer.deleteTimer(timer_id_);
            timer_id_ = -1;
            input_mode_ = false;
            Check();
        }
        else
        {
            SwitchSetMode();
            EndChangePassword();
        }
    }
    else if (input_mode_)
    {
        if (!IsSetMode())
            timer.restartTimer(timer_id_);
        input_ += key;
        input_star_ += '*';
        Tick();
    }
    print(1, input_star_.c_str());
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
        input_star_ = "";
        ++wrong_time_;
        onLcd();
        print(1, "wrong count: ", wrong_time_);
        Tick(3);
        delay(500);
        if (wrong_time_ >= 3)
        {
            print(1, "wait for 10min");
            delay(500);
            offLcd();
            delay((unsigned long)10 * 60 * 1000); // 10분 정지
            wrong_time_ = 0;
        }
    }
    offLcd();
}

void DoorLock::StartGetInput()
{
    input_mode_ = true;
    input_ = "";
    input_star_ = "";
    onLcd();
    Tick();
}

void DoorLock::ResetInput()
{
    input_mode_ = false;
    input_ = "";
    input_star_ = "";
    offLcd();
    print(1, input_star_.c_str());
}

void DoorLock::EndChangePassword()
{
    password_ = input_;
    writeRom(kBaseAddress, input_);
    ResetInput();
}

boolean DoorLock::IsSetMode()
{
    return set_password_mode_;
}

void DoorLock::SwitchSetMode()
{
    set_password_mode_ = !set_password_mode_;
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

void SetPassword()
{
    auto& doorlock = *DoorLock::GetInstance();

    doorlock.SwitchSetMode();
    if (doorlock.IsSetMode())
        doorlock.StartGetInput();
    else
        doorlock.EndChangePassword();
}

void DoReset()
{
    auto& doorlock = *DoorLock::GetInstance();

    doorlock.ResetInput();
    doorlock.Tick(2);
}
