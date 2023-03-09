char AIA_ENGINE_INPUT = 8;
char AIB_ENGINE_INPUT = 9;
char BIA_ENGINE_INPUT = 12;
char BIB_ENGINE_INPUT = 13;

char bluetooth_event;

enum Command {
  MOVE_FORWARD,
  MOVE_BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,

  MOVE_LEFT_FROWARD,
  MOVE_RIGHT_FROWARD,
  MOVE_LEFT_BACKWARD,
  MOVE_RIGHT_BACKWARD,

  UNDEFINED,
};

enum Command command;

class Car
{

public:
    Car() {}; 
    void handle_command(Command cmd);

private:
    
    void move_forward() {
      stop_turning_control_wheels();
      run_driving_wheels();
    
      }
    
    void move_backward() {
      stop_turning_control_wheels();
      run_driving_wheels_in_reverse();
      }
    
    void move_left() {
      turn_wheels_to_left();
      run_driving_wheels();
      }
    
    void move_right() {
      turn_wheels_to_right();
      run_driving_wheels();
      }
    
    void move_left_backward() {
      turn_wheels_to_left();
      run_driving_wheels_in_reverse();
      }
    
    void move_right_backward() {
      turn_wheels_to_right();
      run_driving_wheels_in_reverse();
      }
 
    void run_driving_wheels() {
      digitalWrite(BIB_ENGINE_INPUT, HIGH);
      digitalWrite(BIA_ENGINE_INPUT, LOW);
      }
    
    void run_driving_wheels_in_reverse() {
      digitalWrite(BIB_ENGINE_INPUT, LOW);
      digitalWrite(BIA_ENGINE_INPUT, HIGH);
      }
    
    void turn_wheels_to_left() {
      digitalWrite(AIA_ENGINE_INPUT, LOW);
      digitalWrite(AIB_ENGINE_INPUT, HIGH);
      }
    
    void turn_wheels_to_right() {
      digitalWrite(AIA_ENGINE_INPUT, HIGH);
      digitalWrite(AIB_ENGINE_INPUT, LOW);
      }
    
    void stop_driving_wheels() {
      digitalWrite(BIB_ENGINE_INPUT, LOW);
      digitalWrite(BIA_ENGINE_INPUT, LOW);
      }
    
    void stop_turning_control_wheels() {
      digitalWrite(AIA_ENGINE_INPUT, LOW);
      digitalWrite(AIB_ENGINE_INPUT, LOW);
      }

};

void Car::handle_command(Command cmd) {
    switch (cmd) {
    case MOVE_FORWARD:
      this-> move_forward();
      break;
    case MOVE_BACKWARD:
      this-> move_backward();
      break;
    case TURN_LEFT:
      this-> turn_wheels_to_left();
      break;
    case TURN_RIGHT:
      this-> turn_wheels_to_right();
      break;
    case MOVE_LEFT_FROWARD:
      this-> move_left();
      break;
    case MOVE_RIGHT_FROWARD:
      this-> move_right();
      break;
    case MOVE_LEFT_BACKWARD:
      this-> move_left_backward();
      break;
    case MOVE_RIGHT_BACKWARD:
      this-> move_right_backward();
      break;
    default:
      this-> stop_driving_wheels();
      this-> stop_turning_control_wheels();
      break;
  }
}

Command get_command(char event) {
    switch (event) {
    case 'F':
      return MOVE_FORWARD;
    case 'B':
      return MOVE_BACKWARD;
    case 'L':
      return TURN_LEFT;
    case 'R':
      return TURN_RIGHT;
    case 'G':
      return MOVE_LEFT_FROWARD;
    case 'I':
      return MOVE_RIGHT_FROWARD;
    case 'H':
      return MOVE_LEFT_BACKWARD;
    case 'J':
      return MOVE_RIGHT_BACKWARD;
    default:
      return UNDEFINED;
  }
}

Car car{};



void setup()
{
    Serial.begin(9600);                  /*Baud Rate for serial communication*/
    pinMode(AIA_ENGINE_INPUT, OUTPUT);   /*A input for control wheels engine*/
    pinMode(AIB_ENGINE_INPUT, OUTPUT);   /*B input for control wheels engine*/
    pinMode(BIA_ENGINE_INPUT, OUTPUT);   /*A input for driving wheels engine*/
    pinMode(BIB_ENGINE_INPUT, OUTPUT);   /*B input for driving wheels engine*/
    
}

void loop()
{
    if(Serial.available() > 0) {                /*check for serial data availability*/
        bluetooth_event = Serial.read();        /*read data coming from Bluetooth device*/

        command = get_command(bluetooth_event);
        car.handle_command(command);
    }                            
}
