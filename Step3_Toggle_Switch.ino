// define pins I am using

const int Xpin = A0;

//variables for analog readings
int X;

void setup() {
  //Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //read analog pins

  X = analogRead(Xpin);

  //print values
  Serial.print("X: ");
  Serial.print(X);
  Serial.print("\n");
  delay(700);

  if (X > 517){
    Serial.print("Toggle up");
  }
  else if (X < 517){
    Serial.print("Toggle down");
  }

}
