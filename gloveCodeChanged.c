#include <WiFi.h>

// Pin numbers of the flex sensors

#define flexSens_0 33 // pin of flex sensor on big finger
#define flexSens_1 32 // pin of flex sensor on point finger
#define flexSens_2 35 // pin if flex sensor on middle finger

// Wi-Fi network credentials
const char* ssid     = "CAR_WIFI";
const char* password = "12345678";

WiFiClient master;

void setup() {
  Serial.begin(115200);
  Serial.println("Start!");

// Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(F("."));
  }
  Serial.println(" ");
  Serial.print(F("Connected to Wifi! IP address : ")); 
  Serial.println(WiFi.localIP());

// Connect to the server
  if (master.connect("192.168.4.1", 80)) { 
    Serial.println("Connected to server!");
  }
  else{
    Serial.println("Connected to server error!");
  }
}

// Constrain a value between a minimum and maximum value
int constrainValue(int value, int minValue, int maxValue) {
  if (value < minValue) {
    return minValue;
  } else if (value > maxValue) {
    return maxValue;
  } else {
    return value;
  }
}

void loop() {

  // Read analog values from the flex sensors and map them to a range of 0-255
  int flexDataFinger1 = map(analogRead(flexSens_0), 2000, 600, 0, 255);
  int flexDataFinger2 = map(analogRead(flexSens_1), 2000, 600, 0, 255);
  int flexDataFinger3 = map(analogRead(flexSens_2), 2000, 600, 0, 255);

 // Constrain the flex sensor values within the range of 30-255
  int finger1 = constrainValue(flexDataFinger1, 30, 255);
  int finger2 = constrainValue(flexDataFinger2, 30, 255);
  int finger3 = constrainValue(flexDataFinger3, 30, 255); 

  String output;

// Проверка, если все пальцы равны 0
if (finger1 == 0 && finger2 == 0 && finger3 == 0) {
  output = "A0 B0 C0 D0 "; // Будет отправлено: A0 B0 C0 D0
}
// Проверка, если finger1, finger2 и finger3 равны 0, но finger3 больше 0
else if (finger1 == 0 && finger2 == 0 && finger3 > 0) {
  output = "A" + String(-finger3) + " B" + String(-finger3) + " C" + String(-finger3) + " D" + String(-finger3) + " ";
  // Будет отправлено: A(-finger3) B(-finger3) C(-finger3) D(-finger3), где (-finger3) - значение finger3 со знаком минус
}
// Проверка, если finger1 и finger3 равны 0, но finger2 больше 0
else if (finger1 == 0 && finger2 > 0 && finger3 == 0) {
  output = "A" + String(-finger2) + " B" + String(finger2) + " C" + String(-finger2) + " D" + String(finger2) + " ";
  // Будет отправлено: A(-finger2) B(finger2) C(-finger2) D(finger2), где (-finger2) - значение finger2 со знаком минус
}
// Проверка, если finger1 равен 0, но finger2 и finger3 больше 0
else if (finger1 == 0 && finger2 > 0 && finger3 > 0) {
  output = "A" + String(-finger2) + " B" + String(finger2) + " C" + String(-finger2) + " D" + String(finger2) + " ";
  // Будет отправлено: A(-finger2) B(finger2) C(-finger2) D(finger2), где (-finger2) - значение finger2 со знаком минус
}
// Проверка, если finger2 и finger3 равны 0, но finger1 больше 0
else if (finger1 > 0 && finger2 == 0 && finger3 == 0) {
  output = "A" + String(finger1) + " B" + String(finger1) + " C" + String(finger1) + " D" + String(finger1) + " ";
  // Будет отправлено: A(finger1) B(finger1) C(finger1) D(finger1)
}
// По умолчанию, если ни одно из условий не выполнено
else {
  output = "A0 B0 C0 D0 "; // Будет отправлено: A0 B0 C0 D0
}

 // Send the output string to the server
master.print(output);
master.flush();

// void loop() {
//   int finger1 = map(analogRead(flexSens_0), 2000, 600, 0, 255);
//   int finger2 = map(analogRead(flexSens_1), 2000, 600, 0, 255);
//   int finger3 = map(analogRead(flexSens_2), 2000, 600, 0, 255);


// // If the variable value is less than 30, set it to 0
// // If the variable value is greater than 255, set it to 255
// finger1 = (finger1 < 30) ? 0 : (finger1 > 255) ? 255 : finger1;  
// finger2 = (finger2 < 30) ? 0 : (finger2 > 255) ? 255 : finger2;  
// finger3 = (finger3 < 30) ? 0 : (finger3 > 255) ? 255 : finger3;

//   if(finger2 > 0 && finger1 == 0 && finger3 == 0){
//     master.print("A" + String(finger2) + " B" + String(finger2) + " C" + String(finger2) + " D" + String(finger2) + " ");
//     master.flush();
//   }
//   else if(finger3 > 0 && finger1 == 0 && finger2 == 0){
//     master.print("A" + String(-finger3) + " B" + String(-finger3) + " C" + String(-finger3) + " D" + String(-finger3) + " ");
//     master.flush();
//   }
//   else if(finger2 > 0 && finger1 > 0 && finger3 == 0){
//     master.print("A" + String(-finger2) + " B" + String(finger2) + " C" + String(-finger2) + " D" + String(finger2) + " ");
//     master.flush();
//   }
//   else if(finger2 > 0 && finger3 > 0 && finger1 == 0){
//     master.print("A" + String(finger2) + " B" + String(-finger2) + " C" + String(finger2) + " D" + String(-finger2) + " ");
//     master.flush();
//   }
//   else{
   
//     master.print("A0 B0 C0 D0 ");
//     master.flush();
//   }


// Print finger values to the serial monitor for debugging
  /*Serial.print(analogRead(flexSens_0));
  Serial.print(" ");*/
  Serial.print(finger1);
  Serial.print("   ");
  /*Serial.print(analogRead(flexSens_1));
  Serial.print(" ");*/
  Serial.print(finger2);
  Serial.print("   ");
  /*Serial.print(analogRead(flexSens_2));
  Serial.print(" ");*/
  Serial.print(finger3);
  Serial.println("");

  delay(10);
}