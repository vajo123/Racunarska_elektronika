#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

byte KARAKTER_LEVO_STOPALO_DEO_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001};
byte KARAKTER_LEVO_STOPALO_DEO_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B00000};
byte KARAKTER_DESNO_STOPALO_DEO_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00000};
byte KARAKTER_DESNO_STOPALO_DEO_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000};
byte KARAKTER_GRANA_DEO_1[8] = {B00000, B00100, B00100, B10100, B10100, B11100, B00100, B00100};
byte KARAKTER_GRANA_DEO_2[8] = {B00100, B00101, B00101, B10101, B11111, B00100, B00100, B00100};
byte KARAKTER_PTICIJI_KRILATI_DEO_1[8] = {B00001, B00001, B00001, B00001, B01001, B11111, B00000, B00000};
byte KARAKTER_PTICIJI_KRILATI_DEO_2[8] = {B00000, B10000, B11000, B11100, B11110, B11111, B00000, B00000};

// Definisanje promenljivih
int broj_zivota = 3; // Početni broj života
int skor = 0;
int pozicija_dino_stopala_1 = 1;
int pozicija_dino_stopala_2 = 2;
int pozicija_dino_visina = 1;
unsigned long vreme = 0; // Za korišćenje funkcije millis umesto delay
int period = 100; // Period u milisekundama
int flag = 1;
int pozicija_grane_visina = 0;
int pozicija_grane_kolona = 13;
unsigned long vreme_za_grane = 0;
int a = 0;
int b = 1;
int c = 2;
int d = 0;
unsigned long vreme_za_poen = 0; 
int poeni = 0;
int poeni_drugi = 0;
int slucajni_broj = 1;
int kolona_ptica = 13;
int kolona_1 = 0;
int kolona_2 = 0;
int trenutni_signal = 0;
int prethodni_signal = 0;
int aceleracija = 5;

void setup() {
  lcd.begin(16, 2);               
  lcd.createChar(0, KARAKTER_PTICIJI_KRILATI_DEO_1);      
  lcd.createChar(1, KARAKTER_PTICIJI_KRILATI_DEO_2);               
  lcd.createChar(2, KARAKTER_LEVO_STOPALO_DEO_1);      
  lcd.createChar(3, KARAKTER_LEVO_STOPALO_DEO_2);          
  lcd.createChar(4, KARAKTER_DESNO_STOPALO_DEO_1);      
  lcd.createChar(5, KARAKTER_DESNO_STOPALO_DEO_2);          
  lcd.createChar(6, KARAKTER_GRANA_DEO_1);      
  lcd.createChar(7, KARAKTER_GRANA_DEO_2);
} 

