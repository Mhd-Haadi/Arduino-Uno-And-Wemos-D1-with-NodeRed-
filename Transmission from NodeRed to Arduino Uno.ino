#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include <SPI.h>
//#include <Servo.h>
#define SS_PIN D10
#define RST_PIN D9
#define SS_PIN1 D4
#define RST_PIN1 D2
#define MQTT_SERVER "iot.eclipse.org" //MQTT BROKER ADD
//Servo servosmall;
//Servo servolarge;
byte y=0; byte z=0; byte data = 1; 
byte c=0; //small 
byte d=0; //big
int count=0;char buf[4];
const char* ssid = "Xperia Z3_dd07"; 
const char* password= "ae25cb40d16b";
char* Topic="Topic12343"; //Topic to be notifed about
WiFiClient wifiClient;

MFRC522 rfid1(SS_PIN1, RST_PIN); // Instance of the class
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 
byte sector         = 1;
byte blockAddr      = 4;
byte dataBlock[3]  ;
byte trailerBlock   = 7;
int flag=0;
byte a=0; // a defines the number of times the process of verifying and writing for rfid
int code1[] = {0xCE,0xCA,0x84,0xB9}; //This is the stored UID
int code2[] = {0xF0,0x95,0x1C,0xA4};
int codeRead = 0;
byte beverage = 0;
byte litre = 1;
byte number = 0;
String uidString;
byte toread[16];
byte sector1         = 1;
byte blockAddr1      = 4;
byte dataBlock1[3]  ;
byte trailerBlock1   = 7;
int flag1=0;
byte a1=0; // a defines the number of times the process of verifying and writing for rfid
byte e=0;
int codeRead1 = 0;
byte beverage1 = 0;
byte litre1 = 0;
byte number1 = 0;
String uidString1;
byte toread1[16];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while (!Serial);
delay (100);
//start wifi subsystem
WiFi.begin (ssid,password);
//attempt to reconnect to wifi
reconnect();
delay(2000);

//RFID initializing

SPI.begin(); // Init SPI bus
  rfid.PCD_Init(SS_PIN, RST_PIN); // Init MFRC522 
  // Init MFRC522 
  rfid.PCD_DumpVersionToSerial();
   rfid1.PCD_Init(SS_PIN1, RST_PIN1);
  rfid1.PCD_DumpVersionToSerial();
   
   for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }
  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);

 //servolarge.attach (D2);// attach the servo to the pin 6 
