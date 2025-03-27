#include <stdio.h>
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_log.h"
#include "string.h"
#include "nvs_flash.h"
#include "esp_now.h"
uint8_t esp_mac[6];
static const char* TAG = "ESP-NOW RX";
void esp_now_recv_callback(const esp_now_recv_info_t * esp_now_info, const uint8_t *data, int data_len)
{
 ESP_LOGI(TAG,"received data : %.*s", data_len, data);
}
void wifi_sta_init(void)
{
    esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    nvs_flash_erase();
    ret = nvs_flash_init();
  }
  esp_netif_init();
  esp_event_loop_create_default();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_mode(WIFI_MODE_STA);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_start();
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  esp_read_mac(esp_mac, ESP_MAC_WIFI_STA);
  ESP_LOGI(TAG, "peer mac " MACSTR "", esp_mac[0], esp_mac[1], esp_mac[2], esp_mac[3], esp_mac[4], esp_mac[5]);
}
void app_main(void)
{
  wifi_sta_init();
  esp_now_init();
  esp_now_register_recv_cb(esp_now_recv_callback);
  
  while(1)
  {
  
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}