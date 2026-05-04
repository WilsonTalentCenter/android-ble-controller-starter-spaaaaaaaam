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

const int FRONT_IN1 = 12;
const int FRONT_IN2 = 13;
const int FRONT_SPEED = 14;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(FRONT_IN1,OUTPUT);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

string parse(string parse_string){
    std::string input = "rt,15,16";

    // Find comma positions
    size_t firstComma = input.find(',');
    size_t secondComma = input.find(',', firstComma + 1);

    // Extract parts
    std::string command = input.substr(0, firstComma);
    std::string xStr = input.substr(firstComma + 1, secondComma - firstComma - 1);
    std::string yStr = input.substr(secondComma + 1);

    // Convert manually from string to int
    int x = 0, y = 0;

    for (char c : xStr) {
        x = x * 10 + (c - '0');
    }

}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString.startsWith("rt")){

      
      //parse input string to get x and y values
      digitalWrite(FRONT_IN1,HIGH);
      digitalWrite(FRONT_IN2,LOW);
      analogWrite(FRONT_SPEED, ); //0-255
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
