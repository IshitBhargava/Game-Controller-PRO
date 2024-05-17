const int JoyStick_pin = A5; //plug Joystick 'Button' into pin 8
const int X_pin = A1;       //plug joystick X direction into pin A0
const int Y_pin = A0;       //plug joystick Y direction into pin A1
const int Potentiometer_pin = A2; //plug potentiometer into pin A2
const int buttonPin1 = 8;  // Button 1 connected to digital pin 2
const int buttonPin2 = 10;  // Button 2 connected to digital pin 3
int xc;
int yc;
int JSButton;

void setup() {
  pinMode(JoyStick_pin, INPUT);
  pinMode(Potentiometer_pin, INPUT); // Set potentiometer pin as input
  pinMode(buttonPin1, INPUT_PULLUP);  // Set button 1 pin as input with pull-up resistor
  pinMode(buttonPin2, INPUT_PULLUP);  // Set button 2 pin as input with pull-up resistor
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  int x = analogRead(X_pin);  //read x direction value and -517 to bring back to around 0
  int y = analogRead(Y_pin);  //read y direction value and -512 to bring back to around 0    525
  int potValue = analogRead(Potentiometer_pin); // Read potentiometer value
  int buttonState1 = digitalRead(buttonPin1);  // Read the state of button 1
  int buttonState2 = digitalRead(buttonPin2);  // Read the state of button 2
  if (x < 480) {         
  xc = 0;
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
} else if (x > 550) {   
  xc = 2;
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
} else {
  xc = 1;
  digitalWrite(3, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
}

    
  if(xc != 1){
    yc = 1 ;
  } else {
    if (y < 490) {
      yc = 2;
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    } else if (y > 540) {
      yc = 0;
      digitalWrite(3, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    } else {
      yc = 1;
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }
  }
  int buttonStates = 0;   //set starting value of Joystick button
  int bvalue = analogRead(JoyStick_pin);
  if(bvalue >512){
    buttonStates = 1;
  }

  // Map potentiometer value to ranges and output corresponding values
  int mappedValue;
  if (potValue >= 1 && potValue <= 100) {
    mappedValue = 0;
  } else if (potValue >= 101 && potValue <= 200) {
    mappedValue = 1;
  } else if (potValue >= 201 && potValue <= 300) {
    mappedValue = 2;
  } else if (potValue >= 301 && potValue <= 400) {
    mappedValue = 3;
  } else if (potValue >= 401 && potValue <= 500) {
    mappedValue = 4;
  } else if (potValue >= 501 && potValue <= 600) {
    mappedValue = 5;
  } else if (potValue >= 601 && potValue <= 700) {
    mappedValue = 6;
  } else if (potValue >= 701 && potValue <= 800) {
    mappedValue = 7;
  } else if (potValue >= 801 && potValue <= 900) {
    mappedValue = 8;
  } else if (potValue >= 901 && potValue <= 1000) {
    mappedValue = 9;
  } else {
    mappedValue = 10;
  }
  //Serial.println(x);
  //Serial.println(y);
  
  Serial.print("S");  //start printing the data, format is Sxc,yc,buttonStates,mappedValue > S1,1,0,5
  Serial.print(xc);
  Serial.print(",");
  Serial.print(yc);
  Serial.print(",");
  Serial.print(buttonStates);
  Serial.print(",");
  Serial.print(mappedValue);
  Serial.print(",");
  Serial.print(buttonState1);
  Serial.print(",");
  Serial.println(buttonState2);

  
  delay(40);
}
