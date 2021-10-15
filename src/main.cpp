#include "main.h"
#include "time_api.h"
#include <Arduino.h>
#include "../.pio/libdeps/nodemcuv2/RTClib/src/RTClib.h"
#include "cover_layout.h"
#include "../.pio/libdeps/nodemcuv2/Adafruit NeoPixel/Adafruit_NeoPixel.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define       INIT_RTC_TIME               0
#define       WRITE_ES_IST                1
#define       WRITE_UHR                   1
#define       MAX_WRITE_SIZE              64
#define       LEDS_PER_LETTER             1
#define       LED_COUNT                   180
#define       LED_PIN                     D3
#define       PHOTORES_PIN                A0
#define       BLYNK_TEMPLATE_ID           "TMPLUvgqHBuw"
#define       BLYNK_DEVICE_NAME           "Quickstart Device"
#define       BLYNK_AUTH_TOKEN            "hR_OHElHMlm_kDqa-VxoFI-egUOMmElc"
#define       BLYNK_PRINT                 Serial

// Your WiFi credentials.
// Set password to "" for open networks.
const char* ssid = "Chrimbo 2,4 GHz";
const char* pass = "TegernseerHell";

RTC_DS1307          rtc;
int8_t              rtc_begin_return;
int16_t             api_response_code;
DateTime            dateTime;
int8_t              hours;
int8_t              hours_offset;
int8_t              minutes;  
int8_t              minutes_offset;
uint32_t            unixtime = 0;
int8_t              write_idx[MAX_WRITE_SIZE];
int8_t              active_idx[MAX_WRITE_SIZE];
int8_t              write_idx_ptr;
Adafruit_NeoPixel   strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint8_t             color_red     = 128;
uint8_t             color_green   = 128;
uint8_t             color_blue    = 128;
uint8_t             brightness    = 100;
bool                time_change   = true;
bool                color_change  = false;
bool                brightness_change = false;
bool                rainbow_flag  = false;
bool                use_rtc       = true;
bool                force_refresh = false;
char                auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer          timer;


// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncAll();
}

void myTimerEvent()
{
  Blynk.virtualWrite(V6, hours);
  Blynk.virtualWrite(V7, minutes);
  Blynk.virtualWrite(V8, api_response_code);
  Blynk.virtualWrite(V9, rtc_begin_return);
  Blynk.virtualWrite(V10, hours_offset);
  Blynk.virtualWrite(V11, minutes_offset);
}

bool array_contains(int8_t array[], int elem, int array_size)
{
  for (int i = array_size; i >= 0; i--)
  {
    if (array[i] == elem) {
      return true;
    }
  }
  return false;
}

void led_startup()
{
  int j = 1;
  get_current_time();
  calculate_next_leds();
  for(int i = 0 ; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, strip.Color(color_red, color_green, color_blue));
    j++;
    if (j % 18 == 0)
    {
      strip.show();
      delay(100);
    }
  }
  j = 1;
  for(int i = LED_COUNT; i >= 0; i--)
  {
    if (!array_contains(write_idx, i, MAX_WRITE_SIZE))
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }

    j++;
    if (j % 18 == 0)
    {
      strip.show();
      delay(100);
    }
  }
}

void copy_write_idx_to_active_idx()
{
  for (int i = 0; i < MAX_WRITE_SIZE; i++)
  {
    active_idx[i] = write_idx[i];
  }
}

void clear_write_idx_array()
{
  write_idx_ptr = 0;
  memset(write_idx, -1, MAX_WRITE_SIZE);
}

void add_to_write_idx(int8_t start, int8_t amount)
{
  int8_t i = 0;
  for (; i < amount; write_idx_ptr++ ) 
  {
    write_idx[write_idx_ptr] = start++;
    i++;
  }
}

