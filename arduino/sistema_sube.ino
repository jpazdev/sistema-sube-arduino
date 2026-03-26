//////////////////////////////////////////////////////////////////// Inicio del Programa
//////////////////////////////////////////////////////////////////// Librerías  

#include <Keypad.h>
// #include <Adafruit_I2CDevice.h>
#include <LiquidCrystal.h>                // Libreria para que funcione el LCD 
LiquidCrystal lcd (1, 0, A1, A2, 10, 9);  // RS=1 , E=0, A1=D4, A2=D5, 10=D6, 9= D7 esta linea muestra en que pines debe ir conectado la pantalla LCD a nuestro Arduino


//////////////////////////////////////////////////////////////////// Teclado   

// Teclado de Switch (NO TOCAR): 

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
 {'7', '8', '9', '/'}, 
 {'4', '5', '6', '*'}, 
 {'1', '2', '3', '-'}, 
 {'X', '0', '=', '+'} 
};

byte rowPins[ROWS] = {12,11,8,7}; //Filas(pines del 7,8 y 12, 13)
byte colPins[COLS] = {6,5,4,2}; //Columnas (pines del 2, 4 al 6)

Keypad keypad = Keypad (makeKeymap (keys), rowPins, colPins, ROWS, COLS ); 


//////////////////////////////////////////////////////////////////// Altavoz 

// Variables del Altavoz: 

int pinaltavoz = 3;
int frecuencia = 100;    // Frecuencia correspondiente a la nota La 
int contador;            // Variable para el contador 
float m = 1.059;         // Constante para multiplicar frecuencias 

// Valor de Frecuencia: 
// 100 o 110 pitido negativo 
// 10 pitido positivo 

//////////////////////////////////////////////////////////////////// Luces RGB - Luz Roja

int pinLedR = 13; // Pin Rojo del LED RGB
// int pinLedV = 10; // Pin Verde del LED RGB
// int pinLedA = 9;  // Pin Azul del LED RGB
int pausa = 1000;
// RTC_DS3231 rtc; 

// Método para generar el Color Rojo: 

void color_rojo (int rojo)
  {
    
    analogWrite (pinLedR, rojo);

  }

//////////////////////////////////////////////////////////////////// Variables de Operaciones SUBE

// Variables del SUBE:

// char key;

String Acreditar;
String Descontar;
String resultado; 

float saldo_sube = 0-501;
int acreditar = 0;
float const descontar = 350;
float const descontar_min = 150; 



// Variables del Calculadora:

boolean final = false; 
boolean dato = false;     // Variable usada para acceder al While 

int movimiento; 
int total;
int contador_menu_1 = 0;  // Contador usado para el Primer Caso del Menú 1



//////////////////////////////////////////////////////////////////// VOID SETUP 

void setup () {

// Serial.begin (9600); 

lcd.begin (16, 2); 
lcd.print ("Cargando...");
delay(1000);
lcd.clear ();

// Preparan las luces para su funcionamiento: 

pinMode (pinLedR, OUTPUT);    // Pone el pinLedR (Led Rojo) como output 
// pinMode (pinLedV, OUTPUT); // Pone el pinLedV (Led Verde) como output 
// pinMode (pinLedA, OUTPUT); // Pone el pinLedA (Led Amarillo) como output 

lcd.begin (16, 2);             // Con esta instrucción indicamos cual es la proporción de nuestro LCD
lcd.print ("Inserte su SUBE"); // Una instrucción muy importante ya que con esta imprimiremos el texto en nuestra pantalla

// pinMode (led, OUTPUT); 

}


//////////////////////////////////////////////////////////////////// VOID LOOP

