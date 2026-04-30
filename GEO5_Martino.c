#include <stdio.h>
#include <math.h>

//#DEFINE menup=20;
//#DEFINE maxim=1000;

/* GEO5 - GEODETICKE VYPOCTY (GEO 5.0 BETA)
   ========================================
   Jedna se o prepracovanou verzi slavne GEO4, ktera vznikla Tatickem v Pascalu...
   Toto je Beta verze 5.0, jakekoliv bugy, pripominky, cokoliv
   zaslete prosim na "tarkanjj@gmail.com"
   
   Za่al jsem poprv้ upravovat tento k๓d 20.3.2013 ve 20:00 - Martino ;)

   AUTOR: Ing. Jaroslav Jirsa
   (PRE)PROGRAMATOR: Ing et BSc. Martin Jirsa
*/

int main(int argc, char *argv[])
{
    printf("Menu .......................\n");
    printf("Ulozeni textoveho souboru...\n");
                 /* 'Smernik a delka ............',
                  'Dalkomer Eldi(vypocet Y,X,Z)',
                  'Pridani bodu ...............',
                  'Nacteni textoveho souboru...',
                  'Editace bodu................',
                  'Ukonceni programu ..........',
                  'Ortogonalni hodnoty ........',
                  'Prevod y,x do souboru dxf ..',
                  'Polygon ....................',
                  'Trasa s klotoidou ..........',
                  'Volne stanovisko ...........',
                  'Graficke  zobrazeni ........',
                  'Vyjmuti bodu ...............',
                  'Dalsi ulohy  ...............',
                  'Precislovani bodu  .........',
                  'Vypocet  ploch .............',
                  'Sour. Y  a  X  z ortohodnot.',
                  'Transformace souradnic .....');

     cup = ^E;
     cdown = ^X;
     center= ^M;
     cexit = ^[;  {Esc i Alt+x}
     b1=2; {zelena}
     b2=0; {cerna}
     b3=15;{bila}
     cc=3;     {konstanta = pocet radek od nadpisu}

type cast=array[1..maxim] of real;
*/
  //boolean konec, done;
  char ch;
  int jmenob,t1,t2,vstup; // promenna vstup pro osetreni nacit. neexist.soub.
  short pocetid; 
  double dy,dx,dh,s,d,y1,x1,so,popisv, yv,xv,zv,vs,vc,hzo,hz,zenit,m,dm,vo,h1,dd,nh,ph,mm,r1,r2,r3,r4,r5,r6,r7,q,a1,a2,k1,k2;
  //int jm[1..maxim], id[1..menup];
  //string nazev, nazev1, hladina; 
  //f:text;
  //  x,y,z,a,b,c:cast; {sour.,mistni sour.+stan.  a kolmice}
  // pocetb,i,j,k,imin,jv:0..maxim;      {i=prub. promenna,j=aktualni prom.}
  // ii:1..20;

/*
  procedure inicializace;
 begin
  textattr:=b1*16+b2;
  clrscr ;
  done:=false;
  if ii=8 then done:=true;
  gotoxy(1,1);
  WRITELN('ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป');
  Writeln('บ                    G e o d e t i c k e   v y p o c t y                    บ');
  WRITELN('บฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤบ');
  for ii:=1 to 10 do begin
     gotoxy(1,ii+cc);writeLN('บ        ',men[ii],'                                       บ');
     end ;
  for ii:=11 to 20 do begin
     gotoxy(41,ii-10+cc); writeln(men[ii]);
     end;
  WRITELN('ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ ');
   ii:=1;
  textcolor(b3);gotoxy(10,1+cc);write(men[ii]);
 end;


 procedure Beep;
   begin
     Sound(500);Delay(35);NoSound;
   end;


 procedure stiskklavesy;
    begin
      repeat until keypressed;
    end;

  procedure chyba;
    begin
      vstup:=IOResult;
      if vstup<>0 then begin beep;writeln('Vloz cislo '); end;
    end;
*/

/*
void selectsort(void);
{
  for(i=1;i=pocetb-1;i++) {//i:=1 to pocetb-1 do
         imin = jm[i]; // imin:=jm[i];
         for j:=i+1 to pocetb do
           if jm[j]<imin then begin imin:=jm[j];k:=j;end;
         if jm[i]>imin then
            begin
              jv:=jm[i];yv:=y[i];xv:=x[i];zv:=z[i];
              jm[i]:=jm[k];y[i]:=y[k];x[i]:=x[k];z[i]:=z[k];
              jm[k]:=jv;y[k]:=yv;x[k]:=xv;z[k]:=zv;
            end;
              end;
   } end;

procedure helmert;
  begin                 {nutno nulovat r1 v procedure odkud je helmert volan}
     if r1=0 then  begin r2:=0;r3:=0;r4:=0;r5:=0;r6:=0;r7:=0;ph:=0;nh:=0; end;
     r1:=x[j]*a[k]+y[j]*b[k]+r1;
     r2:=x[j]*b[k]-a[k]*y[j]+r2;
     r3:=x[j]+r3;
     r4:=y[j]+r4;
     r5:=x[j]*x[j]+y[j]*y[j]+r5;
     r6:=a[k]+r6;
     r7:=b[k]+r7;
  if k>1 then  q:=r5-(r3*r3+r4*r4)/k  else q:=1;
     a1:=(r1-(r6*r3+r7*r4)/k)/q;
     a2:=(r2-(r7*r3-r6*r4)/k)/q;
     k1:=(r7-a2*r3-a1*r4)/k;
     k2:=(r6-a1*r3+a2*r4)/k;
     ph:=ph+z[j];
     nh:=nh+c[k];
  end;

*/
  
  puts("");
        
  system("PAUSE");
  return 0;
}

