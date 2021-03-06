/**************************************************************
   WiFiManager is a library for the ESP8266/Arduino platform
   (https://github.com/esp8266/Arduino) to enable easy
   configuration and reconfiguration of WiFi credentials using a Captive Portal
   inspired by:
   http://www.esp8266.com/viewtopic.php?f=29&t=2520
   https://github.com/chriscook8/esp-arduino-apboot
   https://github.com/esp8266/Arduino/tree/esp8266/hardware/esp8266com/esp8266/libraries/DNSServer/examples/CaptivePortalAdvanced
   Built by AlexT https://github.com/tzapu
   Licensed under MIT license
 **************************************************************/

#ifndef WiFiManager_h
#define WiFiManager_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <memory>

extern "C" {
  #include "user_interface.h"
}

#define BASE_64_IMAGE "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\""

#define DEFAULT_HTML_HEAD \
"<!DOCTYPE html>" \
"<html lang=\"en\">" \
"<head>" \
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>" \
    "<title>{v}</title>";

#define DEFAULT_HTML_STYLE \
    "<style>" \
        ".c{" \
            "text-align: center;" \
            "}" \
        "div,input{" \
            "padding:5px;font-size:1em;" \
        "}" \
        "input{" \
            "width:95%;" \
        "}" \
        "body{" \
            "text-align: center;" \
            "font-family:verdana;" \
        "}" \
        "button{" \
            "border:0;" \
            "border-radius:0.3rem;" \
            "background-color:#1fa3ec;" \
            "color:#fff;" \
            "line-height:2.4rem;" \
            "font-size:1.2rem;" \
            "width:100%;" \
        "}" \
        ".q{" \
            "float: right;" \
            "width: 64px;" \
            "text-align: right;" \
        "}" \
        ".l{" \
            "background: url(\"" BASE_64_IMAGE ") no-repeat left center;" \
            "background-size: 1em;" \
        "}" \
    "</style>"

#define DEFAULT_HTML_SCRIPT \
    "<script>" \
        "function c(l){" \
            "document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();" \
        "}" \
    "</script>"

#define DEFAULT_HTML_HEAD_END \
"</head>" \
"<body>" \
    "<div style='text-align:left;display:inline-block;min-width:260px;'>"

#define DEFAULT_HTML_PORTAL_OPTIONS \
    "<form action=\"/wifi\" method=\"get\">" \
        "<button>Configure WiFi</button>" \
    "</form>" \
    "<br/>" \
    "<form action=\"/0wifi\" method=\"get\">" \
        "<button>Configure WiFi (No Scan)</button>" \
    "</form>" \
    "<br/>" \
    "<form action=\"/i\" method=\"get\">" \
        "<button>Info</button>" \
    "</form>" \
    "<br/>" \
    "<form action=\"/r\" method=\"post\">" \
        "<button>Reset</button>" \
    "</form>"

#define DEFAULT_HTML_ITEM \
    "<div>" \
        "<a href='#p' onclick='c(this)'>{v}</a>&nbsp;" \
        "<span class='q {i}'>{r}%</span>" \
    "</div>"

#define DEFAULT_HTML_FORM_START \
    "<form method='get' action='wifisave'>" \
        "<input id='s' name='s' length=32 placeholder='SSID'>" \
        "<br/>" \
        "<input id='p' name='p' length=64 type='password' placeholder='password'>" \
        "<br/>"

#define DEFAULT_HTML_FORM_PARAM \
    "<br/>" \
    "<input id='{i}' name='{n}' length={l} placeholder='{p}' value='{v}' {c}>"

#define DEFAULT_HTML_FORM_END \
    "<br/>" \
    "<button type='submit'>save</button></form>"

#define DEFAULT_HTML_SCAN_LINK \
    "<br/>" \
    "<div class=\"c\">" \
        "<a href=\"/wifi\">Scan</a>" \
    "</div>"

#define DEFAULT_HTML_SAVED \
    "<div>" \
        "Credentials Saved" \
        "<br />" \
        "Trying to connect ESP to network." \
        "<br />" \
        "If it fails reconnect to AP to try again" \
    "</div>"

