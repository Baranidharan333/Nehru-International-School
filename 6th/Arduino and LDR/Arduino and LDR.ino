/*Define the varibales and pins*****************************************************************************/
#define LDRpin A0                     // We define a variable LDRpin and designate the A0 analog pin for it
int LDRValue = 0;                     // We need to define a varibale in which we store values of the LDR

/*NEW: Define the variable for a LED************************************************************************/
int LedPin = 13;                      // We define a variable LedPin and designate the D13 digital pin for it

/*Initiate the Serial communication and define the pin mode for the LDRpin**********************************/
void setup()
{
  Serial.begin(9600);                 // We begin the serial communication 

/*NEW*******************************************************************************************************/
  pinMode(13, OUTPUT);                // We define a digital pin 13 as an Output
  digitalWrite(13, LOW);              // We simply make sure that the LED is turned off at the beginning
}

/*Read the Value from the LDR and display it on the Serial Monitor******************************************/
void loop()
{
  LDRValue = analogRead(LDRpin);      // We read the value of the LDR and store it in the LDRValue variable
  Serial.println(LDRValue);           // We send the LDRValue to be seen on the serial monitor
  delay(2);                           // Wait 2 ms for the value to be displayed

/*NEW: Turn off the light if the sensor senses brightness higher than "300"*********************************/
  if (LDRValue > 300)
  {
    digitalWrite(LedPin, LOW); 
  }
  else
  {
    digitalWrite(LedPin, HIGH);
  }
}
/***********************************************************************************************************/
