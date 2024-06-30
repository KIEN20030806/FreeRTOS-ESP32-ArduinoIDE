SemaphoreHandle_t xMutex;
void setup() {
  Serial.begin(115200);
  /* create Mutex */
  xMutex = xSemaphoreCreateMutex();
  
  xTaskCreate(lowPriorityTask, "lowPriorityTask", 1000, NULL, 1, NULL);                    
  delay(500);
  xTaskCreate(highPriorityTask, "highPriorityTask", 1000, NULL, 4, NULL);                   
}

void loop() {

}
void lowPriorityTask( void * parameter )
{
  Serial.println((char *)parameter);
  for(;;){
    Serial.println("lowPriorityTask gains key");
    xSemaphoreTake( xMutex, portMAX_DELAY );
    Serial.println("lowPriorityTask is running");
    delay(2000);
    Serial.println("lowPriorityTask releases key");
    xSemaphoreGive( xMutex );
  }
  vTaskDelete( NULL );
}

void highPriorityTask( void * parameter )
{
  Serial.println((char *)parameter);
  for(;;){
    Serial.println("highPriorityTask gains key");
    xSemaphoreTake( xMutex, portMAX_DELAY );
    Serial.println("highPriorityTask is running");
    Serial.println("highPriorityTask releases key");
    xSemaphoreGive( xMutex );
    delay(1000);
  }
  vTaskDelete( NULL );
}