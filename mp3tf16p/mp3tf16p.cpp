#include "mp3tf16p.h"

MP3Player::MP3Player(HardwareSerial &serial)
{
    mp3Serial = &serial;
}

void MP3Player::initialize(void)
{
    mp3Serial->begin(9600);
    Serial.println(F("Initializing MP3Player ..."));

    if (!player.begin(*mp3Serial, true, false))
    {
        Serial.println(F("Unable to begin DFPlayer"));
        while (true);
    }

    player.volume(15);
    Serial.println(F("MP3Player online."));
}

void MP3Player::playTrackNumber(int trackNumber, int volume, boolean waitPlayTerminated)
{
    if (trackNumber < 1) return;

    player.volume(volume);
    player.play(trackNumber);

    if (waitPlayTerminated)
        waitPlayIsTerminated();
}


void MP3Player::waitPlayIsTerminated(void)
{
    while (!playCompleted()) {}
}

boolean MP3Player::playCompleted(void)
{
    if (player.available())
        return player.readType() == DFPlayerPlayFinished;

    return false;
}

int MP3Player::serialPrintStatus(int verbose)
{
    if (player.available())
    {
        uint8_t type = player.readType();
        int value = player.read();

        if (verbose == MP3_ERROR_ONLY && type != DFPlayerError)
            return 0;

        statusOnSerial(type, value);
        return (type == DFPlayerError) ? value : 0;
    }
    return 0;
}

void MP3Player::statusOnSerial(uint8_t type, int value)
{
    if (type == DFPlayerError)
    {
        Serial.print(F("DFPlayerError: "));
        Serial.println(value);
    }
}
