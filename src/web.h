#include <Arduino.h>

void handle_index() {
  // send index page
  String index_page = "<html>\
    <head>\
      <title>ESP8266 Web Server POST handling</title>\
      <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      </style>\
    </head>\
    <body>\
      Time: " + String(hours) + ":" + String(minutes) + ":" + String(seconds) + "<br>\
      <h3>Set Brightness value</h3>\
      <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/brightness/\">\
        <input type=\"text\" name=\"brightness\" value=\"" + brightness + "\"> \
        <input type=\"submit\" value=\"Submit\">\
      </form>\
    </body>\
  </html>";

  server.send(200, "text/html", index_page);
}

void post_brightness() {
  //server.send(200, "text/plain", "Brightness set to: " + server.arg("brightness") + "\n");
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
  brightness = server.arg("brightness").toInt();
  refresh = true;
}

void get_all() {
  //get heap status, analog input value and all GPIO statuses in one json call
  String json = "{";
  json += "\"heap\":" + String(ESP.getFreeHeap());
  json += ", \"analog\":" + String(analogRead(A0));
  json += ", \"gpio\":" + String((uint32_t)(((GPI | GPO) & 0xFFFF) | ((GP16I & 0x01) << 16)));
  json += "}";
  server.send(200, "text/json", json);
  json = String();
}
