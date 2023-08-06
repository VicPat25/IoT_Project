#include <stdio.h>           // Librería estándar de entrada y salida de datos.
#include "esp_wifi.h"        // Librería para configurar y gestionar el módulo Wi-Fi del ESP32.
#include "esp_mac.h"         // Librería para obtener la dirección MAC del ESP32.
#include "nvs_flash.h"       // Librería para el almacenamiento no volátil (NVS) en ESP32.
#include "esp_log.h"         // Librería para el registro de mensajes (logs) en ESP32.

// Etiqueta para los registros de ESP_LOG, utilizada para identificar los mensajes de registro
static const char *TAG = "mac_address";

// Función para inicializar el WiFi
static esp_err_t init_wifi(void)
{
    // Configuración predeterminada de WiFi.
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

    // Inicializar el subsistema de red en el ESP32.
    esp_netif_init();

    // Crear un bucle de eventos predeterminado.
    esp_event_loop_create_default();

    // Inicializar la memoria flash no volátil (NVS).
    nvs_flash_init();

    // Inicializar el módulo WiFi con la configuración predeterminada.
    esp_wifi_init(&wifi_init_config);

    // Configurar el modo estación (STA) para el WiFi.
    esp_wifi_set_mode(WIFI_MODE_STA);

    // Configurar el almacenamiento de datos WiFi en la memoria flash.
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);

    // Iniciar el módulo WiFi.
    esp_wifi_start();

    // Obtener la dirección MAC del dispositivo.
    uint8_t mac[6];
    esp_wifi_get_mac(WIFI_IF_STA, mac);

    // Mostrar la dirección MAC del dispositivo en el registro.
    ESP_LOGI(TAG, "Device MAC Address: " MACSTR, MAC2STR(mac));

    // Devolver ESP_OK para indicar que no ha habido errores.
    return ESP_OK;
}

// Función principal del programa.
void app_main(void)
{
    // Inicializar el WiFi y verificar si hay errores en su ejecución.
    ESP_ERROR_CHECK(init_wifi());
}
