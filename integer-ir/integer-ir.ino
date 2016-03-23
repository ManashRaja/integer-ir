#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    String received = String(results.value,HEX);
    int angle = decode_hex(received);
    Serial.print("angle: ");
    Serial.println(angle);
    Serial.println(encode_hex(angle));
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

int decode_hex(String input)
{
  int zeros = 8-input.length();
  for(int i=0; i<zeros;i++)
  {
    input = "0" + input;    
  }
  String hex_data = input.substring(0,2) + input.substring(4,6);  
  Serial.print("Real Hex data: ");
  Serial.println(hex_data); 
  const char * c = hex_data.c_str();
  int output = (int) strtol(c, NULL, 16);
  return output;
}

String encode_hex(int input)
{
  String real_hex = String(input,HEX);
  int zeros = 4-real_hex.length();
  for(int i=0; i<zeros;i++)
  {
    real_hex = "0" + real_hex;    
  }
  
  char HEXADECIMAL[17] = "0123456789abcdef";
  
  String final_hex = real_hex.substring(0,2);
  for(int i = 0; i<2; i++)
  {
    for(int j = 0; j<16; j++)
    {
      if(real_hex.substring(0+i,1+i) == String(HEXADECIMAL[j]))
      {
        final_hex += String(HEXADECIMAL[15-j]);
      }
    }
  }
  
  final_hex += real_hex.substring(2);
  
  for(int i = 0; i<2; i++)
  {
    for(int j = 0; j<16; j++)
    {
      if(real_hex.substring(2+i,3+i) == String(HEXADECIMAL[j]))
      {
        final_hex += String(HEXADECIMAL[15-j]);
      }
    }
  }
  return final_hex;
   
}
