void task1 ( void *param);
void task2 ( void *param);
TaskHandle_t TaskHandle_1 = NULL;
TaskHandle_t TaskHandle_2 = NULL;
TaskHandle_t TaskHandle_3 = NULL;
QueueHandle_t Queue;
char myTxBuff[30];

void task1(void *p) {
  sprintf(myTxBuff, "Một");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
  sprintf(myTxBuff, "Hai");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
  sprintf(myTxBuff, "Ba");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
  sprintf(myTxBuff, "Bốn");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
  sprintf(myTxBuff, "Năm");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
  sprintf(myTxBuff, "Sáu");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
  sprintf(myTxBuff, "Bảy");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
  sprintf(myTxBuff, "Tám");
  xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 0);
  while (true) {
  }
}

// void task2(void *p) {
//   sprintf(myTxBuff, "Năm");
//   xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
//   sprintf(myTxBuff, "Sáu");
//   xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
//   sprintf(myTxBuff, "Bảy");
//   xQueueSend(Queue, (void*) myTxBuff, (TickType_t) 10);
//   while (true) { 
//   }
// }

void task3(void *p) {
  char myRxBuff[30];
  while (true) {
    if (Queue != 0) {
      if (xQueueReceive(Queue, (void*) myRxBuff, (TickType_t) 0)) {
        Serial.print("data receive: ");
        Serial.print(myRxBuff);
        Serial.print("\n");
        Serial.print("    data waiting to be read: ");
        Serial.print(uxQueueMessagesWaiting(Queue));
        Serial.print("\n");
      }
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Queue = xQueueCreate(7, sizeof(myTxBuff));
  xTaskCreatePinnedToCore(task1, "task1", 1024, NULL, 1, &TaskHandle_1,1);
  // xTaskCreatePinnedToCore(task2, "task2", 1024, NULL, 1, &TaskHandle_2,1);
  xTaskCreatePinnedToCore(task3, "task3", 1024, NULL, 1, &TaskHandle_3,1);
}
void loop() {
  // put your main code here, to run repeatedly:
}