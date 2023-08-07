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
#include "driver/adc.h"            // Librería para el control del módulo ADC (Convertidor Analógico-Digital) en ESP32.
#include "esp_adc_cal.h"           // Librería para calibrar el módulo ADC en ESP32.

#define ESP_CHANNEL 1              // Definición de un número de canal para ESP-NOW.
#define LED_PIN 2                  // Definición del número del pin que controla el LED.

#define LM35_GPIO_PIN ADC1_CHANNEL_4  // Definición del pin GPIO utilizado para leer la señal del sensor LM35 (canal 4 del ADC1).

#define VOLTAGE_SUPPLY 3300           // Voltaje de alimentación en milivoltios (mV) para el ADC (3.3V en este caso).
#define ADC_REF_VOLTAGE 1100          // Voltaje de referencia en milivoltios (mV) para el ADC (1.1V en este caso).
#define ADC_WIDTH_BIT 12              // Número de bits de resolución del ADC (12 bits para el ESP32).
#define ADC_MAX_VALUE ((1<<ADC_WIDTH_BIT)-1)  // Valor máximo que puede ser representado por el ADC (2^12 - 1 = 4095).

static esp_adc_cal_characteristics_t adc_chars;  // Estructura que almacena las características calibradas del ADC.
float lm35_value = 0.0;  // Variable que almacena el valor de temperatura del sensor LM35 en grados Celsius.

static uint8_t initiator_mac[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //Mac del Gateway (Initiator)

// Etiqueta para los registros de ESP_LOG, utilizada para identificar los mensajes de registro
static const char *TAG = "esp_now_resp";

static esp_err_t init_wifi(void); // Declaración de la función para inicializar el Wi-Fi.
void recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len); // Declaración de la función de devolución de llamada a datos mediante ESP-NOW.
void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status); //Declaracion de la función de devolución de llamada para enviar datos mediante ESP-NOW.
static esp_err_t init_esp_now(void); // Declaración de la función para inicializar el protocolo ESP-NOW.
static esp_err_t register_peer(uint8_t *peer_addr); // Declaracion de la función para registrar un dispositivo remoto en ESP-NOW.
esp_err_t init_lm35(void); // Declaracion de la función para inicializar el módulo LM35 (sensor de temperatura).
float read_lm35(void); // Declaracion de la función para leer el valor del sensor de temperatura LM35 y convertirlo en grados Celsius.

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
void recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len)
{
    if (data_len == sizeof(uint8_t)) // Verificar si la longitud de los datos recibidos es igual al tamaño de un tipo uint8_t (1 byte).
    {
        uint8_t led_state = data[0]; // Extraer el estado del LED del arreglo data en la posición 0.
        gpio_set_level(LED_PIN, led_state); // Establecer el estado del LED según el valor recibido.
        // Mostrar un mensaje de información en los logs que indica la recepción del estado del LED desde el dispositivo remitente.
        ESP_LOGI(TAG, "Received LED state from " MACSTR ": %d", MAC2STR(esp_now_info->src_addr), led_state);
    }
}

// Función de devolución de llamada para enviar datos mediante ESP-NOW.
void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (status == ESP_NOW_SEND_SUCCESS) // Comprobar si el envío fue exitoso.
    {
        // Mostrar un mensaje de información en los logs que indica que los datos fueron enviados correctamente al dispositivo con la dirección MAC especificada.
        ESP_LOGI(TAG, "Data sent to " MACSTR " successfully", MAC2STR(mac_addr));
    }
    else
    {
        // Mostrar un mensaje de advertencia en los logs que indica que ha ocurrido un fallo en el envío de datos al dispositivo con la dirección MAC especificada.
        ESP_LOGW(TAG, "Data sending to " MACSTR " failed", MAC2STR(mac_addr));
    }
}

// Función para inicializar el protocolo ESP-NOW.
static esp_err_t init_esp_now(void)
{
    esp_now_init(); // Inicializa el protocolo ESP-NOW para la comunicación inalámbrica entre dispositivos.
    esp_now_register_recv_cb(recv_cb); // Registra la función de devolución de llamada recv_cb para recibir datos mediante ESP-NOW.
    ESP_LOGI(TAG, "esp now init completed"); // Muestra un mensaje de información en los logs que indica que la inicialización de ESP-NOW se ha completado.

    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores.
}

