#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

SdFatSdioEX sdEx; // OR SdFatSdio sdEx;

#define GD3_CS 21
// Also adjust '#define CS 8' to match
// in ../libraries/Gameduino2/transports/wiring.h
#define GD3_SCLK 14
#define GD3_MOSI 7
#define GD3_MISO 12

void setup()
{
  // Set the desired pins for Teensy 3.6 before calling GD.begin()
  SPI.setMOSI(GD3_MOSI);
  SPI.setMISO(GD3_MISO);
  SPI.setSCK(GD3_SCLK);
  SPI.begin();

  Serial.begin(115200);
  delay(1000);

  if (!sdEx.begin()) {
    Serial.println("SdFatSdioEX begin() failed");

    sdEx.initErrorHalt("SdFatSdioEX begin() failed");
  }
  sdEx.chvol(); // make sdEx the current volume.

  GD.begin();
  GD.cmd_loadimage(0, 0);
  GD.load("healsky3.jpg");
}

void loop()
{
  GD.Clear();
  GD.Begin(BITMAPS);
  GD.Vertex2ii(0, 0);
  GD.swap();
}
