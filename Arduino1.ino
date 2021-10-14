#include <Password.h> // http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h>   // http://www.arduino.cc/playground/uploads/Code/keypad.zip


Password pwd = Password("1234");   // définition du mot de passe

boolean alarm = false;             // variable stockant l'état de l'alarme
                                   // false = alarme OFF | true = alarme ON
boolean intruder = false;          // variable stockant l'état de l'intrusion
                                   // false = pas d'intrus détecté | true = intrus détecté

#define ROWS 4                                                       //
#define COLS 3                                                       //
char keys[ROWS][COLS] =                                              //
{                                                                    //
  {'1','2','3'},                                                     //
  {'4','5','6'},                                                     // configuration
  {'7','8','9'},                                                     // du clavier
  {'*','0','#'}                                                      //
};                                                                   //
byte rowPins[ROWS] = {8, 7, 6, 5};                                   //
byte colPins[COLS] = {4, 3, 2};                                      //
                                                                     //
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //

void setup()
{
  kpd.addEventListener(kpdEvent);
}


void kpdEvent (KeypadEvent Key)
{
  switch (kpd.getState())
  {
    case PRESSED :
      switch (Key)
      {
        // appui sur '*' -> vérification de la saisie en cours
        case '*' : checkPassword(); break;
        // appui sur '#' -> réinitialisation de la saisie en cours
        case '#' : pwd.reset(); break;
        // sinon on ajoute le chiffre à la combinaison
        default  : pwd.append(Key); break;
      }
    default : break;
  }
}

void checkPassword(void)
{
  // on remet à zéro l'état du mot de passe
  intruder = false;
  // si le mot de passe est juste...
  if (pwd.evaluate())
  {
    // ...on met à jour l'état de l'alarme : ON>OFF / OFF>ON
    alarm = !alarm;
   
  }
  // si le mot de passe est faux...
  else
 {
   // ...on signale l'intrusion à la loop() qui déclenche l'alarme
   // jusqu'à ce que le bon mot de passe soit rentré
   intruder = true;
 }
 // on remet à zéro systématiquement après avoir vérifié pour ne pas avoir d'erreur
 pwd.reset();
}
