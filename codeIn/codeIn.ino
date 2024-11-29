#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino_JSON.h>
#include <ESP32Servo.h>
#include <WebServer.h>



const char* ssid = "Live 4_1573";
const char* password = "nguyennam";

#define cambienRa       33 
#define cambien1        14 
#define cambien2        27 
#define cambien3        26 
#define cambien4        25 

#define RST_PIN         2
#define SS_PIN          5
#define PIN_SERVO       4

// define temperature
#define lm35_pin         34
float temp = 0.0;

Servo myServo;

int UID[4], i;
String apiUrl = "192.168.117.88"; // Thay URL 

LiquidCrystal_I2C lcd(0x27,20,4);
MFRC522 mfrc522(SS_PIN, RST_PIN);




int giatriRa = 0;
int giatri1 = 0;
int giatri2 = 0;
int giatri3 = 0;
int giatri4 = 0;

 WebServer server(80);

void setup() 
{


//  Connect Servo
    myServo.attach(PIN_SERVO);

// Connect LCD
    Serial.begin(9600);   
    lcd.init();
    lcd.backlight();
      

// Connect RFID
    SPI.begin();    
    mfrc522.PCD_Init();


// Connect CamBien

    pinMode(cambienRa, INPUT);
    pinMode(cambien1, INPUT);
    pinMode(cambien2, INPUT);
    pinMode(cambien3, INPUT);
    pinMode(cambien4, INPUT);
// Connect WiFi

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    // Dang ky duong dan cho Server
    
   
    server.begin();
    server.on("/OpenServoIn", openServo);
    server.on("/CloseServoIn", closeServo);

}



void loop() 
{
  server.handleClient();
 
  temperature();

  displaySlot();

  sendTempSlot();

  // while(digitalRead(cambienRa) == 0){
  //   String cardOut = connectRFIDwithLCD();
  //   if(cardOut != ""){
  //     sendCheckOut(cardOut);
  //     break;
  //   }
  // }

  String cardIn = connectRFIDwithLCD();
  if(cardIn != ""){
    Serial.print("hello");
    Serial.print(cardIn);
    sendCheckIn(cardIn);
  }
 
}


void openServo(){
  server.send(200, "text/plain", "Xin chào từ ESP32!");
  Serial.print("OpenServo");
  myServo.write(180);
  delay(180);
  myServo.write(90);
}
void closeServo(){
  server.send(200, "text/plain", "Xin chào từ ESP32!");
  Serial.print("CloseServo");
  myServo.write(0);
  delay(180);
  myServo.write(90);
}

void temperature(){
     // Đọc giá trị từ chân(GPIO 34)
  int analogValue = analogRead(lm35_pin);

  // Chuyển đổi giá trị analog thành điện áp (từ 0-4095 về 0-3.3V)
  float voltage = analogValue * (5 / 4095.0);

  // Chuyển đổi điện áp thành nhiệt độ
  float temperature = voltage * 100; // LM35 xuất ra 10mV cho mỗi độ C


  temp = temperature ;



    // In giá trị ra Serial Monitor
    // Serial.print("Temperature: ");
    // Serial.print(temperature);
    // Serial.println(" °C");

    // get the ADC value from the temperature sensor
// int adcVal = analogRead(lm35_pin);
// // convert the ADC value to voltage in millivolt
// float milliVolt = adcVal * (3300 / 4095);
// // convert the voltage to the temperature in Celsius
// float tempC = milliVolt / 10;
// // convert the Celsius to Fahrenheit
// float tempF = tempC * 9 / 5 + 32;
    
    delay(1000); // Đợi 1 giây trước khi đọc lại
}

void displaySlot(){
  
  if(giatri1 != digitalRead(cambien1) || giatri2 != digitalRead(cambien2) || giatri3 != digitalRead(cambien3) || giatri4 != digitalRead(cambien4) ){

    giatri1 = digitalRead(cambien1);
    giatri2 = digitalRead(cambien2);
    giatri3 = digitalRead(cambien3);
    giatri4 = digitalRead(cambien4);
  lcd.setCursor(1,0);
  lcd.print("SLOT1 :");
  lcd.print(giatri1);

  lcd.setCursor(1,1);
  lcd.print("SLOT2 :");
  lcd.print(giatri2);


  lcd.setCursor(10,0);
  lcd.print("SLOT3 :");
  lcd.print(giatri3);

  lcd.setCursor(10,1);
  lcd.print("SLOT4 :");
  lcd.print(giatri4);

  }


}
 
void startServo(){
  myServo.write(180);
  delay(180);
  myServo.write(90);
  delay(5000);
  myServo.write(0);
  delay(180);
  myServo.write(90);
}

String connectRFIDwithLCD(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return ""; 
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    return "";
  }




  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       
    UID[i] = mfrc522.uid.uidByte[i];


  }

  // chuyen doi thanh string cua ma so xe
  String result = ""; // Khởi tạo chuỗi rỗng

    for (int i = 0; i < 4; i++) {
        result += String(UID[i]); // Chuyển từng phần tử sang String và nối vào result
        if (i < 3) {
            result += " "; // Thêm dấu cách giữa các số
        }
    }

  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();
  return result;
  
}


