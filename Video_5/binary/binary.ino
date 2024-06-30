#include "Arduino.h"

SemaphoreHandle_t Sem_Handle;

void task1(void*) {
  TaskHandle_t tsk1;
  while(1) {
    tsk1 = xTaskGetCurrentTaskHandle();
    Serial.print(pcTaskGetName(tsk1));
    Serial.println(" give semaphore");
    xSemaphoreGive(Sem_Handle);
    Serial.print(pcTaskGetName(tsk1));
    Serial.println(" task1 continute ...");
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void task2(void*) {
  TaskHandle_t tsk2;
  while(1) {
    tsk2 = xTaskGetCurrentTaskHandle();
    if (xSemaphoreTake(Sem_Handle, portMAX_DELAY) == pdTRUE) {
      Serial.print(pcTaskGetName(tsk2));
      Serial.println(" dong bo semaphore");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Sem_Handle = xSemaphoreCreateBinary();
  xTaskCreate(task1, "TASK1", 1000, NULL, 1, NULL);
  xTaskCreate(task2, "TASK2", 1000, NULL, 2, NULL);
  vTaskStartScheduler();
}

void loop() {
  // Không có gì cần thực hiện trong hàm loop() khi sử dụng FreeRTOS
}