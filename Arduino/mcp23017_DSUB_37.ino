
#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_PIN 0     // MCP23XXX pin LED is attached to
#define OUT1_ADDR 0x20
#define OUT2_ADDR 0x21
#define OUT3_ADDR 0x22
#define IN1_ADDR 0x23
#define IN2_ADDR 0x24
#define IN3_ADDR 0x25

LiquidCrystal_I2C lcd(0x27,16,2);

const int next_button = 5;
const int start_button = 4;
const int buz = 6;
const int res_1 = 2;
const int res_2 = 3;

Adafruit_MCP23X17 Out1;
Adafruit_MCP23X17 Out2;
Adafruit_MCP23X17 Out3;
Adafruit_MCP23X17 In1;
Adafruit_MCP23X17 In2;
Adafruit_MCP23X17 In3;

int i;

void set_all_to_output(Adafruit_MCP23X17 &mcp)
{
    for(i = 0; i < 16; i++)
  {
    mcp.pinMode(i, OUTPUT);
  }
}

void set_all_to_input(Adafruit_MCP23X17 &mcp)
{
    for(i = 0; i < 16; i++)
  {
    mcp.pinMode(i, INPUT);
  }
}

void check_presence(Adafruit_MCP23X17 &mcp, uint8_t i2c_addr)
{
  if (!mcp.begin_I2C(i2c_addr)) {
    Serial.println("Error Out");
    while (1);
  }  
}

void beep(int n, int dur)
{
  for(i=0; i<n; i++){
      digitalWrite(buz, HIGH);
      delay(dur);
      digitalWrite(buz, LOW);
      delay(dur);
  }
}

void report (int chan){
  while(digitalRead(next_button) == HIGH){
    lcd.setCursor(0,0);
    lcd.print("CHANNEL FAIL");
    lcd.setCursor(8,1);
    lcd.print(chan);
    delay(16);
    lcd.clear();
  }
}

//Function communicates with each MCP23017 (both input & output) device via I2C interface

void check_chan(Adafruit_MCP23X17 &mcp_out,Adafruit_MCP23X17 &mcp_in, int del, int chan)
{    
     int state = 0;
     Serial.print("Channel: ");
     Serial.print(chan);
     mcp_out.digitalWrite(convert(chan), HIGH);
     delay(del);
     for(int i = 0; i < 5; i++){
        if(mcp_in.digitalRead(convert(chan)) == HIGH)
          state = state +1;      
        delay(50);
     }     
     if(state > 2)
          Serial.print("OK");
     else
     {
          Serial.print(" - FAIL");
          beep(1, 300);
          report(chan);
     }
     mcp_out.digitalWrite(convert(chan), LOW);
     reset_output_mcp();
     Serial.println();
}

//Function converts input number to MCP23017 chanel number

int convert(int num)
{
    if (0 < num && num < 17)
    {
        if (num > 8)
            num = num - 8;
        num = 17 - num * 2;
        return(num);
    }
    else if (16 < num && num < 20)
    {
        num = num - (7 + (num - 17) * 3);
        return(num);
    }
    else if (19 < num && num < 36)
    {
        num = num - 19;
        if (num > 8)
            num = num - 8;
        num = 16 - num * 2;
        return(num);
    }
    else if (35 < num)
    {
        num = num - (27 + (num - 36) * 3);
        return(num);
    }
}

//Function tests each channel accordingly to its number

void channel_test(int num)
{
  if(num < 9 )
    check_chan(Out1, In1, 500, num);
  else if(8 < num && num < 17)
    check_chan(Out2, In2, 500, num);
  else if(16 < num && num < 20)
    check_chan(Out3, In3, 500, num);
  else if(19 < num && num < 27)
    check_chan(Out1, In1, 500, num);
  else if(19 < num && num < 28)
    check_chan(Out1, In1, 500, num);
  else if(27 < num && num < 36)
    check_chan(Out2, In2, 500, num);
  else if(35 < num && num < 38)
    check_chan(Out3, In3, 500, num);  
}

void test(Adafruit_MCP23X17 &mcp_1,Adafruit_MCP23X17 &mcp_2, int del, bool ch)
{ 
  int a,b;
     
  if(ch)
  {
    a = 0;
    b = 16;
  }
  else
  {
    a = 6;
    b = 11;
  }
       for(i = a; i < b; i++)
     {
      mcp_1.digitalWrite(i, HIGH);
      mcp_2.digitalWrite(i, HIGH);
      delay(del);
      mcp_1.digitalWrite(i, LOW);
      mcp_2.digitalWrite(i, LOW);
     }
}

void reset_mcp() {
    digitalWrite(res_2, HIGH);
    digitalWrite(res_1, HIGH);
    delay(50);
    digitalWrite(res_2, LOW);
    digitalWrite(res_1, LOW);
}


void reset_output_mcp() {
    digitalWrite(res_2, HIGH);
    delay(50);
    digitalWrite(res_2, LOW);
}

void clear_channels(Adafruit_MCP23X17 &mcp){
  mcp.writeGPIO(0x00, 0);
  mcp.writeGPIO(0x00, 1);
}

void setup() {
  pinMode(next_button, INPUT);
  pinMode(start_button, INPUT);
  pinMode(res_2, OUTPUT);
  pinMode(buz, OUTPUT);
  
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");

  lcd.init();
  lcd.backlight();
  lcd.print("DB-37 TESTER");
  
  //check avaliability of each device
  check_presence(Out1, OUT1_ADDR);
  check_presence(Out2, OUT2_ADDR);
  check_presence(Out3, OUT3_ADDR);
  check_presence(In1, IN1_ADDR);
  check_presence(In2, IN2_ADDR);
  check_presence(In3, IN3_ADDR);  

  // configure pin for output
  set_all_to_output(Out1);
  set_all_to_output(Out2);
  set_all_to_output(Out3);
  set_all_to_output(In1);
  set_all_to_output(In2);
  set_all_to_output(In3);
  
  Serial.println("Looping...");
  delay(16);
  lcd.clear();
  
  beep(3, 50);
}

void loop() {

    lcd.setCursor(1,0);
    lcd.print("PRESS START");
    lcd.setCursor(3,1);
    lcd.print("TO BEGIN");
      
    while(digitalRead(start_button) == HIGH)
    {
        Serial.println("Press button to start");
        delay(50);               
    }

    lcd.clear();
    
    reset_mcp();

    for(int i = 1; i < 38; i++)
    {
      channel_test(i);
    }
    
}
