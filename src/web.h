void handle_index() {
  //Print Hello at opening homepage
  server.send(200, "text/plain", "Time:  " + String(hours) + ":" + String(minutes) + ":" + String(seconds));
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
