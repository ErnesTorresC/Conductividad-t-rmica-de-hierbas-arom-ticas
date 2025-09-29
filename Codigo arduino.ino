  #include <Adafruit_GFX.h>    // Librería para los gráficos de la pantalla TFT
#include <MCUFRIEND_kbv.h>   // Librería del Hardware especifico
MCUFRIEND_kbv tft;
#include <Adafruit_TFTLCD.h>  //Librería de Diseñó para la pantalla TFT
#include<max6675.h>           //Librería del termopar tipo k
#include <Fonts/FreeSans9pt7b.h> //Tipo de letras para la visualización en la pantalla TFT
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>   
#include <Fonts/FreeMonoOblique12pt7b.h>
#include <TFT_eSPI.h>   //   librería de la modificación para la pantalla TFT
#include <FreeDefaultFonts.h>


//Declaración de colores visuales en la pantalla TFT
#define BLACK   0x0000      
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
#define BLUE    0x001F
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0


// Establecer las variables y el número de puerto para conectar el módulo Max6675 que necesitan los termopares tipo k

#define CSK1 51
#define CS1 53
#define SO1 52
#define gra 0xDF
MAX6675 termopar1(CSK1,CS1,SO1);


#define CSK2 13
#define CS2 12
#define SO2 11
#define gra 0xDF
MAX6675 termopar2(CSK2,CS2,SO2);

#define CSK3 14               
#define CS3 15
#define SO3 16
#define gra 0xDF
MAX6675 termopar3(CSK3,CS3,SO3);

#define CSK4 17
#define CS4 18
#define SO4 19
#define gra 0xDF
MAX6675 termopar4(CSK4,CS4,SO4);

#define CSK5 20
#define CS5 21
#define SO5 22
#define gra 0xDF
MAX6675 termopar5(CSK5,CS5,SO5);

#define CSK6 24  
#define CS6  26
#define SO6  28
#define gra 0xDF
MAX6675 termopar6(CSK6,CS6,SO6);

float  r1=1000000;
float  r2=100000;



//Declarar el diseño propuesto a la pantalla TFT
void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.println("Example: Font_simple");
    Serial.print("found ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; 
    tft.begin(ID);
    tft.setRotation(0);
 
}

void loop(void)
{
 
 //Establecer los parámetros de medición en cada uno de los termopares tipo k
 
    double celsius1 = termopar1.readCelsius();
    double celsius2 = termopar2.readCelsius();
    double celsius3 = termopar3.readCelsius();
    double celsius4 = termopar4.readCelsius();
    double celsius5 = termopar5.readCelsius();
    double celsius6 = termopar6.readCelsius();
//Declarar cada una de las variables para calcular la constante de conductividad térmica
    float promedio2 = (celsius3+celsius4+celsius5+celsius6)/4;//Promedio de las temperaturas de la parte superior 
    float promedio1 = (celsius1+celsius2)/2;//Promedio de las temperaturas en la placa caliente
       float voltaje;// Tensión eléctrica (Volts)
    
 
  

       float Corriente = 0.088;// Corriente eléctrica constante (Amper)
       float calor = voltaje*Corriente; //Potencia suministrada por la tensión y corrientes eléctricas (Watts)
       float espesor =0.692/100;//Espesor constante (cm)
       float temperaturas = promedio1-promedio2;//Diferencia de temperaturas (°C)
       float Area = ((0.7854)*(6.97)*(6.97))/10000;//Área de contacto (cm^2)
       float conductividad=((-calor*espesor))/((temperaturas)*Area); // Ecuación para determinar la constante de la conductividad térmica





  // Se establece el diseño y el tipo de letra para ser visualizadas las variables y los datos en la pantalla TFT
    tft.setRotation(3);
    tft.fillScreen(CYAN);
//Se visualizarán las temperaturas medidas por los termopares 
    showmsgXY(130, 20, 1, &FreeMonoOblique12pt7b, "Menta");
    showmsgXY(20, 50, 1, &FreeSans9pt7b, "T1 =      ");
    tft.setCursor(60, 50);
    tft.print(celsius1);
       
    showmsgXY(140, 50, 1, &FreeSans9pt7b, "T2 =      ");        
    tft.setCursor(190, 50);
    tft.print(celsius2);

    
    showmsgXY(260, 50, 1, &FreeSans9pt7b, "T3 =     ");
      tft.setCursor(310, 50);
    tft.print(celsius3);

    
     showmsgXY(20, 80, 1, &FreeSans9pt7b, "T4 =       ");
        tft.setCursor(60, 80);
    tft.print(celsius4);

    
    showmsgXY(140, 80, 1, &FreeSans9pt7b, "T5 =       ");
        tft.setCursor(190, 80);
    tft.print(celsius5);

    
    showmsgXY(260, 80, 1, &FreeSans9pt7b, "T6 =      ");
        tft.setCursor(310, 80);
    tft.print(celsius6);
    
    
    showmsgXY(380, 80, 1, &FreeSans9pt7b, "      ");
tft.print((char)223);



    showmsgXY(20, 120, 1, &FreeSerif12pt7b, "Promedio de temperaturas ");
   
showmsgXY(10, 170, 1, &FreeSerif12pt7b, "Ti =     ª˚ ");
  tft.setCursor(60, 170);
     tft.print(promedio1);
     tft.print((char)42);          
showmsgXY(110, 170, 1, &FreeSerif12pt7b, "     ºC ");

showmsgXY(250, 170, 1, &FreeSerif12pt7b, "Tf = ª˚ ");
  tft.setCursor(300, 170);
     tft.print(promedio2);
     tft.print((char)42);
showmsgXY(350, 170, 1, &FreeSerif12pt7b, "  ºC ");

//Se visualizaran todos y cada uno de los datos calculados  al obtener las variables solicitadas.

     
    showmsgXY(20, 210, 1, &FreeSerif12pt7b, "Conductividad termica "); 
    showmsgXY(50, 240, 1, &FreeSerif12pt7b, "k =  ");
    tft.print(conductividad);
    showmsgXY(160, 240, 1, &FreeSerif12pt7b, "  W/m°C ");



showmsgXY(20, 270, 1, &FreeSerif12pt7b, "Calor transferido");
    showmsgXY(50, 300, 1, &FreeSerif12pt7b, "Q = ");
    tft.print(calor);
     showmsgXY(150, 300, 1, &FreeSerif12pt7b, "      W ");

     
   // showmsgXY(280, 280, 1, &FreeSerif12pt7b, "V = ");
    //tft.print(voltaje);
     //showmsgXY(350, 280, 1, &FreeSerif12pt7b, "      V ");
           
     
// Se cargan los diseños y los caracteres personalizados
 
    delay(10000);
}

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
    int16_t x1, y1;
    uint16_t wid, ht;
    tft.drawFastHLine(0, y, tft.width(), CYAN);
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(BLACK);
    tft.setTextSize(sz);
    tft.print(msg);
    delay(10);
}
