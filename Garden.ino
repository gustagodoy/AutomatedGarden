/*
 * ----- Connections -----
 * DHT Sensor  - Digital 2 
 * Relay       - Digital 6
 * Hygrometer  - Analogico A0
 * LCD Display - Analogico A5
 * LCD Display - Analogico A4 
*/

/*-----( Importing the required libraries)-----*/
#include <Wire.h>              //I2C Communication Library
#include <LiquidCrystal_I2C.h> //LCD Display Library
#include <DHT.h>               //Temperature Sensor Library

/*-----( Instances )-----*/
#define relay 6         //Relay Port
#define DHTPIN 2        //Dht Port
#define DHTTYPE DHT22   //Temperature Sensor Model

/*-----( Objects )-----*/  
DHT dht(DHTPIN, DHTTYPE);

/* Setting the LCD address to 0x27 for a 20-character 4-line display
   Pin definition on the I2C chip used for LCD connections:
                      addr, en, rw, rs, d4, d5, d6, d7, bl, blpol */
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //LCD I2C Address


/*-----( Variable Declaration )-----*/
float hum = dht.readHumidity();     //Receives the values and stores it in variable
float temp = dht.readTemperature(); //Receives the values and stores it in variable
int hygrometer = analogRead(A0);    //Receives analogue port value A0 and stores it


/*----( Void Setup )----*/
void setup() {
  
    Serial.begin(9600);     //Setting the data rate in bits per second (baud) for data transmission on the Serial port
    dht.begin();            //Initializes the temperature sensor
    pinMode(A0, INPUT);     //Defines as input
    lcd.begin(20,4);        //Initializes the diplay to 20 characters and 4 lines
    pinMode(relay, OUTPUT); //Define as output    
    pinMode(1 ,OUTPUT);     //Define as output (Green)
    pinMode(2 ,OUTPUT);     //Define as output (Yellow)
    pinMode(3 ,OUTPUT);     //Define as output (Red)
}

/*----( Void Loop )----*/
void loop() {

   while (hygrometer < 600 && hygrometer >= 370) {
    (wetsoil);
    (weather);
    delay(2500);
   }

   if (hygrometer < 1000 && hygrometer >= 600) {
    (weather);
    (drysoil);
      while (hygrometer < 1000 && hygrometer >= 600){
        (waterpumpon);
     }
   }
    
    else if(hygrometer < 370) {
      (verywetsoil);
    }

    else if (hygrometer >= 1000) {
      (sensorerror);
    }

}

/*-------------------------------------------------------------------------------------------------------------------------------*/

/*-----( WelcomeMessage )-----*/
void welcome() {
      lcd.setCursor(0,0);
      lcd.print("********************");
      lcd.setCursor(0,1);
      lcd.print("*     Irrigation   *");
      lcd.setCursor(0,2);
      lcd.print("*      System      *");
      lcd.setCursor(0,3);
      lcd.print("********************");
      delay(8000);
      lcd.clear();

      Serial.print("********************"); //Debug - Monitor Serial
      Serial.print("*    Irrigation    *"); //Debug - Monitor Serial
      Serial.print("*      System      *"); //Debug - Monitor Serial
      Serial.print("********************"); //Debug - Monitor Serial 
    }

/*-----( HumidityTemperature )-----*/
void weather(){
      lcd.setCursor(0,0);
      lcd.print("Humidity: "); lcd.print(hum); lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Temperature: "); lcd.print(temp, 0); lcd.print(" C");
      
      Serial.print("Humidity: "); Serial.print(hum);       //Debug - Monitor Serial
      Serial.print("Temperature: "); Serial.print(temp);  //Debug - Monitor Serial

      delay(2500);
}

/*-----( DrySoil )-----*/
void drysoil(){
     lcd.setCursor(0,2);
     lcd.print("Soil Status: Dry");
     
     Serial.print("Dry Soil");           //Debug - Monitor Serial
}

/*-----(WetSoil)-----*/
void wetsoil(){
     (waterpumpoff);                     //Setting waterpump as off
     lcd.setCursor(0,2);
     lcd.print("Soil Status: Wet");
     
     Serial.print("Wet Soil");           //Debug - Monitor Serial
}

/*-----( VeryWetSoil )-----*/
void verywetsoil(){
     (waterpumpoff);                      //Setting waterpump as off
     lcd.setCursor(0,2);
     lcd.print("Soil Status: Very Wet");  
     
     Serial.print("Very Wet");            //Debug - Monitor Serial
}

/*-----( SensorError )-----*/  
void sensorerror(){
     (waterpumpoff);                      //Setting waterpump as off
     lcd.setCursor(0,2);
     lcd.print("Soil Status: Sensor Error");
     
     Serial.print("Sensor disconnected or off the soil"); //Debug - Monitor Serial
} 

/*-----( WaterPumpOn)-----*/
void waterpumpon(){
    digitalWrite(relay,LOW);  // Turns relay On     
}

/*-----( WaterPumpOff )-----*/
void waterpumpoff(){
    digitalWrite(relay,HIGH); // Turns relay Off     
}
