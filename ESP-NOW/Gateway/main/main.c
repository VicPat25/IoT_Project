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

//Dirección MAC del dispositivo remoto (nodo) con el que se va a comunicar
static uint8_t responder_macs[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //Mac del Nodo (Responder)

// Etiqueta para los registros de ESP_LOG, utilizada para identificar los mensajes de registro
static const char *TAG = "esp_now_init";

static esp_err_t init_wifi(void); // Declaración de la función para inicializar el Wi-Fi.
void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status); // Declaración de la función de devolución de llamada para enviar datos mediante ESP-NOW.
static esp_err_t init_esp_now(void); // Declaración de la función para inicializar el protocolo ESP-NOW.
static esp_err_t register_peer(uint8_t *peer_addr); // Declaración de la función para registrar un dispositivo remoto.
esp_err_t init_led(void); // Declaración de la función para inicializar el LED.
esp_err_t toggle_led(void); // Declaración de la función para cambiar el estado del LED.

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

// Función de devolución de llamada para enviar datos mediante ESP-NOW.
void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (status == ESP_NOW_SEND_SUCCESS) // Comprobar si el envío fue exitoso.
    {
        ESP_LOGI(TAG, "ESP_NOW_SEND_SUCCESS"); // Mostrar mensaje de depuración si el envío fue exitoso.
    }
    else
    {
        ESP_LOGW(TAG, "ESP_NOW_SEND_FAIL"); // Mostrar mensaje de advertencia si el envío falló.
    }
}

// Función para inicializar el protocolo ESP-NOW.
static esp_err_t init_esp_now(void)
{
    esp_now_init(); // Inicializar el protocolo ESP-NOW.
    esp_now_register_send_cb(send_cb); // Registrar la función de devolución de llamada para enviar datos mediante ESP-NOW.
    ESP_LOGI(TAG, "esp now completed"); // Mostrar mensaje de depuración para indicar que ESP-NOW se ha completado.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

// Función para registrar un dispositivo remoto.
static esp_err_t register_peer(uint8_t *peer_addr)
{
    esp_now_peer_info_t esp_now_peer_info = {}; // Inicializar la estructura para la información del dispositivo remoto.
    memcpy(esp_now_peer_info.peer_addr, responder_macs, ESP_NOW_ETH_ALEN); // Copiar la dirección MAC del dispositivo remoto en la estructura.
    esp_now_peer_info.channel = ESP_CHANNEL; // Configurar el número de canal para ESP-NOW.
    esp_now_peer_info.ifidx = ESP_IF_WIFI_STA; // Configurar el índice de interfaz Wi-Fi para ESP-NOW.
    esp_now_add_peer(&esp_now_peer_info); // Agregar el dispositivo remoto a la lista de peers de ESP-NOW.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

// Función para inicializar el LED.
esp_err_t init_led(void)
{
    gpio_reset_pin(LED_PIN); // Reiniciar el pin GPIO que controla el LED.
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // Configurar el pin GPIO como salida.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

// Función para cambiar el estado del LED.
esp_err_t toggle_led(void)
{
    led_state = !led_state; // Cambiar el estado del LED (encendido/apagado).
    gpio_set_level(LED_PIN, led_state); // Actualizar el valor del pin GPIO para reflejar el estado del LED.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

// Función principal del programa.
void app_main(void)
{
    ESP_ERROR_CHECK(init_wifi()); // Inicializar el Wi-Fi y verificar si hay errores en su ejecución.
    ESP_ERROR_CHECK(init_esp_now()); // Inicializar ESP-NOW y verificar si hay errores en su ejecución.
    ESP_ERROR_CHECK(register_peer(responder_macs)); // Registrar el dispositivo remoto para la comunicación mediante ESP-NOW.
    ESP_ERROR_CHECK(init_led()); // Inicializar el LED y verificar si hay errores en su ejecución.

    while (1) // Bucle principal para mantener el programa en ejecución.
    {
        toggle_led(); // Cambiar el estado del LED.
        esp_now_send(responder_macs, &led_state, sizeof(led_state)); // Enviar el estado del LED al dispositivo remoto mediante ESP-NOW.
        vTaskDelay(pdMS_TO_TICKS(1000)); // Esperar 1000 milisegundos (1 segundo) antes de repetir el proceso.
    }
}
