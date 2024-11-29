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


#define RST_PIN         2
#define SS_PIN          5
#define PIN_SERVO       4

// define temperature

Servo myServo;

int UID[4], i;
String apiUrl = "192.168.117.88"; // Thay URL 

MFRC522 mfrc522(SS_PIN, RST_PIN);




// int giatriRa = 0;
// int giatri1 = 0;
// int giatri2 = 0;
// int giatri3 = 0;
// int giatri4 = 0;

 WebServer server(80);

void setup() 
{


//  Connect Servo
    myServo.attach(PIN_SERVO);


// // Connect LCD
    Serial.begin(9600);   
//     lcd.init();
//     lcd.backlight();
      

// Connect RFID
    SPI.begin();    
    mfrc522.PCD_Init();

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
    server.on("/OpenServoOut", openServo);
    server.on("/CloseServoOut", closeServo);


}



void loop() 
{
   server.handleClient();
 


// startServo();
  String cardIn = connectRFIDwithLCD();
  if(cardIn != ""){
    Serial.print("hello");
    Serial.print(cardIn);
    sendCheckOut(cardIn);
  }
 
}


void openServo(){
  server.send(200, "text/plain", "Xin chào từ ESP32!");
  Serial.print("OpenServo");
  myServo.write(0);
  delay(180);
  myServo.write(90);
}
void closeServo(){
  server.send(200, "text/plain", "Xin chào từ ESP32!");
  Serial.print("CloseServo");
  myServo.write(180);
  delay(180);
  myServo.write(90);
}
 
void startServo(){
  myServo.write(0);
  delay(180);
  myServo.write(90);
  delay(5000);
  myServo.write(180);
  delay(180);
  myServo.write(90);
}

String connectRFIDwithLCD(){
  // startServo();
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
              Serial.println();


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




void sendCheckOut(String idCustomer) {
     if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http; // Tạo đối tượng HTTPClient
        String url = "http://" + apiUrl +":8080/inOut/out"; // Thay đổi địa chỉ IP


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

                  startServo();            
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