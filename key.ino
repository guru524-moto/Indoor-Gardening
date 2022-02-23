int valAnalog;
char KeyOld;
#define pinAnalog	A0


ISR(TIMER2_COMPA_vect){//timer2 interrupt 1kHz toggles pin 8

}

char key_read(void)
{
	char KeyVal;
	valAnalog = analogRead(pinAnalog);
	if(valAnalog<1000)
	{
		if(valAnalog<10)
			KeyVal=KEY_1;
		if((valAnalog>85)&&(valAnalog<125))
			KeyVal=KEY_2;
		if((valAnalog>190)&&(valAnalog<230))
			KeyVal=KEY_3;
		if((valAnalog>315)&&(valAnalog<345))
			KeyVal=KEY_4;
		if((valAnalog>460)&&(valAnalog<500))
			KeyVal=KEY_5;
		if((valAnalog>700)&&(valAnalog<740))
			KeyVal=KEY_6;
	}
	else
	{
		KeyVal=0;
	}
	if(KeyVal)
	{
		if(KeyVal==KeyOld) //verifica ce tasta a fost apasata
		{
			KeyOld=0;
			switch(KeyVal)
			{
				case KEY_6:
					pcf8574.digitalWrite(P5, LOW);
					break;
				case KEY_5:
					pcf8574.digitalWrite(P4, LOW);
					break;
				case KEY_4:
					pcf8574.digitalWrite(P3, LOW);
					break;
				case KEY_3:
					pcf8574.digitalWrite(P2, LOW);
					break;
				case KEY_2:
       pcf8574.digitalWrite(P3,LOW);
       motorON = true;
					break;
				case KEY_1:
       if(tempF){
        pcf8574.digitalWrite(P4,LOW);
        tempF=0;
        Serial.print("tempF=0\n");
        
        }else {
          pcf8574.digitalWrite(P4,HIGH);
          tempF=1;
          Serial.print("tempF=1\n");
          }
           lcd.setCursor(8,0);
    lcd.print("Ta= ");
              if(tempF){
          lcd.print(dht_F);
    lcd.setCursor(14,0);
    lcd.print("F ");
    }else{
    lcd.print(DHT.temperature);
    lcd.setCursor(14,0);
    lcd.print("C ");
    }

          
					break;
			}
		}
		else
    {
			KeyOld=KeyVal;
      motorON = false;
	}
	return KeyVal;
}
}
