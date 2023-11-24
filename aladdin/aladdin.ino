#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const byte DNS_PORT = 53;
int name = 40;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);
// int Ip[100];
char Display[50][25];
int count = 0;

// Dicitinary to store user info

String responseHTML = ""
                      "<!DOCTYPE html><html lang='en'><head>"
                      "<meta charset='UTF-8'>"
                      "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                      "<title>Restaurant Menu</title>"
                      "<style>"
                      "body {"
                      "background-color: #f2f2f2;"
                      "}"
                      ".menu-container {"
                      "display: flex;"
                      "flex-direction: column;"
                      "max-width: 600px;"
                      "margin: 0 auto;"
                      "padding: 20px;"
                      "background-color: #ffffff;"
                      "box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);"
                      "justify-content: space-between;"
                      "}"
                      ".menu-item {"
                      "display: flex;"
                      "height: 100px;"
                      "justify-content: space-between;"
                      "align-items: center;"
                      "border-bottom: 1px solid #ddd;"
                      "padding: 10px 0;"
                      "}"
                      ".menu-item:last-child {"
                      "border-bottom: none;"
                      "}"
                      ".menu-item-name {"
                      "font-weight: bold;"
                      "font-size: 25px;"
                      "font-family: Courier, monospace;"
                      "}"
                      ".menu-item-price {"
                      "color: #aa0000;"
                      "font-size: 18px;"
                      "font-family: 'Lucida Console', 'Courier New', monospace;"
                      "}"
                      ".order-button {"
                      "background-color: #aa0000;"
                      "color: #fff;"
                      "border: none;"
                      "padding: 5px 10px;"
                      "cursor: pointer;"
                      "border-radius: 5px;"
                      "transition: background-color 0.3s;"
                      "}"
                      ".order-button:hover {"
                      "background-color: #880000;"
                      "}"
                      ".menu-header {"
                      "text-align: center;"
                      "background-color: #aa0000;"
                      "color: #fff;"
                      "padding: 10px;"
                      "font-size: 24px;"
                      "width: 70%;"
                      "margin: 0 auto;"
                      "display: flex;"
                      "align-items: center;"
                      "justify-content: center;"
                      "}"
                      "span {"
                      "width: 100px;"
                      "}"
                      "</style>"
                      "</head>"
                      "<body>"
                      "<div class='menu-header'>MENU</div>"
                      "<div class='menu-container'>"
                      "<div class='menu-item'>"
                      "</div>"
                      "</div>"
                      "<div class='menu-container'>"
                      "<div class='menu-item'>"
                      "<span class='menu-item-name'>Burger</span>"
                      "<span class='menu-item-price'>$10.99</span>"
                      "<form action='/burger' method='get'>"
                      "<button class='order-button'>"
                      "ORDER"
                      "</button>"
                      "</form>"
                      "</div>"
                      "<div class='menu-item'>"
                      "<span class='menu-item-name'>Pizza</span>"
                      "<span class='menu-item-price'>$12.99</span>"
                      "<form action='/pizza' method='get'>"
                      "<button class='order-button'>"
                      "ORDER"
                      "</button>"
                      "</form>"
                      "</div>"
                      "<div class='menu-item'>"
                      "<span class='menu-item-name'>French Fries</span>"
                      "<span class='menu-item-price'>$9.99</span>"
                      "<form action='/french-fries' method='get'>"
                      "<button class='order-button'>"
                      "ORDER"
                      "</button>"
                      "</form>"
                      "</div>"
                      "<div class='menu-item'>"
                      "<span class='menu-item-name'>Caesar Salad</span>"
                      "<span class='menu-item-price'>$14.99</span>"
                      "<form action='/caesar' method='get'>"
                      "<button class='order-button'>"
                      "ORDER"
                      "</button>"
                      "</form>"
                      "</div>"
                      "<div class='menu-item'>"
                      "<span class='menu-item-name'>Chicken Alfredo</span>"
                      "<span class='menu-item-price'>$11.99</span>"
                      "<form action='/chicken' method='get'>"
                      "<button class='order-button'>"
                      "ORDER"
                      "</button>"
                      "</form>"
                      "</div>"
                      "<div class='menu-item'>"
                      "<span class='menu-item-name'>Chocolate Fondue</span>"
                      "<span class='menu-item-price'>$8.99</span>"
                      "<form action='/fondue' method='get'>"
                      "<button class='order-button'>"
                      "ORDER"
                      "</button>"
                      "</form>"
                      "</div>"
                      "</div>"
                      "</body>"
                      "</html>";

void addToDisplay1() {
  char name[] = "Burger";
  int len = strlen(name);
  for (int i = 0; i < len; i++)
  Display[count][i] = name[i];
  count++;
}

void addToDisplay2() {
  char name[] = "Pizza";
  int len = strlen(name);
  for (int i = 0; i < len; i++)
  Display[count][i] = name[i];
  count++;

}

void addToDisplay3() {
  char name[] = "french-fries";
  int len = strlen(name);
  for (int i = 0; i < len; i++)
  Display[count][i] = name[i];
  count++;

}

void addToDisplay4() {
  char name[] = "Caesar";
  int len = strlen(name);
  for (int i = 0; i < len; i++)
  Display[count][i] = name[i];
  count++;

}

void addToDisplay5() {
  char name[] = "Chicken";
  int len = strlen(name);
  for (int i = 0; i < len; i++)
  Display[count][i] = name[i];
  count++;

}

void addToDisplay6() {
  char name[] = "Fondue";
  int len = strlen(name);
  for (int i = 0; i < len; i++)
  Display[count][i] = name[i];
  count++;

}

void printOrder() {
  // lcd display loop
  for (int i = 0; i < count; i++) {
    lcd.setCursor(0, 0);
    lcd.print(Display[i]);
    delay(1500);
    lcd.clear();
  }
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin();     
  lcd.backlight();
  lcd.clear();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Aladdin");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  //serial monitor
  Serial.begin(9600);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();

  dnsServer.processNextRequest();
  webServer.handleClient();
  webServer.on("/burger", HTTP_GET, []() {
    addToDisplay1();
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.on("/pizza", HTTP_GET, []() {
    addToDisplay2();
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.on("/french-fries", HTTP_GET, []() {
    addToDisplay3();
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.on("/caesar", HTTP_GET, []() {
    addToDisplay4();
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.on("/chicken", HTTP_GET, []() {
    addToDisplay5();
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.on("/fondue", HTTP_GET, []() {
    addToDisplay6();
    webServer.send(200, "text/html", responseHTML);
  });
  // GET SERVERS IPADD
  Serial.println((WiFi.localIP()));
  // GET NUM OF CONNECTED STATIONS(CLIENTS)
  Serial.print("connected stations:");
  Serial.println((WiFi.softAPgetStationNum()));
  printOrder();
  delay(500);
}
