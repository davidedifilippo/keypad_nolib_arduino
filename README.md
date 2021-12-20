# keypad_nolib_arduino

Nel programma si esegue la scansione rapida delle colonne del tastierino:

- si mette a GND la colonna c
- si controllano i livelli di tensione sui piedini di riga 1,2,3,4
- se il piedino r di input è basso allora è stato premuto il pulsante all'incrocio tra riga r e colonna c 
- si stampa sulla seriale il carattere corrispondente

