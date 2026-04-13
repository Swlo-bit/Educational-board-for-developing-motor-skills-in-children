#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#define MP3_ERROR_ONLY 1
#define MP3_ALL_MESSAGE 2

class MP3Player
{
private:
    HardwareSerial *mp3Serial;
    void statusOnSerial(uint8_t type, int value);
    void waitPlayIsTerminated(void);

public:
    DFRobotDFPlayerMini player;
    MP3Player(HardwareSerial &serial);
    void playTrackNumber(int trackNumber, int volume, boolean waitPlayTerminated = false);
    boolean playCompleted(void);
    void initialize(void);
    int serialPrintStatus(int errorOnly);
};
