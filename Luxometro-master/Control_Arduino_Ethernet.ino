/* Control Arduino Ethernet
 by: HAR21 B
 controla el encendido o apagado de los Pin 2,3,4 ,5  del Arduino.
 Controla el giro de un servomotor conectado al pin 7
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <BH1750.h> 

BH1750 lightMeter;
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //Direccion Fisica MAC
byte ip[] = { 192, 168, 1, 50 };                       // IP Local que usted debe configurar 
byte gateway[] = { 192, 168, 1, 1 };                   // Puerta de enlace
byte subnet[] = { 255, 255, 255, 0 };                  //Mascara de Sub Red
EthernetServer server(80);                             //Se usa el puerto 80 del servidor     
String readString;

void setup() {

 Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // On esp8266 devices you can select SCL and SDA pins using Wire.begin(D4, D3);
  Wire.begin();

  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
   while (!Serial) {   // Espera a que el puerto serial sea conectado, Solo necesario para el Leonardo
    ; 
  }
  pinMode(2,OUTPUT);        // Se configura como salidas los puertos del 2 al 5
  pinMode(3,OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5,OUTPUT);
 
  Ethernet.begin(mac, ip, gateway, subnet); // Inicializa la conexion Ethernet y el servidor
  server.begin();
  Serial.print("El Servidor es: ");
  Serial.println(Ethernet.localIP());    // Imprime la direccion IP Local
}


void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
  
  // Crea una conexion Cliente
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //Lee caracter por caracter HTTP
        if (readString.length() < 100) {
          //Almacena los caracteres a un String
          readString += c;
          
         }

         // si el requerimiento HTTP fue finalizado
         if (c == '\n') {          
           Serial.println(readString); //Imprime en el monitor serial
     
           client.println("HTTP/1.1 200 OK");           //envia una nueva pagina en codigo HTML
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<TITLE>Ethernet Arduino</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<hr />");
           client.println("<H1>Arduino Ethernet Shield</H1>");
           
           client.println("<a href=\"/?button2on\"\"> Encender led 1</a> ");           // construye en la pagina cada uno de los botones
           client.println(" | | | ");
           client.println("<a href=\"/?button2off\"\"> Apagar led 1</a><br /> ");   
           client.println("<br />");
           
           client.println("<br />"); 
           client.println("<a href=\"/?button3on\"\"> Encender led 2</a> ");
           client.println(" | | | ");
           client.println("<a href=\"/?button3off\"\"> Apagar led 2</a><br /> ");   
           client.println("<br />");
           
           client.println("<br />"); 
           client.println("<a href=\"/?button4on\"\"> Encender led 3</a> ");
           client.println(" | | | ");
           client.println("<a href=\"/?button4off\"\"> Apagar led 3</a><br /> ");   
           client.println("<br />");
           
           client.println("<br />");  
           client.println("<a href=\"/?button5on\"\"> Encender led 4</a>");
           client.println(" | | | ");
           client.println("<a href=\"/?button5off\"\"> Apagar led 4</a><br />");   
           client.println("<br />");
           
           client.println("<p>by: HAR21 B</p>");  
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           client.stop();
           
           //control del arduino si un boton es presionado
                   
           if (readString.indexOf("?button2on") >0){
               digitalWrite(2, HIGH);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(2, LOW);
           }
           
           if (readString.indexOf("?button3on") >0){
               digitalWrite(3, HIGH);
           }
           if (readString.indexOf("?button3off") >0){
               digitalWrite(3, LOW);
           }
           
           
           if (readString.indexOf("?button4on") >0){
               digitalWrite(4, HIGH);
           }
           if (readString.indexOf("?button4off") >0){
               digitalWrite(4, LOW);
           }
           
            if (readString.indexOf("?button5on") >0){
               digitalWrite(5, HIGH);
           }
           if (readString.indexOf("?button5off") >0){
               digitalWrite(5, LOW);
           }
            // Limpia el String(Cadena de Caracteres para una nueva lectura
            readString="";  
           
         }
       }
    }
}
}
