// Mux control pins
// mux 0
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;
// Fix me. 할당 핀 번호에 따라 추가로 적어주세요
// mux 1
int s4 =
int s5 =
int s6 =
int s7 =
// mux 2
int s8 =
int s9 =
int s10 =
int s11 =
// mux 3
int s12 =
int s13 =
int s14 =
int s15 =
// mux 4
int s16 =
int s17 =
int s18 =
int s19 =
// mux 5
int s20 =
int s21 =
int s22 =
int s23 =

// Mux in “SIG” pin
int SIG_pin = 0;

// 아두이노의 setup 함수. I/O 설정
void setup()
{
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(s4, OUTPUT);
    pinMode(s5, OUTPUT);
    pinMode(s6, OUTPUT);
    pinMode(s7, OUTPUT);
    pinMode(s8, OUTPUT);
    pinMode(s9, OUTPUT);
    pinMode(s10, OUTPUT);
    pinMode(s11, OUTPUT);
    pinMode(s12, OUTPUT);
    pinMode(s13, OUTPUT);
    pinMode(s14, OUTPUT);
    pinMode(s15, OUTPUT);
    pinMode(s16, OUTPUT);
    pinMode(s17, OUTPUT);
    pinMode(s18, OUTPUT);
    pinMode(s19, OUTPUT);
    pinMode(s20, OUTPUT);
    pinMode(s21, OUTPUT);
    pinMode(s22, OUTPUT);
    pinMode(s23, OUTPUT);
    pinMode(SIG_pin, INPUT);

    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s5, LOW);
    digitalWrite(s6, LOW);
    digitalWrite(s7, LOW);
    digitalWrite(s8, LOW);
    digitalWrite(s9, LOW);
    digitalWrite(s10, LOW);
    digitalWrite(s11, LOW);
    digitalWrite(s12, LOW);
    digitalWrite(s13, LOW);
    digitalWrite(s14, LOW);
    digitalWrite(s15, LOW);
    digitalWrite(s16, LOW);
    digitalWrite(s17, LOW);
    digitalWrite(s18, LOW);
    digitalWrite(s19, LOW);
    digitalWrite(s20, LOW);
    digitalWrite(s21, LOW);
    digitalWrite(s22, LOW);
    digitalWrite(s23, LOW);

    Serial.begin(9600);
}

