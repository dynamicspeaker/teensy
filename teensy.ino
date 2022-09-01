#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AsyncAudioInputSPDIF3    spdif_async1(false, false, 120, 70, 80);   //xy=446.41976165771484,696.1728219985962
AudioInputUSB            usb_in;         //xy=482.8641662597656,628.8394775390625
AudioMixer4              mixer2;         //xy=630.8641662597656,793.8394775390625
AudioMixer4              mixer1;         //xy=780.8641662597656,635.8394775390625
AudioMixer4              mixer_mono;     //xy=810.8641662597656,847.8394775390625
AudioFilterStateVariable filter2;        //xy=975.8641662597656,623.8394775390625
AudioFilterStateVariable filter_lp;      //xy=981.1975173950195,882.061695098877
AudioFilterStateVariable filter1;        //xy=984.8641662597656,693.8394775390625
AudioAnalyzeNoteFrequency notefreq1;      //xy=1179.3085556030273,855.5061359405518
AudioOutputI2S           i2s_out;        //xy=1185.8641662597656,624.8394775390625
AudioConnection          patchCord1(spdif_async1, 0, mixer1, 0);
AudioConnection          patchCord2(spdif_async1, 1, mixer2, 0);
AudioConnection          patchCord3(usb_in, 0, mixer1, 1);
AudioConnection          patchCord4(usb_in, 1, mixer2, 1);
AudioConnection          patchCord5(mixer2, 0, mixer_mono, 1);
AudioConnection          patchCord6(mixer1, 0, mixer_mono, 0);
AudioConnection          patchCord7(mixer_mono, 0, filter_lp, 0);
AudioConnection          patchCord8(mixer_mono, 0, filter1, 0);
AudioConnection          patchCord9(mixer_mono, 0, filter2, 0);
AudioConnection          patchCord10(filter2, 0, i2s_out, 0);
AudioConnection          patchCord11(filter_lp, 0, notefreq1, 0);
AudioConnection          patchCord12(filter1, 2, i2s_out, 1);
// GUItool: end automatically generated code


unsigned long prevRun1 = 0;

void setup() {
  // put your setup code here, to run once:

  AudioMemory(1000);

  
  mixer_mono.gain(0, 0.5);
  mixer_mono.gain(1, 0.5);
  
  mixer1.gain(0, 1);
  mixer2.gain(0, 1);
  
  filter_lp.frequency(100);
  filter_lp.octaveControl(1.0);
  filter_lp.resonance(0.707);
  
  filter1.frequency(150);
  filter1.resonance(0.707);

  filter2.frequency(150);
  filter2.resonance(0.707);
  
  //set_volume();

  notefreq1.begin(.5);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  set_volume();

  if (notefreq1.available()) {
    float note = notefreq1.read();
    float prob = notefreq1.probability();
    Serial.printf("Note: %3.2f | Probability: %.2f\n", note, prob);
  }

  if (millis() - prevRun1 > 200) {
    prevRun1 = millis();
  }
}

void set_volume() {
  float gain_setting = pow(2, usb_in.volume()) - 1;
  mixer1.gain(1, gain_setting);
  mixer2.gain(1, gain_setting);
}
