// Cờ tác vụ
TaskHandle_t xTask1Handle;
TaskHandle_t xTask2Handle;

// Cờ báo hiệu sản phẩm hoàn thành
uint32_t ulTaskFlag = 0;
uint32_t ulTaskNotification;

void vTask1(void *pvParameters)
{  
  while (true)
  {
    Serial.println("Tao san pham");
  // Đặt cờ báo hiệu sản phẩm hoàn thành
    xTaskNotify(xTask2Handle, 0x01, eSetBits);
  }
}

void vTask2(void *pvParameters)
{
  while (true)
  {
    // Chờ cờ báo hiệu sản phẩm hoàn thành
    ulTaskNotification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    if (ulTaskNotification & 0x01)
    {
      Serial.println("Da nhan san pham");
    }
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(vTask1, "Task1", 2048, NULL, 1,  &xTask1Handle, 0);
  xTaskCreatePinnedToCore(vTask2, "Task2", 2048, NULL, 1,  &xTask2Handle, 0);
}

void loop() {
  // Định nghĩa các thao tác lặp lại ở đây
}

