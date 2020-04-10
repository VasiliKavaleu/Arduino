
//L298N Драйвер двигателей
  const int motorA1B  = 5;  // L298N'in IN3
  const int motorA1A  = 6;  // L298N'in IN1
  const int motorB1A  = 10; // L298N'in IN2
  const int motorB1B  = 9;  // L298N'in IN4


  int i=0; //Случайная переменная, назначенная циклам
  int j=0; //Случайная переменная, назначенная циклам
  int state; //Переменная сигнала от устройства Bluetooth
  int vSpeed=255;     // Стандартная скорость может принимать значение от 0-255

void setup() {
    // Определение  контактов
    pinMode(motorA1B, OUTPUT);
    pinMode(motorA1A, OUTPUT);
    pinMode(motorB1A, OUTPUT);
    pinMode(motorB1B, OUTPUT);    
    // Открытие последовательного порта со скоростью 9600
    Serial.begin(9600);
}
 
void loop() {
  //Остановить авто, когда соединение Bluetooth отключено.
 //(Удалить "//" подстроки для активации.)
  //   if(digitalRead(BTState)==LOW) { state='S'; }

  //Сохранить входящие данные в переменную " состояние
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  
  // 4 уровня скорости, которые можно регулировать из приложения.(Значения должны быть между 0-255)
    if (state == '0'){
      vSpeed=0;}
    else if (state == '1'){
      vSpeed=100;}
    else if (state == '2'){
      vSpeed=180;}
    else if (state == '3'){
      vSpeed=200;}
    else if (state == '4'){
      vSpeed=255;}
     
  //Если входящие данные "F" автомобиль идет вперед.
    if (state == 'F') {
      analogWrite(motorA1B, 0); analogWrite(motorA1A, 255);
        analogWrite(motorB1A, 255); analogWrite(motorB1B, 255); 
    }
  
  //Автомобиль идет вперед влево(по диагонали), если входящие данные " G.
    else if (state == 'G') {
      analogWrite(motorA1B, 0); analogWrite(motorA1A, 255);  
        analogWrite(motorB1A, 0);    analogWrite(motorB1B, 255); 
    }
  
  //Если входящие данные' I ' автомобиль идет вперед вправо(по диагонали).
    else if (state == 'I') {
        analogWrite(motorA1B, 0); analogWrite(motorA1A, 255); 
        analogWrite(motorB1A, 255);      analogWrite(motorB1B, 0); 
    }
  
  //Автомобиль возвращается, если входящие данные " B.
    else if (state == 'B') {
      analogWrite(motorA1B, 255);   analogWrite(motorA1A, 0); 
        analogWrite(motorB1A, 255);   analogWrite(motorB1B, 255); 
    }
  
  //Если данные из ' H ' автомобиль возвращается влево(по диагонали) 
    else if (state == 'H') {
      analogWrite(motorA1B, 255);   analogWrite(motorA1A, 0); 
        analogWrite(motorB1A, 0); analogWrite(motorB1B, 255); 
    }
 
  //Если входящие данные 'J' автомобиль возвращается вправо(по диагонали)
    else if (state == 'J') {
      analogWrite(motorA1B, 255);   analogWrite(motorA1A, 0); 
        analogWrite(motorB1A, 255);   analogWrite(motorB1B, 0); 
    }
  
  //Если входящие данные 'L' автомобиль идет влево.
    else if (state == 'L') {
      analogWrite(motorA1B, 255);   analogWrite(motorA1A, 255); 
        analogWrite(motorB1A, 0); analogWrite(motorB1B, 255); 
    }
 
  //Если входящие данные 'R' автомобиль идет вправо
    else if (state == 'R') {
      analogWrite(motorA1B, 255);   analogWrite(motorA1A, 255); 
        analogWrite(motorB1A, 255);   analogWrite(motorB1B, 0);     
    }
  
  //Остановить автомобиль, если входящие данные' s.
    else if (state == 'S'){
        analogWrite(motorA1B, 255);  analogWrite(motorA1A, 255); 
        analogWrite(motorB1A, 255);  analogWrite(motorB1B, 255);
    }  
}

