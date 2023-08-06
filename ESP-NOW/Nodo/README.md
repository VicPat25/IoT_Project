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

El objetivo es un dispositivo que participa en la comunicación inalámbrica de forma unidireccional o bidireccional utilizando el protocolo ESP-NOW. En este protocolo, los nodos se organizan en un sistema de red donde uno de ellos actúa como "Initiator" (iniciador) y los demás como "Responders" (respondedores).


### ESTRUCTURA

El código implementa un dispositivo ESP32 que actúa como un responder ESP-NOW. Recibe datos inalámbricos mediante el protocolo ESP-NOW y actualiza el estado de un LED según el valor recibido. El dispositivo se configura para operar en modo estación (STA) Wi-Fi y utiliza el canal 1 para la comunicación ESP-NOW. El LED se controla mediante el pin GPIO 2. La función recv_cb() se encarga de procesar los datos recibidos y actualizar el LED en consecuencia. El programa entra en un bucle infinito y se queda esperando durante un segundo entre cada iteración mientras envía periódicamente el estado del LED al dispositivo remoto.