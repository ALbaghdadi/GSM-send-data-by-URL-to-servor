#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(10, 11);



int   ID_location=2;
float voltageAC=10;
float currentAC=1;
float voltageDC=12;
float currentDC=2;
void setup()
{
  gprsSerial.begin(9600);
  Serial.begin(9600);
}
void setup_GSM()
{
   
  Serial.println("shutdown the module the module");
  gprsSerial.println("AT+CIPSHUT");
    toSerial(5000);
  Serial.println("Restart the module");
  gprsSerial.println("AT+CFUN=1,1");
    toSerial(5000);
  Serial.println("Config SIM900...");
  delay(2000);
  
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();
Serial.println("AT+CFUN=1");
  gprsSerial.println("AT+CFUN=1");
  toSerial(30000);
  // attach or detach from GPRS service 
   Serial.println("AT+CGATT=0");
  gprsSerial.println("AT+CGATT=0");
  toSerial(5000);
   Serial.println("AT+CGATT=1");
  gprsSerial.println("AT+CGATT=1");
  toSerial(5000);


  // bearer settings
  
  Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");

  toSerial(5000);
//AT+CSTT="3gprs","3gprs","3gprs"
  // bearer settings
  Serial.println("AT+CSTT=\"net.asiacell.com\",\"\",\"\"");
  gprsSerial.println("AT+CSTT=\"net.asiacell.com\",\"\",\"\"");
  toSerial(3000);

  // bearer settings
   Serial.println("AT+SAPBR=0,1");
   gprsSerial.println("AT+SAPBR=0,1");
  toSerial(5000);
   Serial.println("AT+SAPBR=1,1");
  gprsSerial.println("AT+SAPBR=1,1");
  toSerial(5000);
 


 //  toSerial(5000);
  // Serial.println("AT+HTTPREAD"); 
  // gprsSerial.println("AT+HTTPREAD"); 
 //  toSerial(5000);

  // gprsSerial.println("");
 //  gprsSerial.println("AT+HTTPTERM");
   toSerial(5000);





    
}

 
void http_init(void)
{
 Serial.println("AT+HTTPINIT");
 gprsSerial.println("AT+HTTPINIT");
  toSerial(5000);

Serial.println("AT+HTTPPARA=\"CID\",1"); 
gprsSerial.println("AT+HTTPPARA=\"CID\",1"); 
   toSerial(5000);
}
void loop()
{
  ID_location=4;
voltageAC=voltageAC+1;
currentAC=currentAC+1;
voltageDC=voltageDC+1;
currentDC=currentDC+1;


     setup_GSM();
    http_init();
  
       Serial.println("AT+HTTPPARA=\"URL\",\"http://109.224.39.221:1239/testcode/dht4.php?ID_location="+String(ID_location)+"&voltageAC="+String(voltageAC)+"&currentAC="+String(currentAC)+"&voltageDC="+String(voltageDC)+"&currentDC="+String(currentDC)+"\"");  
 gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://109.224.39.221:1239/testcode/dht4.php?ID_location="+String(ID_location)+"&voltageAC="+String(voltageAC)+"&currentAC="+String(currentAC)+"&voltageDC="+String(voltageDC)+"&currentDC="+String(currentDC)+"\"");
   toSerial(3000);
   Serial.println("AT+HTTPACTION=0");
   gprsSerial.println("AT+HTTPACTION=0");
      toSerial(10000);


  // Serial.println("AT+HTTPREAD"); 
//   gprsSerial.println("AT+HTTPREAD"); 
   toSerial(20000);
 Serial.println("close the session");
  gprsSerial.println("AT+HTTPTERM");
   toSerial(10000);

      

   
}

void toSerial(int tim)
{
  for( int i=0;i<(tim);i++)
 { while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
  delay(1);
}
}
