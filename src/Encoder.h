#ifndef ENCODER_H
#define ENCODER_H

#ifdef AVR
#include <stdint.h>
#else
#include <cstdint>

using std::int8_t;
#endif

class Encoder
{
public:
    // I made this a singleton b/c of the ISRs, but b/c it's Arduino, it doesn't have to be
    static Encoder &getInstance();

    void Init();
    void Run();

    int8_t GetPosition();
    void SetPosition(uint8_t position);

    bool GetButton();
    void SetButton(bool button);

private:
    Encoder() {}

    bool initialized = false;

public:
    Encoder(Encoder const &) = delete;
    void operator=(Encoder const &) = delete;
};

#endif