void loop ()
{

  char key = keypad.getKey (); // key != NO_KEY

  if (key) 
    {

      // Menú N°1: Menú de las Teclas Operacionales ('X'): 

      if (key != NO_KEY && key == 'X') // Cuando en key "X" es oprimida...   
        {
            lcd.clear();
            // digitalWrite(led, LOW);   // El led se apaga

            final = false;
            acreditar = 0;
            Acreditar = "";
            resultado = "";
            total = 0;
            contador_menu_1 = 0; 

            lcd.begin (16, 2); 
            lcd.print ("Inserte su SUBE:");
            Serial.println ("X");

            dato = false;
            
            // digitalWrite(led, LOW);   // El led se apaga

        }

      // Menú N°1: Menú de las Teclas Operacionales ('/','*','-','+'): 

          // valorActual == false && 
      if  (key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+' || key == '=')) // Caso N°2
        {                                                                                         // Cuando en key "/" es oprimida.. 
            lcd.setCursor (0, 1);                                                                 // Cuando en key "*" es oprimida... 
            lcd.print ("Press: 1, 2 o 3");                                                        // Cuando en key "-" es oprimida..
            //digitalWrite (led, LOW);    // El led se apaga                                      // Cuando en key "+" es oprimida..

            delay(1500);
            lcd.clear ();

            lcd.begin (16, 2); 
            lcd.print ("Inserte su SUBE:");
          
        } 
    }

  // Menú N°2: Menú del Teclado Númerico: 
  
      if (key != NO_KEY && (key =='1')) //////////////////////////////////////////////////////////////////// En uso
        {

          lcd.setCursor (0, 1); 
          lcd.print ("Acreditar Saldo");   // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD 

          delay(2000);
          lcd.clear();

          lcd.setCursor (0, 0); 
          lcd.print ("Acreditar Saldo:");

          dato = true;

            while (dato)
              {
                
                key = keypad.getKey ();

                  if (key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+')) // Caso N°1
                    {                                                                          // Cuando en key "/" es oprimida... 
                                                                                               // Cuando en key "*" es oprimida... 
                      lcd.setCursor (0, 1);                                                    // Cuando en key "-" es oprimida... 
                      lcd.print ("Presione Numeros");                                          // Cuando en key "+" es oprimida... 
                      delay(1500);
                      lcd.clear ();

                      lcd.setCursor (0, 0);
                      lcd.print ("Acreditar Saldo:");
                      lcd.setCursor (0, 1);  
                      lcd.println (Acreditar);

                    }
                  
                  else if (key != NO_KEY && (key == '1' || key == '2'|| key == '3' || key == '4' || key == '5' || key == '6' || key=='7' || key== '8' || key == '9' || key == '0')) // Caso N°2
                        {
                          if (contador_menu_1 <= 4)
                            {

                              Acreditar = Acreditar + key; 
                              lcd.setCursor (0, 1);  
                              lcd.print (Acreditar); 
                              // int numLength = saldo.length(); 
                              // movimiento = numLength; 
                              contador_menu_1 = contador_menu_1 + 1;

                            }

                          else if (contador_menu_1 >= 5)
                            {

                              lcd.setCursor (0, 1);  
                              lcd.println ("No más de 9999");

                              for (contador = 0, frecuencia = 100; contador < 1; contador++)
                                {
                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300); 
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300); 
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                              lcd.setCursor (0, 0);
                              lcd.print ("Acreditar Saldo:");
                              lcd.setCursor (0, 1);  
                              lcd.print (Acreditar);

                              final = true;

                            }
                        }
                  
                  else if (key != NO_KEY && key == '=' || final == true) // Caso N°3
                    {                                                    // Cuando en key "=" es oprimida... 
                      acreditar = acreditar + Acreditar.toInt ();
                      total = acreditar + saldo_sube;
                      resultado = String (total);

                        if (acreditar <= 99)
                          {

                            delay(1000);
                            lcd.clear();

                            lcd.setCursor (0, 2);  
                            lcd.println ("Seleccione +$100");

                            for (contador = 0, frecuencia = 100; contador < 1; contador++)
                                {
                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300); 
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300); 
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                            delay(1000);
                            lcd.clear();

                            lcd.setCursor (0, 0);
                            lcd.print ("Acreditar Saldo:");
                            lcd.setCursor (0, 1);  
                            lcd.println (Acreditar);

                          }
                          
                        else if (acreditar >= 9999 || total >= 9999)
                          {

                            delay(1000);
                            lcd.clear();

                            lcd.setCursor (0, 2);  
                            lcd.print ("No mas de $9999");

                            for (contador = 0, frecuencia = 100; contador < 1; contador++)
                                {

                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300); 
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300); 
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                            delay(1000);
                            lcd.clear();

                            lcd.setCursor (0, 0);
                            lcd.print ("Acreditar Saldo:");
                            lcd.setCursor (0, 1);  
                            lcd.println (Acreditar);

                          }

                        else if (contador_menu_1 <= 4 && contador_menu_1 >= 2 && total <= 10000)
                          {
                            delay(2000);
                            lcd.clear();

                            saldo_sube = saldo_sube + acreditar;

                            lcd.setCursor (0, 0);
                            lcd.println ("Su saldo actual:");
                            lcd.setCursor (1, 1);
                            lcd.println ("$");
                            lcd.setCursor (2, 1);
                            lcd.println (saldo_sube);

                            for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }
                            
                            delay(2000);
                            lcd.clear();

                            lcd.begin (16, 2); 
                            lcd.print ("Inserte su SUBE:");

                            final = false;
                            resultado = "";
                            acreditar = 0;
                            Acreditar = "";
                            total = 0;
                            contador_menu_1 = 0;
                            dato = false;
                            key = 'X'; 

                            break;

                          }
                    }
                  
                  else if (key != NO_KEY && key == 'X') // Cuando en key "X" es oprimida...   
                    {
                      
                      resultado = "";
                      acreditar = 0;
                      Acreditar = "";
                      total = 0;
                      final = false;
                      contador_menu_1 = 0;  
                      

                      lcd.clear();
                      // digitalWrite(led, LOW);   // El led se apaga
                      lcd.begin (16, 2); 
                      lcd.print ("Inserte su SUBE:");

                      dato = false;

                      break;

                    }
                }
        }
      
      if (key != NO_KEY && (key == '2')) //////////////////////////////////////////////////////////////////// En uso
        {

          lcd.setCursor (0, 1); 
          lcd.print ("Mostrar Saldo");        // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD      

          delay(2000);
          lcd.clear();

          lcd.setCursor (0, 0);
          lcd.println ("El Saldo Actual:");
          lcd.setCursor (1, 1);
          lcd.println ("$");
          lcd.setCursor (2, 1);
          lcd.println (saldo_sube);           // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD          

          delay(3000);
          lcd.clear();

          lcd.begin (16,2); 
          lcd.print ("Inserte su SUBE:");

        }

      if (key != NO_KEY && (key == '3')) //////////////////////////////////////////////////////////////////// En uso
        {
          
          lcd.setCursor (0, 1); 
          lcd.print ("Pagar Pasaje");   // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD

          delay(2000);
          lcd.clear();

          lcd.setCursor (0, 0);
          lcd.print ("Select Subsidio:");

          lcd.setCursor (0, 1);
          lcd.print ("Press op 1-6");

          dato = true;

            while (dato)
              {
                  key = keypad.getKey ();

                    if (key != NO_KEY && (key == '1' || key=='2' || key == '3' || key == '4' || key == '5' || key == '6'))
                      {
                        if (saldo_sube >= (0-500))
                          {
                            if (key == '1')     // Caso N°1 // Boleto Estudiante Secundario/Universitario (20%)($350)
                              {

                                delay(1000);
                                lcd.clear();

                                float descontar_estudiante = descontar - ((descontar * 20)/100); 
                                saldo_sube = saldo_sube - descontar_estudiante;

                                lcd.setCursor (0, 0);
                                lcd.println ("Boleto Estudiante:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (descontar_estudiante);

                                for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Su saldo actual:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (saldo_sube);

                                delay(1000);
                                lcd.clear();

                                lcd.begin (16, 2); 
                                lcd.print ("Inserte su SUBE:");
                                
                                dato = false;
                                break;

                              }
                            
                            else if (key == '2') // Caso N°2 // Boleto Maternidad (35%)($350)
                              { 

                                delay(1000);
                                lcd.clear();
                                float descontar_maternidad = descontar - ((descontar * 35)/100); 
                                saldo_sube = saldo_sube - descontar_maternidad;

                                lcd.setCursor (0, 0);
                                lcd.println ("Boleto Maternidad:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (descontar_maternidad);

                                for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Su saldo actual:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (saldo_sube);

                                delay(1000);
                                lcd.clear();

                                lcd.begin (16, 2); 
                                lcd.print ("Inserte su SUBE:");

                                dato = false;
                                break;

                              }
                            
                            else if (key == '3') // Caso N°3 // Boleto Jubilado (55%)($350)
                              { 
                                
                                delay(1000);
                                lcd.clear();

                                float descontar_jubilado = descontar - ((descontar * 55)/100); 
                                saldo_sube = saldo_sube - descontar_jubilado;

                                lcd.setCursor (0, 0);
                                lcd.println ("Boleto Jubilado:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (descontar_jubilado);
                                
                                for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Su saldo actual:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (saldo_sube);

                                delay(1000);
                                lcd.clear();

                                lcd.begin (16, 2); 
                                lcd.print ("Inserte su SUBE:");

                                dato = false;
                                break;

                              }
                            else if (key == '4') // Caso N°4 // Boleto CUD (Certificado Único de Discapacidad)(100%)($350)
                              { 
                                
                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Boleto CUD:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println ("00.00");
                                
                                for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Su saldo actual:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (saldo_sube);

                                delay(1000);
                                lcd.clear();

                                lcd.begin (16, 2); 
                                lcd.print ("Inserte su SUBE:");

                                dato = false;
                                break;

                              }
                            
                           else if (key == '5') // Caso N°5 // Boleto Pagar el Mínimo ($150)
                              { 
                                
                                delay(1000);
                                lcd.clear();

                                saldo_sube = saldo_sube - descontar_min; 

                                lcd.setCursor (0, 0);
                                lcd.println ("Boleto Minimo:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (descontar_min);

                                for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Su saldo actual:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (saldo_sube);

                                delay(1000);
                                lcd.clear();

                                lcd.begin (16, 2); 
                                lcd.print ("Inserte su SUBE:");

                                dato = false;
                                break;

                              }
                            
                            else if (key == '6') // Caso N°6 // Boleto Normal ($350)
                              { 

                                delay(1000);
                                lcd.clear();

                                saldo_sube = saldo_sube - descontar; 

                                lcd.setCursor (0, 0);
                                lcd.println ("Boleto Comun:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (descontar);

                                for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Su saldo actual:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (saldo_sube);

                                delay(1000);
                                lcd.clear();

                                lcd.begin (16, 2); 
                                lcd.print ("Inserte su SUBE:");

                                dato = false;
                                break;

                              }
                          }
                        
                        else if (saldo_sube <= (0-500) && (key == '4')) // Caso N°4 // Boleto CUD (Certificado Único de Discapacidad)(100%)($350)
                              { 
                                
                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Boleto CUD:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println ("00.00");
                                
                                for (contador = 0, frecuencia = 10; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);

                                }

                                delay(1000);
                                lcd.clear();

                                lcd.setCursor (0, 0);
                                lcd.println ("Su saldo actual:");
                                lcd.setCursor (1, 1);
                                lcd.println ("$");
                                lcd.setCursor (2, 1);
                                lcd.println (saldo_sube);

                                delay(1000);
                                lcd.clear();

                                lcd.begin (16, 2); 
                                lcd.print ("Inserte su SUBE:");

                                dato = false;
                                break;

                              }

                        else if (saldo_sube <= (0-500))
                          {
                            
                            delay (500);
                            lcd.clear ();

                            lcd.setCursor (6, 0);
                            lcd.print ("X");

                            lcd.setCursor (0, 1);
                            lcd.print ("Saldo Negativo");

                            // 100 o 110 pitido negativo
                            // 10 pitido positivo

                            for (contador = 0, frecuencia = 100; contador < 1; contador++)
                                {

                                  
                                  frecuencia = frecuencia * m;    // Actualiza la frecuencia 
                                  color_rojo (255);
                                  tone (pinaltavoz, frecuencia);  // Emite el tono 
                                  delay (300);
                                  noTone (pinaltavoz);            // Para el tono 
                                  delay (300);
                                  color_rojo (0);

                                }
                            
                            ////////////////////////////////////////////////////////////////// Luz Roja RGB

                            delay (2000);
                            lcd.clear ();

                            lcd.begin (16, 2); 
                            lcd.print ("Inserte su SUBE:");

                            dato = false;
                            break;

                          }
                      }

                    else if (key != NO_KEY && key == 'X') // Caso N°3 - Cuando en key "X" es oprimida... 
                      {
                        
                        resultado = "";
                        total = 0;
                        final = false;
                        contador_menu_1 = 0;  
                        

                        lcd.clear();
                        // digitalWrite(led, LOW);   // El led se apaga
                        lcd.begin (16, 2); 
                        lcd.print ("Inserte su SUBE:");

                        dato = false;

                        break;

                      } 
              }
        }
}
