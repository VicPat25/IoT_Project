# MAC-Address

## Placa de desarrollo implementada

### DOIT ESP32 DEVKIT V1

La tarjeta DOIT ESP32 DevKit V1 es una placa de desarrollo basada en el chip ESP32 de Espressif Systems
Destaca por su potente microcontrolador de dos núcleos, esta característica permite que el dispositivo funcione con mayor eficiencia y rendimiento. 
Adicionalmente, este microcontrolador de bajo costo y alto rendimiento combina Wi-Fi y Bluetooth en un solo chip, lo que lo hace ideal para una amplia gama de aplicaciones de IoT (Internet de las cosas) y proyectos de desarrollo. Su principal característica es la integración del protocolo de comunicación inalámbrica ESP-NOW, que permite la comunicación directa entre dispositivos ESP32 sin necesidad de un enrutador Wi-Fi.

### PINOUT

![](docs/PINOUT_ESP32.jpg)

## SOFTWARE

### FINALIDAD

El objetivo es actuar como un punto central que facilita la interconexión entre dispositivos que no pueden comunicarse directamente entre sí debido a limitaciones de alcance, protocolos o tecnologías incompatibles.

En una red que utiliza ESP-NOW, el gateway juega un papel crucial al funcionar como un intermediario que permite que los dispositivos de la red se comuniquen con otros dispositivos externos o con servicios en la nube. Actúa como un puente que traduce los mensajes o datos recibidos de los dispositivos locales a un formato o protocolo que pueda ser comprendido por el destino final fuera de la red local.


### ESTRUCTURA

El código proporcionado es un ejemplo que muestra cómo utilizar el protocolo de comunicación ESP-NOW en un ESP32 para enviar y recibir datos entre dispositivos. 

El código define constantes como "ESP_CHANNEL" para el número de canal en ESP-NOW y "LED_PIN" para el número del pin que controla el LED. Además, se declaran variables y arreglos necesarios para almacenar información sobre los dispositivos remotos con los que se comunicará el ESP32.

Se declara una función para inicializar el Wi-Fi ("init_wifi"), que utiliza las librerías mencionadas anteriormente para configurar la conexión Wi-Fi en el ESP32.

La función de devolución de llamada "recv_cb" se utiliza para recibir datos mediante ESP-NOW. Verifica el tamaño de los datos recibidos y almacena las temperaturas recibidas de cada responder, así como su estado de conexión y el tiempo de la última actualización.

La función "check_disconnections" se utiliza para verificar si ha habido desconexiones de los nodos remotos y actualiza su estado en consecuencia.

La función de devolución de llamada "send_cb" se encarga de mostrar mensajes de depuración indicando si el envío de datos mediante ESP-NOW ha sido exitoso o no.

Existen funciones para inicializar el protocolo ESP-NOW ("init_esp_now") y para registrar los dispositivos remotos ("register_peers"), donde se utilizan las librerías relevantes para configurar y registrar los peers para la comunicación mediante ESP-NOW.

Se definen funciones para inicializar el LED ("init_led") y cambiar su estado ("toggle_led"), utilizando la librería "driver/gpio.h" para controlar el LED.

La función principal "app_main" es donde se inicia el programa. En esta función, se invocan las funciones de inicialización y registro, y se entra en un bucle principal para mantener el programa en ejecución. En este bucle, se verifica la conexión de los nodos remotos, se cambia el estado del LED y se envía el estado del LED a cada uno de los responders registrados mediante ESP-NOW. Además, se muestra un mensaje de depuración para indicar que se ha enviado el estado del LED a todos los responders, y luego se espera 1 segundo antes de repetir el bucle.