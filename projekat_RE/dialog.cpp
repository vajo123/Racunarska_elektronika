#include "dialog.h"
#include "ui_dialog.h"

unsigned char KARAKTER_LEVO_STOPALO_DEO_1[8] = {0b00000, 0b00000, 0b00010, 0b00010, 0b00011, 0b00011, 0b00001, 0b00001};
unsigned char KARAKTER_LEVO_STOPALO_DEO_2[8] = {0b00111, 0b00111, 0b00111, 0b00100, 0b11100, 0b11100, 0b11000, 0b00000};
unsigned char KARAKTER_DESNO_STOPALO_DEO_1[8] = {0b00000, 0b00000, 0b00010, 0b00010, 0b00011, 0b00011, 0b00001, 0b00000};
unsigned char KARAKTER_DESNO_STOPALO_DEO_2[8] = {0b00111, 0b00111, 0b00111, 0b00100, 0b11100, 0b11100, 0b11000, 0b01000};
unsigned char KARAKTER_GRANA_DEO_1[8] = {0b00000, 0b00100, 0b00100, 0b10100, 0b10100, 0b11100, 0b00100, 0b00100};
unsigned char KARAKTER_GRANA_DEO_2[8] = {0b00100, 0b00101, 0b00101, 0b10101, 0b11111, 0b00100, 0b00100, 0b00100};
unsigned char KARAKTER_PTICIJI_KRILATI_DEO_1[8] = {0b00001, 0b00001, 0b00001, 0b00001, 0b01001, 0b11111, 0b00000, 0b00000};
unsigned char KARAKTER_PTICIJI_KRILATI_DEO_2[8] = {0b00000, 0b10000, 0b11000, 0b11100, 0b11110, 0b11111, 0b00000, 0b00000};


const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

// Definisanje promenljivih
int broj_zivota = 3; // Početni broj života
int pozicija_dino_stopala_1 = 1;
int pozicija_dino_stopala_2 = 2;
int pozicija_dino_visina = 1;
unsigned long vreme = 0; // Za korišćenje funkcije millis umesto delay
int period = 400; // Period u milisekundama
int flag = 1;
int pozicija_grane_visina = 0;
int pozicija_grane_kolona = 13;
unsigned long vreme_za_grane = 0;
int a = 1;
int b = 1;
int c = 2;
int d = 0;
unsigned long vreme_za_poen = 0;
int poeni = 0;
int poeni_drugi = 0;
int slucajni_broj = 1;
int kolona_ptica = 13;
int ukp_poeni = 0;
int aceleracija = 50;

int lcd;
QString pom;
QString poruka;

