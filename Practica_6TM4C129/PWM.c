
#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
   SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo PWM0 pag 354 ------------    Se habilita reloj del modulo 0   
    SYSCTL->RCGCGPIO |= (1<<1); //Habilitar reloj de GPIO Puerto B  pin 4 (Solo se esta poniendo 1 del puerto b)   - Pag 1233
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); //Control de registros ya sea por GPIO o Otros Pag 672    //ESTO SI SE COMENTA
    SYSCTL->RCC |=(1<<20);  //Activamos USEPWMDIV para dividir la señal del reloj 
    SYSCTL->RCC &= 0xFFF0FFFF; //Indicamos en los pines 17-19 que se divida entre 2
    
    GPIOB->AFSEL |= (1<<4); //Indicamos que queremos una funcion alterna en el pin b4 
    GPIOB->PCTL |= 0x00040000; //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    //Aqui habilitamos la funcion 4 del pin PB4 - en el port mux 4 
    //Se usa el enmascaramiento porque no tiene valores por default 

    GPIOB->DEN |= (1<<4); // para decirle al pin 4 que es digital Pag 682
    // PWM0->CC &= ~(1<<8);  //Enable o Disable Divisor  Pag 1747 ------TIVA GRANDE ESTO SI SE COMENTA

    //El número indica el generador que se va a usar
    PWM1->_1_CTL &= ~(1<<0);  //Se deshabilita el generador 1 del PWM0 para poder configurarlo POR??
    PWM1->_1_GENA = 0x008C; //Se utilizara el generador A del generador 1 del 
    // El 8C es para decir que cuando coincidan, el otro baje para que se genere el PWM 
    //Se va a tener un contador descendente cuando el contador llegue al valor de la carga y va a bajar cuando sea igual 
    //al valor del comparador va a bajar  

    //SE COMIENZAN A HACER LOS CALCULOS 

    PWM1->_1_LOAD = 2500; //cuentas=fclk/fpwm  para 1khz cuentas = (25,000,000/10000)= 2500 ***Se fija a 2499 porque es 2500-1 pq inicia en 0
    //Se utilizo un duty cycle de 20%
    PWM1->_1_CMPB = 2000; // El duty cycle es de 80% (Es el 80% de 2499)
    PWM1->_1_CMPA = 2000; //El duty cycle es 80%
    
    PWM1->_1_CTL |= (1<<0);// Se habilita el generador 1 del PWM0
    PWM1->ENABLE = (1<<2); //habilitar el PWM2EN (Es ese porque es el modulo 0 generador 1) bloque pa que pase Pag 1247
    //La señal pwm1A' generada se pasa al pin MnPWM2
 
}
