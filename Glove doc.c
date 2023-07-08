# C Glove code Documentation

## Introduction
This documentation provides an overview and explanation of the C code written for the C Sniper project. The code utilizes the WiFi library in order to establish a connection with a server and send data from flex sensors to the server.

## Code Overview
The code consists of the following main components:
1. Variable and Constant Definitions
2. `setup()` Function
3. `constrainValue()` Function
4. `loop()` Function

### Variable and Constant Definitions
The following variables and constants are defined at the beginning of the code:
- `flexSens_0`, `flexSens_1`, `flexSens_2`: Pin numbers of the flex sensors connected to the microcontroller.
- `ssid`: Name of the Wi-Fi network to connect to.
- `password`: Password for the Wi-Fi network.
- `master`: WiFiClient object used for communication with the server.

### `setup()` Function
The `setup()` function is executed once when the microcontroller starts. Its main purpose is to initialize the serial communication and establish a Wi-Fi connection with the specified network. The function performs the following steps:
1. Initializes the serial communication at a baud rate of 115200.
2. Prints the "Start!" message to the serial monitor.
3. Calls `WiFi.begin(ssid, password)` to connect to the Wi-Fi network.
4. Waits until the connection is established by continuously checking the Wi-Fi status using `WiFi.status()`.
5. Prints a series of dots to indicate the connection progress.
6. Prints the IP address of the connected Wi-Fi network.
7. Attempts to connect to the server at the specified IP address ("192.168.4.1") and port (80).
8. Prints a "Connected to server!" message if the connection is successful, or a "Connected to server error!" message if the connection fails.

### `constrainValue()` Function
The `constrainValue()` function takes an input value and constrains it between a minimum and maximum value. It returns the constrained value. The function is used to ensure that the flex sensor data falls within a specific range. It performs the following checks:
- If the input value is less than the minimum value, it returns the minimum value.
- If the input value is greater than the maximum value, it returns the maximum value.
- Otherwise, it returns the input value without any changes.

### `loop()` Function
The `loop()` function is the main execution loop of the program. It repeatedly performs the following steps:
1. Reads the analog values from the flex sensors (`flexSens_0`, `flexSens_1`, `flexSens_2`) using `analogRead()`.
2. Maps the analog values from the flex sensors to a range of 0-255 using the `map()` function. The mapping is done based on the specific range of the analog values obtained from the flex sensors.
3. Calls `constrainValue()` on each mapped value to ensure it falls within the desired range (30-255).
4. Performs conditional checks to determine the finger position based on the flex sensor values and generates an appropriate output string (`output`) accordingly.
   - If all finger values are 0, the output string will be "A0 B0 C0 D0".
   - If only finger 3 has a non-zero value, the output string will be "A(-finger3) B(-finger3) C(-finger3) D(-finger3)", where (-finger3) represents the value of finger 3 with a negative sign.
   - If only finger 2 has a non-zero value, the output string will be "A(-finger2) B(finger2) C(-finger2) D(finger2)", where (-finger2) represents the value of finger 2 with a negative sign.
   - If finger 2 and finger 3 have non-zero values, the output string will be "A(-finger2) B(finger2) C(-finger2) D(finger2)", where (-finger2) represents the value of finger 2 with a negative sign.
   - If finger 1 has a non-zero value, the output string will be "A(finger1) B(finger1) C(finger1) D(finger1)".
   - For any other case, the output string will be "A0 B0 C0 D0".
5. Prints the output string to the server using `master.print(output)` and flushes the buffer.
6. Prints the values of finger 1, finger 2, and finger 3 to the serial monitor for debugging purposes.
7. Adds a delay of 10 milliseconds before repeating the loop.

## Conclusion
This technical documentation provides an overview of the C code for the C glove project. It explains the purpose and functionality of each component of the code, including variable definitions, the setup function, the constrainValue function, and the main loop. Understanding this documentation will assist in further development, debugging, and customization of the C glove project.