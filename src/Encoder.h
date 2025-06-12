#ifndef ENCODER_H
#define ENCODER_H

#ifdef AVR
#include <stdint.h>
#else
#include <cstdint>

using std::uint8_t;
#endif

class Encoder
{
public:
    static Encoder &getInstance();

    void Init();
    void Run();

    uint8_t GetPosition();
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
