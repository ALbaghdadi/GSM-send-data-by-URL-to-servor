#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(10, 11);

void setup()
{
  gprsSerial.begin(9600);
  Serial.begin(9600);

  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  // attach or detach from GPRS service 
  gprsSerial.println("AT+CGATT?");

  toSerial();
delay(100);

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"net.asiacell.com\",\"\"");
  delay(2000);
  toSerial();

  // bearer settings
   gprsSerial.println("AT+SAPBR=0,1");
   delay(2000);
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
}


void loop()
{
   // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   // set http param value
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://www.website123456.com/data/index.php?data1=2.88&data2=2.93\""); 
   delay(20000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(6000);
   toSerial();

   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(10000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("");
   delay(10000);
}



void toSerial()
{
 // run over and over
  if (gprsSerial.available()) {
    Serial.write(gprsSerial.read());
  }
  if (Serial.available()) {
    gprsSerial.write(Serial.read());
  }
}