/*
program GEO;

uses crt;

const menup=20;
 type
   menu=array[1..menup] of string[29];

const maxim=1000;
      men : menu= ('Menu .......................',
                  'Ulozeni textoveho souboru...',
                  'Smernik a delka ............',
                  'Dalkomer Eldi(vypocet Y,X,Z)',
                  'Pridani bodu ...............',
                  'Nacteni textoveho souboru...',
                  'Editace bodu................',
                  'Ukonceni programu ..........',
                  'Ortogonalni hodnoty ........',
                  'Prevod y,x do souboru dxf ..',
                  'Polygon ....................',
                  'Trasa s klotoidou ..........',
                  'Volne stanovisko ...........',
                  'Graficke  zobrazeni ........',
                  'Vyjmuti bodu ...............',
                  'Dalsi ulohy  ...............',
                  'Precislovani bodu  .........',
                  'Vypocet  ploch .............',
                  'Sour. Y  a  X  z ortohodnot.',
                  'Transformace souradnic .....');

     cup = ^E;
     cdown = ^X;
     center= ^M;
     cexit = ^[;  {Esc i Alt+x}
     b1=2; {zelena}
     b2=0; {cerna}
     b3=15;{bila}
     cc=3;     {konstanta = pocet radek od nadpisu}

type cast=array[1..maxim] of real;

var f:text;
    x,y,z,a,b,c:cast; {sour.,mistni sour.+stan.  a kolmice}
    jm:array[1..maxim] of integer;
    id:array[1..menup] of integer;
    pocetid: shortint;
    nazev,hladina:string;
    nazev1:string;
    jmenob,t1,t2:integer;
    pocetb,i,j,k,imin,jv:0..maxim;      {i=prub. promenna,j=aktualni prom.}
    dy,dx,dh,s,d,y1,x1,so,popisv:real;
    yv,xv,zv,vs,vc,hzo,hz,zenit,m,dm,vo,h1,dd:real;
    nh,ph,mm:real;
    konec:boolean;
    done:boolean;
    vstup:integer;  {promenna vstup pro osetreni nacit. neexist.soub.}
    ch:char;
    r1,r2,r3,r4,r5,r6,r7,q,a1,a2,k1,k2: real;  {transformace}
    ii:1..20;


  procedure inicializace;
 begin
  textattr:=b1*16+b2;
  clrscr ;
  done:=false;
  if ii=8 then done:=true;
  gotoxy(1,1);
  WRITELN('ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป');
  Writeln('บ                    G e o d e t i c k e   v y p o c t y                    บ');
  WRITELN('บฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤบ');
  for ii:=1 to 10 do begin
     gotoxy(1,ii+cc);writeLN('บ        ',men[ii],'                                       บ');
     end ;
  for ii:=11 to 20 do begin
     gotoxy(41,ii-10+cc); writeln(men[ii]);
     end;
  WRITELN('ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ ');
   ii:=1;
  textcolor(b3);gotoxy(10,1+cc);write(men[ii]);
 end;


 procedure Beep;
   begin
     Sound(500);Delay(35);NoSound;
   end;


 procedure stiskklavesy;
    begin
      repeat until keypressed;
    end;

  procedure chyba;
    begin
      vstup:=IOResult;
      if vstup<>0 then begin beep;writeln('Vloz cislo '); end;
    end;

  procedure selectsort;

   begin
     for i:=1 to pocetb-1 do
       begin
         imin:=jm[i];
         for j:=i+1 to pocetb do
           if jm[j]<imin then begin imin:=jm[j];k:=j;end;
         if jm[i]>imin then
            begin
              jv:=jm[i];yv:=y[i];xv:=x[i];zv:=z[i];
              jm[i]:=jm[k];y[i]:=y[k];x[i]:=x[k];z[i]:=z[k];
              jm[k]:=jv;y[k]:=yv;x[k]:=xv;z[k]:=zv;
            end;
        end;
    end;

procedure helmert;
  begin                 {nutno nulovat r1 v procedure odkud je helmert volan}
     if r1=0 then  begin r2:=0;r3:=0;r4:=0;r5:=0;r6:=0;r7:=0;ph:=0;nh:=0; end;
     r1:=x[j]*a[k]+y[j]*b[k]+r1;
     r2:=x[j]*b[k]-a[k]*y[j]+r2;
     r3:=x[j]+r3;
     r4:=y[j]+r4;
     r5:=x[j]*x[j]+y[j]*y[j]+r5;
     r6:=a[k]+r6;
     r7:=b[k]+r7;
  if k>1 then  q:=r5-(r3*r3+r4*r4)/k  else q:=1;
     a1:=(r1-(r6*r3+r7*r4)/k)/q;
     a2:=(r2-(r7*r3-r6*r4)/k)/q;
     k1:=(r7-a2*r3-a1*r4)/k;
     k2:=(r6-a1*r3+a2*r4)/k;
     ph:=ph+z[j];
     nh:=nh+c[k];
  end;


  procedure transrovnice;
    begin
     yv:=y[i];
     y[i]:=k1+a2*x[i]+a1*yv;
     x[i]:=k2+a1*x[i]-a2*yv;
     z[i]:=z[i]+(nh-ph)/pocetid;
    end;

procedure smernikdelka(dy,dx:real;var s,d:real);
    begin
     if not((dy=0) or (dx=0)) then s:=arctan(dy/dx)*200/pi;
     if ((dx=0) and (dy=0)) then s:=0;
     if ((dx=0) and (dy<0)) then s:=300;
     if ((dx=0) and (dy<0)) then s:=100;
     if ((dx>0) and (dy=0)) then s:=0;
     if ((dx<0) and (dy=0)) then s:=200;
     if ((dx>0) and (dy<0)) then s:=400+s;
     if ((dx<0) and (dy<0)) then s:=200+s;
     if ((dx<0) and (dy>0)) then s:=200+s;
     d:=sqrt(dx*dx+dy*dy);
    end;

procedure nactenibodu;       {pocetb znaci pocet bodu celkem}
  {$I-}

/* Prvnํ výskyt týhle {$I-} "sra่ky" => turns off automatic Input/Output (I/O) checking. By default, Pascal assumes {$I+} is active, meaning that if an I/O operation fails (e.g., trying to open a file that doesn't exist, reading invalid data type), the program will immediately terminate with a run-time error. */

  begin
    repeat
     write ('Nazev souboru se souradnicemi:');
     readln (nazev);
     assign (f,nazev);
     reset(f);
    vstup:=IOResult;
    if vstup<>0 then  writeln(' soubor ',nazev,'  neexistuje ');writeln;
   until vstup=0;
    {$I+}
     pocetb:=0;
     while not eof(f) do
      begin
       pocetb:=pocetb+1;
       readln(f,jm[pocetb],y[pocetb],x[pocetb],z[pocetb]);
      end;
    inicializace;
    end;

 procedure ulozenibodu;
    begin
     write ( 'Ulozeni bodu do souboru: ');
     readln (nazev);
     assign (f,nazev);
     rewrite (f);
     for i:=1 to pocetb do writeln (f,jm[i],' ',y[i]:6:3,' ',x[i]:7:3,' ',z[i]:4:3);
     close (f);
    inicializace;
    end;

 procedure vkladanibodu;              {vlozeni bodu a setrideni bodu dle jmena}
    {$I-}
    begin
     pocetb:=pocetb+1;
     j:=pocetb;
    repeat
     jm[pocetb]:=jmenob;
     write ('  Y= ');
     readln (y[pocetb]);
     chyba;
    until vstup=0;
    repeat
     write ('  X= ');
     readln(x[pocetb]);
     chyba;
    until vstup=0;
    repeat
     write ('  Vyska bodu=');
     readln (z[pocetb]);
     chyba;
    until vstup=0;
    {$I+}
    end;

 procedure hledanibodu;  {podle jmena bodu jmenob a pripadne vlozeni bodu}
    begin
     i:=0;
     jm[pocetb+1]:=jmenob;
     repeat
      i:=i+1;
     until jmenob=jm[i];
      j:=i;
     if i=(pocetb+1) then  vkladanibodu;
{    if (pocetb+1)>=4 then selectsort;  }
    end;


     procedure vklad;
  {$I-} 
   begin
  repeat
   write(' Vlozeni bodu cislo: ');
   readln(jmenob);
   chyba;
  until vstup=0;
   hledanibodu;
   inicializace;
  {$I+}
   end;


   procedure transfobody;
    {$I-}
    begin
         writeln('Bod ',id[k] ,'(zadej souradnice soustavy do ktere se transf.');
          repeat
           write('Y(po transf.)=');readln(b[k]);
           chyba;
          until vstup=0;
          repeat
           write('X(po transf.)=');readln(a[k]);
           chyba;
          until vstup=0;
          repeat
           write('H(po transf.)=');readln(c[k]);
           chyba;
          until vstup=0;
    {$I+}
    end;

   procedure transformace;
  {$I-}
   begin
   i:=1;
   r1:=0;
   pocetid:=0;
   k:=0;
   clrscr;
   writeln('Transformace bodu ');
   writeln('==================');
   repeat
      repeat
        writeln('...................................................');
        write('Bod   ? (ne=0,ano dalsi cislo bodu) '); readln(i);
       chyba;
      until vstup=0;
  {$I+}
      jmenob:=i;
      if i<>0 then
        begin
           k:=k+1;
           pocetid:=pocetid+1;
           id[k]:=i;
           if pocetb=0 then vkladanibodu ;
           hledanibodu;
           transfobody;
           helmert;
         end;
      until i=0;
   if k>1 then
    begin
     writeln;
     writeln('        Porovnani souradnic identickych bodu ');
     writeln('         ======================================');
     writeln('Bod        dy         dx        dh ');
      for k:=1 to pocetid do
       begin
         jmenob:=id[k];
         hledanibodu;
         dy:=-b[k]+k1+a2*x[j]+a1*y[j];
         dx:=-a[k]+k2+a1*x[j]-a2*y[j];
         dh:= c[k]-(z[j]+(nh-ph)/pocetid);
         writeln(id[k],'     ',dy:6:3,'    ',dx:6:3,'   ',dh:6:3);
       end;
       mm:=sqrt(a1*a1+a2*a2);
       writeln('Meritko transformace=',mm:2:8);
       stiskklavesy;
       selectsort;
     end;

     if (k=1) or (k=0) then
        begin
        writeln;
        writeln('Uvedeny maly pocet bodu');
        stiskklavesy;
        transformace;
        end;
     writeln;
   {$I-}
    repeat
     write(' Pocatecni bod od ktereho se provede transformace:');readln(imin);
     chyba;
    until vstup=0;
    repeat
     write(' Posledni bod transformace:');readln(jv);
     chyba;
    until vstup=0;
   {$I+}
    if jv>=imin then
     begin
      i:=0;
      repeat
       i:=i+1
      until jm[i]>=imin;

  if jv>=jm[pocetb] then
    begin
      repeat
       transrovnice;
       i:=i+1;
      until i=pocetb+1;
     end;
   if jv<jm[pocetb] then
    begin
     repeat
      transrovnice;
      i:=i+1;
     until jm[i]>jv;
    end;
   end;
    for k:=1 to pocetid do
     begin
      jmenob:=id[k];
      hledanibodu;
      y[j]:=b[k];
      x[j]:=a[k];
      z[j]:=c[k];
     end;
  end;



  procedure polarni;  {(dy,dx:real; var s,d:real); }
  {$I-}
  begin
   writeln('  Vypocet smerniku a delky ');
   writeln('  ************************ ');
  repeat
   write(' Cislo poc. bodu :');
   readln(jmenob);
   chyba;
   until vstup=0;
   if pocetb=0 then vkladanibodu else hledanibodu;
   y1:=y[j];
   x1:=x[j];
   writeln;
   i:=0;
 repeat
   if i<>0  then jmenob:=i  else begin write('Cislo konc. bodu :');
                        readln(jmenob);
                end;
   hledanibodu;
   dy:=y[j]-y1;
   dx:=x[j]-x1;
   smernikdelka(dy,dx,s,d);
   writeln('Smernik=',s:4:5,'   delka=',d:5:4);
   writeln ;
  repeat
   write('Dalsi bod (ne=0 , jinak cislo koncoveho bodu) ');
   readln(i);
   chyba;
   until vstup=0;
  until i=0;
  selectsort;
 {$I-};
  end;

  procedure editacebodu;
    begin
    i:=0;
      repeat
       i:=i+1;
       writeln(jm[i],'  ',y[i]:6:3,'  ',x[i]:7:3,'  ',z[i]:4:3);
      until i=pocetb;
      stiskklavesy;
    end;

       procedure podrobnybod;
     {$I-}
     begin
      writeln;
     { write(' cislo podrob. bodu :'); readln(jmenob);}
     jmenob:=i;
     repeat
      write('  mer. delka='); readln(dm);
      chyba;
     until vstup=0;
     repeat
      write('  vyska cile='); readln(vc);
      chyba;
     until vstup=0;
     repeat
      write('  horiz.smer='); readln(hz);
      chyba;
     until vstup=0;
     repeat
      write('  zenit     =');readln(zenit);
      chyba;
     until vstup=0;
      dm:=dm-0.085*cos(zenit/200*pi);
      vo:=h1+vs-vc+dm*cos(zenit/200*pi);
      dd:=dm*sin(zenit/200*pi);
      hz:=hz-hzo+s;
      y[pocetb+1]:=y1+dd*sin(hz/200*pi);
      x[pocetb+1]:=x1+dd*cos(hz/200*pi);
      z[pocetb+1]:=vo;
      k:=0;i:=0;
      repeat
        i:=i+1;
        if jmenob=jm[i] then k:=i;
      until i=pocetb;
  if k>0 then
         begin
          writeln('Bod ',jm[k],' existuje Y=',y[k]:6:3,'  X=',x[k]:7:3,'  H=',z[k]:4:3);
          writeln(' nove sour.:      ' ,y[pocetb+1]:6:3,' ',x[pocetb+1]:7:3,' ',z[pocetb+1]:4:3);
         repeat
          write('Souradnice puvodni/nove ? (1/2)  :');readln(i);
          chyba;
         until vstup=0;
          if i=2 then begin
                        y[k]:=y[pocetb+1];x[k]:=x[pocetb+1];z[k]:=z[pocetb+1];
                            end;
         end;
  if k=0 then begin
     pocetb:=pocetb+1;  jm[pocetb]:=jmenob;
     writeln;
