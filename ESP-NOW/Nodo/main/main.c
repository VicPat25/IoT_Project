#include <stdio.h>                 // Librería estándar de entrada y salida de datos.
#include "string.h"                // Librería para funciones de manejo de cadenas de caracteres.
#include "freertos/FreeRTOS.h"     // Librería para el sistema operativo en tiempo real FreeRTOS.
#include "freertos/task.h"         // Librería para crear y gestionar tareas en FreeRTOS.
#include "esp_now.h"               // Librería para utilizar el protocolo de comunicación ESP-NOW.
#include "esp_wifi.h"              // Librería para configurar y gestionar el módulo Wi-Fi del ESP32.
#include "esp_netif.h"             // Librería para manejar interfaces de red en ESP32.
#include "esp_mac.h"               // Librería para obtener la dirección MAC del ESP32.
#include "esp_event.h"             // Librería para gestionar eventos en ESP32.
#include "nvs_flash.h"             // Librería para el almacenamiento no volátil (NVS) en ESP32.
#include "esp_log.h"               // Librería para el registro de mensajes (logs) en ESP32.
#include "driver/gpio.h"           // Librería para controlar los pines GPIO en ESP32.

#define ESP_CHANNEL 1              // Definición de un número de canal para ESP-NOW.
#define LED_PIN 2                  // Definición del número del pin que controla el LED.

uint8_t led_state = 0;             // Variable para almacenar el estado del LED.

static uint8_t initiator_mac[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //Mac del Gateway (Initiator)

// Etiqueta para los registros de ESP_LOG, utilizada para identificar los mensajes de registro
static const char *TAG = "esp_now_resp";

static esp_err_t init_wifi(void); // Declaración de la función para inicializar el Wi-Fi.
void recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len); // Declaración de la función de devolución de llamada a datos mediante ESP-NOW.
static esp_err_t init_esp_now(void); // Declaración de la función para inicializar el protocolo ESP-NOW.
esp_err_t init_led(void); // Declaración de la función para inicializar el LED.

// Función para inicializar el WiFi
static esp_err_t init_wifi(void)
{
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT(); // Configuración predeterminada de WiFi.
    esp_netif_init(); // Inicializar el subsistema de red en el ESP32.
    esp_event_loop_create_default(); // Crear un bucle de eventos predeterminado.
    nvs_flash_init(); // Inicializar la memoria flash no volátil (NVS).
    esp_wifi_init(&wifi_init_config); // Inicializar el módulo WiFi con la configuración predeterminada.
    esp_wifi_set_mode(WIFI_MODE_STA); // Configurar el modo estación (STA) para el WiFi.
    esp_wifi_set_storage(WIFI_STORAGE_FLASH); // Configurar el almacenamiento de datos WiFi en la memoria flash.
    esp_wifi_start(); // Iniciar el módulo WiFi.
    ESP_LOGI(TAG, "wifi init completed"); // Mostrar mensaje de depuración para indicar que la inicialización del Wi-Fi se ha completado.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

// Función de devolución de llamada a datos mediante ESP-NOW
void recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    if (data_len == sizeof(led_state)) // Comprobar si el tamaño de los datos recibidos es igual al tamaño de la variable led_state.
    {
        led_state = *data; // Asignar el valor recibido a la variable led_state.
        gpio_set_level(LED_PIN, led_state); // Configurar el pin GPIO que controla el LED con el valor de led_state (encendido o apagado).
        ESP_LOGI(TAG, "LED state changed to: %d", led_state); // Mostrar un mensaje de depuración en el registro indicando el cambio de estado del LED.
    }
}

// Función para inicializar el protocolo ESP-NOW.
static esp_err_t init_esp_now(void)
{
    esp_err_t ret = esp_now_init(); // Variable para almacenar el resultado de la inicialización de ESP-NOW.
    if (ret != ESP_OK) // Comprobar si la inicialización de ESP-NOW fue exitosa.
    {
        // Mostrar un mensaje de error en el registro con el código de error específico en caso de fallo.
        ESP_LOGE(TAG, "Error initializing ESP-NOW: %d", ret);
        // Devolver el código de error para que el llamador pueda tomar medidas si es necesario.
        return ret;
    }
    esp_now_register_recv_cb(recv_cb); // Registrar la función de devolución de llamada para recibir datos mediante ESP-NOW.
    ESP_LOGI(TAG, "esp now completed"); // Mostrar mensaje de depuración para indicar que ESP-NOW se ha completado.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

// Función para inicializar el LED.
esp_err_t init_led(void)
{
    gpio_reset_pin(LED_PIN); // Reiniciar el pin GPIO que controla el LED.
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // Configurar el pin GPIO como salida.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

void app_main(void)
{
    ESP_ERROR_CHECK(init_wifi()); // Inicializar el Wi-Fi y verificar si hay errores en su ejecución.
    ESP_ERROR_CHECK(init_esp_now()); // Inicializar ESP-NOW y verificar si hay errores en su ejecución.
    ESP_ERROR_CHECK(init_led()); // Inicializar el LED y verificar si hay errores en su ejecución.

    while (1) // Bucle principal para mantener el programa en ejecución.
    {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Esperar 1000 milisegundos (1 segundo) antes de repetir el proceso.
    }
}
