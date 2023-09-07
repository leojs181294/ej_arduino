// C++ code
//
#include <Adafruit_LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 12
#define PIN 2
#define PINRUEDA 3
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
#define VELOCIDAD 10//Velocidad a la que se mueve el texto

//Se define el pin circular
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, PINRUEDA, NEO_GRB + NEO_KHZ800);
//Se define el pin tira led
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//Se drfine la pantalla
Adafruit_LiquidCrystal lcd(0);

int pinButton = 13;   // Pin para el pulsador 
int pinButton2 = 5;   // Pin para el pulsador 2

const int pinTone1 = 12;  // Pin para el primer tono
const int pinTone2 = 11;  // Pin para el segundo tono
const int pinTone3 = 10;  // Pin para el tercer tono

//incializacion de variables
int delayval = 100; // tiempo delay en milisegundos de colores
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int Tiempodeespera = 2000;
int Tiempodeesperacorto = 1000;
int segundos = 0;
int Button1 = 0;
int Button2 = 0;

// Textos
String texto_fila = "PAPF";
String texto_fila1 = "Gabriel Solano, Franco Rodriguez, Jesica sosa, Leonardo Salamone, Santigo Rodriguez.";

void setup() {
    //pulasdor configuracion
    pinMode(pinButton, INPUT_PULLUP);
    pinMode(pinButton2, INPUT_PULLUP);
    // Configurar los pines de los tonos como salidas
    pinMode(pinTone1, OUTPUT);
    pinMode(pinTone2, OUTPUT);
    pinMode(pinTone3, OUTPUT);
    //semaforo y rgb salida como salida
    pinMode(9, OUTPUT);//rojo
    pinMode(8, OUTPUT);//amarillo
    pinMode(7, OUTPUT);//VERDE
    //tirapixel
    pixels.begin();
    // Configuración monitor serie
    Serial.begin(9600);
    // Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
    lcd.begin(COLS, ROWS);

#if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

#endif
    strip.begin();
    strip.show();
}
// Funcion para los tonos 
void parlante_tonos() {

    // Definir las frecuencias de los tres tonos
    int toneFreq1 = 440;  // Frecuencia en Hz
    int toneFreq2 = 523;  // Frecuencia en Hz
    int toneFreq3 = 659;  // Frecuencia en Hz
    // Definir la duración de cada tono en milisegundos
    int toneDuration = 500;  // 0.5 segundos
    // Tocar el primer tono
    tone(pinTone1, toneFreq1, toneDuration);
    delay(toneDuration);  // Pausa entre tonos
    // Tocar el segundo tono
    tone(pinTone2, toneFreq2, toneDuration);
    delay(toneDuration);  // Pausa entre tonos
    // Tocar el tercer tono
    tone(pinTone3, toneFreq3, toneDuration);
    delay(toneDuration);  // Pausa entre tonos);
}
//Funcion para determinar colores de la tira led
void setColor() {
    redColor = random(0, 255);
    greenColor = random(0, 255);
    blueColor = random(0, 255);
}

void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}
void theaterChase(uint32_t c, uint8_t wait) {
    for (int j = 0; j < 10; j++) {
        for (int q = 0; q < 3; q++) {
            for (int i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, c);
            }
            strip.show();
            delay(wait);
            for (int i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, 0);
            }
        }
    }
}
void rueda_led() {

    colorWipe(strip.Color(255, 0, 0), 50);
    colorWipe(strip.Color(0, 255, 0), 50);
    colorWipe(strip.Color(0, 0, 255), 50);
    theaterChase(strip.Color(127, 127, 127), 50);
    theaterChase(strip.Color(127, 0, 0), 50);
    theaterChase(strip.Color(0, 0, 127), 50);
}
//Funcion de pantalla primer boton
void LCD() {
    // Obtenemos el tamaño del texto
    int tam_texto = texto_fila.length();
    for (int i = tam_texto; i > 0; i--)
    {
        String texto = texto_fila.substring(i - 1);
        // Limpiamos pantalla
        lcd.clear();
        //Situamos el cursor
        lcd.setCursor(0, 0);
        // Escribimos el texto
        lcd.print(texto);
        // Esperamos
        delay(200);
    }
}
//Funcion de pantalla segundo boton
void LCD2() {
    // Obtenemos el tamaño del texto
    int tam_texto = texto_fila1.length();

    // Mostramos entrada texto por la izquierda
    for (int i = tam_texto; i > 0; i--)
    {
        String texto = texto_fila1.substring(i - 1);
        // Limpiamos pantalla
        lcd.clear();
        //Situamos el cursor
        lcd.setCursor(0, 0);
        // Escribimos el texto
        lcd.print(texto);
        // Esperamos
        delay(VELOCIDAD);
    }

    // Desplazamos el texto hacia la derecha
    for (int i = 1; i <= 16; i++)
    {
        // Limpiamos pantalla
        lcd.clear();
        //Situamos el cursor
        lcd.setCursor(i, 0);
        // Escribimos el texto
        lcd.print(texto_fila1);
        // Esperamos
        delay(VELOCIDAD);
    }

    // Desplazamos el texto hacia la izquierda en la segunda fila
    for (int i = 16; i >= 1; i--)
    {
        // Limpiamos pantalla
        lcd.clear();
        //Situamos el cursor
        lcd.setCursor(i, 1);
        // Escribimos el texto
        lcd.print(texto_fila1);
        // Esperamos
        delay(VELOCIDAD);
    }

    // Mostramos salida del texto por la izquierda
    for (int i = 1; i <= tam_texto; i++)
    {
        String texto = texto_fila1.substring(i - 1);
        // Limpiamos pantalla
        lcd.clear();
        //Situamos el cursor
        lcd.setCursor(0, 1);
        // Escribimos el texto
        lcd.print(texto);
        // Esperamos
        delay(VELOCIDAD);
    }
}


//Funcion del semaforo y rgb
void Semaforo() {
    digitalWrite(9, HIGH);
    delay(Tiempodeespera);
    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
    delay(Tiempodeesperacorto);
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
    delay(Tiempodeespera);
    digitalWrite(7, LOW);
}

void loop() {
    Button1 = digitalRead(pinButton);
    Button2 = digitalRead(pinButton2);
    if (Button1 == HIGH) {
        while (Button2 != HIGH) {
            parlante_tonos();
            setColor();
            for (int i = 0; i < NUMPIXELS; i++) {
                // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
                pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
                // This sends the updated pixel color to the hardware.
                pixels.show();
                // Delay for a period of time (in milliseconds).
                delay(delayval);
            }
            Semaforo();
            LCD();
            Button2 = digitalRead(pinButton2);
        }
    }
    if (Button2 == HIGH) {
        Button1 = LOW;
        rueda_led();
        LCD2();
    }
}