void loop() {
  if (millis() > vreme + period) {		
    vreme = millis();
    if (flag == 1) {
      flag = 2;
    } else if (flag == 2) {
      flag = 1;
    }  
  }  
  
  if (millis() > vreme_za_grane + period) {			
    vreme_za_grane = millis();
    pozicija_grane_kolona = pozicija_grane_kolona - 1;
    
    if (pozicija_grane_kolona < 0) {
      pozicija_grane_kolona = 13;  
      period = period - aceleracija;
      if(period < 50)
        period = 50;
      
      slucajni_broj = random(0, 3);
    }
      
    int f = pozicija_grane_kolona + 1;
    lcd.setCursor(f, 1);	// Čišćenje dole
    lcd.print(" ");    
      
    f = pozicija_grane_kolona + 1;
    lcd.setCursor(f, 0);	// Čišćenje gore
    lcd.print(" ");   
      
    lcd.setCursor(0, 1);	// Čišćenje dole
    lcd.print(" ");
      
    lcd.setCursor(0, 0);					
    lcd.print(" "); 

    a = 1;
  }

  if (d == 0) {
    if (flag == 1) {  
      lcd.setCursor(pozicija_dino_stopala_1, pozicija_dino_visina); 
      lcd.write(byte(2));
      lcd.setCursor(pozicija_dino_stopala_2, pozicija_dino_visina);
      lcd.write(byte(3));
    }
    if (flag == 2) {
      lcd.setCursor(pozicija_dino_stopala_1, pozicija_dino_visina); 
      lcd.write(byte(4));
      lcd.setCursor(pozicija_dino_stopala_2, pozicija_dino_visina);
      lcd.write(byte(5));
    }
  }
  
  if (a == 1) {
    if (slucajni_broj == 1) {
      pozicija_grane_visina = 1;
      //lcd.createChar(6, KARAKTER_GRANA_DEO_1);
      lcd.setCursor(pozicija_grane_kolona, pozicija_grane_visina); 
      lcd.write(byte(6));
    } else if (slucajni_broj == 2) {
      pozicija_grane_visina = 1;
      //lcd.createChar(7, KARAKTER_GRANA_DEO_2);
      lcd.setCursor(pozicija_grane_kolona, pozicija_grane_visina);
      lcd.write(byte(7));
    } else {
      kolona_ptica = pozicija_grane_kolona;
      kolona_ptica = kolona_ptica - 1;
      pozicija_grane_visina = 0;
      //lcd.createChar(6, KARAKTER_PTICIJI_KRILATI_DEO_1);
      lcd.setCursor(kolona_ptica, pozicija_grane_visina); 
      lcd.write(byte(0));
          
      //lcd.createChar(7, KARAKTER_PTICIJI_KRILATI_DEO_2);  
      lcd.setCursor(pozicija_grane_kolona, pozicija_grane_visina); 
      lcd.write(byte(1));   
    }
    
    a = 0;
  }

  if (digitalRead(13) == HIGH && (pozicija_grane_kolona == 1 || pozicija_grane_kolona == 2 || kolona_ptica == 1 || kolona_ptica == 2) && pozicija_grane_visina == 0) {
    broj_zivota--; // Smanji broj života nakon sudara
    lcd.clear();
    lcd.setCursor(5, 0);					
    lcd.print("UDAR!!");
    lcd.setCursor(4, 1);
    lcd.print(String(broj_zivota) + " zivota");
    delay(2000);
    lcd.clear();
    pozicija_grane_kolona = 14;
    period += 20;
    if(period > 100)
      period = 100;
    
    if (broj_zivota <= 0) {
      	skor = poeni_drugi * 100 + poeni;
        lcd.setCursor(3, 0);					
        lcd.print("KRAJ IGRE!");
      	lcd.setCursor(0, 1);
      	lcd.print("SKOR: " + String(skor));
      	
      	
        while (true) {
            // Loop će ostati ovde i prikazivati "KRAJ IGRE" sve dok ne resetujete sistem
        }
    }
  }

  if ((pozicija_grane_kolona == b || pozicija_grane_kolona == c) && pozicija_grane_visina == 1) {   
    broj_zivota--; // Smanji broj života nakon sudara
    lcd.clear();
    lcd.setCursor(5, 0);					
    lcd.print("UDAR!!");
    lcd.setCursor(4, 1);
    lcd.print(String(broj_zivota) + " zivota");
    delay(2000);
    lcd.clear();
    pozicija_grane_kolona = 15;
    period += 20;
    if(period > 100)
      period = 100;
    
    if (broj_zivota <= 0) {
      	skor = poeni_drugi * 100 + poeni;
        lcd.setCursor(3, 0);					
        lcd.print("KRAJ IGRE!");
      	lcd.setCursor(0, 1);
      	lcd.print("SKOR: " + String(skor));
      	
      	
        while (true) {
            // Loop će ostati ovde i prikazivati "KRAJ IGRE" sve dok ne resetujete sistem
        }
    }
  }

  if (digitalRead(13) == HIGH) {
    b = 50; 
    c = 50;

    if (d == 0) {
      lcd.setCursor(0, 1);		 
      lcd.print("    ");   
    }
    d = 1; 

    lcd.setCursor(pozicija_dino_stopala_1, 0); 
    lcd.write(byte(2));
    lcd.setCursor(pozicija_dino_stopala_2, 0);
    lcd.write(byte(3));   
  } else {    
    b = 1;		
    c = 2;
    d = 0;
  }

  // Kreiranje kašnjenja za poene
  if (millis() > vreme_za_poen + period) {		
    vreme_za_poen = millis();
    lcd.setCursor(14, 1);					
    lcd.print(poeni);
    
    poeni = poeni + 1;
    if (poeni == 100) {
      poeni = 0;
      poeni_drugi = poeni_drugi + 1;
      if (poeni_drugi == 100) {
        poeni_drugi = 0;
      }
    }
  }  

  lcd.setCursor(14, 1);					
  lcd.print(poeni);
  lcd.setCursor(14, 0);					
  lcd.print(poeni_drugi);

  // Detekcija promene stanja na tasteru
  trenutni_signal = digitalRead(13);
  if (trenutni_signal != prethodni_signal && trenutni_signal == 0) {
    lcd.setCursor(1, 0);					
    lcd.print("  "); 
  }
  prethodni_signal = trenutni_signal;
  
  
  // DIZAJNIRANO OD STRANE CREA ELECTRONICA 
  // https://www.youtube.com/watch?v=yki4MBmUFI4&t=2s
}
