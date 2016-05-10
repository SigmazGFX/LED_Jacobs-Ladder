
int trigger = 17; //analog pin 3  //this pin currently goes LOW to activate a WAV shield, we can eliminate that addon by using the TMRPWM library and a hard wired SD card.

int PIR = 19;    //analog pin 5  //Tie pin high to start animation currently defined to utlize a PIR sensor

int LEDPin = 13; //cuurently goes high for 300ms and then low again when PIR event it tied HIGH Im assuming this is to wake up the origianl EL distro card.

#define A  2  // - pins for corrosponding LED's on ladder A-H
#define B  3
#define C  4
#define D  5
#define E  6
#define F  7
#define G  8
#define H  9
#define pulse_width  3

void on(char);
void off(char);
void all_on(void);
void all_off(void);
void fade_in(char);
void fade_out(char);

void setup()                    // run once, when the sketch starts
{
   all_off();
  pinMode(trigger, OUTPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(trigger, HIGH);
  pinMode(PIR, INPUT);
}

void loop()                     // run over and over again
{
  if (digitalRead(PIR) == HIGH) {
    digitalWrite(trigger, LOW);
    digitalWrite(LEDPin, HIGH);
    delay(300);
    digitalWrite(trigger, HIGH);
    digitalWrite(LEDPin, LOW);
    for (int string = A; string <= H; string++)
    {
      fade_in(string);
      delay(5);
      fade_out(string);
    }
    delay(500);
  }
}

void fade_in(char channel)
{
  for (int brightness = 0; brightness <= pulse_width; brightness++) {
    for (int duration = 0; duration < 1; duration++) {
      on(channel);
      delay(brightness);
      off(channel);
      delay(pulse_width - brightness);
    }
  }
  on(channel);
}

void fade_out(char channel)
{
  for (int brightness = pulse_width; brightness >= 0; brightness--) {
    for (int duration = 0; duration < 1; duration++) {
      on(channel);
      delay(brightness);
      off(channel);
      delay(pulse_width - brightness);
    }
  }
}
void all_off(void)
{

  for (int i = A; i < 10; i++)
    off(i);
}
void off(char channel)
{
  pinMode(channel, INPUT);
}
void on(char channel)
{
  pinMode(channel, OUTPUT);
  digitalWrite(channel, LOW);
}
