#ifndef RELAY
#define RELAY

class Relay{

private:
  bool m_state;
public:
  Relay() : m_state{false}{        
      pinMode(PIN_A1, INPUT);
  }

  void toggle(){
      m_state = !m_state;
      if(m_state){
        open();  
      }else{
        close();
      }
  }

  bool active(){
      return (m_state == true);
  }

  void open(){
      pinMode(PIN_A1, OUTPUT);
  }

  void close(){
      pinMode(PIN_A1, INPUT);
  }

  void setState(const bool &newState){
      m_state = newState;
  }

};

#endif // RELAY