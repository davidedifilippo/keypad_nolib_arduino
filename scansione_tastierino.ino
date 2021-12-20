const int numRows = 4;       // numero di righe
const int numCols = 4;       // numero di colonne
const int debounceTime = 20; // millisecondi necessari allo switch per diventare stabile

// Mappa dei caratteri sul tastierino
const char keymap[numRows][numCols] = 
{
  { '1', '2', '3' , 'A' } ,
  { '4', '5', '6' , 'B' } ,
  { '7', '8', '9' , 'C' } ,
  { '*', '0', '#' , 'D' }
};

// Definisco i pin connessi alle righe o alle colonne
const int rowPins[numRows] = {9, 8, 7, 6};   // Pin di arduino connessi ai pin 1,2,3,4 delle righe del keypad
const int colPins[numCols] = {5, 4, 3, 2};   // Pin di arduino connessi ai pin 5,6,7,8 delle colonne del keypad

void setup()
{
  Serial.begin(9600);
  for (int row = 0; row < numRows; row++)
  {
    pinMode(rowPins[row],INPUT);       // Imposta i pin di riga come input
    digitalWrite(rowPins[row],HIGH);   // Abilita sui pin di riga i resistori di pull up 
  }
  for (int column = 0; column < numCols; column++)
  {
    pinMode(colPins[column],OUTPUT);     // Setta i pin delle colonne come input
    digitalWrite(colPins[column],HIGH);  // Imposta le colonne a livello HIGH 
  }
}

void loop()
{
  char key = getKey();
  if( key != '\0') 
  {       
    // se il carattere non è '\0' allora ho premuto un pulsante
    Serial.print("Hai premuto: ");
    Serial.println(key);
  }
}

// funzione che restituisce il tasto premuto o '\0' se nessun tasto è digitato 
char getKey()
{
  char key = '\0';                                  // '\0' indica nessun tasto premuto

  for(int c = 0; c < numCols; c++)
  {
    digitalWrite(colPins[c],LOW);         // abbassa la tensione sulla colonna c 
    for(int r = 0; r < numRows; r++)      // Scorro tutte le righe
    {
      if(digitalRead(rowPins[r]) == LOW)  // rilevo tensione bassa solo se il tasto r,c è stato premuto 
      {
        delay(debounceTime);                     //attendo che il segnale si stabilizzi
        while(digitalRead(rowPins[r]) == LOW); // attendo che il tasto sia rilasciato
        key = keymap[r][c];               // Memorizzo quale sia il tasto premuto
      }
    }
    digitalWrite(colPins[c],HIGH);     // Fine controllo colonna c
  }
  return key;  // restituisce il tasto premuto oppure '\0'
}
