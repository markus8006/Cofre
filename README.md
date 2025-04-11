## Codigo para cofre

Estou estudando sobre eletrônica embarcada e tive que fazer tal atividade
O projeto funciona fisicamente mas no simulador não funciona, há muito ruido no encoder

# 🔐 Cofre Eletrônico com Senha Rotativa - Arduino

Projeto de cofre eletrônico que utiliza um **encoder rotativo** para entrada de senha, com feedback via **LCD**, **LEDs**, **servo motor** e **buzzer**. Desenvolvido para o **Arduino Uno**, com simulação compatível no **Wokwi**.

---

## 🧰 Componentes Utilizados

| Componente          | Quantidade | Função                                 |
|---------------------|------------|----------------------------------------|
| Arduino Uno         | 1          | Microcontrolador                       |
| Encoder KY-040      | 1          | Entrada de senha (rotativo + botão)    |
| LCD 16x2 I2C        | 1          | Exibe informações (senha/tentativas)   |
| Servo Motor         | 1          | Simula abertura do cofre               |
| LED Vermelho        | 1          | Indica erro na senha                   |
| LED Verde           | 1          | Indica senha correta                   |
| Buzzer              | 1          | Alarme de bloqueio                     |
| Jumpers             | Vários     | Conexões                               |

---

## ⚙️ Funcionamento

1. **Gire o encoder:**
   - **Sentido horário**: adiciona `'A'` à senha.
   - **Sentido anti-horário**: adiciona `'B'`.

2. **Pressione o botão** do encoder:
   - A senha digitada é enviada e comparada com a senha correta.
   - Feedback visual e sonoro é fornecido com LEDs, buzzer e LCD.
   - Se acertar, o servo motor "abre o cofre".
   - Após 3 erros, o sistema bloqueia temporariamente com o alarme.

---

## 🔢 Senha Padrão

```cpp
String senhaCorreta = "AABBA";
```
---

## 📜 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

