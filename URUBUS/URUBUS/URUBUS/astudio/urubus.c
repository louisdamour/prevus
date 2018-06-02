/*- Includes ---------------------------------------------------------------*/

#include "sys.h"
#include "phy.h"

/*- Prototypes -------------------------------------------------------------*/

char Lis_UART(void);
void Ecris_UART(char data);
void init_UART(void);
void SYS_Init(void);
void red(void);
void magenta(void);
void cyan(void);
void yellow(void);
void off(void);

/*- Variables --------------------------------------------------------------*/

uint8_t receivedWireless;	//cette variable deviendra 1 lorsqu'un nouveau paquet aura été recu via wireless (et copié dans "PHY_DataInd_t ind"
							//il faut la mettre a 0 apres avoir géré le paquet; tout message recu via wireless pendant que cette variable est a 1 sera jeté

PHY_DataInd_t ind; //cet objet contiendra les informations concernant le dernier paquet qui vient de rentrer

// IMPLEMENTATION
/*************************************************************************//**
*****************************************************************************/
static void APP_TaskHandler(void)
{
  char receivedUart = 0;

  receivedUart = Lis_UART();  
  if(receivedUart)		//est-ce qu'un caractere a été recu par l'UART?
  {
	  Ecris_UART(receivedUart);	//envoie l'echo du caractere recu par l'UART

	  if(receivedUart == 'a')	//est-ce que le caractere recu est 'a'? 
		{
		uint8_t demonstration_string[128] = "Hello World!"; //data packet bidon
		Ecris_Wireless(demonstration_string, 12); //envoie le data packet; nombre d'éléments utiles du paquet à envoyer
		}
  }

  if(receivedWireless == 1) //est-ce qu'un paquet a été recu sur le wireless? 
  {
	char buf[196];

//si quelqu'un a une méthode plus propre / mieux intégrée à proposer pour faire des "printf" avec notre fonction Ecris_UART, je veux bien l'entendre! 
	sprintf( buf, "\n\rnew trame! size: %d, RSSI: %ddBm\n\r", ind.size, ind.rssi );
	char *ptr = buf;
	while( *ptr != (char)0 )
		Ecris_UART( *ptr++ );
		
	sprintf( buf, "contenu: ");
	ptr = buf;
	while( *ptr != (char)0 )
		Ecris_UART( *ptr++ );

	ptr = ind.data;
	char i = 0;
	while( i < ind.size )
	{
		Ecris_UART( *ptr++ );
		i++;
	}

	sprintf( buf, "\n\r");
	ptr = buf;
	while( *ptr != (char)0 )
		Ecris_UART( *ptr++ );
	
	receivedWireless = 0; 
  }
}

//MAIN
/*****************************************************************************
*****************************************************************************/
int main(void)
{
  SYS_Init();
   
  while (1)
  {
    PHY_TaskHandler(); //stack wireless: va vérifier s'il y a un paquet recu
    APP_TaskHandler(); //l'application principale roule ici
  }
}

//FONCTION D'INITIALISATION
/*****************************************************************************
*****************************************************************************/
void SYS_Init(void)
{
receivedWireless = 0;
wdt_disable(); 
init_UART();
PHY_Init(); //initialise le wireless
PHY_SetRxState(1); //TRX_CMD_RX_ON
	
	DPDS0 = 0x1; // 4 mA
	DDRB = 0xE; //PB1, PB2, PB3 output
	PORTB |= 0xE; //Turn off LED
	off();
}

//FONCTIONS POUR L'UART
/*****************************************************************************
*****************************************************************************/
char Lis_UART(void)
{

char data = 0; 

	if(UCSR1A & (0x01 << RXC1))
	{
		data = UDR1;
	}
	
return data;
}

void Ecris_UART(char data)
{
	UDR1 = data;
	while(!(UCSR1A & (0x01 << UDRE1)));
}

void init_UART(void)
{
	//baud rate register = Fcpu / (16*baud rate - 1)
	//baudrate = 9600bps //s'assurer que la fuse CLKDIV8 n'est pas activée dans les Fuses, sinon ca donne 1200bps
	UBRR1H = 0x00;
	UBRR1L = 53;
	
	UCSR1A = 0x00;
	UCSR1B = 0x18; //receiver, transmitter enable, no parity
	UCSR1C = 0x06; //8-bits per character, 1 stop bit
}


//FONCTIONS POUR RGB
/*****************************************************************************
*****************************************************************************/

void red()
{
	PORTB |= 0x2;
	PORTB &= ~0xC; 
}

void magenta()
{
	PORTB |= 0xA;
	PORTB &= ~0x4;
}

void cyan()
{
	PORTB |= 0xC;
	PORTB &= ~0x2;
}

void yellow()
{
	PORTB |= 0x6;
	PORTB &= ~0x8;
}

void off()
{
	PORTB &= ~0xE;
}