#include <LiquidCrystal.h>    //Library for LCD screen
#include <mcp2515.h>          //Library for CAN interfaces
#include <SPI.h>              //Library for using SPI Communication 

//Define the CS pin for each MCP2515 board
const int CS_PIN_1 = 9;
const int CS_PIN_2 = 10;

//create instances of the MCP2515 class for each board
MCP2515 mcp2515_1(CS_PIN_1);
MCP2515 mcp2515_2(CS_PIN_2);

struct can_frame canMsg; 

// Pins for LCD screen
const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define analogue pin for joystick
const int Xpin = A0;

// Variable for analogue reading
int X;

// Variable to track state of joystick (up or down)
bool joystickUp = false;
bool joystickDown = false;

// Variable to track timestamp when the joystick was last moved
unsigned long lastJoystickUpTime = 0;
unsigned long lastJoystickDownTime = 0;

int currentRiderWeight = 90;

//Blocked CAN messages & quantity of blocked signals
int PassThroughAdressesBlocked[] = {0x500, 0x200, 0x55};
int actualsize = sizeof(PassThroughAdressesBlocked)/sizeof(PassThroughAdressesBlocked[0]);

void setup() {
  SPI.begin();                       //Begins SPI communication

  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate 

  mcp2515_1.reset();
  mcp2515_2.reset();                          

  mcp2515_1.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515_2.setBitrate(CAN_500KBPS,MCP_8MHZ);

  mcp2515_1.setNormalMode();                  //Sets CAN at normal mode
  mcp2515_2.setNormalMode();                  //Sets CAN at normal mode

  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  delay(100);

  lcd.print("Rider Weight:");
  // Set the cursor to column 0, line 1
  // Line 1 is second row, as it begins at 0
  lcd.setCursor(0, 1);
  lcd.print("90 Kg");
}

void loop() {

  X = analogRead(Xpin);

  // Joystick Up Logic
  if (X > 600) {
    if (!joystickUp) {
      lastJoystickUpTime = millis();
      joystickUp = true;
    }

    if (millis() - lastJoystickUpTime >= 2000) {
      updateRiderWeightUp();
    }
  } else {
    // Joystick is not up
    joystickUp = false;
  }

  // Joystick Down Logic
  if (X < 450) {

    if (!joystickDown) {
      lastJoystickDownTime = millis();
      joystickDown = true;
    }

    if (millis() - lastJoystickDownTime >= 2000) {
      updateRiderWeightDown();
    }
  } else {
    // Joystick is not down
    joystickDown = false;
  }

  if (mcp2515_1.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  { 
    passthrough_CAN1_TO_CAN2();
  }

  if (mcp2515_2.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  { 
    passthrough_CAN2_TO_CAN1();
  }
}

void updateRiderWeightUp() {
  currentRiderWeight += 5;
  updateLCD();
  delay(500);
}

void updateRiderWeightDown() {
  currentRiderWeight -= 5;
  updateLCD();
  delay(500);
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rider Weight:");
  lcd.setCursor(0, 1);
  lcd.print(currentRiderWeight);
  lcd.print(" Kg");
  Serial.println(currentRiderWeight);
}

void passthrough_CAN1_TO_CAN2(){
  bool blockMessage = false;

  //check if the recieved message's ID is in the list of blocked adresses
    for (int i = 0; i < sizeof(PassThroughAdressesBlocked) / sizeof(PassThroughAdressesBlocked[0]); i++) {
      if (canMsg.can_id == PassThroughAdressesBlocked[i]) {
        //check if signal blocked was one i want to add rider weight too
        if(canMsg.can_id == 0x500){
          addRiderWeightToMessage();
          mcp2515_2.sendMessage(&canMsg);
        }
        
        blockMessage = true;
        break; // Exit loop as soon as match found
    }
  }

  // If the message is not blocked, send it to CAN 2
    if (!blockMessage) {
      mcp2515_2.sendMessage(&canMsg);
  }
}

void passthrough_CAN2_TO_CAN1(){
  bool blockMessage = false;

  //check if the recieved message's ID is in the list of blocked adresses
    for (int i = 0; i < sizeof(PassThroughAdressesBlocked) / sizeof(PassThroughAdressesBlocked[0]); i++) {
      if (canMsg.can_id == PassThroughAdressesBlocked[i]) {
        blockMessage = true;
        break; // Exit loop as soon as match found
    }
  }

  // If the message is not blocked, send it to CAN 2
    if (!blockMessage) {
      mcp2515_1.sendMessage(&canMsg);
  }
}

void addRiderWeightToMessage(){
  canMsg.data[7] = currentRiderWeight;
}


