#include <Arduino.h>
#include "Encoder.h"
// #include "HeartbeatLed.h"

#include "HID-Project.h"

#ifndef AVR
using std::uint8_t;
#endif

enum
{
  // ledBuiltinPin = LED_BUILTIN,
  StepsPerVolumeCommand = 4,
};

Encoder &encoder = Encoder::getInstance();
// HeartbeatLed hbLed = HeartbeatLed(ledBuiltinPin);

static int pendingRotation;
static bool prevButton;

void setup()
{
  Serial.begin(115200);

  encoder.Init();

  BootKeyboard.begin();
  BootKeyboard.releaseAll();
  Consumer.begin();
}

void loop()
{
  // delay(200);

  // bool pressed = !digitalRead(2);

  // if(pressed && !prevPressed)
  // {
  //   Serial.println("Pressed!\n");
  //   Consumer.write(MEDIA_VOLUME_MUTE);
  // }

  // prevPressed = pressed;

  encoder.Run();

  pendingRotation += encoder.GetPosition();
  encoder.SetPosition(0);

  if(pendingRotation >= StepsPerVolumeCommand)
  {
    Consumer.write(MEDIA_VOLUME_UP);
    pendingRotation -= StepsPerVolumeCommand;
  }
  else if(pendingRotation <= (0 - StepsPerVolumeCommand))
  {
    Consumer.write(MEDIA_VOLUME_DOWN);
    pendingRotation += StepsPerVolumeCommand;
  }

  // Serial.print(digitalRead(2));
  // Serial.print("   ");
  // Serial.print(digitalRead(3));
  // Serial.print("   ");
  // Serial.print(digitalRead(7));
  // Serial.println();

  // This is disabled b/c my encoder is broken, and somehow the button is tied to one of the encoder pins?

  // bool button = encoder.GetButton();
  // if(button != prevButton)
  // {
  //   Consumer.write(MEDIA_VOLUME_MUTE);
  //   prevButton = button;
  // }

  delay(50);
}