// Mux의 값을 읽어오는 함수.
int readMux(int channel)
{
    int controlPin[] = {s0, s1, s2, s3,
                        s4, s5, s6, s7,
                        s8, s9, s10, s11,
                        s12, s13, s14, s15,
                        s16, s17, s18, s19,
                        s20, s21, s22, s23};

    int muxChannel[6][16][4] = {
        // Mux 0
        {
            // channel 0
            {0, 0, 0, 0},
            // channel 1
            {1, 0, 0, 0},
            // channel 2
            {0, 1, 0, 0},
            // channel 3
            {1, 1, 0, 0},
            // channel 4
            {0, 0, 1, 0},
            // channel 5
            {1, 0, 1, 0},
            // channel 6
            {0, 1, 1, 0},
            // channel 7
            {1, 1, 1, 0},
            // channel 8
            {0, 0, 0, 1},
            // channel 9
            {1, 0, 0, 1},
            // channel 10
            {0, 1, 0, 1},
            // channel 11
            {1, 1, 0, 1},
            // channel 12
            {0, 0, 1, 1},
            // channel 13
            {1, 0, 1, 1},
            // channel 14
            {0, 1, 1, 1},
            // channel 15
            {1, 1, 1, 1}
        },
        // Mux 1
        {
            // channel 16
            {0, 0, 0, 0},
            // channel 17
            {1, 0, 0, 0},
            // channel 18
            {0, 1, 0, 0},
            // channel 19
            {1, 1, 0, 0},
            // channel 20
            {0, 0, 1, 0},
            // channel 21
            {1, 0, 1, 0},
            // channel 22
            {0, 1, 1, 0},
            // channel 23
            {1, 1, 1, 0},
            // channel 24
            {0, 0, 0, 1},
            // channel 25
            {1, 0, 0, 1},
            // channel 26
            {0, 1, 0, 1},
            // channel 27
            {1, 1, 0, 1},
            // channel 28
            {0, 0, 1, 1},
            // channel 29
            {1, 0, 1, 1},
            // channel 30
            {0, 1, 1, 1},
            // channel 31
            {1, 1, 1, 1}
        },
        // Mux 2
        {
            // channel 32
            {0, 0, 0, 0},
            // channel 33
            {1, 0, 0, 0},
            // channel 34
            {0, 1, 0, 0},
            // channel 35
            {1, 1, 0, 0},
            // channel 36
            {0, 0, 1, 0},
            // channel 37
            {1, 0, 1, 0},
            // channel 38
            {0, 1, 1, 0},
            // channel 39
            {1, 1, 1, 0},
            // channel 40
            {0, 0, 0, 1},
            // channel 41
            {1, 0, 0, 1},
            // channel 42
            {0, 1, 0, 1},
            // channel 43
            {1, 1, 0, 1},
            // channel 44
            {0, 0, 1, 1},
            // channel 45
            {1, 0, 1, 1},
            // channel 46
            {0, 1, 1, 1},
            // channel 47
            {1, 1, 1, 1}
        },
        // Mux 3
        {
            // channel 48
            {0, 0, 0, 0},
            // channel 49
            {1, 0, 0, 0},
            // channel 50
            {0, 1, 0, 0},
            // channel 51
            {1, 1, 0, 0},
            // channel 52
            {0, 0, 1, 0},
            // channel 53
            {1, 0, 1, 0},
            // channel 54
            {0, 1, 1, 0},
            // channel 55
            {1, 1, 1, 0},
            // channel 56
            {0, 0, 0, 1},
            // channel 57
            {1, 0, 0, 1},
            // channel 58
            {0, 1, 0, 1},
            // channel 59
            {1, 1, 0, 1},
            // channel 60
            {0, 0, 1, 1},
            // channel 61
            {1, 0, 1, 1},
            // channel 62
            {0, 1, 1, 1},
            // channel 63
            {1, 1, 1, 1}
        },
        // Mux 4
        {
            // channel 64
            {0, 0, 0, 0},
            // channel 65
            {1, 0, 0, 0},
            // channel 66
            {0, 1, 0, 0},
            // channel 67
            {1, 1, 0, 0},
            // channel 68
            {0, 0, 1, 0},
            // channel 69
            {1, 0, 1, 0},
            // channel 70
            {0, 1, 1, 0},
            // channel 71
            {1, 1, 1, 0},
            // channel 72
            {0, 0, 0, 1},
            // channel 73
            {1, 0, 0, 1},
            // channel 74
            {0, 1, 0, 1},
            // channel 75
            {1, 1, 0, 1},
            // channel 76
            {0, 0, 1, 1},
            // channel 77
            {1, 0, 1, 1},
            // channel 78
            {0, 1, 1, 1},
            // channel 79
            {1, 1, 1, 1}
        },
        // Mux 5
        {
            // channel 80
            {0, 0, 0, 0},
            // channel 81
            {1, 0, 0, 0},
            // channel 82
            {0, 1, 0, 0},
            // channel 83
            {1, 1, 0, 0},
            // channel 84
            {0, 0, 1, 0},
            // channel 85
            {1, 0, 1, 0},
            // channel 86
            {0, 1, 1, 0},
            // channel 87
            {1, 1, 1, 0},
            // channel 88
            {0, 0, 0, 1},
            // channel 89
            {1, 0, 0, 1},
            // channel 90
            {0, 1, 0, 1},
            // channel 91
            {1, 1, 0, 1},
            // channel 92
            {0, 0, 1, 1},
            // channel 93
            {1, 0, 1, 1},
            // channel 94
            {0, 1, 1, 1},
            // channel 95
            {1, 1, 1, 1}
        }
    };

    // loop through the 4 sig
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            digitalWrite(controlPin[i], muxChannel[j][channel][i]);
        }
    }
    // read the value at the SIG pin
    int val = analogRead(SIG_pin); // return the value
    return val;
}

// 아두이노의 main문
void loop()
{
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            Serial.print("Value at channel ");
            Serial.print(i + (16 * j));
            Serial.print(": ");
            Serial.println(readMux(i + (16 * j)));
            delay(50);
        }
    }
}