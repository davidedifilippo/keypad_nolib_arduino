## keypad 4x4

Nel programma si esegue la scansione rapida delle colonne del tastierino:

- si mette a GND la colonna c
- si controllano i livelli di tensione sui piedini di riga 1,2,3,4
- se il piedino r di input è basso allora è stato premuto il pulsante all'incrocio tra riga r e colonna c 
- si stampa sulla seriale il carattere corrispondente

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

Partendo dalla prima colonna e si mettono a livello basso le tensioni di colonna tramite digitalWrite una per volta. Per la colonna c si legge lo stato delle varie righe r tramite digtalRead. Se una delle tensioni di riga è a livello basso è stato premuto il pulsante all'incrocio tra colonna c e riga r. 

    // Mappa dei caratteri sul tastierino
    const char keymap[numRows][numCols] = 
    {
       { '1', '2', '3' , 'A' } ,
       { '4', '5', '6' , 'B' } ,
       { '7', '8', '9' , 'C' } ,
       { '*', '0', '#' , 'D' }
    };