// servosmall.attach (D15); 
}
PubSubClient client(MQTT_SERVER,1883,callback,wifiClient);
void loop() {
  if(!client.connected()&&WiFi.status()==3) {reconnect();}


//Maintain MQTT connection
client.loop();
itoa (count, buf, 10);client.publish("outTopic12343",buf);
Serial.println("Connection maintained");



//codes for RFID

if((c >0) && (d>0)) //c & y small    d & z big
{ switch (e)


{
  case 1:
{

do{ 
  
do { //Verify Loop
      if ( ! rfid.PICC_IsNewCardPresent())
      
        return;

    // Select one of the cards
    if ( ! rfid.PICC_ReadCardSerial())
        
         return; 
  
      readRFID();
  }while (flag==0); //flag is the variable used to keep determine if writing can be done or not. if flag is equal to 1, do writing
  
  
//rfid.PICC_HaltA();
//
//  // Stop encryption on PCD
//  rfid.PCD_StopCrypto1();

do { Serial.println("Write now");
  { rfid.PCD_Init(SS_PIN, RST_PIN);
    if ( ! rfid.PICC_IsNewCardPresent())
      
        return;

    // Select one of the cards
    if ( ! rfid.PICC_ReadCardSerial())
        
         return;Serial.println("Recognised");
  }
  
  wemos1rfid();
 

Serial.print(a);
flag=0;
  } while (flag==1);
Serial.println("Done"); //a is the variable used to determine the whole loop for one complete process for the do while loop
Serial.println (a);
  servoLarge();
 do{  delay(200);
 data= Serial.read();

  }while(data !=2);
// while(!Serial.available());
count++;itoa (count, buf, 10); //converts number to string
client.publish("outTopic12343",buf);
a++; 
data=255;
}while (a<d);
a=0;
Serial.println("Done for Large");

  
e=0;
  break;
  }

  case 0:
  {


do{
  


//  Serial.println("Here");
 
 rfid1.PCD_Init(SS_PIN1, RST_PIN1);
    do { //Verify Loop
      
//      rfid1.PCD_Init(SS_PIN1, RST_PIN);
      if( ! rfid1.PICC_IsNewCardPresent())
      
        return;
//Serial.println (flag1);
//    // Select one of the cards
    if ( ! rfid1.PICC_ReadCardSerial())
       
         return; 
 
  
      readRFID1();
   }while (flag1==0); //flag is the variable used to keep determine if writing can be done or not. if flag is equal to 1, do writing
  
  
//rfid.PICC_HaltA();
//
//  // Stop encryption on PCD
//  rfid.PCD_StopCrypto1();

do { Serial.println("Write now");
   rfid1.PCD_Init(SS_PIN1, RST_PIN1);
    if ( ! rfid1.PICC_IsNewCardPresent())
      
        return;

    // Select one of the cards
    if ( ! rfid1.PICC_ReadCardSerial())
        
         return;Serial.println("Recognised");
  
  wemos2rfid();
 

Serial.print(a1);
flag1=0;
  } while (flag1==1);
Serial.println("Done"); //a is the variable used to determine the whole loop for one complete process for the do while loop
Serial.println (a1);

servoSmall();
do{  delay(200);
 data= Serial.read();
  }while(data!=2);
//  while(!Serial.available());

a1++;
data=255;
count++; itoa (count, buf, 10);client.publish("outTopic12343",buf);
}while (a1<c);
Serial.println("Done for small");
a1=0;



c=0; d=0; count =0;
break;
  }
  
  }
  
  
  
  }







if ((c >0) && (d==0)) //c and y small  d and z big Only small active

{
 do{
  


//  Serial.println("Here");
 
 rfid1.PCD_Init(SS_PIN1, RST_PIN1);
    do { //Verify Loop
      
//      rfid1.PCD_Init(SS_PIN1, RST_PIN);
      if( ! rfid1.PICC_IsNewCardPresent())
      
        return;
//Serial.println (flag1);
//    // Select one of the cards
    if ( ! rfid1.PICC_ReadCardSerial())
       
         return; 
 
  
      readRFID1();
   }while (flag1==0); //flag is the variable used to keep determine if writing can be done or not. if flag is equal to 1, do writing
  
  
//rfid.PICC_HaltA();
//
//  // Stop encryption on PCD
//  rfid.PCD_StopCrypto1();

do { Serial.println("Write now");
   rfid1.PCD_Init(SS_PIN1, RST_PIN1);
    if ( ! rfid1.PICC_IsNewCardPresent())
      
        return;

    // Select one of the cards
    if ( ! rfid1.PICC_ReadCardSerial())
        
         return;Serial.println("Recognised");
  
  wemos2rfid();
 

Serial.print(a1);
flag1=0;
  } while (flag1==1);
Serial.println("Done"); //a is the variable used to determine the whole loop for one complete process for the do while loop
Serial.println (a1);
servoSmall();
 do{  delay(200);
 data= Serial.read();

  }while(data !=2);
count++; itoa (count, buf, 10);client.publish("outTopic12343",buf);
a1++; 
data=255;
}while (a1< c);
Serial.println("Done for small");
c=0; a1=0;
count=0; 
  }
if((d>0) && (c==0)) // c and y small   d and z big. only big active

{
  do{ 
  
do { //Verify Loop
      if ( ! rfid.PICC_IsNewCardPresent())
      
        return;

    // Select one of the cards
    if ( ! rfid.PICC_ReadCardSerial())
        
         return; 
  
      readRFID();
  }while (flag==0); //flag is the variable used to keep determine if writing can be done or not. if flag is equal to 1, do writing
  
  
//rfid.PICC_HaltA();
//
//  // Stop encryption on PCD
//  rfid.PCD_StopCrypto1();

do { Serial.println("Write now");
  { rfid.PCD_Init(SS_PIN, RST_PIN);
    if ( ! rfid.PICC_IsNewCardPresent())
      
        return;

    // Select one of the cards
    if ( ! rfid.PICC_ReadCardSerial())
        
         return;Serial.println("Recognised");
  }
  
  wemos1rfid();
 

Serial.print(a);
flag=0;
  } while (flag==1);
Serial.println("Done"); //a is the variable used to determine the whole loop for one complete process for the do while loop
Serial.println ();
  servoLarge();
 do{  delay(200);
 data= Serial.read();
  }while(data !=2);
  
count++;itoa (count, buf, 10); //converts number to string
client.publish("outTopic12343",buf);
a++;
data=255;
}while (a<d);
Serial.println("Done for large");
d=0;count=0;
a=0;
  }

}
void callback(char* topic,byte * payload,unsigned int length)
{
  //convert topic to string to make it easier to work with
//  
//  Serial.println((byte)payload[0]);
  String topicStr=topic;
//  Serial.println(topic);
//  Serial.println(topicStr); 
 
  y= ((byte)payload[1])- '0';   
   c= y;
  z = ((byte)payload[3])- '0';
   d=z;
   if((c>0)&&(d>0))
   {e=1;}
  Serial.println(c);
Serial.println(d);
 

// client.publish("outTopic12343",);
 }
