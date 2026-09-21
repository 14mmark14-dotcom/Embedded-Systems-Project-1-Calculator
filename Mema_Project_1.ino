#define BUFFER_SIZE 32
char inputBuffer[BUFFER_SIZE];




void setup() {
  Serial.begin(9600);
  Serial.println("This is a basic calculator that can perform four operations:");
  Serial.println();
  Serial.println("To Add, use the + operator, (ex. 5+4)");
  Serial.println("To Subtract, use the - operator, (ex. 54-2)");
  Serial.println("To Multiply, use the * operator. (ex. 5*8)");
  Serial.println("To Divide, use the / operator. (ex. 74/32)");
  Serial.println();
  Serial.println("Enter desired calculation into the message box above.");
  Serial.println();
}

void loop() {
  if (Serial.available() > 0) {
    int inputLength = Serial.readBytesUntil('\n', inputBuffer, BUFFER_SIZE - 1);
    inputBuffer[inputLength] = '\0';

    //char for operator, int for its slot
    char op = '\0';
    int opSlot = -1;

    //finds the operator and what slot of inputBuffer its in
    for (int i = 1; i < inputLength; i++) {
      if (inputBuffer[i] == '+' || 
          inputBuffer[i] == '-' ||
          inputBuffer[i] == '*' ||
          inputBuffer[i] == '/') {
        op = inputBuffer[i];
        opSlot = i;
        break;
      }
    }
    if (opSlot == -1) {
      Serial.println("Error: operator not found. Please use +, -, *, or /");
      Serial.println();
    }

    //atof to get floats of both input values
    else {
      float value1 = atof(&inputBuffer[0]);
      float value2 = atof(&inputBuffer[opSlot + 1]);

      float answer = 0;
      //bool for handling divide by 0
      bool real = true;
    
      //switch for the calculations
      switch (op) {
        case '+':
          answer = value1 + value2;
          break;

        case '-':
          answer = value1 - value2;
          break;

        case '*':
          answer = value1 * value2;
          break;

        case '/':
          if (value2 == 0) {
            Serial.println("You divided by 0! The universe explodes now :(");
            Serial.println();
            real = false;
          } else {
            answer = value1 / value2;
          }
          break;

        default:
          Serial.println("Unexpected error encountered.");
          Serial.println();
          real = false;
           break;
      }

      //print out answer
      if (real){
        Serial.print(inputBuffer);
        Serial.print(" = ");
        Serial.println(answer, 3);
        Serial.println();
      }
    }
  }
}
