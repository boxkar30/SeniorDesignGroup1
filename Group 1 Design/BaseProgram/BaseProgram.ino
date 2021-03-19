/*
 *  Watering System for Senior Design Group 1
 *  
 *  Used to record data from the DHT11 and to turn on the Lamp and Pump
 *  
 *  Designed for Sparkfun RedBoard
 * 
 * Circuit Pins
 * 
 ** DHT11 - pin 7 
 * 
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 * 
 * 
 ** Lamp Relay = pin 8
 ** Pump Relay = pin 9
 * 
 * 
 * created   Feb 2021
 * by Karsen Box
 * 
 * 
 */
#include <dht.h> // includes the dht library
#include <SPI.h>
#include <SD.h>


const int chipSelect = 10;
dht DHT; // sets the dht to DHT
#define DHT11_PIN 7 // defines the pin used for the dht

bool lampStatus;
bool pumpStatus;

void setup() {
  Serial.begin(9600); // starts the serial
  
  pinMode(8, OUTPUT); //sets pin 1 and 2 || These are the Relays
  pinMode(9, OUTPUT);

  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {

    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");

    while (true);

  }
  Serial.println("initialization done.");
}




void loop() {
    float chk = DHT.read11(DHT11_PIN); // polls the DHT
    float DHTTA = DHT.temperature;
    float DHTHA = DHT.humidity;

    // reads from first DHT sensor

    if(DHTTA < 13.0){
      lampStatus = true;

      // checks to see if temperature is lower than 13C and then turns on LAMP

      }else if(DHTTA > 25) {
        lampStatus = false;

        // if not below 13 than it will turn off the LAMP
        
        }

    if(DHTHA < 60.0){
      pumpStatus = true;

      // checks to see if temperature is lower than 13C and then turns on LAMP

       }else if(DHTHA > 80.0) {
        pumpStatus = false;

        // if not below 13 than it will turn off the LAMP

        }  
              
  Serial.print("Lamp Status = "); //debug
  Serial.println(lampStatus); //debug
  Serial.print("Pump Status = "); //debug
  Serial.println(pumpStatus); //debug  
  Serial.print("Temperature = ");
  Serial.println(DHTTA); // prints the temp
  Serial.print("Humidity = ");
  Serial.println(DHTHA); // prints the humid
  
      String dataString = "";

      dataString += String(lampStatus);
      dataString += ",";
      dataString += String(pumpStatus);
      dataString += ",";
      dataString += String(DHTTA);
      dataString += ",";
      dataString += String(DHTHA);

      

    
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:

  if (dataFile) {
    
      dataFile.println(dataString); // prints the humid

      dataFile.close();

    // print to the serial port too:

    Serial.println(dataString);

    

  }

  else {

    Serial.println("error opening datalog.txt");

  }
}
