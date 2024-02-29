#ifndef BUTTON
#define BUTTON

#include "Relay.h"

typedef void (*func)(const char *);

class Button{

private:  
  const int m_delay;
  const int m_press_delay;
  int m_clicks;
  int m_counter;
  int m_dbl_click_counter;
  bool m_click_state;
  bool m_press_state;

public:

  int state;

  Button() : 
  m_delay{400},
  m_press_delay{5000},
  m_clicks{0},
  m_counter{0},
  m_dbl_click_counter{0},
  m_click_state{false},
  m_press_state{false}
  {
      pinMode(PIN_A0, INPUT);
      Serial.begin(9600);
  }

  void readPins(func fn){
    auto val = analogRead(A0);  // read the input pin    
    m_dbl_click_counter++;

    //button down
    if(val <= 0){
      m_counter++;      
      //on click
      if(m_counter <= m_press_delay){                
        if(m_counter >= m_delay && !m_click_state){
          m_click_state = true;
          m_clicks++;               
        }
      }else if(m_click_state && !m_press_state){
          m_press_state = true;  
          fn("press");
      }                  
      return;    
    }
    //button up
    if(m_click_state || m_press_state){
      if(!m_press_state && m_clicks > 0 && m_clicks <= 1){                  
        fn("click");
      }
      if(m_clicks > 1){
        fn("dblclick");  
      }         
      m_click_state = false;
      m_press_state = false;   
    }        
    m_counter = 0;
    if(m_dbl_click_counter > m_press_delay){
      m_dbl_click_counter = 0;
      m_clicks = 0;
    }
  }
};

#endif //BUTTON