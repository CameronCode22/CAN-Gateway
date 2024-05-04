#include <mcp2515.h>

#include <SPI.h>              //Library for using SPI Communication 

// Define the CS pin for each MCP2515 board
const int CS_PIN_1 = 10;
const int CS_PIN_2 = 9;

//create instances of teh MCP2515 class for each board
MCP2515 mcp2515_1(CS_PIN_1);
MCP2515 mcp2515_2(CS_PIN_2);

struct can_frame canMsg; 

void setup() {

  SPI.begin();                       //Begins SPI communication

  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate 

  mcp2515_1.reset();
  mcp2515_2.reset();                          

  mcp2515_1.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515_2.setBitrate(CAN_500KBPS,MCP_8MHZ);

  mcp2515_1.setNormalMode();
  mcp2515_2.setNormalMode();                  //Sets CAN at normal mode

}

int x;
int y;

void loop() 

{
  
  if (mcp2515_2.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)

  {

     x = 0x20         
     y = 0x30    

     Serial.print("MCP CAN 2 board");
     Serial.print("\n");
     Serial.print(x);   
    }


  canMsg.can_id = 0x030;
  canMsg.can_dlc = 8;
  canMsg.data[0] = x;
  canMsg.data[1] = y;
  canMsg.data[2] = 0x00;
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x20;
  canMsg.data[7] = 0x20;
  mcp2515_1.sendMessage(&canMsg); //sends the CAN message on M2
  
  delay(1000);

}


