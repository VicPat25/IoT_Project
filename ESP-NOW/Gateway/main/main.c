#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define ESP_CHANNEL 1
#define LED_PIN 2
#define LED_PIN1 32
#define LED_PIN2 33
uint8_t led_state = 0;

#define MAX_RESPONDERS 4
static uint8_t responder_macs[MAX_RESPONDERS][ESP_NOW_ETH_ALEN] = {
    {0x58, 0xbf, 0x25, 0x05, 0x6f, 0xf8},
    {0x30, 0xc6, 0xf7, 0x1e, 0x8e, 0x0c},
    {0x3c, 0x61, 0x05, 0x13, 0x75, 0xe4},
    {0xf0, 0x08, 0xd1, 0xd8, 0x26, 0x00}
};

static float temperatures[MAX_RESPONDERS] = {0.0};
static bool connected[MAX_RESPONDERS] = {false};
static TickType_t last_update[MAX_RESPONDERS] = {0};

#define DISCONNECT_THRESHOLD_MS 2000
#define MAX_DISCONNECT_TIMEOUT_MS 3000

static const char *TAG = "esp_now_init";

static esp_err_t init_wifi(void);
void recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len);
void check_disconnections();
void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
static esp_err_t init_esp_now(void);
static esp_err_t register_peer(uint8_t *peer_addr);
esp_err_t init_led(void);

#define BUF_SIZE (1024)

static QueueHandle_t uart_queue;

void uart_event_task(void *pvParameters) {
    uart_event_t event;
    uint8_t *dtmp = (uint8_t *)malloc(BUF_SIZE);
    while (1) {
    if (xQueueReceive(uart_queue, (void *)&event, portMAX_DELAY)) {
            if (event.type == UART_DATA) {
                uint8_t* data = (uint8_t*) malloc(event.size);
                uart_read_bytes(UART_NUM_0, data, event.size, portMAX_DELAY);
                for (int i = 0; i < event.size; i++) {
                    char inChar = (char)data[i];
                    if (inChar == '\n') {
                        if (strncmp((char*)dtmp, "$On1", 4) == 0) {
                            gpio_set_level(LED_PIN1, 1);

                            for (int i = 0; i < MAX_RESPONDERS; i++)
                                {
                                    if (memcmp(responder_macs[i], (uint8_t[]){0x58, 0xbf, 0x25, 0x05, 0x6f, 0xf8}, ESP_NOW_ETH_ALEN) == 0)
                                    {
                                        uint8_t data = 1;
                                        esp_err_t result = esp_now_send(responder_macs[i], &data, sizeof(data));
                                        break; // Solo queremos enviar una vez a la MAC específica
                                    }
                                }


                        } else if (strncmp((char*)dtmp, "$Off1", 5) == 0) {
                            gpio_set_level(LED_PIN1, 0);

                            for (int i = 0; i < MAX_RESPONDERS; i++)
                                {
                                    if (memcmp(responder_macs[i], (uint8_t[]){0x58, 0xbf, 0x25, 0x05, 0x6f, 0xf8}, ESP_NOW_ETH_ALEN) == 0)
                                    {
                                        uint8_t data = 0;
                                        esp_err_t result = esp_now_send(responder_macs[i], &data, sizeof(data));
                                        break; // Solo queremos enviar una vez a la MAC específica
                                    }
                                }

                        } else if (strncmp((char*)dtmp, "$On2", 4) == 0) {
                            gpio_set_level(LED_PIN2, 1);

                            for (int i = 0; i < MAX_RESPONDERS; i++)
                                {
                                    if (memcmp(responder_macs[i], (uint8_t[]){0x30, 0xc6, 0xf7, 0x1e, 0x8e, 0x0c}, ESP_NOW_ETH_ALEN) == 0)
                                    {
                                        uint8_t data = 1;
                                        esp_err_t result = esp_now_send(responder_macs[i], &data, sizeof(data));
                                        break; // Solo queremos enviar una vez a la MAC específica
                                    }
                                }

                        } else if (strncmp((char*)dtmp, "$Off2", 5) == 0) {
                            gpio_set_level(LED_PIN2, 0);
                            
                            for (int i = 0; i < MAX_RESPONDERS; i++)
                                {
                                    if (memcmp(responder_macs[i], (uint8_t[]){0x30, 0xc6, 0xf7, 0x1e, 0x8e, 0x0c}, ESP_NOW_ETH_ALEN) == 0)
                                    {
                                        uint8_t data = 0;
                                        esp_err_t result = esp_now_send(responder_macs[i], &data, sizeof(data));
                                        break; // Solo queremos enviar una vez a la MAC específica
                                    }
                                }
                        }
                        memset(dtmp, 0, BUF_SIZE);
                    } else {
                        if (strlen((char*)dtmp) < BUF_SIZE - 1) {
                            strncat((char*)dtmp, &inChar, 1);
                        }
                    }
                }
                free(data);
            }
        }
    }
    free(dtmp);
}

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
    return ESP_OK;
}

void recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len)
{
    if (data_len == sizeof(float))
    {
        float temperature;
        memcpy(&temperature, data, sizeof(float));
        int index = -1;
        for (int i = 0; i < MAX_RESPONDERS; i++)
        {
            if (memcmp(esp_now_info->src_addr, responder_macs[i], ESP_NOW_ETH_ALEN) == 0)
            {
                index = i;
                break;
            }
        }
        if (index >= 0 && index < MAX_RESPONDERS)
        {
            temperatures[index] = temperature;
            connected[index] = true;
            last_update[index] = xTaskGetTickCount();
        }
    }
}

void check_disconnections()
{
    TickType_t current_time = xTaskGetTickCount();
    for (int i = 0; i < MAX_RESPONDERS; i++)
    {
        if (connected[i] && (current_time - last_update[i]) >= pdMS_TO_TICKS(MAX_DISCONNECT_TIMEOUT_MS))
        {
            connected[i] = false;
            temperatures[i] = 0.0;
        }
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
    esp_err_t err = esp_now_init();
    if (err == ESP_OK)
    {
        esp_now_register_recv_cb(recv_cb);
    }
    return err;
}

static esp_err_t register_peers(void)
{
    for (int i = 0; i < MAX_RESPONDERS; i++)
    {
        esp_now_peer_info_t esp_now_peer_info = {};
        memcpy(esp_now_peer_info.peer_addr, responder_macs[i], ESP_NOW_ETH_ALEN);
        esp_now_peer_info.channel = ESP_CHANNEL;
        esp_now_peer_info.ifidx = ESP_IF_WIFI_STA;
        esp_err_t err = esp_now_add_peer(&esp_now_peer_info);
    }
    return ESP_OK;
}

esp_err_t init_led(void)
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    return ESP_OK;
}




void app_main(void)
{
    init_wifi();
    init_esp_now();
    register_peers();
    init_led();

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 256, 0, 10, &uart_queue, 0);

    gpio_set_direction(LED_PIN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN2, GPIO_MODE_OUTPUT);

    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 1, NULL);

    while (1)
    {
        check_disconnections();


        vTaskDelay(pdMS_TO_TICKS(100)); // Pequeña pausa para evitar un bucle de ocupación del CPU

        for (int i = 0; i < MAX_RESPONDERS; i++)
        {
            if (connected[i])
            {
                printf("%.2f", temperatures[i]);
            }
            else
            {
                printf("0");
            }

            if (i < MAX_RESPONDERS - 1)
            {
                printf(", ");
            }
        }
        printf("\n");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}