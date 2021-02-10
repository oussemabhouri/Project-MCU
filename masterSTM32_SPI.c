#include<SPI.h>                                                              

#define SS PA4                                                              

#include<LiquidCrystal.h>                                                     

const int rs = PB0, en = PB1, d4 = PB10 , d5 = PB11 , d6 = PC13, d7 = PC14;   

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);                                       

void setup (void)

{
  lcd.begin(16,2);                                                         
  lcd.setCursor(0,0);                                                  
  lcd.print("CIRCUIT DIGEST");                                                
  delay(3000);                                                                
  lcd.clear();                                                                
  
  Serial.begin(9600);                                                         
  pinMode(SS,OUTPUT);                                                         
  SPI.begin();                                                               
  SPI.setClockDivider(SPI_CLOCK_DIV16);                                       
  digitalWrite(SS,HIGH);                                                      
}

void loop(void)
{ 
  
  byte MasterSend,MasterReceive;
  
  int pot = analogRead(PA0);                                                   
  
  MasterSend = map(pot,0,4096,0,255);                                          
  
  digitalWrite(SS, LOW);                                                       
  
  MasterReceive=SPI.transfer(MasterSend);                                    
  Serial.println("Slave Arduino to Master STM32");                            
  Serial.println(MasterReceive);                                      
  lcd.setCursor(0,0);                                                          
  lcd.print("Master: STM32");
  lcd.setCursor(0,1);                                                    
  lcd.print("SalveVal:");                                                         
  lcd.print(MasterReceive);                                                    
  delay(500);
  digitalWrite(SS, HIGH);                                              
  lcd.clear();

}
