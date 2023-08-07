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
#define MAX_RESPONDERS 4
static uint8_t responder_macs[MAX_RESPONDERS][ESP_NOW_ETH_ALEN] = {
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Mac del Nodo1 (Responder)
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Mac del Nodo2 (Responder)
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Mac del Nodo3 (Responder)
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Mac del Nodo4 (Responder)
};

static float temperatures[MAX_RESPONDERS] = {0.0}; // Array to store temperatures
static bool connected[MAX_RESPONDERS] = {false};   // Array to track node connection status
static TickType_t last_update[MAX_RESPONDERS] = {0}; // Array to track last update time

#define DISCONNECT_THRESHOLD_MS 3000 // Tiempo para determinar cuándo se considera que un nodo está desconectado
#define MAX_DISCONNECT_TIMEOUT_MS 5000 // Tiempo máximo que un nodo puede estar desconectado antes de que se actualice su estado en el arreglo

// Etiqueta para los registros de ESP_LOG, utilizada para identificar los mensajes de registro
static const char *TAG = "esp_now_init";

static esp_err_t init_wifi(void); // Declaración de la función para inicializar el Wi-Fi.
void recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len); // Declaración de la función de devolución de llamada a datos mediante ESP-NOW.
void check_disconnections(); // Declaracion de la función para verificar si alguno de los nodos conectados a través de ESP-NOW se ha desconectado
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
void recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len)
{
    if (data_len == sizeof(float)) // Verificar si la longitud de los datos recibidos es igual al tamaño de un tipo float (4 bytes).
    {
        float temperature;
        memcpy(&temperature, data, sizeof(float)); // Copiar los datos recibidos al puntero temperature utilizando memcpy.

        // Buscar el índice del nodo remitente en el arreglo responder_macs.
        int index = -1;
        for (int i = 0; i < MAX_RESPONDERS; i++)
        {
            // Comparar las direcciones MAC del nodo remitente con las direcciones MAC almacenadas en responder_macs.
            if (memcmp(esp_now_info->src_addr, responder_macs[i], ESP_NOW_ETH_ALEN) == 0)
            {
                // Si se encuentra una coincidencia, establecer el índice en el valor encontrado y salir del bucle.
                index = i;
                break;
            }
        }

        // Verificar si se encontró un índice válido para el nodo remitente.
        if (index >= 0 && index < MAX_RESPONDERS)
        {
            temperatures[index] = temperature; // Actualizar la temperatura recibida en el arreglo temperatures en la posición correspondiente al nodo remitente.
            connected[index] = true; // Marcar el nodo como conectado estableciendo el valor de connected a true.
            last_update[index] = xTaskGetTickCount(); // Actualizar el tiempo de la última actualización en el arreglo last_update.
            // Mostrar un mensaje de información en los logs que indica la recepción de la temperatura del nodo remitente.
            ESP_LOGI(TAG, "Received temperature from N%d: %.2f C", index + 1, temperature);
        }
    }
}

void check_disconnections() 
{
    // Obtener el tiempo actual en milisegundos utilizando la función xTaskGetTickCount().
    TickType_t current_time = xTaskGetTickCount();

    for (int i = 0; i < MAX_RESPONDERS; i++) // Recorrer el arreglo connected para verificar si ha habido desconexiones de nodos.
    {
        // Verificar si el nodo está marcado como conectado y si ha superado el umbral de desconexión.
        if (connected[i] && (current_time - last_update[i]) >= pdMS_TO_TICKS(MAX_DISCONNECT_TIMEOUT_MS))
        {
            connected[i] = false; // Marcar el nodo como desconectado estableciendo el valor de connected a false.
            temperatures[i] = 0.0; // Restablecer el valor de temperatura en temperatures a 0.0.
            // Mostrar un mensaje de advertencia en los logs indicando que el nodo se ha desconectado.
            ESP_LOGW(TAG, "Responder %d disconnected", i + 1);
        }
    }
}

