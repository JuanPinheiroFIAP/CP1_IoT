# CHECKPOINT01-IoT

## TURMA: 3ESPW

## Integrates

NOME | RM
:-----:|:---:
Kaiky Alvaro de Miranda|98118
Lucas Rodrigues da Silva|98344
Juan Pinheiro de França|552202
Matheus Gusmão Aragão|550826 
Júlia Marques Mendes das Neves|98680

## Descrição

Este projeto integra um Arduino Uno com sensores DHT11 (temperatura e umidade) e LDR (luminosidade), além de um servo motor controlado pelo Node-RED. O Arduino lê os dados dos sensores e envia para o Node-RED, que exibe as informações em um dashboard e permite controlar a posição do servo motor através de botões.

### Componentes

![image](https://github.com/user-attachments/assets/38b7b679-53a3-4dc5-b9f6-9ef4db2ac74f)


## Arquivos

### Código Arduino (sensor_servo_control.ino)

- #include <DHT.h> e #include <Servo.h>: Incluem as bibliotecas necessárias para os sensores e servo.
- #define: Define os pinos de conexão dos sensores e servo.
- DHT dht(DHTPIN, DHTTYPE); e Servo myservo;: Criam os objetos para os sensores e servo.
- void setup(): Inicializa a comunicação serial, os sensores e associa o servo ao pino.

void loop():

- Lê os dados dos sensores DHT11 e LDR a cada 3 segundos.
- Converte a temperatura de Celsius para Fahrenheit.
- Formata os dados como JSON e envia pela porta serial (ex: `{"tempF":77.00,"humidity":50.00,"ldr":512}`).
- Controla o servo motor com base nos comandos recebidos pela porta serial (1 para 0°, 2 para 90°, 3 para 180°).

Imagem da solução no Tinkercad:
![image](https://github.com/user-attachments/assets/7f851abf-e9b5-4b81-a3af-d1c943e3845f)


### Fluxo Node-RED (node-red_flow.json)

- serial in: Lê os dados JSON da porta serial do Arduino.
- json: Converte os dados recebidos em formato JSON.
- ui_gauge: Exibe os valores de temperatura, umidade e luminosidade em gauges no dashboard.
- ui_button: Cria botões para controlar a posição do servo motor (0°, 90°, 180°).
- serial out: Envia os comandos para o Arduino controlar o servo.

## Configuração

### Arduino:
- Conecte os sensores e o servo motor ao Arduino conforme especificado nos comentários do código.
- Carregue o código sensor_servo_control.ino no Arduino IDE.

### Node-RED:

- Instale o pacote node-red-dashboard.
- Importe o fluxo node-red_flow.json no Node-RED.
- Configure o nó serial in e o nó serial out com a porta serial correta do Arduino (ex: COM3, /dev/ttyACM0).
- Implante o fluxo.
- Acesse o dashboard no localhost.

## Funcionamento

- O Arduino lê os dados dos sensores e envia para o Node-RED via porta serial.
- O Node-RED exibe os dados em tempo real no dashboard.
- Os botões no dashboard permitem enviar comandos para o Arduino, controlando a posição do servo motor.

## Observações
- Certifique-se de que a taxa de baud (9600) no código Arduino corresponde à configuração no nó serial in e serial out do Node-RED.
- Verifique as conexões físicas dos sensores e do servo motor ao Arduino.
- Se os dados não estiverem aparecendo, verifique se o Node-RED está recebendo os dados corretamente do Arduino.
Se o servo não estiver respondendo aos comandos, verifique se a porta serial está configurada corretamente e se as conexões estão corretas.

## Fluxo



## Dashboard
