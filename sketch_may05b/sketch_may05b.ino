#include <mcp2515.h>

MCP2515 mcp2515(10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

struct can_frame frame;
uint8_t c = 0;

void loop() {
  // put your main code here, to run repeatedly:
  /*if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK){
    Serial.print("recieved can msg -> ");
    Serial.print("id = ");
    Serial.print(frame.can_id);
    Serial.print("; length = ");
    Serial.print(frame.can_dlc);
    Serial.print("; data = ");
    Serial.println(frame.data[0]);
  }
  else{
    Serial.println("no msg");
  }*/

  frame = can_frame();

  //

  frame.can_id = 1;
  frame.can_dlc = 1;
  frame.data[0] = c;

  mcp2515.sendMessage(&frame);
  Serial.print("sent req frame = ");
  Serial.println(c);
  c++;
  //

  frame = can_frame();

  //

  int t = 0;
  while (t < 20){
    
    if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK && frame.can_id == 2){
        Serial.print("recieved success can frame -> ");
        Serial.print("id = ");
        Serial.print(frame.can_id);
        Serial.print("; length = ");
        Serial.print(frame.can_dlc);
        Serial.print("; data = ");
        Serial.println(frame.data[0]);
        delay(50);
        return;
    }
    t++;
    delay(50);
  }

  // no msg recv
  Serial.println("failed to recv success frame");
}

