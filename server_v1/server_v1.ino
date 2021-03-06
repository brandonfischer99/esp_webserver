/*********
  Brandon Fischer
  code adapted from Ruis Santos @ https://randomnerdtutorials.com/esp8266-web-server/
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
//Load i2c library
#include <Wire.h>

#define MAX_HEADER 512

// Replace with your network credentials
const char* ssid     = "ATTE3S6txi";
const char* password = "ahk7m8d3gvkq";

// Set web server port number to 80
WiFiServer server(80);

// Variables to store the full HTTP request header, the request type, and the url
//i is index variable for reading characters into header
char header[MAX_HEADER];
char *req_type = NULL;
char *url = NULL;
int i = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      while (client.available() > 0) {             // if there's bytes to read from the client,
        //make sure header's not too long
        if(i < MAX_HEADER)
        {
          header[i] = client.read();        // read a byte, then
          Serial.print(header[i]);          // print it out the serial monitor
          i++;
        }
        else
        {
          //header too long, send back error
          client.println("HTTP/1.1 431 Header Too Long");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          break; 
        }
      }
        
//      client.println("HTTP/1.1 200 OK");
//      client.println("Content-type:text/html");
//      client.println("Connection: close");
//      client.println();

      // Display the HTML web page
      client.println("<!DOCTYPE html><html>");
      client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
      client.println("<link rel=\"icon\" href=\"data:,\">");
      // CSS to style the on/off buttons 
      // Feel free to change the background-color and font-size attributes to fit your preferences
      client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
      client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
      client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
      client.println(".button2 {background-color: #77878A;}</style></head>");
      
      // Web Page Heading
      client.println("<body><h1>ESP8266 Web Server</h1>");

      //Break header into request type and url with 2 strtok calls
      req_type = strtok(header, " ");
      url = strtok(NULL, " ");
            
      Serial.println(req_type);
      Serial.println(url);

      //Index page
      if(url == NULL)
      {
        client.println("<p>NodeMCU: 'What is my purpose master?'<br>Me: 'To light a seven segment display'<br>NodeMCU: 'Oh my god'</p>");
      }
      else if(url[0] == '/' && url[1] == 0)
      {
        client.println("<p>NodeMCU: 'What is my purpose master?'<br>Me: 'To light a seven segment display'<br>NodeMCU: 'Oh my god'</p>");
      }
      else
      {
        char *endpoint;
        char *argument;
        //separate url into endpoint and argument
        endpoint = strtok(url, "/");
        argument = strtok(NULL, "/");

        Serial.println(endpoint);
        Serial.println(argument);

        //First endpoint: writess for write seven segment
        //Format: /writess/<int> where int is an integer 0-9
        if(strcmp(endpoint, "writess") == 0)
        {
            if(argument != NULL)
            {
              //Begin i2c transmission to board controlling display
              Wire.beginTransmission(8);
              //Transmit integer value of first digit in argument
              Serial.println(argument[0]-48);
              Wire.write(argument[0]-48);
              Wire.endTransmission();
            }
            else
            {
              client.println("<p>Correct endpoint usage: /writess/num where num is a digit 0-9</p>");
            }
        }
      }
      
      
      client.println("</body></html>");
      
      // The HTTP response ends with another blank line
      client.println();
      break;
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    memset(header, 0, MAX_HEADER);
    i = 0;
  }
}
