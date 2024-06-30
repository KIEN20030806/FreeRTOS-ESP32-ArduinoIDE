//=====================Tạo Task===============================
//#if CONFIG_FREERTOS_UNICORE
//#define ARDUINO_RUNNING_CORE 0
//#else
//#define ARDUINO_RUNNING_CORE 1
//#endif
//
//
//#define LED_GPIO 19
//
//
//// define two tasks for Blink & AnalogRead
//void TaskBlink( void *pvParameters );
//void TaskAnalogReadA3( void *pvParameters );
//
//// the setup function runs once when you press reset or power the board
//void setup() {
//
//  // initialize serial communication at 115200 bits per second:
//  Serial.begin(115200);
//
//  // Now set up two tasks to run independently.
//  xTaskCreatePinnedToCore(
//    TaskBlink
//    ,  "TaskBlink"   // A name just for humans
//    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
//    ,  NULL
//    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//    ,  NULL
//    ,  0);
//
//  xTaskCreatePinnedToCore(
//    TaskAnalogReadA3
//    ,  "AnalogReadA3"
//    ,  1024  // Stack size
//    ,  NULL
//    ,  1  // Priority
//    ,  NULL
//    ,  1);
//
//  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
//  
//}
//
//void loop()
//{
//  // Empty. Things are done in Tasks.
//}
//
///*--------------------------------------------------*/
///*---------------------- Tasks ---------------------*/
///*--------------------------------------------------*/
//
//void TaskBlink(void *pvParameters)  // This is a task.
//{
//  (void) pvParameters;
//
//  /*
//    Blink
//    Turns on an LED on for one second, then off for one second, repeatedly.
//
//    If you want to know what pin the on-board LED is connected to on your ESP32 model, check
//    the Technical Specs of your board.
//  */
//
//  // initialize digital LED_GPIO on pin 13 as an output.
//  pinMode(LED_GPIO, OUTPUT);
//
//  for (;;) // A Task shall never return or exit.
//  {
//    Serial.print("Task1: ");
//    Serial.println(xPortGetCoreID());
//    digitalWrite(LED_GPIO, HIGH);   // turn the LED on (HIGH is the voltage level)
//    vTaskDelay(250);  // one tick delay (15ms) in between reads for stability
//    digitalWrite(LED_GPIO, LOW);    // turn the LED off by making the voltage LOW
//    vTaskDelay(250);  // one tick delay (15ms) in between reads for stability
//  }
//  vTaskDelete(NULL);
//}
//
//void TaskAnalogReadA3(void *pvParameters)  // This is a task.
//{
//  (void) pvParameters;
//
//  /*
//    AnalogReadSerial A3
//    SN GPIO ADC3
//
//    This example code is in the public domain.
//  */
//
//  for (;;)
//  {
//    // read the input on analog pin A3:
//    int sensorValueA3 = analogRead(A3);
//    // print out the value you read:
//    Serial.println(sensorValueA3);
//    Serial.print("Task2: ");
//    Serial.println(xPortGetCoreID());
//    vTaskDelay(500);  // one tick delay (15ms) in between reads for stability
//  }
//  vTaskDelete(NULL);
//}
//========================Suppend & Resume=================================
 //Định nghĩa 2 task
void Task_Print1(void *param);
void Task_Print2(void *param);
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
int counter = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(Task_Print1, "Task1", 2048, NULL, 1, &TaskHandle_1);
  xTaskCreate(Task_Print2, "Task2", 2048, NULL, 1, &TaskHandle_2);
}
void loop() {
  // put your main code here, to run repeatedly:
}
void Task_Print1(void * param){
  (void)param;
  TickType_t getTick;
  getTick = xTaskGetTickCount();
  while(1){
    Serial.println("TASK 1");
    if (counter == 21){
      vTaskDelete(TaskHandle_1);
    }
    counter++;
    if (counter == 15){
      vTaskResume(TaskHandle_2);   // Tiếp tục Task 2
    }
    vTaskDelayUntil(&getTick, 1000/ portTICK_PERIOD_MS);
  }
}
void Task_Print2(void *param){
  (void)param;
  while(1){
    Serial.println("TASK 2");
    counter++;
    if (counter == 10){
      vTaskSuspend(TaskHandle_2);   // Tạm dừng Task 2
    }
    vTaskDelay( 1000/ portTICK_PERIOD_MS);
  }
}