// Función de devolución de llamada para enviar datos mediante ESP-NOW.
void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (status == ESP_NOW_SEND_SUCCESS) // Comprobar si el envío fue exitoso.
    {
        ESP_LOGI(TAG, "Data sent to " MACSTR " successfully", MAC2STR(mac_addr)); // Mostrar mensaje de depuración si el envío fue exitoso.
    }
    else
    {
        ESP_LOGW(TAG, "Data sending to " MACSTR " failed", MAC2STR(mac_addr)); // Mostrar mensaje de advertencia si el envío falló.
    }
}

// Función para inicializar el protocolo ESP-NOW.
static esp_err_t init_esp_now(void)
{
    esp_err_t err = esp_now_init(); // Inicializar ESP-NOW y almacenar el resultado en la variable err.

    if (err == ESP_OK) // Verificar si la inicialización de ESP-NOW fue exitosa.
    {
        esp_now_register_recv_cb(recv_cb); // Si fue exitosa, registrar la función de devolución de llamada recv_cb para recibir datos mediante ESP-NOW.
        ESP_LOGI(TAG, "esp now completed"); // Mostrar un mensaje de información en los logs para indicar que la inicialización de ESP-NOW se ha completado.
    }
    else
    {
        ESP_LOGE(TAG, "esp now init failed: %s", esp_err_to_name(err)); // Si la inicialización falló, mostrar un mensaje de error en los logs con el código de error correspondiente.

    }
    return err; // Devolver el resultado de la inicialización de ESP-NOW (ESP_OK si fue exitosa, o un código de error en caso contrario).
}

// Función para registrar un dispositivo remoto.
static esp_err_t register_peers(void)
{
    // Bucle para registrar cada uno de los dispositivos remotos (peers) en ESP-NOW.
    for (int i = 0; i < MAX_RESPONDERS; i++)
    {
        esp_now_peer_info_t esp_now_peer_info = {}; // Inicializar la estructura para la información del dispositivo remoto.
        memcpy(esp_now_peer_info.peer_addr, responder_macs[i], ESP_NOW_ETH_ALEN); // Copiar la dirección MAC del peer desde el array responder_macs[i] a la estructura esp_now_peer_info.
        esp_now_peer_info.channel = ESP_CHANNEL; // Configurar el número de canal para la comunicación con el peer.
        esp_now_peer_info.ifidx = ESP_IF_WIFI_STA; // Configurar el índice de interfaz WiFi para el peer (ESP_IF_WIFI_STA para el modo estación).
        esp_err_t err = esp_now_add_peer(&esp_now_peer_info); // Añadir el peer a la lista de peers de ESP-NOW y almacenar el resultado en la variable err.

        if (err == ESP_OK) // Verificar si el registro del peer fue exitoso.
        {
            ESP_LOGI(TAG, "Peer %d registered", i + 1); // Si fue exitoso, mostrar un mensaje de información en los logs indicando que el peer ha sido registrado.
        }
        else
        {
            ESP_LOGE(TAG, "Peer %d registration failed: %s", i + 1, esp_err_to_name(err)); // Si el registro falló, mostrar un mensaje de error en los logs con el código de error correspondiente.
        }
    }
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores durante el registro de los peers.
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
    ESP_ERROR_CHECK(register_peers()); // Registrar el dispositivo remoto para la comunicación mediante ESP-NOW.
    ESP_ERROR_CHECK(init_led()); // Inicializar el LED y verificar si hay errores en su ejecución.

    while (1) // Bucle principal para mantener el programa en ejecución.
    {
        check_disconnections(); // Verificar si hay nodos desconectados y actualizar su estado.
        toggle_led(); // Cambiar el estado del LED.
        // Enviar el estado del LED a cada uno de los responders registrados.
        for (int i = 0; i < MAX_RESPONDERS; i++)
        {
            esp_now_send(responder_macs[i], &led_state, sizeof(led_state));
        }
        ESP_LOGI(TAG, "___________________________"); // Mostrar mensaje de depuración para indicar que se ha enviado el estado del LED a todos los responders.

        vTaskDelay(pdMS_TO_TICKS(1000)); // Esperar 1000 milisegundos (1 segundo) antes de repetir el proceso.
    }
}
