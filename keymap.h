const byte KEY_ROWS = 4;
const byte KEY_COLS = 4;

char keys_4x4[KEY_ROWS][KEY_COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte row_pins[KEY_ROWS] = {7, 6, 5, 4}; // R1, R2, R3, R4 단자가 연결된 핀 번호
byte col_pins[KEY_COLS] = {8, 9, 10, 11}; // C1, C2, C3, C4 단자가 연결된 핀 번호
