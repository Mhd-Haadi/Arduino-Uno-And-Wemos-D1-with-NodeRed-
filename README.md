The project simulate a beverage online order based on two bottle sizes Large and Small which is ordered via a GUI on NodeRed.
The project relates to the use of Arduino Uno and NodeMCU ESP8266 combines with RFID readers and servo motors.
The data transmission is done via NodeRed through a GUI
The connection between the Arduino Uno to the NodeMCU is a Slave-to-Master connection respectively.
The code is divided into three sections.
The Transmission from NodeRed_to_Arduino_Uno.ino provides the code required to upload for transmission of data from NodeRed via wifi to the NodeMCU to read RFID tags and continue the process until the beverage order is completed
The Nodemcu_master_microcontroller.ino file provide the codes for the connection and set up between the nodeMCU and Arduino Uno
An additional PNG for the connections between the two micro controller is also available
