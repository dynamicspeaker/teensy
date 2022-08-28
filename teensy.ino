#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S2           i2s2_1;         //xy=379.6666564941406,494.5555419921875
AudioInputUSB            usb_in;         //xy=411.6666564941406,430.5555419921875
AudioMixer4              mixer2;         //xy=559.6666564941406,595.5555419921875
AudioMixer4              mixer1;         //xy=709.6666564941406,437.5555419921875
AudioMixer4              mixer_mono;     //xy=739.6666564941406,649.5555419921875
AudioFilterStateVariable filter_lp;      //xy=886.6666564941406,591.5555419921875
AudioFilterStateVariable filter2;        //xy=904.6666717529297,425.55555725097656
AudioFilterStateVariable filter1;        //xy=913.6666717529297,495.55555725097656
AudioAnalyzeNoteFrequency notefreq1;      //xy=1023.6666564941406,650.5555419921875
AudioOutputI2S           i2s_out;        //xy=1114.6666564941406,426.5555419921875
AudioConnection          patchCord1(i2s2_1, 0, mixer1, 0);
AudioConnection          patchCord2(i2s2_1, 1, mixer2, 0);
AudioConnection          patchCord3(usb_in, 0, mixer1, 1);
AudioConnection          patchCord4(usb_in, 1, mixer2, 1);
AudioConnection          patchCord5(mixer2, 0, mixer_mono, 1);
AudioConnection          patchCord6(mixer2, 0, filter1, 0);
AudioConnection          patchCord7(mixer1, 0, mixer_mono, 0);
AudioConnection          patchCord8(mixer1, 0, filter2, 0);
AudioConnection          patchCord9(mixer_mono, 0, filter_lp, 0);
AudioConnection          patchCord10(filter_lp, 0, notefreq1, 0);
AudioConnection          patchCord11(filter2, 0, i2s_out, 0);
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