// Función para registrar un dispositivo remoto en ESP-NOW.
static esp_err_t register_peer(uint8_t *peer_addr)
{
    esp_now_peer_info_t esp_now_peer_info = {}; // Inicializar la estructura para la información del dispositivo remoto.
    memcpy(esp_now_peer_info.peer_addr, peer_addr, ESP_NOW_ETH_ALEN); // Copiar la dirección MAC del dispositivo remoto desde el puntero peer_addr a la estructura esp_now_peer_info.
    esp_now_peer_info.channel = ESP_CHANNEL; // Configurar el número de canal para la comunicación con el dispositivo remoto.
    esp_now_peer_info.ifidx = ESP_IF_WIFI_STA; // Configurar el índice de interfaz WiFi para el dispositivo remoto (ESP_IF_WIFI_STA para el modo estación).
    esp_now_add_peer(&esp_now_peer_info); // Añadir el dispositivo remoto a la lista de peers de ESP-NOW.
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores durante el registro del dispositivo remoto.
}

// Función para inicializar el módulo LM35 (sensor de temperatura).
esp_err_t init_lm35(void)
{
    adc1_config_width(ADC_WIDTH_BIT); // Configurar el ancho de bits de la lectura del ADC a 12 bits.
    adc1_config_channel_atten(LM35_GPIO_PIN, ADC_ATTEN_DB_11); // Configurar la atenuación del canal ADC para la lectura del sensor LM35.
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT, ADC_REF_VOLTAGE, &adc_chars); // Calibrar el módulo ADC utilizando las características específicas del ESP32 (almacenadas en adc_chars).
    return ESP_OK; // Devolver ESP_OK para indicar que no ha habido errores durante la inicialización del módulo LM35.
}

// Función para leer el valor del sensor de temperatura LM35 y convertirlo en grados Celsius.
float read_lm35(void)
{
    uint32_t adc_reading = adc1_get_raw(LM35_GPIO_PIN); // Leer el valor del sensor LM35 utilizando el ADC.
    uint32_t millivolts = esp_adc_cal_raw_to_voltage(adc_reading, &adc_chars); // Convertir el valor del ADC a milivoltios utilizando las características calibradas del ADC (almacenadas en adc_chars).
    return (float)(millivolts / 10.0); // Calcular el valor de temperatura en grados Celsius y devolverlo como un número flotante.
}

void app_main(void)
{
   ESP_ERROR_CHECK(init_wifi()); // Inicializar el Wi-Fi y verificar si hay errores en su ejecución.
    ESP_ERROR_CHECK(init_esp_now()); // Inicializar ESP-NOW y verificar si hay errores en su ejecución.
    ESP_ERROR_CHECK(register_peer(initiator_mac)); // Registra el dispositivo remoto (peer) con la dirección MAC `initiator_mac` para la comunicación mediante ESP-NOW y verifica si hay errores.
    ESP_ERROR_CHECK(init_lm35()); // Inicializa el módulo LM35 para la lectura de temperatura y verifica si hay errores.

    gpio_reset_pin(LED_PIN); // Reinicia el pin GPIO que controla el LED.
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // Configura el pin GPIO como salida.
    gpio_set_level(LED_PIN, 0); // Establece el nivel del pin GPIO a 0 (apaga el LED).

    while (1) // Bucle principal para mantener el programa en ejecución.
    {
        lm35_value = read_lm35(); // Lee el valor de temperatura del módulo LM35.
        esp_now_send(initiator_mac, (uint8_t *)&lm35_value, sizeof(lm35_value)); // Envía el valor de temperatura al dispositivo remoto (initiator) mediante ESP-NOW.
        // Muestra un mensaje de información en los logs que indica la temperatura enviada.
        ESP_LOGI(TAG, "Temperature sent: %.2f °C", lm35_value);

        vTaskDelay(pdMS_TO_TICKS(1000)); // Esperar 1000 milisegundos (1 segundo) antes de repetir el proceso.
    }
}
