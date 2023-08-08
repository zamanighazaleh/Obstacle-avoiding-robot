
#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "";
const char* password = "";

const int output = 2;

// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <title>ESP Pushbutton Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px;}
      .button {
        padding: 10px 20px;
        font-size: 24px;
        text-align: center;
        outline: none;
        color: #fff;
        background-color: #2f4468;
        border: none;
        border-radius: 5px;
        box-shadow: 0 6px #999;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }  
      .button:hover {background-color: #1f2e45}
      .button:active {
        background-color: #1f2e45;
        box-shadow: 0 4px #666;
        transform: translateY(2px);
      }
    </style>
  </head>
  <body>
    <h1>ESP Pushbutton Web Server</h1>
    <button class="button"  ontouchstart="toggleCheckbox('0');" ontouchend="toggleCheckbox('off');">Forward</button>
    <button class="button"  ontouchstart="toggleCheckbox('1');" ontouchend="toggleCheckbox('off');">Left</button>
    <button class="button"  ontouchstart="toggleCheckbox('2');" ontouchend="toggleCheckbox('off');">Right</button>
    <button class="button"  ontouchstart="toggleCheckbox('3');" ontouchend="toggleCheckbox('off');">Backward</button>
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
  </script>
  </body>
</html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("ESP IP Address: http://");
  Serial.println(WiFi.localIP());
  
  
  // Send web page to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Receive an HTTP GET request
  server.on("/0", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //forward
    Serial.println("forward");
    request->send(200, "text/plain", "ok");
  });
    // Receive an HTTP GET request
  server.on("/1", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //forward
    Serial.println("LEft");
    request->send(200, "text/plain", "ok");
  });
    // Receive an HTTP GET request
  server.on("/2", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //forward
    Serial.println("RIght");
    request->send(200, "text/plain", "ok");
  });
    // Receive an HTTP GET request
  server.on("/3", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //forward
    Serial.println("backward");
    request->send(200, "text/plain", "ok");
  });

  // Receive an HTTP GET request
  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //stop
    Serial.println("stop");
    request->send(200, "text/plain", "ok");
  });
  
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
 
}

