# ESP8266 Stock Ticker

![Demo Image](/images/Demo.png)

- [Major Components](#major-components)
    - [Hardware](#hardware)
    - [Libraries](#libraries)
    - [Constants](#constants)
    - [Functions](#functions)
- [How It Works](#how-it-works)
- [Usage & Setup](#usage)
    - [Pinout](#pinout)
    - [Keys.h Setup](#keysh-setup)
    - [How to Use Different LCD Sizes](#how-to-use-different-lcd-sizes)
- [Contributing](#contributing)
- [Contact](#contact)
- [Acknowledgements](#acknowledgements)


This project is a stock ticker display using ESP8266. It fetches stock data from Finnhub.io and displays it on an LCD screen (Either 1602 or 2004). The ticker symbols are customizable, and the display rotates through the selected stocks at a configurable interval.



## Major Components

### Hardware

The project uses the following hardware:
- `NodeMCU ESP8266`: Microcontroller used for running the program, connecting to wifi, parsing the retrieved data from the API, and passing along said data to the outputs. [Get it On Amazon](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES)
- `LCD1602 OR LCD2004`: Liquid Crystal Displays to display the stock information. The code is setup to work with either size (16x2 or 20x4 (See [How to Use Different LCD Sizes](#how-to-use-different-lcd-sizes))) | [LCD1602 I2C on Amazon](https://www.amazon.com/Display-Module-Backlight-Arduino-MEGA2560/dp/B07T8ZG5D1/ref=sr_1_4?crid=NVVEFIL8ELO5&keywords=lcd1602+i2c&qid=1704004894&s=electronics&sprefix=lcd1602+i2c%2Celectronics%2C81&sr=1-4) | [LCD2004 I2C on Amazon](https://www.amazon.com/Hosyond-Module-Display-Arduino-Raspberry/dp/B0C1G9GBRZ/ref=sr_1_3?crid=1PLCR7OO8KAWF&keywords=lcd%2B2004%2Bi2c&qid=1704004946&s=electronics&sprefix=lcd2004%2Bi2c%2Celectronics%2C67&sr=1-3&th=1)
- `COMING SOON: 3D Print Files`: I have designed a model for a case for both 16x2 and 20x4 LCD Screens. Both require some reworking to properly fit the ESP8266 board before I add them here.

### Libraries

The project uses several libraries:

- `ESP8266WiFi.h`: For connecting to a WiFi network using the ESP8266 microcontroller.
- `WiFiClientSecure.h`: For making secure HTTP requests.
- `ArduinoJson.h`: For parsing JSON responses from the Finnhub API.
- `Math.h`: For simple mathematical operations.
- `lcd_functions.h`: Custom library (included in repo) for handling LCD display operations.
- `keys.h`: Contains sensitive information like WiFi SSID, password, and API key. (Change the parameters accordingly for your own usage)

### Constants

The project defines several constants:

- `TEST_HOST`: The API host. (keys.h)
- `ssid` and `password`: Network credentials. (keys.h)
- `TEST_HOST_FINGERPRINT`: SSL fingerprint for the API host. (keys.h)
- `apikey`: API key for Finnhub.io. (keys.h)
- `SYMBOL1`, `SYMBOL2`, etc.: Stock symbols to fetch data for.
- `stockRotationDelay`: Delay between switching of stock ticker display.

### Functions

The project has several functions:

- `setup()`: Initializes the serial communication, LCD display, and sets the WiFi client to insecure mode.
- `loop()`: Main loop that periodically reconnects to WiFi and fetches data for each stock symbol.
- `getData(String ticker)`: Fetches and displays data for a given stock symbol. (Copy and paste this function in the loop followed by a delay to add more tickers)
- `connectToWiFi()`: Connects to the WiFi network.

## How It Works

The `loop()` function periodically reconnects to WiFi (if necessary) and fetches data for each stock symbol. The `getData()` function makes a secure HTTP GET request to the Finnhub.io API, parses the JSON response, and displays the stock data on the LCD screen. The `connectToWiFi()` function handles connecting to the WiFi network.

## Usage & Setup

To use this project, you need to:

1. See [Pinout](#pinout) and configure your electronics. *NOTE: If using an I2C Board (As Recommended), the pinout will be the same for both 16x2 and 20x4 liquid crystal displays*
2. Install the required libraries. (lcd_functions.h and keys.h are included within the repo)
3. Define your WiFi credentials and API key in the `keys.h` file. (See [Keys.h Setup](#keysh-setup) for more information)
4. Define the stock symbols you want to track and optionally the delay between the ticker switching.
5. Upload the code to your ESP8266. Due to this board not being a direct product from Arduino, you will need to install the ESP8266 via the boards manager (Arduino IDE)

For more detailed instructions, please refer to the comments in the code.

### Pinout
![ESP8266 to I2C Pinout Diagram](/images/esp8266_LCD.webp)

### Keys.h Setup

You will need to change the parameters within the keys.h file before uploading the code to the ESP8266.

1. Change `YOURSSID` to your wireless network SSID
2. Change `YOURPASSWORD` to your wireless network password
3. Change `YOURFINGERPRINT` to your SSL fingerprint. To find this, [Follow This Tutorial](https://serverok.in/how-to-find-ssl-certificate-fingerprint)
4. Create an account at [Finnhub.io](https://finnhub.io/) and paste your api key in `YOURAPIKEY`

### How to Use Different LCD Sizes

As of now, the code works on both LCD1602 and LCD2004 displays, however the only difference is the overall look. I do plan on incoorporating a more efficient design for the LCD2004 in the future.

If you are using an LCD2004, follow the steps below:

1. Navigate to `lcd_functions.cpp`
2. Change bool value `lcd2004` from `false` to `true`

## Contributing

This project is open for contributions. Please fork the repository and submit a pull request with your changes.


## Contact

Created by Billups Tillman - feel free to contact me at bpt3creations@gmail.com

## Acknowledgements

- Finnhub.io for providing the stock data API.
- ESP8266WiFi library for providing the WiFi functionality.
- ArduinoJson library for providing the JSON parsing functionality.

