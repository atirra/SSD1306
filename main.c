/*******************************************************************************
 * File:        main.c
 * Project:     SSD1306 
 * Author:      Nicolas Meyertöns
 * Version:     
 * Web:         http://pic-projekte.de
 ******************************************************************************/

#include <xc.h>
#include <stdbool.h>
#include "main.h"
#include "lcd.h"

#pragma config FOSC = INTIO67       // Internal oscillator block
#pragma config PWRTEN = ON          // Power up timer enabled
#pragma config BOREN = OFF          // Brown-out Reset disabled
#pragma config WDTEN = OFF          // Watch dog timer is always disabled
#pragma config MCLRE = INTMCLR      // MCLR disabled
#pragma config LVP = OFF            // Single-Supply ICSP disabled

/*******************************************************************************
 * Diverse Einstellungen zum PIC (IO, Takt, ...)
 */

void initPIC(void)
{
    LATBbits.LB0 = 1;
    
    TRISA = 0x00;
    TRISB = 0x01;                   // RB0 Eingang
    TRISC = 0x10;                   // C4 Eingang
    TRISD = 0x03;                   // D0,D1 Eingänge
    TRISE = 0x00;

    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    ANSELD = 0x00;
    ANSELE = 0x00;

    OSCCON2bits.MFIOSEL = 0;        // 111: 16 MHz
    OSCCONbits.IRCF2 = 1;           // 110:  8 MHz <-- aktiv
    OSCCONbits.IRCF1 = 1;           // 101:  4 MHz
    OSCCONbits.IRCF0 = 0;           // 100:  2 MHz
}

/*******************************************************************************
 * Durchführen sämtlicher Initialisierungen beim Bootvorgang
 */

void initAll (void)
{
    initPIC();
    initI2C();
}


void delayMS(uint16_t ms)
{
    uint16_t k=0;
    
    for(k=0; k<ms; k++)
    {
        __delay_ms(1);
    }
}

/*******************************************************************************
 * Main Routine
 */

void main (void)
{
    uint16_t k = 0;
    
    /*Alle Initialisierungen durchführen*/
    initAll();

    lcd_init();
    
    fb_draw_string(0,0,"SSD1306");
    fb_draw_string(0,1,"pic-projekte.de");
    fb_show();
    
    /*Endlosschleife*/
    while(1)
    {   
    }
}