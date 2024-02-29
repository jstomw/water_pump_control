#include "Button.h"
#include "Relay.h"
#include "LedControl.h"

LedControl *led;
Button *btn;
Relay *rel;

int global_timer;
int global_timer_limit;

auto toggleCalback = [](const char *cmd){
  if(cmd == "click"){
    led->toggleSpeed(2000);
    rel->toggle();
    if(rel->active()){
        global_timer = 0;
        global_timer_limit = 250;  
    }
  }
  if(cmd == "press"){
    led->toggleSpeed(20000);
    rel->toggle();    
    if(rel->active()){
        global_timer = 0;
        global_timer_limit = 500;  
    }
  }    
};

auto timer = [rel, led](void){
  if(rel->active()){
      global_timer++;
      if(global_timer > global_timer_limit){
        rel->close();
        rel->setState(false);
        led->close();
      }
  }
};

void setup() {
  btn = new Button();
  rel = new Relay();
  led = new LedControl(timer);
}

void loop() {
  //relay events
  btn->readPins(toggleCalback);

  //blink
  if(rel->active()){
    led->blink();
  }else{
    led->close();
    global_timer = 0;
  }
}
