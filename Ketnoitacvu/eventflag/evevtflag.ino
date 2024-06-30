#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

// Khai báo event flag
EventGroupHandle_t event_group;

// Xác định các bit flag
#define BUTTON_PRESSED_FLAG (1 << 0)

// Task 1: Giả lập nút bấm "Đổi đèn"
void task_button(void *pvParameters)
{
  while (true) {
    // Chờ 2 giây
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    // Set event flag "BUTTON_PRESSED_FLAG"
    xEventGroupSetBits(event_group, BUTTON_PRESSED_FLAG);

    // In ra thông báo
    printf("Nút bấm được nhấn!\n");
  }
}

// Task 2: Quản lý trạng thái đèn giao thông
void task_traffic_light(void *pvParameters)
{
  uint8_t current_state = 0; // 0: Đỏ, 1: Vàng, 2: Xanh

  while (true) {
    // Chờ event flag "BUTTON_PRESSED_FLAG"
    xEventGroupWaitBits(event_group, BUTTON_PRESSED_FLAG, pdTRUE, pdTRUE, portMAX_DELAY);

    // Cập nhật trạng thái đèn
    current_state = (current_state + 1) % 3;

    // In ra trạng thái đèn
    switch (current_state) {
      case 0:
        printf("Đèn đỏ!\n");
        break;
      case 1:
        printf("Đèn vàng!\n");
        break;
      case 2:
        printf("Đèn xanh!\n");
        break;
    }

    // Hiển thị trạng thái đèn (bằng LED hoặc in ra màn hình)
    // ...

    // Chờ 1 giây
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task 3: Hiển thị trạng thái đèn giao thông
void task_display(void *pvParameters)
{
  while (true) {
    // Hiển thị trạng thái đèn (bằng LED hoặc in ra màn hình)
    // ...

    // Chờ 0.5 giây
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // Tạo event flag
  event_group = xEventGroupCreate();

  // Tạo các task
  xTaskCreate(task_button, "Button", 1024, NULL, 1, NULL);
  xTaskCreate(task_traffic_light, "Traffic Light", 1024, NULL, 2, NULL);
  xTaskCreate(task_display, "Display", 1024, NULL, 3, NULL);
}

void loop() {
}