void reconnect()
{
  //attempt to reconnect to wifi if lost
  if(WiFi.status()!=WL_CONNECTED)
  {
    while (WiFi.status()!=WL_CONNECTED){
     delay(500);
     Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
     Serial.print("...");}
      }
  if(WiFi.status()==WL_CONNECTED){
    while(!client.connected()){
    //Generate client name based on MAC address and last 8 bits of microsecond counter
  String clientName;
  clientName+= "esp8266";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName+= macToStr(mac);
  if(client.connect((char*)clientName.c_str()))
  {
    Serial.println("\tMQTT Connected");
    client.subscribe(Topic);
    }
    else{Serial.println("\tFailed");abort();}
    }
  }
  }

  String macToStr(const uint8_t* mac)
  {
    String result;
    for(int i=0;i<6;++i)
    { result+= String(mac[i],16);
    if (i<5)
    {
     result+= ':'; }
      }
      return result;
    }



void readRFID()
{
  
  
  Serial.print(F("\nPICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

    
   
    Serial.println("Scanned PICC's UID:");
    printDec(rfid.uid.uidByte, rfid.uid.size);

    uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
    
    

    int i = 0;
    boolean match = true;
    while(i<rfid.uid.size)
    {
      if(!((rfid.uid.uidByte[i] == code1[i])||(rfid.uid.uidByte[i] == code2[i])))
      {
           match = false;
      }
      i++;
    }

    if(match)
    {
      Serial.println("\nI know this Bottle!");
      flag=1;
      //Function for further Processes 
      
    }else
    { flag =0;
      Serial.println("\nUnknown Bottle");
    }


    // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
void wemos1rfid() {
  Serial.println(flag);
   // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    Serial.println(rfid.PICC_GetTypeName(piccType));

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
    }

    // In this sample we use the second sector,
    // that is: sector #1, covering block #4 up to and including block #7
    
    
    MFRC522::StatusCode status;
    byte buffer[18];
    byte size = sizeof(buffer);
dataBlock[0] = beverage;
dataBlock[1] = litre;
dataBlock[2]= number;
    // Authenticate using key A
    Serial.println(F("Authenticating using key A..."));
    status = (MFRC522::StatusCode) rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(rfid.GetStatusCodeName(status));
        return;
    }

//    // Show the whole sector as it currently is
//    Serial.println(F("Current data in sector:"));
//    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
//    Serial.println();


//    // Write data to the block
     Serial.print(F("Writing data into block ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    dump_byte_array(dataBlock, 16); Serial.println();
    status = (MFRC522::StatusCode) rfid.MIFARE_Write(blockAddr, dataBlock, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(rfid.GetStatusCodeName(status));
    }
    Serial.println();

    // Read data from the block (again, should now be what we have written)
    Serial.print(F("Reading data from block ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    status = (MFRC522::StatusCode) rfid.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(rfid.GetStatusCodeName(status));
    }
    Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
    dump_byte_array(buffer, 16); Serial.println();
        
    // Check that data in block is what we have written
    // by counting the number of bytes that are equal
//    Serial.println(F("Checking result..."));
//    for (byte j= 0; j<4; j++)
//    {toread[j]=buffer[j];
//   }
//    byte count = 0;
//    for (byte i = 0; i < 4; i++) {
//        // Compare buffer (= what we've read) with dataBlock (= what we've written)
//        if (buffer[i] == dataBlock[i])
//            count++;
//    }
//    Serial.print(F("Number of bytes that match = ")); Serial.println(count);
//    if (count == 4) {
//        Serial.println(F("Success :-)"));
//        
//    }
//    else {
//        Serial.println(F("Failure, no match :-("));
//        Serial.println(F("  perhaps the write didn't work properly..."));
//    }
//    
//    Serial.println();
//        
    // Dump the sector data
    Serial.println(F("Current data in sector:"));
    rfid.PICC_DumpMifareClassicSectorToSerial(&(rfid.uid), &key, sector);
    Serial.println();

    // Halt PICC
    rfid.PICC_HaltA();
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
    
}


void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

void readRFID1()
{
  
  
  Serial.print(F("\nPICC type: "));
  MFRC522::PICC_Type piccType = rfid1.PICC_GetType(rfid1.uid.sak);
  Serial.println(rfid1.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

    
   
    Serial.println("Scanned PICC's UID:");
    printDec(rfid1.uid.uidByte, rfid1.uid.size);

    uidString1 = String(rfid1.uid.uidByte[0])+" "+String(rfid1.uid.uidByte[1])+" "+String(rfid1.uid.uidByte[2])+ " "+String(rfid1.uid.uidByte[3]);
    
    

    int i = 0;
    boolean match = true;
    while(i<rfid1.uid.size)
    {
      if(!((rfid1.uid.uidByte[i] == code1[i])||(rfid1.uid.uidByte[i] == code2[i])))
      {
           match = false;
      }
      i++;
    }

    if(match)
    {
      Serial.println("\nI know this Bottle!");
      flag1=1;
      //Function for further Processes 
      
    }else
    { flag1 =0;
      Serial.println("\nUnknown Bottle");
    }


    // Halt PICC
  rfid1.PICC_HaltA();

  // Stop encryption on PCD
  rfid1.PCD_StopCrypto1();
//  rfid1.PCD_Init(SS_PIN1, RST_PIN);
}

//void printDec(byte *buffer, byte bufferSize) {
//  for (byte i = 0; i < bufferSize; i++) {
//    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
//    Serial.print(buffer[i], DEC);
//  }
//}
void wemos2rfid() {
  Serial.println(flag1);
   // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(rfid1.uid.uidByte, rfid1.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = rfid1.PICC_GetType(rfid1.uid.sak);
    Serial.println(rfid1.PICC_GetTypeName(piccType));

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
    }

    // In this sample we use the second sector,
    // that is: sector #1, covering block #4 up to and including block #7
    
    
    MFRC522::StatusCode status;
    byte buffer[18];
    byte size = sizeof(buffer);
dataBlock1[0] = beverage1;
dataBlock1[1] = litre1;
dataBlock1[2]= number1;
    // Authenticate using key A
    Serial.println(F("Authenticating using key A..."));
    status = (MFRC522::StatusCode) rfid1.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock1, &key, &(rfid1.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(rfid1.GetStatusCodeName(status));
        return;
    }

//    // Show the whole sector as it currently is
//    Serial.println(F("Current data in sector:"));
//    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
//    Serial.println();


//    // Write data to the block
     Serial.print(F("Writing data into block ")); Serial.print(blockAddr1);
    Serial.println(F(" ..."));
    dump_byte_array(dataBlock1, 16); Serial.println();
    status = (MFRC522::StatusCode) rfid1.MIFARE_Write(blockAddr1, dataBlock1, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(rfid1.GetStatusCodeName(status));
    }
    Serial.println();

    // Read data from the block (again, should now be what we have written)
    Serial.print(F("Reading data from block ")); Serial.print(blockAddr1);
    Serial.println(F(" ..."));
    status = (MFRC522::StatusCode) rfid1.MIFARE_Read(blockAddr1, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(rfid1.GetStatusCodeName(status));
    }
    Serial.print(F("Data in block ")); Serial.print(blockAddr1); Serial.println(F(":"));
    dump_byte_array(buffer, 16); Serial.println();
        
    // Check that data in block is what we have written
    // by counting the number of bytes that are equal
//    Serial.println(F("Checking result..."));
//    for (byte j= 0; j<4; j++)
//    {toread[j]=buffer[j];
//   }
//    byte count = 0;
//    for (byte i = 0; i < 4; i++) {
//        // Compare buffer (= what we've read) with dataBlock (= what we've written)
//        if (buffer[i] == dataBlock[i])
//            count++;
//    }
//    Serial.print(F("Number of bytes that match = ")); Serial.println(count);
//    if (count == 4) {
//        Serial.println(F("Success :-)"));
//        
//    }
//    else {
//        Serial.println(F("Failure, no match :-("));
//        Serial.println(F("  perhaps the write didn't work properly..."));
//    }
//    
//    Serial.println();
//        
    // Dump the sector data
    Serial.println(F("Current data in sector:"));
    rfid1.PICC_DumpMifareClassicSectorToSerial(&(rfid1.uid), &key, sector1);
    Serial.println();

    // Halt PICC
    rfid1.PICC_HaltA();
    // Stop encryption on PCD
    rfid1.PCD_StopCrypto1();
    
}

void servoSmall ()
{
  Serial.println("Run Small Motor");
   Serial.write(2);
  delay(250);
  
//servosmall.write(360);
//delay(1270);
//servosmall.detach();
}

void servoLarge ()
{
  Serial.println("Run Large motor");
  Serial.write(1);
  delay(250);
//servolarge.write(360);
//delay(1270);
//servolarge.detach();
}


  
