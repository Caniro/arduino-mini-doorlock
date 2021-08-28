#pragma once

#include <Arduino.h>

class Melody
{
protected:
    int pin;
    int *notes; // 음계 배열
    int *durations; // 박자 배열
    int length; // 음 개수
    int cur_ix; // 현재 연주하는 음의 인덱스
    long old_time; // 이전 시간
    int note_duration; // 현재 연주하는 음의 길이
    boolean b_play; // 연주 여부

public:
    Melody(int pin, int *notes, int *durations, int length);
    void play();
    void stop();
    int toggle(bool bpause=false); // 기본은 stop, true이면 pause
    void replay();
    int getNote();
    void run();
};
