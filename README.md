## keypad 4x4

Nel programma si esegue la scansione rapida delle colonne del tastierino:

- si mette a GND la colonna c
- si controllano i livelli di tensione sui piedini di riga 1,2,3,4
- se il piedino r di input è basso allora è stato premuto il pulsante all'incrocio tra riga r e colonna c 
- si stampa sulla seriale il carattere corrispondente

      int numRows = 4;
      int numCols = 4;
      int colPins[4] = {2,3,4,5};
      int rowPins[4] = {6,7,8,9};

## Fase di setup

Si impostano i piedini di colonna come OUTPUT e poi si mettono a 5V tramite l'istruzione digitalWrite.

     for (int column = 0; column < numCols; column++)
     {
       pinMode(colPins[column],OUTPUT);     // Setta i pin delle colonne come input
       digitalWrite(colPins[column],HIGH);  // Imposta le colonne a livello HIGH 
      }

Si impostano i piedini di riga come input

     for (int row = 0; row < numRows; row++)
     {
      pinMode(rowPins[row],INPUT);       // Imposta i pin di riga come input
      digitalWrite(rowPins[row],HIGH);   // Abilita sui pin di riga i resistori di pull up 
     }

la cosa strana è che sembrerebbe di impostare la tensione sul piedino di uscita a livello alto. In effetti con i piedini impostati come ingresso esiste la possibilità di collegare il piedino a 5V attraverso una resistenza interna da 10KOhm.
In questo modo però ogni volta che leggo la tensione sul piedino trovo HIGH.



## Fase di loop

Nel loop la chiamata:

     char key = getKey();
     
restituisce il carattere premuto dall'utente oppure il carattere nullo '\0'
      
       if( key != '\0') 
       {   
       Serial.print("Hai premuto: ");
       Serial.println(key);
      }
Se il carattere è diverso dal carattere nullo viene stampato sulla seriale.

## La funzione getKey()

In questa fuznione si controlla se è stato premuto uno dei tasti.

Tramite digitalWrite si mette a livello basso la colonna c del tastierino. 

     for(int c = 0; c < numCols; c++)  digitalWrite(colPins[c],LOW); 

Per la colonna c si legge lo stato delle varie righe r tramite digtalRead. 


     for(int r = 0; r < numRows; r++)      // Scorro tutte le righe
     {
     if(digitalRead(rowPins[r]) == LOW)  // rilevo tensione bassa solo se il tasto in posizione r,c è stato premuto 
     key = keymap[r][c];                 // Memorizzo quale sia il tasto premuto
     }


Se una delle tensioni di riga è a livello basso è stato premuto il pulsante all'incrocio tra colonna c e riga r. 

    // Mappa dei caratteri sul tastierino
    const char keymap[numRows][numCols] = 
    {
       { '1', '2', '3' , 'A' } ,
       { '4', '5', '6' , 'B' } ,
       { '7', '8', '9' , 'C' } ,
       { '*', '0', '#' , 'D' }
    };
    
  Si recupera la lattera e si restituisce al chiamante.

