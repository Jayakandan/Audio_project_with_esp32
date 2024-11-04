#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include "FS.h"
#include "SPIFFS.h"

#define I2S_DOUT 25  // Connect to your DAC's data out pin
#define I2S_BCLK 27  // Connect to your DAC's bit clock pin
#define I2S_LRC 26   // Connect to your DAC's word select pin

Audio audio;
String ssid = "ACTFIBERNET";       // Replace with your WiFi SSID
String password = "act12345"; // Replace with your WiFi password

void setup() {
    Serial.begin(115200);

    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    // Connect to Wi-Fi (optional if you don't need WiFi)
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(1500);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi!");

    // Set up audio output
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(100); // Set volume level (0-255)

    // Connect to the audio file in SPIFFS
    if (!audio.connecttofile("/sample.wav")) {
        Serial.println("Failed to connect to audio file");
    }
}

void loop() {
    audio.loop(); // Keep audio playback running
}
