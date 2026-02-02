#include "Serial.h"

// Redirect printf -> Serial
static int serial_putc(char c, FILE *stream) {
    Serial.write(c);
    return 0;
}

static FILE serial_stdout;

void serialInit(unsigned long baudRate) {
    Serial.begin(baudRate);

    fdev_setup_stream(&serial_stdout, serial_putc, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_stdout;

    serialPrint("System Ready!");
    serialPrint("Send 'led on' or 'led off'");
}

bool serialReadCommand(char* buffer, size_t size) {
    if (Serial.available() > 0) {
        size_t n = Serial.readBytesUntil('\n', buffer, size - 1);
        buffer[n] = '\0';

        // echo what was typed
        printf(">> %s\n", buffer);

        for (size_t i = 0; i < n; i++) {
        if (buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
        }
        return true;
    }
    return false;
}

void serialPrint(const char* message) {
    printf("%s\n", message);
}
