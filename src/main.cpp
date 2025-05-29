#include <Arduino.h>
#include "Encoder.h"
// #include "HeartbeatLed.h"

#include "HID-Project.h"

using std::uint8_t;

enum
{
  ledBuiltinPin = LED_BUILTIN,
  taskStackSize = 10000,
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

  BootKeyboard.begin();
  BootKeyboard.releaseAll();

  Consumer.begin();
}

void loop()
{
  encoder.Run();
  delay(50);

  // This is dumb, no velocity or momentum, just one click = 1 volume
  uint8_t position = encoder.GetPosition();
  encoder.SetPosition(0);
  if(position > 0)
  {
    for(; position > 0; position--)
    {
      Consumer.write(MEDIA_VOLUME_UP)
    }
  }
  else
  {
    for(; position < 0; position++)
    {
      Consumer.write(MEDIA_VOLUME_DOWN)
    }
  }
}