void calculate_next_leds()
{
  
  static int8_t prev_minutes = -1;
  if (use_rtc)
  {
    hours = dateTime.hour();
    minutes = dateTime.minute();
  }
  int8_t minutes_mod_5 = minutes % 5;
  int8_t minutes_div_5 = 0;
  bool   get_next_hour = false;
  bool   full_hour     = false;

  if (prev_minutes != minutes || force_refresh)
  {
    time_change = true;

    minutes_div_5 = minutes - minutes_mod_5;

    #if WRITE_ES_IST
      // ES
      add_to_write_idx(0, 2);
      // IST
      add_to_write_idx(3, 3);
    #endif


    switch(minutes_div_5)
    {
      case(5):
        Serial.print("FÜNF NACH ");
        // FÜNF
        add_to_write_idx(words[2].position, words[2].length);
        // NACH
        add_to_write_idx(words[7].position, words[7].length);
        break;
      case(10):
        Serial.print("ZEHN NACH ");
        // ZEHN
        add_to_write_idx(words[3].position, words[3].length);
        // NACH
        add_to_write_idx(words[7].position, words[7].length);
        break;
      case(15):
        Serial.print("VIERTEL NACH ");
        // VIERTEL
        add_to_write_idx(words[22].position, words[22].length);
        // NACH
        add_to_write_idx(words[7].position, words[7].length);
        break;
      case(20):
        Serial.print("ZWANZIG NACH ");
        // ZWANZIG
        add_to_write_idx(words[4].position, words[4].length);
        // NACH
        add_to_write_idx(words[7].position, words[7].length);
        break;
      case(25):
        Serial.print("FÜNF VOR HALB ");
        // FÜNF
        add_to_write_idx(words[2].position, words[2].length);
        // VOR
        add_to_write_idx(words[6].position, words[6].length);
        // HALB
        add_to_write_idx(words[8].position, words[8].length);
        get_next_hour = true;
        break;
      case(30):
        add_to_write_idx(words[8].position, words[8].length);
        // HALB
        add_to_write_idx(44, 4);
        get_next_hour = true;
        break;
      case(35):
        Serial.print("FÜNF NACH HALB ");
        // FÜNF
         add_to_write_idx(words[2].position, words[2].length);
        // NACH
        add_to_write_idx(words[7].position, words[7].length);
        // HALB
         add_to_write_idx(words[8].position, words[8].length);
        get_next_hour = true;
        break;
      case(40):
        Serial.print("ZWANZIG VOR ");
        // ZWANZIG
        add_to_write_idx(words[4].position, words[4].length);
        // VOR
        add_to_write_idx(words[6].position, words[6].length);
        get_next_hour = true;
        break;
      case(45):
        Serial.print("VIERTEL VOR ");
        // VIERTEL
        add_to_write_idx(words[22].position, words[22].length);
        // VOR
        add_to_write_idx(words[6].position, words[6].length);
        get_next_hour = true;
        break;
      case(50):
        Serial.print("ZEHN VOR ");
        // ZEHN
        add_to_write_idx(words[3].position, words[3].length);
        // VOR
        add_to_write_idx(words[6].position, words[6].length);
        get_next_hour = true;
        break;
      case(55):
        Serial.print("FÜNF VOR ");
        // FÜNF
        add_to_write_idx(words[2].position, words[2].length);
        // VOR
        add_to_write_idx(words[6].position, words[6].length);
        get_next_hour = true;
        break;
      default:
        full_hour = true;
        break;    
    }

    if (get_next_hour) hours++;
    if (hours > 12) hours = hours - 12;

    switch(hours)
    {
      case(1):

        // EIN
        if (full_hour) {
          add_to_write_idx(words[23].position, words[23].length);
          Serial.print("EIN");
        }
        // EINS
        else {
          Serial.print("EINS");
          add_to_write_idx(words[11].position, words[11].length);
        }
        break;
      case(2):
        Serial.print("ZWEI");
        // ZWEI
        add_to_write_idx(words[12].position, words[12].length);
        break;
      case(3):
        Serial.print("DREI");
        // DREI
       add_to_write_idx(words[13].position, words[13].length);
        break;
      case(4):
        Serial.print("VIER");
        // VIER
        add_to_write_idx(words[14].position, words[14].length);
        break;
      case(5):
        Serial.print("FÜNF");
        // FÜNF
        add_to_write_idx(words[10].position, words[10].length);
        break;
      case(6):
        Serial.print("SECHS");
        // SECHS
        add_to_write_idx(words[15].position, words[15].length);
        break;
      case(7):
        Serial.print("SIEBEN");
        // SIEBEN
       add_to_write_idx(words[17].position, words[17].length);
        break;
      case(8):
        Serial.print("ACHT");
        // ACHT
        add_to_write_idx(words[16].position, words[16].length);
        break;
      case(9):
        Serial.print("NEUN");
        // NEUN
        add_to_write_idx(words[20].position, words[20].length);
        break;
      case(10):
        Serial.print("ZEHN");
        // ZEHN
        add_to_write_idx(words[19].position, words[19].length);
        break;
      case(11):
        Serial.print("ELF");
        // ELF
        add_to_write_idx(words[9].position, words[9].length);
        break;
      case(12):
        Serial.print("ZWÖLF");
        // ZWÖLF
       add_to_write_idx(words[18].position, words[18].length);
        break;
    }

    switch (minutes_mod_5)
    {
    case(1):
      Serial.println(" + 1");
      break;
    case(2):
      Serial.println(" + 2");
      break;
    case(3):
      Serial.println(" + 3");
      break;
    case(4):
      Serial.println(" + 4");
      break;
    default:
      Serial.println();
      break;
    }

    #if WRITE_UHR
      if (full_hour)
      {
        // UHR
        add_to_write_idx(99, 3);
      }
    #endif
  prev_minutes = minutes;
  copy_write_idx_to_active_idx();
  }
  else
  {
    time_change = false;
  }
  
}

