# CAN-Gateway
![Screenshot](https://github.com/CameronCode22/CAN-Gateway/blob/main/Image_Folder_GitHub/CAN_Gateway.jpg)



Arduino CAN communication with LED &amp; toggle switch in order to select weight changes

Introduction: The CAN gateway was designed in order to block current signals on the CAN-bus. Edit them and put them back onto the bus. This method was chosen opposed to using developement signals in the electronic control units and sending messages to the module. Due to timing constraints.

This proposed a slightly more complicated solution, as in order to do a CAN gateway you need to physically splice the bus. This is my proof of concept I built with an Arduino:

I followed the most logical appraoch I could think of. And that was to modurarly build the code and hardware up.

Step 1 was to use the motherboards as one transciever and one reciever. While altering two bytes.
Step 2 was to test the LCD screen in isolation
Step 3 was to test the LCD along with the joystick
Final was to implement step 3 and the CAN gateway together, using functions for the CAN bypass and blocking certain signals I wanted to change



# What the Customer Wanted
a CAN-bus gateway in order to block exisiting signals, edit them and send them back onto the CAN-bus. They wanted a protype proof of concept, that they could manipulate the signals. Hence the choice for a CAN gateway rather than using developement signals and using a seperate node through the OBD port.

# What I Did
Created the concept, purchased required equipment, including the MCP-2515 CAN motherboards. 
Created the wiring input and boards
Delibvered business plan including extenral suppliers to the business
Risks, cost analysis
C++ code to operate
CANoe trace and replication to test gateway

# Results and Impact


This image shows the CAN passthrough function working correctly. Passing one signal from CAN1 onto CAN2
![Screenshot](https://github.com/CameronCode22/CAN-Gateway/blob/main/Image_Folder_GitHub/CAN_Passthrough.png?raw=true)
