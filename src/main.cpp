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
  // taskStackSize = 10000,
};

Encoder &encoder = Encoder::getInstance();
// HeartbeatLed hbLed = HeartbeatLed(ledBuiltinPin);

// TaskHandle_t BleTaskHandle;

// void BluetoothTask(void *parameter)
// {
//   (void)parameter;

//   while (true)
//   {
//     delay(200);

//     bool button = encoder.GetButton();
//     bluetooth.SetButton(button);

//     uint8_t position = encoder.GetPosition();
//     bluetooth.SetPosition(position);
//   }
// }

void setup()
{
  Serial.begin(115200);

  encoder.Init();
  // bluetooth.Init(&hbLed);

  // xTaskCreate(BluetoothTask, "BLE Task", taskStackSize, NULL, 1, &BleTaskHandle);

  pinMode(2, INPUT_PULLUP);

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
  delay(50);

  // Serial.print(digitalRead(2));
  // Serial.print("   ");
  // Serial.print(digitalRead(3));
  // Serial.print("   ");
  // Serial.print(digitalRead(7));
  // Serial.println();

  // // This is dumb, no velocity or momentum, just one click = 1 volume
  uint8_t _position = encoder.GetPosition();
  int8_t position = *(int8_t *)&_position;
  encoder.SetPosition(0);

  Serial.println(position);

  if(position > 0)
  {
    for(; position > 0; position--)
    {
      Consumer.write(MEDIA_VOLUME_UP);
    }
  }
  else
  {
    for(; position < 0; position++)
    {
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
  }
}