void show_leds()
{
  if (time_change)
  {
    strip.clear();
    int8_t idx = 0;
    while (idx < MAX_WRITE_SIZE && write_idx[idx] >= 0)
    {
      strip.setPixelColor(write_idx[idx], strip.Color(color_red, color_green, color_blue));
      idx++;
    }
    strip.show();
    clear_write_idx_array();
  }
  else if (color_change || brightness_change)
  {
    strip.clear();
    int8_t idx = 0;
    while (idx < MAX_WRITE_SIZE && active_idx[idx] >= 0)
    {
      strip.setPixelColor(active_idx[idx], strip.Color(color_red, color_green, color_blue));
      idx++;
    }
    strip.show();
  }
  else
  {
    // do nothing
  }
}

BLYNK_WRITE(V0)
{
  color_red = param.asInt();
  color_change = true;
  show_leds();
  color_change = false;
}

BLYNK_WRITE(V1)
{
  color_green = param.asInt();
  color_change = true;
  show_leds();
  color_change = false;
}

BLYNK_WRITE(V2)
{
  color_blue = param.asInt();
  color_change = true;
  show_leds();
  color_change = false;
}

BLYNK_WRITE(V3)
{
  brightness = param.asInt();
  brightness_change = true;
  strip.setBrightness(brightness);
  show_leds();
  brightness_change = false;
}

BLYNK_WRITE(V4)
{
  param.asInt() > 0 ? rainbow_flag = true: rainbow_flag = false;
}

BLYNK_WRITE(V5)
{
  param.asInt() == 0 ? use_rtc = true: use_rtc = false;
}

BLYNK_WRITE(V10)
{
  hours_offset = param.asInt();
  calculate_next_leds();
}

BLYNK_WRITE(V11)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    force_display_refresh();
  }
}

BLYNK_WRITE(V12)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    set_rtc_with_current_api_time();
    force_display_refresh();
  }
}

void set_rtc_with_current_api_time()
{
  if (rtc_begin_return && WiFi.status() == WL_CONNECTED)
  {
    get_time_from_api();
    if (unixtime != 0)
    {
      rtc.adjust(DateTime(unixtime));
      Serial.println("RTC set with current API time!");
      Serial.println(unixtime);
      DateTime now = rtc.now();
      int temphour = now.hour();
      int tempmin = now.minute();
      Serial.println(temphour);
      Serial.println(tempmin);
    }
    else {
      Serial.println("Time couldn't be set.");
    }
  }
  else 
  {
    Serial.println("Missing RTC or WiFi connection.");
  }
}

void force_display_refresh()
{
  force_refresh = true;
  calculate_next_leds();
  Serial.println("Forced display refresh.");
  force_refresh = false;
}

void get_current_time()
{
  if (use_rtc)
    dateTime = rtc.now();
  else
    get_time_from_api();
}

/* void get_brightness()
{
  float bright = analogRead(PHOTORES_PIN) * 1.0;
  brightness = (bright/70.0 * 100) - 20;
  Serial.println(brightness);
  strip.setBrightness(brightness);
  brightness_change = true;
} */

void setup() 
{
  Serial.begin(9600);
   Serial.println("Hallo :)");
  rtc_begin_return = rtc.begin();
  if (! rtc.begin() ) 
  {
    use_rtc = false;
    Serial.println("Couldn't find RTC, using API.");
  }
  else
  {
    #if INIT_RTC_TIME
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      Serial.println("RTC adjusted!");
    #endif
  }
  clear_write_idx_array();
  strip.begin();
  strip.setBrightness(brightness);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  // Setup a function to be called every second
  timer.setInterval(1000, myTimerEvent);

  // Setup WiFi for API Call
  WiFi.begin(ssid, pass);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  led_startup();
}

void loop() 
{
/*   get_brightness(); */
  // get_current_time();
  // calculate_next_leds();
  // for (size_t i = 0; i < 24; i++)
  // {
  //   strip.clear();
  //   strip.show();
  //   Serial.println(words[i].word);
  //   add_to_write_idx(words[i].position,words[i].length);
  //   show_leds();
  //   delay(5000);
  //   /* code */
  // }

  for (size_t i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i,strip.Color(255,255,255));
    strip.show();
    delay(200);
  }
  
  
  // show_leds();
  // Blynk.run();
  // timer.run();
}