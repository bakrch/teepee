#include <Arduino.h>
class Printer {
public:
    HardwareSerial& serial;

    Printer(HardwareSerial& s)
        : serial(s)
    {}

    void raw(const uint8_t* data, size_t len) {
        serial.write(data, len);
    }

    void text(const String& str) {
        serial.print(str);
    }

    void line(const String& str) {
        serial.println(str);
    }

    void feed(uint8_t lines = 3) {
        while(lines--)
            serial.write('\n');
    }

    void cut() {
        uint8_t cmd[] = {
            0x1D, 0x56, 0x00
        };
        serial.write(cmd, sizeof(cmd));
    }

    void init() {
        uint8_t cmd[] = {
            0x1B, 0x40
        };
        serial.write(cmd, sizeof(cmd));
    }
};