/*  MSP430F5529
    Author: Jacob Okun and Cameron Korzeniowski
    Created: November 5, 2018
    Last Updated: November 29, 2018*/

#include <msp430.h>
#include "stdint.h"
#include "stdlib.h"

#define testFlag 1  //test flags

//global values
uint8_t lowBit = 0, highBit = 0;
float ADC_Voltage, temp;
float voltage;
//initialization methods
void ADC(void);
void UART(void);
int state = 0;
int currentTemperature;
volatile float error;
volatile float previousError;
volatile int derivative;
volatile int integral;
volatile int kp = 10;
volatile int ki = 0;
volatile int kd = 0;
volatile float dt = 0.01;
float clkFrequency = 1000000.0;
int target = 30;
int minpwm = 1;
int maxpwm = 255;
int pwm = 0;

int main(void)
{
  P1DIR |= BIT3;
  P1OUT |= BIT3; //sets PWM on initially

  WDTCTL = WDTPW + WDTHOLD; //stops watchdog timer

  TA0CCTL1 = CCIE;
  TA0CTL = TASSEL_1 + MC_1 + ID_0 + TAIE + TAIFG;   //SMCLK up mode, clear flag
  TA0CCR1 = 64;
  TA0CCR0 = 255;

ADC();
UART();

  while (1)
  {
    ADC12CTL0 |= ADC12SC;

    lowBit = ADC12MEM0;
    highBit = ADC12MEM0 >> 8;
    voltage = ADC12MEM0;
    ADC_Voltage = (voltage/4095) * 3.3;

    if((ADC_Voltage < 1.74))
    {
      temperature= -((165000-(171225*ADC_Voltage))/(2849*ADC_Voltage)); // Temperature Range: 15-30
    }
    else if((ADC_Voltage >= 1.74)&&( ADC_Voltage < 2.22))
    {
      temperature= -((330000-(262460*ADC_Voltage))/(2729*ADC_Voltage)); // Temperature Range: 30-45
    }
    else if((ADC_Voltage >= 2.22)&&( ADC_Voltage < 2.59))
    {
       temperature= -((330000-(205960*ADC_Voltage))/(1383*ADC_Voltage)); // Temperature Range: 45-60
    }
    else if((ADC_Voltage >= 2.59)&&(ADC_Voltage < 2.84))
        {
           temperature= -((330000-(169120*ADC_Voltage))/(737*ADC_Voltage)); // Temperature Range: 45-60
        }
    else if((ADC_Voltage >= 2.84))
          {
             temperature= -((330000-(145640*ADC_Voltage))/(411*ADC_Voltage)); // Temperature Range: 45-60
          }

    currentTemperature = temperature;   //load temperature
    error = target - currentTemperature;    //find error
    integral = integral + 1 * error * dt;   // find integral
    derivative = (error - previousError) / dt;  //find derivative
    pwm = (kp * error) + (ki * integral) + (kd * derivative);   //find PWM
    previousError = error;  //store last error
    if (error > 1){pwm = 1;}
    if (error == 0){pwm = 1;}
    TA0CCR1 = pwm;

#if testFlag == 1
         while (!(UCA1IFG&UCTXIFG));           // USCI_A0 TX buffer ready?
                      UCA1TXBUF = (uint8_t)temperature;
#elif testFlag == 0
    while (!(UCA1IFG&UCTXIFG));           // USCI_A0 TX buffer ready?
              UCA1TXBUF = highBit;    // TX -> RXed character

    while (!(UCA1IFG&UCTXIFG));         // USCI_A0 TX buffer ready?
              UCA1TXBUF = lowBit;    // TX -> RXed character
#endif
#if testFlag == 1
#endif
              __delay_cycles(1000);

              __bis_SR_register(GIE);       // Enter LPM0, interrupts enabled
    __no_operation();                       // For debugger
  }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    if (ADC12MEM0 >= 0x7ff)                 // ADC12MEM = A0 > 0.5AVcc?
      P1OUT |= BIT0;                        // P1.0 = 1
    else
      P1OUT &= ~BIT0;                       // P1.0 = 0
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)

{
    while(!(UCA1IFG & UCTXIFG));
    target = UCA1RXBUF;

}
void UART(){
    P4SEL |= BIT4+BIT5;
    P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 TXD/RXD
    UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCA1CTL1 |= UCSSEL_2;                     // SMCLK
    UCA1BR0 = 6;                              // 1MHz 9600 (see User's Guide)
    UCA1BR1 = 0;                              // 1MHz 9600
    UCA1MCTL |= UCBRS_0 + UCBRF_13 +UCOS16;
    UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    UCA1IE |= UCRXIE;// P1.0 output
}
void ADC(){
    ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP;                     // Use sampling
    ADC12IE = 0x01;                           // Enable interrupt
    ADC12CTL0 |= ADC12ENC;
    P6SEL |= 0x01;                            // P6.0 ADC option select
    P1DIR |= 0x01;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR (void) //CONTROLS PWM for the fan
{
switch(TA0IV)
    {

    case 2: //Case 2 defines interrupt on CCR1

            P1OUT &= ~BIT3;     //turn LED off for CCR1 interrupt
            break;

    case 14: //Case 2 defines interrupt on CCR0
        P1OUT |= BIT3;     //turn LED off for CCR0 interrupt
        break;
    }
}

