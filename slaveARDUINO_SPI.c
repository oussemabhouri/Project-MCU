#include<SPI.h>                        
#include<LiquidCrystal.h>                
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);    
volatile boolean received;
volatile byte SlaveReceived,Slavesend;
void setup()

{ 
  lcd.begin(16,2);                        
  lcd.setCursor(0,0);                     
  lcd.print("CIRCUIT DIGEST");           
  delay(3000);                           
  lcd.clear();                            
  
  Serial.begin(9600);                     
  
  pinMode(MISO,OUTPUT);                   

  SPCR |= _BV(SPE);                       
  received = false;
  SPI.attachInterrupt();                  
}

ISR (SPI_STC_vect)                        
{
  SlaveReceived = SPDR;                   
  received = true;                        
}

void loop()
{ 
  int pot = analogRead(A0);              
  Slavesend = map(pot,0,1023,0,255);      
                              
  SPDR = Slavesend;                    
  lcd.setCursor(0,0);                     
  lcd.print("Slave: Arduino");
  lcd.setCursor(0,1);                                                     
  lcd.print("MasterVal:");    
  Serial.println("Master STM32 to Slave Arduino");   
  Serial.println(SlaveReceived);                                     
  lcd.print(SlaveReceived);                        
  lcd.clear();
}