#define DEFAULT_HTML_END \
"</div>" \
"</body>" \
"</html>"

// Define HTML pages as EXTERN if you want the user define this
//#define EXTERN_HTML_PAGES

// Since the C++ compiler identify near string as a concatenation we can pretify this asset's
#ifndef EXTERN_HTML_PAGES
const char HTML_HEAD[]                  PROGMEM = DEFAULT_HTML_HEAD;
const char HTML_STYLE[]                 PROGMEM = DEFAULT_HTML_STYLE;
const char HTML_SCRIPT[]                PROGMEM = DEFAULT_HTML_SCRIPT;
const char HTML_HEAD_END[]              PROGMEM = DEFAULT_HTML_HEAD_END;
const char HTML_PORTAL_OPTIONS[]        PROGMEM = DEFAULT_HTML_PORTAL_OPTIONS;
const char HTML_ITEM[]                  PROGMEM = DEFAULT_HTML_ITEM;
const char HTML_FORM_START[]            PROGMEM = DEFAULT_HTML_FORM_START;
const char HTML_FORM_PARAM[]            PROGMEM = DEFAULT_HTML_FORM_PARAM;
const char HTML_FORM_END[]              PROGMEM = DEFAULT_HTML_FORM_END;
const char HTML_SCAN_LINK[]             PROGMEM = DEFAULT_HTML_SCAN_LINK;
const char HTML_SAVED[]                 PROGMEM = DEFAULT_HTML_SAVED;
const char HTML_END[]                   PROGMEM = DEFAULT_HTML_END;
#else
extern const char HTML_HEAD[]           PROGMEM;
extern const char HTML_STYLE[]          PROGMEM;
extern const char HTML_SCRIPT[]         PROGMEM;
extern const char HTML_HEAD_END[]       PROGMEM;
extern const char HTML_PORTAL_OPTIONS[] PROGMEM;
extern const char HTML_ITEM[]           PROGMEM;
extern const char HTML_FORM_START[]     PROGMEM;
extern const char HTML_FORM_PARAM[]     PROGMEM;
extern const char HTML_FORM_END[]       PROGMEM;
extern const char HTML_SCAN_LINK[]      PROGMEM;
extern const char HTML_SAVED[]          PROGMEM;
extern const char HTML_END[]            PROGMEM;
#endif

#define WIFI_MANAGER_MAX_PARAMS 10

// Enable debug using software serial, instead of the default Serial
#define SOFTWARE_SERIAL_DEBUG
#define SOFTWARE_SERIAL_OBJECT  ESPSerial
#define SOFTWARE_SERIAL_SPEED   115200
#define DEBUG_RX_PIN            12
#define DEBUG_TX_PIN            13

#ifdef SOFTWARE_SERIAL_DEBUG
#include <SoftwareSerial.h>
// Software Serial should be static since this file can be called multiple times
SoftwareSerial static SOFTWARE_SERIAL_OBJECT(DEBUG_RX_PIN, DEBUG_TX_PIN);
#endif

class WiFiManagerParameter {
  public:
    WiFiManagerParameter(const char *custom);
    WiFiManagerParameter(const char *id,
                         const char *placeholder,
                         const char *defaultValue,
                         int length);
    WiFiManagerParameter(const char *id,
                         const char *placeholder,
                         const char *defaultValue,
                         int length,
                         const char *custom);

    const char *getID();
    const char *getValue();
    const char *getPlaceholder();
    int         getValueLength();
    const char *getCustomHTML();
  private:
    const char *_id;
    const char *_placeholder;
    char       *_value;
    int         _length;
    const char *_customHTML;

    void init(const char *id,
              const char *placeholder,
              const char *defaultValue,
              int length,
              const char *custom);

    friend class WiFiManager;
};


class WiFiManager
{
  public:
    WiFiManager();

    boolean       autoConnect();
    boolean       autoConnect(char const *apName, char const *apPassword = NULL);

    //if you want to always start the config portal, without trying to connect first
    boolean       startConfigPortal(char const *apName, char const *apPassword = NULL);

