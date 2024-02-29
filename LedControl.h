#ifndef LEDCONTROL
#define LEDCONTROL

typedef void (*tick)(void);

class LedControl{

private:
  int m_delay;
  int m_counter;
  int m_speed;
  bool state;
  tick m_fn;

public:
  LedControl(tick fn = nullptr):
    m_delay{10000},
    m_counter{0},
    m_speed{300},
    state{false}
  {
      pinMode(LED_BUILTIN, OUTPUT);
      close();
      m_fn = fn;
  }

  void blink(const int &count = 1, const double &dly = 1){
    const int speed = (int)(m_speed / count);
    m_counter++;
    if(m_counter == m_delay){                    
        m_counter = 0;
        toggle();        
    }
  }

  void toggle(){
    state = !state;
    if(state) open(); else close();
    m_fn();
  }

  void open(){
    digitalWrite(LED_BUILTIN, HIGH); 
  }

  void close(){
    digitalWrite(LED_BUILTIN, LOW); 
  }

  void toggleSpeed(const int &speed = 0){
    if(speed != 0){
      m_delay =  speed;
    }else{
      m_delay = (m_delay == 10000) ? 2500 : 10000;
    }    
    m_counter = 0;
  }

};

#endif // LEDCONTROL