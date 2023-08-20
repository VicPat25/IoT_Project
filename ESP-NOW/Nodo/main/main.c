#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "nvs_flash.h"
#include "esp_log.h"

#define ESP_CHANNEL 1
#define LM35_GPIO_PIN ADC1_CHANNEL_4
#define VOLTAGE_SUPPLY 3300
#define ADC_REF_VOLTAGE 1100
#define ADC_WIDTH_BIT 12
#define ADC_MAX_VALUE ((1<<ADC_WIDTH_BIT)-1)

#define LED_PIN 2

static esp_adc_cal_characteristics_t adc_chars;
static uint8_t initiator_mac[ESP_NOW_ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static const char *TAG = "esp_now_resp";

float lm35_value = 0.0;

static esp_err_t init_wifi(void)
{
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_netif_init();
    esp_event_loop_create_default();
    nvs_flash_init();
    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);
    esp_wifi_start();
    ESP_LOGI(TAG, "wifi init completed");
    return ESP_OK;
}

void recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len)
{
    if (data_len == sizeof(uint8_t))
    {
        uint8_t led_state = data[0];
        gpio_set_level(LED_PIN, led_state);
        ESP_LOGI(TAG, "Received LED state from " MACSTR ": %d", MAC2STR(esp_now_info->src_addr), led_state);
    }
}

void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (status == ESP_NOW_SEND_SUCCESS)
    {
        ESP_LOGI(TAG, "Data sent to " MACSTR " successfully", MAC2STR(mac_addr));
    }
    else
    {
        ESP_LOGW(TAG, "Data sending to " MACSTR " failed", MAC2STR(mac_addr));
    }
}

static esp_err_t init_esp_now(void)
{
    esp_now_init();
    esp_now_register_recv_cb(recv_cb);
    ESP_LOGI(TAG, "esp now init completed");
    return ESP_OK;
}

static esp_err_t register_peer(uint8_t *peer_addr)
{
    esp_now_peer_info_t esp_now_peer_info = {};
    memcpy(esp_now_peer_info.peer_addr, peer_addr, ESP_NOW_ETH_ALEN);
    esp_now_peer_info.channel = ESP_CHANNEL;
    esp_now_peer_info.ifidx = ESP_IF_WIFI_STA;
    esp_now_add_peer(&esp_now_peer_info);
    return ESP_OK;
}

esp_err_t init_lm35(void)
{
    adc1_config_width(ADC_WIDTH_BIT);
    adc1_config_channel_atten(LM35_GPIO_PIN, ADC_ATTEN_DB_11);
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT, ADC_REF_VOLTAGE, &adc_chars);
    return ESP_OK;
}

float read_lm35(void)
{
    uint32_t adc_reading = adc1_get_raw(LM35_GPIO_PIN);
    uint32_t millivolts = esp_adc_cal_raw_to_voltage(adc_reading, &adc_chars);
    return (float)(millivolts / 10.0); 
}

void app_main(void)
{
    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(initiator_mac));
    ESP_ERROR_CHECK(init_lm35());

    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 0);

    while (1)
    {
        lm35_value = read_lm35();
        esp_now_send(initiator_mac, (uint8_t *)&lm35_value, sizeof(lm35_value));
        ESP_LOGI(TAG, "Temperature sent: %.2f °C", lm35_value);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
