/*
  GetYahooWeatherReport
  
  Demonstrates making a request to the Yahoo Weather API using the Temboo Arduino Yun SDK.
  
  This example code is in the public domain.
*/
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <SoftwareSerial.h>
#include <Bridge.h>
#include <Temboo.h>
#define TEMBOO_ACCOUNT ""  // your Temboo account name 
#define TEMBOO_APP_KEY_NAME ""  // your Temboo app key name
#define TEMBOO_APP_KEY  ""
#define RAW_DATA_LEN 197
uint16_t rawData1[RAW_DATA_LEN]={5972, 7020, 592, 472, 592, 468, 588, 476, 588, 472, 588, 472, 592, 472, 592, 464, 588, 476, 592, 468, 592, 472, 588, 472, 588, 472, 588, 472, 592, 468, 592, 472, 588, 472, 588, 472, 588, 472, 588, 476, 588, 472, 588, 472, 588, 472, 588, 476, 588, 472, 592, 472, 592, 464, 592, 472, 588, 472, 588, 472, 592, 472, 588, 472, 592, 468, 596, 468, 588, 472, 592, 468, 592, 468, 592, 472, 588, 472, 592, 468, 588, 476, 588, 472, 588, 472, 588, 472, 592, 472, 592, 468, 588, 476, 584, 472, 596, 468, 592, 468, 592, 468, 588, 480, 584, 472, 588, 472, 592, 468, 592, 472, 588, 472, 592, 472, 588, 468, 592, 472, 592, 468, 588, 472, 592, 468, 596, 468, 592, 468, 592, 472, 588, 468, 592, 472, 588, 472, 588, 476, 592, 468, 592, 468, 592, 472, 584, 1536, 588, 472, 592, 472, 592, 1528, 592, 472, 588, 1532, 592, 468, 592, 468, 596, 1528, 592, 468, 592, 1532, 592, 472, 588, 472, 592, 1528, 592, 472, 588, 1532, 592, 472, 592, 1528, 592, 1536, 588, 1528, 592, 472, 588, 472, 588, 1532, 592, 1532, 596, 7044, 596};
uint16_t rawData[RAW_DATA_LEN]={5948, 7016, 588, 476, 588, 472, 588, 472, 588, 472, 592, 468, 592, 468, 588, 472, 592, 472, 588, 468, 592, 468, 588, 476, 588, 472, 592, 468, 588, 472, 592, 468, 592, 468, 592, 468, 592, 468, 592, 468, 592, 468, 588, 472, 592, 472, 588, 468, 592, 472, 588, 472, 592, 468, 592, 468, 592, 468, 592, 468, 588, 472, 592, 468, 584, 476, 588, 472, 592, 468, 588, 472, 592, 468, 592, 468, 588, 472, 592, 472, 584, 472, 588, 472, 588, 472, 592, 472, 588, 468, 588, 472, 592, 468, 588, 472, 592, 468, 588, 476, 588, 472, 584, 476, 588, 472, 588, 472, 588, 472, 588, 472, 584, 476, 588, 472, 588, 1532, 584, 476, 592, 468, 592, 468, 592, 468, 588, 472, 588, 472, 592, 468, 588, 472, 588, 472, 588, 472, 592, 468, 588, 472, 592, 468, 592, 468, 592, 1528, 588, 472, 592, 468, 592, 1528, 592, 468, 592, 1528, 588, 476, 588, 468, 596, 1528, 588, 472, 588, 1532, 584, 476, 588, 472, 584, 1536, 588, 472, 592, 1528, 588, 472, 588, 472, 588, 472, 588, 472, 588, 1532, 592, 468, 592, 1528, 588, 1532, 592, 7040, 592}; 

IRsendRaw mySender;



String ADDRESS_FOR_FORECAST = ""; // the address for which a weather forecast will be retrieved
int sensor = A1;
int ledPin = 2;
int tempout;
int numRuns = 1;   // execution count, so that this doesn't run forever
int maxRuns = 1000;  // max number of times the Yahoo WeatherByAddress Choreo should be run
bool isOpen = false;



void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(sensor,INPUT);
              
  // for debugging, wait until a serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();

}

void loop()
{

      
    // print status
    Serial.println("Running GetWeatherByAddress - Run #" + String(numRuns++) + "...");

    // create a TembooChoreo object to send a Choreo request to Temboo
    TembooChoreo  GetWeatherByAddressChoreo;    
    // invoke the Temboo client
    GetWeatherByAddressChoreo.begin();

    // add your temboo account info
    GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // set the name of the choreo we want to run
    GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");
    
    // set choreo inputs; in this case, the address for which to retrieve weather data
    // the Temboo client provides standardized calls to 100+ cloud APIs
    GetWeatherByAddressChoreo.addInput("Address", ADDRESS_FOR_FORECAST);
    GetWeatherByAddressChoreo.addInput("Units","c");


    // add an output filter to extract the current temperature
    GetWeatherByAddressChoreo.addOutputFilter("Temperature", "/rss/channel/item/yweather:condition/@temp", "Response");
    
    // run the choreo 
    GetWeatherByAddressChoreo.run();
        
    // when the choreo results are available, print them to the serial monitor

      while(GetWeatherByAddressChoreo.available()) {
       // read the name of the next output item
        String name = GetWeatherByAddressChoreo.readStringUntil('\x1F');
        name.trim(); // use “trim” to get rid of newlines

        // read the value of the next output item
        String data = GetWeatherByAddressChoreo.readStringUntil('\x1E');
        data.trim(); // use “trim” to get rid of newline
        
        while (name == "Temperature") {
        int tempO = data.toInt(); // THE GOOD STUFF (variable temp = temperature!!)
        Serial.print("Outside Temprature Is:\t");
        Serial.print(tempO); // Print the Temperature
        tempout = tempO;
         break;
        }
       
      }     
         
    
    GetWeatherByAddressChoreo.close();

  
  int temp = analogRead(sensor);
  temp = (temp*500)/1023;
  Serial.print("\n");
  Serial.print("Inside Temprature Is:\t");
  Serial.print(temp);
  Serial.print("\n");
  if(tempout >= 28 && (tempout - temp >= 10 || tempout - temp <= -10  )){
  if(!isOpen){
    digitalWrite(ledPin, true);
    Serial.print("Opening AC...\n");
    mySender.send(rawData,RAW_DATA_LEN,38);
    isOpen = true;
  }else{
    Serial.print("AC already open.\n");
  }
  }else{
    if(isOpen){
      digitalWrite(ledPin, true);
      Serial.print("Closing AC...\n");
      mySender.send(rawData1,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
      isOpen = false;
    }else{
      Serial.print("AC already closed.\n");
    }

  }
 
  Serial.print("\n");
  Serial.println("Waiting...");
  Serial.println("");
  delay(500);
  digitalWrite(ledPin,false);
  delay(300000); // wait 5 minutes between GetWeatherByAddress calls
}



