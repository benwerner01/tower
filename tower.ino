#include <FastLED.h>

#define COLOR_ORDER RGB
#define CHIPSET     WS2812B
#define NUM_LEDS    450
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 60

static CRGB pride_colors_rgb[6] = { CRGB(118, 0, 137), CRGB(0, 68, 255), CRGB(0, 129, 31), CRGB(255, 239, 0), CRGB(255, 140, 0),  CRGB(231, 0, 0) }; 

bool gReverseDirection = false;

CRGB leds[4][NUM_LEDS];


int DebugPrintf(char* pszFmt, ... ) {

    int cargs = 0;
    char* pszTmp;

    for (pszTmp = pszFmt; *pszTmp; pszTmp++)  
        if (*pszTmp == '%')  
            cargs++; 

    va_list argv;
    va_start(argv, cargs);

    pszTmp = pszFmt;
    while (*pszTmp)
    {
        if (*pszTmp == '%')
        {
            pszTmp++;
            switch (*pszTmp)
            {
                case 'd':   
                    Serial.print(va_arg(argv, int));    
                    break;

                case 'x':   
                    Serial.print(va_arg(argv, int), HEX);    
                    break;

                case 'l':   
                    Serial.print(va_arg(argv, long));
                    break;

                case 'u':
                    Serial.print(va_arg(argv, unsigned long));
                    break;

                case 'f':
                    Serial.print(va_arg(argv, double));
                    break;

                case 'F':
                    Serial.print(va_arg(argv, double), 8);
                    break;

                case 'c':
                    Serial.print((char) va_arg(argv, int));
                    break;

                case 's':
                    Serial.print(va_arg(argv, char*));
                    break;

                case '%':
                    Serial.print('%');
                    break;

                default:
                    break;
            }
        }
        else if (*pszTmp == '\n')
        {
            Serial.println();
        }
        else
        {
            Serial.print(*pszTmp);
        }

        pszTmp++;
    }
}




void setup() 
{
  
  delay(3000); // ?
  
  FastLED.addLeds<CHIPSET, 5, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, 6, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, 12, COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, 9, COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection( TypicalLEDStrip );
  
  FastLED.setBrightness( BRIGHTNESS );

}

void loop()
{
  Rainbow(pride_colors_rgb, 6);
}

void Rainbow(CRGB colors[], int number_of_colors)
{
  for (int x=0; x < number_of_colors; x++) {
    for (int i=0; i<4; i++)
    {
      fill_solid(&(leds[i][ (NUM_LEDS / number_of_colors) * x ]), 75, colors[x]);
    }
  }
  FastLED.show();
}



void ShootUp()
{
  static long pos = 0;

  for (int i=0; i<4; i++)
  {
    fill_solid( &(leds[i][0]), NUM_LEDS, CRGB::Black );
    fill_solid(&(leds[i][ pos ]), 10, CRGB::Green);
  }

  pos += 10;
  if (pos > NUM_LEDS - 10)
  {
    pos = 0;
  }
  
  FastLED.show();
  delay(1);
  
}


void QuickHueFade()
{
  static uint8_t hue = 0;
  hue += 3;
  FastLED.showColor(CHSV(hue, 255, 255)); 
  delay(1);
}


void SlowHueFade()
{
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255)); 
  delay(100);
}
