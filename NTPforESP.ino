// Please go to Blynk and add datastream Virtual V5 as String

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6jEr8VlQS"
#define BLYNK_TEMPLATE_NAME "buang"
#define BLYNK_AUTH_TOKEN "gCNOaICiz5DfYya0mc2qUyLPPTRPM-SI"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";
BlynkTimer timer;

#include <ezTime.h>
Timezone local;

BLYNK_CONNECTED() 
{ Blynk.sendInternal("utc", "time");      
  Blynk.sendInternal("utc", "tz_rule");
  Blynk.sendInternal("rtc", "sync");
  Blynk.syncAll();
}

BLYNK_WRITE(InternalPinUTC) 
{ String cmd = param[0].asStr();
  if (cmd == "time") 
  { const uint64_t utc_time = param[1].asLongLong();
    UTC.setTime(utc_time / 1000, utc_time % 1000);
  } 
  else if (cmd == "tz_rule") 
  { String tz_rule = param[1].asStr();
    local.setPosix(tz_rule);
  }
}
long ts;
BLYNK_WRITE(InternalPinRTC) { ts = param.asLong(); }

char tx2buf[100];
void localTime() 
{ sprintf(tx2buf,"Time:%d:%d:%d Day:%d/%d/%d",
  local.hour(),local.minute(),local.second(),
  local.day(),local.month(),local.year());
  
  Blynk.virtualWrite(V5,tx2buf);
  Serial.println(tx2buf);
}

void setup()
{ Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L,localTime);
}

void loop()
{ Blynk.run();
  timer.run();
}