void sendCheckIn(String idCustomer) {

      if(giatri1 + giatri2 + giatri3 + giatri4 == 0 ){
                lcd.clear();
                lcd.setCursor(1,1);
                lcd.print("Het cho");
                delay(1000);
                lcd.clear();
                giatri1 = 1 - giatri1;
                displaySlot();
                return;
      }
     if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http; // Tạo đối tượng HTTPClient
        String url = "http://" + apiUrl + ":8080/inOut/in"; // Thay đổi địa chỉ IP


        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        StaticJsonDocument<200> jsonDoc;
        jsonDoc["card_code"] = idCustomer; // Thêm tham số

    // Chuyển đổi đối tượng JSON thành chuỗi
        String jsonData;
        serializeJson(jsonDoc, jsonData);
        int httpResponseCode = http.POST(jsonData);


        if (httpResponseCode > 0) {
            String responseBody = "{}";
            responseBody = http.getString(); // Nhận phản hồi
            JSONVar responseJson = JSON.parse(responseBody);
            
            String checkValue = JSON.stringify(responseJson["check"]);
             if (checkValue == "1") {
                String car_code = JSON.stringify(responseJson["car_code"]);
                lcd.clear();
                lcd.setCursor(1,1);
                lcd.print(car_code);
                lcd.setCursor(2,2);
                lcd.print("Thanh Cong");
                startServo();
                lcd.clear();
                giatri1 = 1 - giatri1;
                displaySlot();
            }
            else{
              String message = JSON.stringify(responseJson["message"]);
                lcd.clear();
                lcd.setCursor(1,1);
                lcd.print(message);
                delay(1000);
                lcd.clear();
                giatri1 = 1 - giatri1;
                displaySlot();
            }
          
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }

        http.end(); // Giải phóng tài nguyên
    } else {
        Serial.println("WiFi not connected");
    }
}

// void sendCheckOut(String idCustomer) {
//      if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http; // Tạo đối tượng HTTPClient
//         String url = "http://" + apiUrl +":8080/inOut/out"; // Thay đổi địa chỉ IP


//         http.begin(url);
//         http.addHeader("Content-Type", "application/json");

//         StaticJsonDocument<200> jsonDoc;
//         jsonDoc["card_code"] = idCustomer; // Thêm tham số

//     // Chuyển đổi đối tượng JSON thành chuỗi
//         String jsonData;
//         serializeJson(jsonDoc, jsonData);
//         int httpResponseCode = http.POST(jsonData);


//         if (httpResponseCode > 0) {
//             String responseBody = "{}";
//             responseBody = http.getString(); // Nhận phản hồi
//             JSONVar responseJson = JSON.parse(responseBody);
            
//             String checkValue = JSON.stringify(responseJson["check"]);
//             if (checkValue == "1") {
//                 lcd.clear();
//                 lcd.setCursor(1,1);
//                 lcd.print(idCustomer);
//                 lcd.setCursor(1,2);
//                 lcd.print("Thanh toan: ");
//                 lcd.print(responseJson["price"]);
//                 startServo();
//                 lcd.clear();
//             }
//             else {
//               lcd.clear();
//               lcd.setCursor(1,1);
//               lcd.print("The khong hop le");
//               lcd.clear();
//             }
//             giatri1 = 1 - giatri1;
//             displaySlot();

//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end(); // Giải phóng tài nguyên
//     } else {
//         Serial.println("WiFi not connected");
//     }
// }

void sendTempSlot() {
     if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http; // Tạo đối tượng HTTPClient
        String url = "http://" + apiUrl + ":8080/tempSlot"; // Thay đổi địa chỉ IP


        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        StaticJsonDocument<200> jsonDoc;
        jsonDoc["temp"] = temp; // Thêm tham số
        jsonDoc["tongViTri"] = (giatri1 + giatri2 + giatri3 + giatri4) * 1.0;
        jsonDoc["giatri1"] = giatri1 * 1.0;
        jsonDoc["giatri2"] = giatri2 * 1.0;
        jsonDoc["giatri3"] = giatri3 * 1.0;
        jsonDoc["giatri4"] = giatri4 * 1.0;

    // Chuyển đổi đối tượng JSON thành chuỗi
        String jsonData;
        serializeJson(jsonDoc, jsonData);
        int httpResponseCode = http.POST(jsonData);


        if (httpResponseCode > 0) {
            String responseBody = "{}";
            responseBody = http.getString(); // Nhận phản hồi
            JSONVar responseJson = JSON.parse(responseBody);
    
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }

        http.end(); // Giải phóng tài nguyên
    } else {
        Serial.println("WiFi not connected");
    }
}
void handlePost() {
    if (server.hasArg("plain")) { // Kiểm tra xem có dữ liệu gửi đến không
        String message = server.arg("plain");
        Serial.println("Received: " + message); // In dữ liệu nhận được ra Serial Monitor
        server.send(200, "text/plain", "Data received"); // Gửi phản hồi về client
    } else {
        server.send(400, "text/plain", "No data received");
    }
}

