/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/communication/SerialEvent/
*/

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

const int FRONT_IN1 = 47;//G
const int FRONT_IN2 = 51;//B
const int FRONT_SPEED = 13;//Y

const int BACK_IN1 = 37;//G
const int BACK_IN2 = 39;//B
const int BACK_SPEED = 9;//Y

const int RIGHT_IN1 = 49;//G
const int RIGHT_IN2 = 53;//B
const int RIGHT_SPEED = 6;//Y

const int LEFT_IN1 = 35;//G
const int LEFT_IN2 = 41;//B
const int LEFT_SPEED = 8;//Y

const int SPINNY_DIR = 30;
const int SPINNY_SPEED = 10;



void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);



  pinMode(FRONT_IN1,OUTPUT);
  pinMode(FRONT_IN2,OUTPUT);
  pinMode(FRONT_SPEED,OUTPUT);
    pinMode(BACK_IN1,OUTPUT);
  pinMode(BACK_IN2,OUTPUT);
  pinMode(BACK_SPEED,OUTPUT);
    pinMode(LEFT_IN1,OUTPUT);
  pinMode(LEFT_IN2,OUTPUT);
  pinMode(LEFT_SPEED,OUTPUT);
    pinMode(RIGHT_IN1,OUTPUT);
  pinMode(RIGHT_IN2,OUTPUT);
  pinMode(RIGHT_SPEED,OUTPUT);

  pinMode(SPINNY_SPEED,OUTPUT);
  pinMode(SPINNY_DIR,OUTPUT);

  pinMode(28,OUTPUT);

  digitalWrite(FRONT_IN1,LOW);
  digitalWrite(FRONT_IN2,LOW);
  analogWrite(FRONT_SPEED,0);
  digitalWrite(BACK_IN1,LOW);
  digitalWrite(BACK_IN2,LOW);
  analogWrite(BACK_SPEED,0);
  digitalWrite(LEFT_IN1,LOW);
  digitalWrite(LEFT_IN2,LOW);
  analogWrite(LEFT_SPEED,0);
  digitalWrite(RIGHT_IN1,LOW);
  digitalWrite(RIGHT_IN2,LOW);
  analogWrite(RIGHT_SPEED,0);

  digitalWrite(SPINNY_DIR,LOW);
  analogWrite(SPINNY_SPEED,0);

  digitalWrite(28,HIGH);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}


void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    // Serial.println(inputString);
    if(inputString.startsWith("mv")){
    // Find comma positions
    int firstComma = inputString.indexOf(',');
    int secondComma = inputString.indexOf(',', firstComma + 1);

    // Extract parts
    String command = inputString.substring(0, firstComma);
    String xStr = inputString.substring(firstComma + 1, secondComma);
    String yStr = inputString.substring(secondComma + 1);
      
      int xInt = xStr.toInt();
      int yInt = yStr.toInt();

      //parse input string to get x and y values

      if(yInt>20){
        digitalWrite(LEFT_IN1,HIGH);
        digitalWrite(LEFT_IN2,LOW);
        analogWrite(LEFT_SPEED, abs(yInt*2)); //0-255

        digitalWrite(RIGHT_IN1,LOW);
        digitalWrite(RIGHT_IN2,HIGH);
        analogWrite(RIGHT_SPEED, abs(yInt*2)); //0-255
      }else if(yInt<-20){
        digitalWrite(LEFT_IN1,LOW);
        digitalWrite(LEFT_IN2,HIGH);
        analogWrite(LEFT_SPEED, abs(yInt*2)); //0-255

        digitalWrite(RIGHT_IN1,HIGH);
        digitalWrite(RIGHT_IN2,LOW);
        analogWrite(RIGHT_SPEED, abs(yInt*2)); //0-255
      }else{
        digitalWrite(LEFT_IN1,LOW);
        digitalWrite(LEFT_IN2,LOW);
        analogWrite(LEFT_SPEED, 0); //0-255

        digitalWrite(RIGHT_IN1,LOW);
        digitalWrite(RIGHT_IN2,LOW);
        analogWrite(RIGHT_SPEED, 0); //0-255
      }

      if(xInt>20){
        digitalWrite(FRONT_IN1,HIGH);
        digitalWrite(FRONT_IN2,LOW);
        analogWrite(FRONT_SPEED, abs(xInt*2)); //0-255

        digitalWrite(BACK_IN1,HIGH);
        digitalWrite(BACK_IN2,LOW);
        analogWrite(BACK_SPEED, abs(xInt*2)); //0-255
      }else if(xInt<-20){
        digitalWrite(FRONT_IN1,LOW);
        digitalWrite(FRONT_IN2,HIGH);
        analogWrite(FRONT_SPEED, abs(xInt*2)); //0-255`

        digitalWrite(BACK_IN1,LOW);
        digitalWrite(BACK_IN2,HIGH);
        analogWrite(BACK_SPEED, abs(xInt*2)); //0-255
      }else{
        digitalWrite(FRONT_IN1,LOW);
        digitalWrite(FRONT_IN2,LOW);
        analogWrite(FRONT_SPEED, 0); //0-255`

        digitalWrite(BACK_IN1,LOW);
        digitalWrite(BACK_IN2,LOW);
        analogWrite(BACK_SPEED, 0); //0-255
      }

    }

    if(inputString.startsWith("ra")){
    // Find comma positions
    int firstComma = inputString.indexOf(',');
    int secondComma = inputString.indexOf(',', firstComma + 1);

    // Extract parts
    String command = inputString.substring(0, firstComma);
    String xStr = inputString.substring(firstComma + 1, secondComma);
      
      int xInt = xStr.toInt();

      //parse input string to get x and y values

      if(xInt>20){
        digitalWrite(SPINNY_DIR,HIGH);
        analogWrite(SPINNY_SPEED,abs(xInt*2));
      }else if(xInt<-20){
        digitalWrite(SPINNY_DIR,LOW);
        analogWrite(SPINNY_SPEED,abs(xInt*2));
      }else{
        analogWrite(SPINNY_SPEED,0);
      }
    }

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
