#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define A 6            // CLK do encoder    
#define B 7            // DT do encoder  
#define botao 8        // SW do encoder
#define led_Erro 4     // LED vermelho
#define led_Acerto 3   // LED verde
#define buzzer 2       // Alarme
#define SERVO_PIN 11   // Pino do servo motor

// Inicializa LCD I2C com endereço 0x27 e dimensões 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Inicializa o objeto servo
Servo servoMotor;

int tentativas = 0;            // para limitar o número de tentativas
int pos;                       // para saber onde o encoder está inicialmente
int atual;                     // para verificar mudanças
int total_tentativas = 3;      // número máximo de tentativas
bool Fim = false;            // para verificar se as tentativas foram esgotadas
String senhaAtual = ""; 
String senhaCorreta = "AABBA"; // defina a senha de comparação

void setup() 
{
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(botao, INPUT);
  pinMode(led_Erro, OUTPUT);
  pinMode(led_Acerto, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  pos = digitalRead(A); // define a posição inicial do encoder
  Serial.begin(9600);    

  // Inicializa e configura o LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tentativa: ");
  lcd.print(tentativas);
  lcd.setCursor(0, 1);
  lcd.print("Senha:");

  // Inicializa o servo motor na posição fechada (0 graus)
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(0);
}

void loop() {
  atual = digitalRead(A); // atualiza a leitura do encoder

  if (atual != pos) {  // verifica se houve mudança no pino A
    if (digitalRead(B) != atual) {  
      Serial.println("Anti-horário");
      senhaAtual += "B"; // acrescenta "B" na senha
    } 
    else {  
      Serial.println("Horário"); 
      senhaAtual += "A"; // acrescenta "A" na senha
    }
    
    Serial.print("Senha atual: ");
    Serial.println(senhaAtual);
    pos = atual; // atualiza a posição para a próxima mudança  
    
    // Atualiza o LCD com a senha atual e tentativas
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tentativa: ");
    lcd.print(tentativas);
    lcd.setCursor(0, 1);
    lcd.print(senhaAtual);
  }

  if (digitalRead(botao) == HIGH) { // verifica se o botão foi pressionado para enviar a senha
    tentativas++; // incrementa as tentativas

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tentativa: ");
    lcd.print(tentativas);
    lcd.setCursor(0, 1);

    if (senhaAtual == senhaCorreta) {
      Serial.println("Senha Correta!");
      lcd.print("Senha Correta!");
      digitalWrite(led_Acerto, HIGH); 
      digitalWrite(led_Erro, LOW);
      
      // Aciona o servo motor para "abrir o cofre"
      servoMotor.write(90); // abre (por exemplo, 90 graus)
      delay(2000);
      servoMotor.write(0);  // retorna à posição fechada
      tentativas = 0;       // reseta as tentativas
    } 
    else {
      Serial.println("Senha Errada.");
      lcd.print("Senha Errada!");
      digitalWrite(led_Erro, HIGH); 
      digitalWrite(led_Acerto, LOW);
      
      if (tentativas >= total_tentativas) {
        Serial.println("FIM");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FIM de Tent.");
        lcd.setCursor(0, 1);
        lcd.print("Senha Incorreta");
        Fim = true; // sinaliza que esgotou as tentativas
      }
    }

    delay(2000); 
    digitalWrite(led_Erro, LOW);
    digitalWrite(led_Acerto, LOW);
    senhaAtual = "";  // reseta a senha atual

    if (Fim) {
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      Fim = false;
    }
  }

  delay(20);   
}