writeln(jm[pocetb],' Y=',y[pocetb]:6:3,' X=',x[pocetb]:7:3,' H=',z[pocetb]:4:3);

         end;
{$I-}
  end;

  procedure ortobod;
    begin
    jmenob:=i;
    hledanibodu;
    dy:=y[j]-y1; dx:=x[j]-x1;
    smernikdelka(dy,dx,s,d);
    s:=s-so;
    a[j]:=d*cos(s/200*pi);
    b[j]:=d*sin(s/200*pi);
    writeln ( 'Staniceni=',a[j]:5:3);
    writeln ( 'Kolmice  =',b[j]:5:3);
    end;

  procedure dalkomereldi;
    {$I-}
    begin
      writeln;
      writeln(' Vypocty souradnic merenim dalkomerem  Eldi4 ');
      writeln('.............................................');
      writeln;
     repeat
      write(' Stanovisko (bod) : ');
      readln(jmenob);
      writeln('------------------');
      chyba;
     until vstup=0;
      if pocetb=0 then vkladanibodu else hledanibodu;
     repeat
      write(' Vyska stroje='); readln(vs);
      chyba;
     until vstup=0;
      y1:=y[j];
      x1:=x[j];
      h1:=z[j];
      writeln;
     repeat
      write(' Orientace na bod : ');
      readln(jmenob);
      writeln('------------------');
      chyba;
     until vstup=0;
      hledanibodu;
      dy:=y[j]-y1; dx:=x[j]-x1;
      smernikdelka(dy,dx,s,d);
     repeat
      write('  mer. delka='); readln(dm);
      chyba;
     until vstup=0;
     repeat
      write('  vyska cile='); readln(vc);
      chyba;
     until vstup=0;
     repeat
      write('  horiz.smer='); readln(hzo);
      chyba;
     until vstup=0;
     repeat
      write('  zenit     =');readln(zenit);
      chyba;
     until vstup=0;
      dm:=dm-0.085*cos(zenit/200*pi);
      vo:=h1+vs-vc+dm*cos(zenit/200*pi);
      dd:=dm*sin(zenit/200*pi);
      writeln('..................................................');
      writeln(' Vyp. delka=',d:4:3,'  vyska bodu orient.=',z[j]:4:3);
      writeln(' Delka mer.=',dd:4:3,'       vyska z mer.=',vo:4:3);
      writeln;
     repeat
      write(' Cislo podr. bodu: ');readln(i);
      chyba;
     until vstup=0;
      podrobnybod;
    repeat
      writeln;
      selectsort;
     repeat
      write('Bod   ? (ne=0,ano dalsi cislo bodu) '); readln(i);
      chyba;
     until vstup=0;
      if i<>0 then podrobnybod;
    until i=0;
  {$I+}
      selectsort;
      inicializace;
    end;

   procedure ortogonal;
    begin
      writeln;
      writeln(' Vypocty ortogonalnich hodnot z x a y        ');
      writeln('.............................................');
      writeln;
      write(' Stanovisko (bod) : ');
      readln(jmenob);
      writeln('------------------');
      if pocetb=0 then vkladanibodu else hledanibodu;
      y1:=y[j];
      x1:=x[j];
      writeln;
      write(' Orientace na bod : ');
      readln(jmenob);
      writeln('------------------');
      hledanibodu;
      dy:=y[j]-y1; dx:=x[j]-x1;
      smernikdelka(dy,dx,s,d);
      writeln('..................................................');
      so:=s;
    repeat
      writeln;
     repeat
      write('Dalsi bod ? (ne=0, ano= vloz cislo bodu): '); readln(i);
      chyba;
     until vstup=0;
      if i<>0 then ortobod;
    until i=0;
      selectsort;
      inicializace;
    end;

  procedure dxfformat;
    begin
     writeln ('Prevod souradnic z aktualniho souboru do tvaru dxf ');
     writeln;
                 write('Ulozeni bodu do souboru(bez dxf): ');
                 readln(nazev1);
     writeln;
     write('Velikost popisu (pro 1:500 je 0.7 ) : ');
     readln(popisv);
     write('Nazev koncovky pro hladiny v ACADu:');
     readln(hladina);

     nazev1:=nazev1+'.dxf';
     assign (f,nazev1);
     rewrite (f);
     writeln(f,'0');
     writeln(f,'SECTION');
     writeln(f,'2');
     writeln(f,'ENTITIES');
     writeln(f,'0');
     for i:=1 to pocetb do
             BEGIN
               writeln (f,'TEXT');
               writeln (f,'8');
               writeln (f,'CISLA'+HLADINA);
               writeln (f,'10');
               writeln (f,(-y[i]+popisv*0.5):7:3);
               writeln (f,'20');
               writeln (f,-x[i]:7:3);
               writeln (f,'40');
               writeln (f,popisv:3:3);
               writeln (f,'1');
               writeln (f,jm[i]);
               writeln (f,'0');
               writeln (f,'TEXT');
               writeln (f,'8');
               writeln (f,'VYSKY'+HLADINA);
               writeln (f,'10');
               writeln (f,(-y[i]-popisv*2.5):7:3);
               writeln (f,'20');
               writeln (f,(-x[i]-popisv):7:3);
               writeln (f,'40');
               writeln (f,(popisv*0.9):3:3);
               writeln (f,'1');
               writeln (f,int(z[i]):3:0,' ',(frac(z[i])*1000):3:0);
               writeln (f,'0');
               writeln (f,'POINT');
               writeln (f,'8');
               writeln (f,'BODY'+HLADINA);
               writeln (f,'10');
               writeln (f,-y[i]:7:3);
               writeln (f,'20');
               writeln (f,-x[i]:7:3);
               writeln (f,'0');
             end;
     WRITELN(f,'ENDSEC');
     WRITELN(f,'0');
     WRITELN(f,'EOF');
     close (f);

    end;

 function readchar:char;
  var ch:char;
    begin
      ch:= readkey;
       if ch = #0 then
         case readkey of
         #45: ch:= cexit;
         #72: ch:=cup;
         #80: ch:=cdown;
       end;
       readchar:=ch;
     end;


       procedure  ccup;
   begin
    if ((ii>=1) and (ii<=20)) then
    begin
      if ii>10 then t1:=31 else t1:=0;
      if ii>10 then t2:=-10 else t2:=0;
      textcolor(b2);gotoxy(10+t1,ii+cc+t2);write(men[ii]);
      if ii<>1 then ii:= ii-1 else ii:=20;
      if ii>10 then t1:=31 else t1:=0;
      if ii>10 then t2:=-10 else t2:=0;
      textcolor(b3);gotoxy(10+t1,ii+cc+t2);write(men[ii]);
    end;
   end;

  procedure  ccdown;
  begin
    if ((ii>=1) and (ii<=20)) then
    begin
      if ii>10 then t1:=31 else t1:=0;
      if ii>10 then t2:=-10 else t2:=0;
      textcolor(b2);gotoxy(10+t1,ii+cc+t2);write(men[ii]);
      if ii<>20 then ii:= ii+1 else ii:=1;
      if ii>10 then t1:=31 else t1:=0;
      if ii>10 then t2:=-10 else t2:=0;
      textcolor(b3);gotoxy(10+t1,ii+cc+t2);write(men[ii]);
    end;
 end;

  procedure ccenter;
   begin
     gotoxy(1,cc+menup+2);
     textcolor(b2);
     clrscr;
     if ii=6 then nactenibodu;
     if ii=2 then ulozenibodu;
     if ii=3 then polarni;
     if ii=4 then dalkomereldi;
     if ii=5 then vklad;
     if ii=7 then editacebodu;
     if ii=9 then ortogonal;
     if ii=10 then dxfformat;
     if ii=20 then transformace;
     inicializace;
   end;

   begin
  inicializace;
  pocetb:=0;
  j:=0;
  repeat
    ch:= readchar;
         case ch of
         cup: ccup;
         cdown:ccdown;
         center:ccenter;
         cexit: done:=true;
    end;
   until done;
end.
*/
