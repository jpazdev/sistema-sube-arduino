# Sistema SUBE - Simulación con Arduino y Proteus

## 📌 Descripción
Simulación de una consola de operador de transporte público (tipo SUBE) desarrollada con Arduino UNO en Proteus. El sistema permite gestionar operaciones básicas como acreditación de saldo, consulta de saldo y pago de boleto mediante un teclado matricial y una pantalla LCD.

## 🛠️ Tecnologías utilizadas
- Arduino UNO (ATmega328p)
- Lenguaje C/C++ (Arduino)
- Proteus 8 Professional
- Arduino IDE
- Librerías: Keypad.h, LiquidCrystal.h, Adafruit_I2CDevice.h

## ⚙️ Funcionalidades principales

### 1. Acreditar saldo
Permite ingresar un monto mediante teclado y sumarlo al saldo actual, con validaciones:
- Monto mínimo: $100  
- Monto máximo: $9999  
- Límite total de saldo: $9999  

### 2. Mostrar saldo
Muestra el saldo actual de la tarjeta SUBE en pantalla LCD.

### 3. Pagar boleto
Simula el cobro del pasaje con distintos tipos de subsidios:
- Estudiantil (20% descuento)
- Maternidad (35%)
- Jubilado (55%)
- Discapacidad (100%)
- Boleto mínimo ($150)
- Boleto común ($350)

El sistema valida saldo disponible y muestra errores en caso de saldo insuficiente.

## 🔊 Interacción del sistema
- Teclado matricial 4x4 para ingreso de datos
- Pantalla LCD para visualización
- Parlante para alertas (sonido positivo/negativo)
- LED rojo para indicar errores

## ▶️ Ejecución
1. Abrir el proyecto en Proteus
2. Cargar el archivo `.ino` en Arduino IDE
3. Ejecutar la simulación

## 📄 Documentación completa
Para ver la explicación técnica detallada, diagramas y desarrollo completo:

👉 Ver archivo en `/docs/explicacion.pdf`

## 👨‍💻 Autor
José Alejandro Tomás Paz