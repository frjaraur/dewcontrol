#include <SimpleTimer.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
long previoustime =0;


// the timer object
SimpleTimer timer;

// Random Number
long randNumber;
long randNumber2;
String Numbers;

// a function to be executed periodically
void repeatMe() {
    //Serial.print("Uptime (s): ");
    Serial.println(millis());
    randomSeed(analogRead(0));
    randNumber = random(300);
}

void RepeatEvery10000secs() {
    //Serial.print("Uptime (s): ");
    previoustime = previoustime + 10000;
  if ((previoustime ) <= millis()){
    //Serial.println(millis());
    randomSeed(analogRead(0));
    randNumber = random(300);
    randNumber2=random(300);
    Numbers=String(randNumber + " " + randNumber2);
    Serial.println(Numbers);
  }
}


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
    // initialize the serial communications:
  Serial.begin(9600);
  
   //randomSeed(analogRead(0));
   
   timer.setInterval(10000, RepeatEvery10000secs);
   //timer.setInterval(1000, repeatMe);

}

// the loop routine runs over and over again forever:
void loop() {
 
  timer.run();
  
  // when characters arrive over the serial port...
  if (Serial.available()) {
    Serial.write("SERIAL\n");
    // wait a bit for the entire message to arrive
    //delay(100);
    // clear the screen
//    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      int i = 0;
      Serial.write(Serial.read());
      delay(10);
      //lcd.write(Serial.read());
    }
  }else{
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW

  //delay(1000);               // wait for a second
  }
    
}
