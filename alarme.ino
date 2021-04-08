#include <LiquidCrystal.h>   
#include <Keypad.h>


int var = 0; 					
char senha[5];
char nova_senha[5];
char contra_senha[5] = "1234";
bool ativado;
bool pir;
char modo;

int volta = 1;
  
char key;
const byte filas = 4; 		//numero de filas.
const byte colunas = 4; 		//numero de colunas.

char tecla[filas][colunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_filas[filas] = {7, 6, 5, 4}; 		//declaração dos pinos ligados as filas
byte pin_colunas[colunas] = {3, 2, 1, 0}; 	//declaração dos pinos ligados as colunas

Keypad keypad = Keypad( makeKeymap(tecla), pin_filas, pin_colunas, filas, colunas );
LiquidCrystal lcd(8,9,10,11,12,13); //D7,D6,D4,E,RS

#define pinPIR 14
#define pinLED 15


void setup()
{
  pinMode(pinPIR, INPUT);
  lcd.begin(16,2); //LCD (16 COLUNAS e 2 FILAS)
  lcd.setCursor(0,0);
  ativado = 0;
  modo = 'D';
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("DESATIVADO");
  	
}
  
void loop()
{
  key = keypad.getKey();
  
  // modo de validação de ativação ou desativação
  if (modo == 'S') { 
    
    if (key) {
      
      lcd.setCursor(6 + var, 1);
      lcd.print('*');	//imprimir o caracter * no lcd
      senha[var] = key;
      var++;
    }  
    if (var == 4) {
      
      if (!strcmp(senha, contra_senha))
      {
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("senha valida");
        delay(3000);
        
        if (ativado) {
          ativado = 0;
          modo = 'D';
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print("DESATIVADO");
        }
        else {
          ativado = 1;
          modo = 'A';
          lcd.clear();
    	  lcd.setCursor(5,0);
    	  lcd.print("ATIVADO");
        }
      }
      else {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("senha invalida");
        delay(3000);
        
        if (ativado) {
          modo = 'A';
          lcd.clear();
    	  lcd.setCursor(4,0);
    	  lcd.print("ATIVADO");
        }
        else {
          modo = 'D';
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print("DESATIVADO");
        }
      }
      var = 0;

    }

  }
  
  // modo de alteração de senha
  if (modo == 'N') {
    
    if (key) {
      
      lcd.setCursor(6 + var, 1);
      lcd.print('*');	//imprimir o caracter * no lcd
      senha[var] = key;
      var++;
    }  
    if (var == 4) {
      
      if (volta == 2) {
        if (!strcmp(nova_senha, senha))
        {
          strcpy(contra_senha, senha);
          
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("senha alterada");
          delay(3000);

          modo = 'D';
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print("DESATIVADO");
        }
        else {
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("não combinam");
          delay(3000);

          modo = 'D';
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print("DESATIVADO");
        }
        
      }
      if (volta == 1) {
        strcpy(nova_senha, senha);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Repita Senha:");
        volta = 2;
      }
      var = 0;

    }

  }
  
  // modo de validação de alteração de senha
  if (modo == '#') { 
    
    if (key) {
      
      lcd.setCursor(6 + var, 1);
      lcd.print('*');	//imprimir o caracter * no lcd
      senha[var] = key;
      var++;
    }  
    if (var == 4) {
    
      if (!strcmp(senha, contra_senha))
      {
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("senha valida");
        delay(3000);
        
        modo = 'N';
        volta = 1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Nova Senha:");
      }
      else {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("senha invalida");
        delay(3000);
        
        modo = 'D';
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("DESATIVADO");
      }
      var = 0;

    }

  }
  
  // modo ativado
  if (modo == 'A') {
    
    pir = digitalRead(pinPIR);
  
  	if (pir == HIGH) {
      digitalWrite(pinLED, HIGH);
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("ALARME!");
      delay(1000);
    }
    
    if (key) {
      if (key == 'D') {
        modo = 'S';
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Insira a Senha:");
      }
    }
  }
  
  // modo destivado
  if (modo == 'D') {
    
    digitalWrite(pinLED, LOW);
    
    if (key) {
      if (key == 'A') {
        modo = 'S';
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Insira a Senha:");
      }
      if (key == '#') {
        modo = '#';
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Insira a Senha:");
      }
    }
  } 
  
}
