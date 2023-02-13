#include <graphics.h>

#include <conio.h>

#include<stdlib.h>

#include<time.h>

float  max_data = 0, a, b, entered = 0, c, o;
char str[50];
int n = 0, i, j, u, v;
int container[100];
float orig_data[100], mod_data[100];
int displays();
int main() {


    do {

        printf("How many data you want to enter?");
        scanf("%d", & n); //runs loop until n data between 1 t 12 is entered
        if (n > 12 || n == 0) {
            system("cls");
            if (n > 12) {

                printf("!!!Only upto 12 data can be entered!!!\n");
            } else {
                printf("!!!Data should be entered!!!\n");
            }
        }
    } while (n > 12 || n == 0);

    for (i = 0; i < n; i++) {
        printf("Enter data %d: ", i + 1);// Taking n data to be displayed
        scanf("%f", & orig_data[i]);
        if (max_data < orig_data[i]) {
            max_data = orig_data[i];// Store maxmimum data which will be further used in mathematical calculation
        }
    }
    if (max_data <= 100) {
        max_data = max_data + 0.00;//if max data is less than 100 then bar line of data varies from 0 to max data; say [10,20,30,40] then line vary from 0 to 40
    } else {
        max_data = max_data + 50.00;// bar line varies from 0 to max_data + 50; say[50,250,500,1000],then line ary from 0 to 10000
    }
    for (i = 0; i < n; i++) {
        container[i] = (rand() % 13) + 1;//container used to randomize the bar color and style; for n data n number is stored in container and number of container
        for (j = 0; j < i; j++) {        // is from 1 to 12;not making from 0 to 12 because 0 means black and empty fill
            if (container[i] == container[j]) {
                i--;//making sure that all the element in container are unique
            }
        }
    }

    for (i = 0; i < n; i++) {
        mod_data[i] = (float)(orig_data[i] / max_data) * 360.00;//making a suitable size of bar ,in our case there are 360 lines so 1 line represent 3.6
    }                                                           //say  [230,300,98,150,200] ---> [236.57,308.57,100.8,154.28,205.77]; 
																// and our line varies from 0 to 300+50 = 350
    int gd = DETECT, gm;
    initgraph( & gd, & gm, "C:\TC\BGI");
    displays();//display the data without sorting i.e display as ordere entered by user
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(200, 200, "PRESS ANY KEY TO SORT"); // hold the screen
    getch();
    cleardevice();
    displays();//same as above
    for (u = 0; u < n; ++u) {  // this is the basic program of sorting array in c

        for (v = u + 1; v < n; ++v) {

            if (mod_data[u] > mod_data[v]) {
                entered = 1;//indicating that it is swapping variable which is uded in display() function below
                a = mod_data[u];
                b = orig_data[u];
                c = container[u];
                mod_data[u] = mod_data[v];       // orig data along with modified and container is also sorted
                orig_data[u] = orig_data[v];
                container[u] = container[v];
                mod_data[v] = a;
                orig_data[v] = b;
                container[v] = c;
                displays();  //  display  data  swapping
                entered = 0;
            }
            // displays();

        }

        // displays();

    }
    displays();
}
int displays() {
    float x, x1 = 150, x2 = 200, y = 420;
    o = x;
    x = (n + 1) * 100;
    setcolor(YELLOW);
    rectangle(0, 30, x + 50, 450);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy((x + 50) / 2, 0, "DATA CHART");
    setlinestyle(SOLID_LINE, 0, 2);
    line(100, 420, 100, 40);
    line(100, 420, x, 420);
    line(90, 50, 100, 40);
    line(110, 50, 100, 40);
    line(x - 10, 410, x, 420);
    line(x - 10, 430, x, 420);
    outtextxy(75, 35, "Y");
    outtextxy(x + 10, 405, "X");
    outtextxy(80, 420, "O");
    settextstyle(2, HORIZ_DIR, 1);
    for (i = 0; i < 360; i++) {
        if (i % 5 == 0) {
            line(100, y, 95, y);
            line(100, y, 105, y);
        }
        y = y - 1;
    }
    if (entered == 1) {
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        sprintf(str, "%d and %d exchanged", int(orig_data[v]), int(orig_data[u]));
        outtextxy((x + 50) / 2, 460, str);

    }

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    for (i = 0; i < n; i++) {
        setfillstyle(container[i], container[i]);
        bar(x1, 420 - mod_data[i], x2, 419);
        sprintf(str, "%d", int(orig_data[i]));
        outtextxy(x1 + 5, 425, str);
        x1 = x1 + 75;
        x2 = x2 + 75;
    }
    delay(3000);
    if (u < n) {
        cleardevice();
        return 0;
    }
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy((x + 50) / 2, 460, "ALL THE DATA ARE SORTED");
    delay(3000);
    getch();
    return 0;

}