    // get the AP name of the config portal, so it can be used in the callback
    String        getConfigPortalSSID();

    void          resetSettings();

    //sets timeout before webserver loop ends and exits even if there has been no setup.
    //usefully for devices that failed to connect at some point and got stuck in a webserver loop
    //in seconds setConfigPortalTimeout is a new name for setTimeout
    void          setConfigPortalTimeout(unsigned long seconds);
    void          setTimeout(unsigned long seconds);

    //sets timeout for which to attempt connecting, usefull if you get a lot of failed connects
    void          setConnectTimeout(unsigned long seconds);


    void          setDebugOutput(boolean debug);
    //defaults to not showing anything under 8% signal quality if called
    void          setMinimumSignalQuality(int quality = 8);
    //sets a custom ip /gateway /subnet configuration
    void          setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    //sets config for a static IP
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    //called when AP mode and config portal is started
    void          setAPCallback( void (*func)(WiFiManager*) );
    //called when settings have been changed and connection was successful
    void          setSaveConfigCallback( void (*func)(void) );
    //adds a custom parameter
    void          addParameter(WiFiManagerParameter *p);
    //if this is set, it will exit after config, even if connection is unsucessful.
    void          setBreakAfterConfig(boolean shouldBreak);
    //if this is set, try WPS setup when starting (this will delay config portal for up to 2 mins)
    //TODO
    //if this is set, customise style
    void          setCustomHeadElement(const char* element);
    //if this is true, remove duplicated Access Points - defaut true
    void          setRemoveDuplicateAPs(boolean removeDuplicates);

  private:
    std::unique_ptr<DNSServer>        dnsServer;
    std::unique_ptr<ESP8266WebServer> server;

    //const int     WM_DONE                 = 0;
    //const int     WM_WAIT                 = 10;

    //const String  HTML_HEAD = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/><title>{v}</title>";

    void          setupConfigPortal();
    void          startWPS();

    const char*   _apName                 = "no-net";
    const char*   _apPassword             = NULL;
    String        _ssid                   = "";
    String        _pass                   = "";
    unsigned long _configPortalTimeout    = 0;
    unsigned long _connectTimeout         = 0;
    unsigned long _configPortalStart      = 0;

    IPAddress     _ap_static_ip;
    IPAddress     _ap_static_gw;
    IPAddress     _ap_static_sn;
    IPAddress     _sta_static_ip;
    IPAddress     _sta_static_gw;
    IPAddress     _sta_static_sn;

    int           _paramsCount            = 0;
    int           _minimumQuality         = -1;
    boolean       _removeDuplicateAPs     = true;
    boolean       _shouldBreakAfterConfig = false;
    boolean       _tryWPS                 = false;

    const char*   _customHeadElement      = "";

    //String        getEEPROMString(int start, int len);
    //void          setEEPROMString(int start, int len, String string);

    int           status = WL_IDLE_STATUS;
    int           connectWifi(String ssid, String pass);
    uint8_t       waitForConnectResult();

    void          handleRoot();
    void          handleWifi(boolean scan);
    void          handleWifiSave();
    void          handleInfo();
    void          handleReset();
    void          handleNotFound();
    void          handle204();
    boolean       captivePortal();

    // DNS server
    const byte    DNS_PORT = 53;

    //helpers
    int           getRSSIasQuality(int RSSI);
    boolean       isIp(String str);
    String        toStringIp(IPAddress ip);

    boolean       connect;
    boolean       _debug = true;

    void (*_apcallback)(WiFiManager*) = NULL;
    void (*_savecallback)(void) = NULL;

    WiFiManagerParameter* _params[WIFI_MANAGER_MAX_PARAMS];

    template <typename Generic>
    void          DEBUG_WM(Generic text);

    template <class T>
    auto optionalIPFromString(T *obj, const char *s) -> decltype(  obj->fromString(s)  ) {
      return  obj->fromString(s);
    }
    auto optionalIPFromString(...) -> bool {
      DEBUG_WM("NO fromString METHOD ON IPAddress, you need ESP8266 core 2.1.0 or newer for Custom IP configuration to work.");
      return false;
    }
};

#endif
