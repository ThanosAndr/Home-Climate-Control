/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender

IRsendRaw mySender;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  Serial.println(F("Every time you press a key is a serial monitor we will send."));
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */
#define RAW_DATA_LEN 197
uint16_t rawData[RAW_DATA_LEN]={6104, 7380, 552, 1676, 528, 1644, 552, 1648, 612, 1588, 612, 1588, 612, 1588, 612, 1592, 572, 1628, 528, 584, 608, 532, 608, 476, 556, 584, 612, 528, 524, 560, 612, 524, 576, 564, 524, 1648, 616, 1584, 616, 1584, 616, 1584, 616, 1584, 612, 1592, 572, 1628, 524, 1672, 528, 588, 612, 528, 608, 504, 552, 584, 612, 528, 576, 536, 612, 524, 616, 524, 580, 1616, 532, 1672, 580, 1592, 616, 1584, 616, 1588, 612, 1584, 612, 1592, 612, 1588, 600, 536, 524, 588, 616, 524, 576, 536, 612, 524, 612, 528, 580, 532, 616, 524, 612, 1588, 576, 1620, 576, 1624, 528, 560, 616, 524, 572, 540, 548, 588, 616, 1584, 616, 524, 576, 536, 616, 524, 604, 1592, 580, 1620, 580, 1620, 576, 1628, 572, 536, 616, 524, 576, 1624, 572, 1628, 528, 584, 616, 1584, 608, 532, 572, 1624, 576, 1624, 580, 1596, 552, 584, 616, 524, 572, 1628, 572, 540, 612, 1588, 616, 524, 580, 556, 588, 524, 616, 1584, 612, 528, 572, 1624, 528, 588, 612, 1584, 612, 528, 576, 536, 608, 1592, 612, 528, 612, 1588, 604, 532, 524, 1648, 556, 584, 616, 1584, 612, 1588, 600, 7328, 616};




/*
 * Cut-and-paste into the area above.
 */
   
void loop() {
  if (Serial.read() != -1) {
    //send a code every time a character is received from the 
    // serial port. You could modify this sketch to send when you
    // push a button connected to an digital input pin.
    mySender.send(rawData,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
    Serial.println(F("Sent signal."));
  }
}