QTimer *timer;
char buffer[20];

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    if(wiringPiSetup() == -1)
            exit(1);

    lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2,D3, D0, D1, D2, D3);
    lcdClear(lcd);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(lcdPrint()));
    timer->start(period);

    lcdCharDef (lcd, 0, KARAKTER_PTICIJI_KRILATI_DEO_1);
    lcdCharDef (lcd, 1, KARAKTER_PTICIJI_KRILATI_DEO_2);
    lcdCharDef (lcd, 2, KARAKTER_LEVO_STOPALO_DEO_1);
    lcdCharDef (lcd, 3, KARAKTER_LEVO_STOPALO_DEO_2);
    lcdCharDef (lcd, 4, KARAKTER_DESNO_STOPALO_DEO_1);
    lcdCharDef (lcd, 5, KARAKTER_DESNO_STOPALO_DEO_2);
    lcdCharDef (lcd, 6, KARAKTER_GRANA_DEO_1);
    lcdCharDef (lcd, 7, KARAKTER_GRANA_DEO_2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QString styleSheet = "background-image: url(/home/raspberry/Desktop/Vajo/qt/jump_dino/poz.png);";

    setStyleSheet(styleSheet);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::lcdPrint()
{

    if(broj_zivota == 3){
        ui->label->setPixmap(QPixmap(":/slike/zq.png"));
        ui->label_2->setPixmap(QPixmap(":/slike/zq.png"));
        ui->label_3->setPixmap(QPixmap(":/slike/zq.png"));
    }
    else if(broj_zivota == 2){
        ui->label_3->clear();
    }
    else if(broj_zivota == 1){
        ui->label_2->clear();
    }
    else if(broj_zivota == 0){
        ui->label->clear();

    }

    if(broj_zivota > 0){
        ukp_poeni = poeni + 100 * poeni_drugi;
        pom = QString::number(ukp_poeni);
        ui->lineEdit->setText(pom);


        //pomeranje noge dinosaurusa
        if (flag == 1) {
            flag = 2;
        }
        else if (flag == 2) {
            flag = 1;
        }
        if (d == 0) {
            if (flag == 1) {
                    lcdPosition(lcd, pozicija_dino_stopala_1, pozicija_dino_visina);
                    lcdPutchar (lcd, 2);
                    lcdPosition(lcd, pozicija_dino_stopala_2, pozicija_dino_visina);
                    lcdPutchar (lcd, 3);
                }
                if (flag == 2) {
                    lcdPosition(lcd, pozicija_dino_stopala_1, pozicija_dino_visina);
                    lcdPutchar (lcd, 4);
                    lcdPosition(lcd, pozicija_dino_stopala_2, pozicija_dino_visina);
                    lcdPutchar (lcd, 5);
                }
        }

        //pomeranje prepreke u levo
        pozicija_grane_kolona = pozicija_grane_kolona - 1;

        if (pozicija_grane_kolona < 0) {
            pozicija_grane_kolona = 13;
            period = period - aceleracija;
            if(period < 100)
                period = 100;

            timer->setInterval(period);
            slucajni_broj = random() % 3 + 1;
        }

        int f = pozicija_grane_kolona + 1;

        lcdPosition(lcd, 0, 1);	// Čišćenje dole
        lcdPrintf(lcd, " ");

        lcdPosition(lcd, 0, 0);
        lcdPrintf(lcd, " ");
        if (slucajni_broj == 1) {
            lcdPosition(lcd, f, 1);	// Čišćenje dole
            lcdPrintf(lcd, " ");

            pozicija_grane_visina = 1;
            lcdPosition(lcd, pozicija_grane_kolona, pozicija_grane_visina);
            lcdPutchar (lcd, 6);
        } else if (slucajni_broj == 2) {
            lcdPosition(lcd, f, 1);	// Čišćenje dole
            lcdPrintf(lcd, " ");

            pozicija_grane_visina = 1;
            lcdPosition(lcd, pozicija_grane_kolona, pozicija_grane_visina);
            lcdPutchar (lcd, 7);
        } else {
            lcdPosition(lcd, f, 0);	// Čišćenje gore
            lcdPrintf(lcd, " ");

            kolona_ptica = pozicija_grane_kolona;
            kolona_ptica = kolona_ptica - 1;
            pozicija_grane_visina = 0;

            if(kolona_ptica >= 0){
                lcdPosition(lcd, kolona_ptica, pozicija_grane_visina);
                lcdPutchar (lcd, 0);
            }

            lcdPosition(lcd, pozicija_grane_kolona, pozicija_grane_visina);
            lcdPutchar (lcd, 1);
        }

        //poeni
        poeni = poeni + 1;
        if (poeni == 100) {
            poeni = 0;
            poeni_drugi = poeni_drugi + 1;
            if (poeni_drugi == 100) {
            poeni_drugi = 0;
            }
        }

        lcdPosition(lcd, 14, 1);
        sprintf(buffer, "%d", poeni);
        lcdPuts(lcd, buffer);

        lcdPosition(lcd, 14, 0);
        sprintf(buffer, "%d", poeni_drugi);
        lcdPuts(lcd, buffer);


        //provera sudara sa pticom
        if(d == 1 && (pozicija_grane_kolona == 1 || pozicija_grane_kolona == 2 || kolona_ptica == 1 || kolona_ptica == 2) && pozicija_grane_visina == 0){
            broj_zivota--; // Smanji broj života nakon sudara

            if (broj_zivota == 0) {
                lcdClear(lcd);
                lcdPosition(lcd, 3, 0);
                lcdPrintf(lcd, "KRAJ IGRE!");

                lcdPosition(lcd, 0, 1);
                sprintf(buffer, "REZULTAT: %d", ukp_poeni);
                lcdPuts(lcd, buffer);

                ui->label->clear();

                poruka = QString("Vas rezultat je: %1\n Za ponovnu igru pritisnite OK.").arg(ukp_poeni);

                QMessageBox::warning(this, "KRAJ IGRE", poruka);

                lcdClear(lcd);
                pozicija_grane_kolona = 14;
                period = 400;
                broj_zivota = 3;
                poeni = 0;
                poeni_drugi = 0;

            }
            else{
                lcdClear(lcd);
                lcdPosition(lcd, 5, 0);
                lcdPrintf(lcd, "UDAR!!");
                lcdPosition(lcd, 4, 1);
                char buffer[20];
                sprintf(buffer, "%d zivota", broj_zivota);
                lcdPuts(lcd, buffer);

                QThread::msleep(2000);
                lcdClear(lcd);
                pozicija_grane_kolona = 14;
                period += 100;
                if(period > 400)
                    period = 400;

            }
        }

        //provera sudara sa kaktusom
        if ((pozicija_grane_kolona == b || pozicija_grane_kolona == c) && pozicija_grane_visina == 1) {
            broj_zivota--; // Smanji broj života nakon sudara

            if (broj_zivota == 0) {
                lcdClear(lcd);
                lcdPosition(lcd, 3, 0);
                lcdPrintf(lcd, "KRAJ IGRE!");

                lcdPosition(lcd, 0, 1);
                sprintf(buffer, "REZULTAT: %d", ukp_poeni);
                lcdPuts(lcd, buffer);

                ui->label->clear();
                poruka = QString("Vas rezultat je: %1\n Za ponovnu igru pritisnite OK.").arg(ukp_poeni);

                QMessageBox::warning(this, "KRAJ IGRE", poruka);

                lcdClear(lcd);
                pozicija_grane_kolona = 14;
                period = 400;
                broj_zivota = 3;
                poeni = 0;
                poeni_drugi = 0;

            }
            else{

                lcdClear(lcd);
                lcdPosition(lcd, 5, 0);
                lcdPrintf(lcd, "UDAR!!");
                lcdPosition(lcd, 4, 1);
                char buffer[20];
                sprintf(buffer, "%d zivota", broj_zivota);
                lcdPuts(lcd, buffer);

                QThread::msleep(2000);
                lcdClear(lcd);
                pozicija_grane_kolona = 14;
                period += 100;
                if(period > 400)
                    period = 400;

            }

        }
    }


}

void Dialog::on_pushButton_pressed()
{

    b = 50;
    c = 50;

    if (d == 0) {
        lcdPosition(lcd, 0, 1);
        lcdPrintf(lcd, "    ");
    }
    d = 1;
    lcdPosition(lcd, pozicija_dino_stopala_1, 0);
    lcdPutchar (lcd, 2);
    lcdPosition(lcd, pozicija_dino_stopala_2, 0);
    lcdPutchar (lcd, 3);

    if((pozicija_grane_kolona == 1 || pozicija_grane_kolona == 2 || kolona_ptica == 1 || kolona_ptica == 2) && pozicija_grane_visina == 0){
        broj_zivota--; // Smanji broj života nakon sudara

        if (broj_zivota == 0) {
            lcdClear(lcd);
            lcdPosition(lcd, 3, 0);
            lcdPrintf(lcd, "KRAJ IGRE!");

            lcdPosition(lcd, 0, 1);
            sprintf(buffer, "REZULTAT: %d", ukp_poeni);
            lcdPuts(lcd, buffer);

            poruka = QString("Vas rezultat je: %1\n Za ponovnu igru pritisnite OK.").arg(ukp_poeni);

            QMessageBox::warning(this, "KRAJ IGRE", poruka);

            lcdClear(lcd);
            pozicija_grane_kolona = 14;
            period = 400;
            broj_zivota = 3;
            poeni = 0;
            poeni_drugi = 0;

        }
        else{

            lcdClear(lcd);
            lcdPosition(lcd, 5, 0);
            lcdPrintf(lcd, "UDAR!!");
            lcdPosition(lcd, 4, 1);
            char buffer[20];
            sprintf(buffer, "%d zivota", broj_zivota);
            lcdPuts(lcd, buffer);

            QThread::msleep(2000);
            lcdClear(lcd);
            pozicija_grane_kolona = 14;
            period += 100;
            if(period > 400)
                period = 400;
        }
   }

}

void Dialog::on_pushButton_released()
{

    lcdPosition(lcd, 1, 0);
    lcdPrintf(lcd, "  ");

    b = 1;
    c = 2;
    d = 0;

    if(broj_zivota > 0){

        if (flag == 1) {
            lcdPosition(lcd, pozicija_dino_stopala_1, pozicija_dino_visina);
            lcdPutchar (lcd, 2);
            lcdPosition(lcd, pozicija_dino_stopala_2, pozicija_dino_visina);
            lcdPutchar (lcd, 3);
        }
        if (flag == 2) {
            lcdPosition(lcd, pozicija_dino_stopala_1, pozicija_dino_visina);
            lcdPutchar (lcd, 4);
            lcdPosition(lcd, pozicija_dino_stopala_2, pozicija_dino_visina);
            lcdPutchar (lcd, 5);
        }
    }

    //provera sudara sa kaktusom
    if ((pozicija_grane_kolona == b || pozicija_grane_kolona == c) && pozicija_grane_visina == 1) {
        broj_zivota--; // Smanji broj života nakon sudara

        if (broj_zivota == 0) {
            lcdClear(lcd);
            lcdPosition(lcd, 3, 0);
            lcdPrintf(lcd, "KRAJ IGRE!");

            lcdPosition(lcd, 0, 1);
            sprintf(buffer, "REZULTAT: %d", ukp_poeni);
            lcdPuts(lcd, buffer);

            poruka = QString("Vas rezultat je: %1\n Za ponovnu igru pritisnite OK.").arg(ukp_poeni);

            QMessageBox::warning(this, "KRAJ IGRE", poruka);

            lcdClear(lcd);
            pozicija_grane_kolona = 14;
            period = 400;
            broj_zivota = 3;
            poeni = 0;
            poeni_drugi = 0;

        }
        else{

            lcdClear(lcd);
            lcdPosition(lcd, 5, 0);
            lcdPrintf(lcd, "UDAR!!");
            lcdPosition(lcd, 4, 1);
            char buffer[20];
            sprintf(buffer, "%d zivota", broj_zivota);
            lcdPuts(lcd, buffer);

            QThread::msleep(2000);
            lcdClear(lcd);
            pozicija_grane_kolona = 14;
            period += 100;
            if(period > 400)
                period = 400;
        }

    }

}
