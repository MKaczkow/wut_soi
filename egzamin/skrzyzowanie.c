//skrzyżowanie

monitor cwiartka;
var war_bezpri, war_pri:condition;
wolna:boolean;

procedure zajmij (prior:boolean)
begin
   else if not wolna and prior then war_pri.wait
   else if not wolna then war_bezpri.wait;
   wolna:=false
end;

procedure zwolnij;
begin
   wolna:=true;
   if not war_pri.empty then war_pri.signal
   else if not war_bezpri.empty then war_bezpri.signal
end;
begin wolna:=true end;


class skrzyżowanie;

//operacja i+ to (i+1) mod 4

var cwiartki:array[0..3]of cwiartka;
var tory:array[0..3]of cwiartka;

procedure jedź_wzdluz_torów(i:0..3; kier:(l,n,p));
//i-skąd jedzie,
//kier - dokąd jedzie: l-w lewo, n-na wprost, p-w prawo, z-zawraca
begin
        case kier of
                p: begin cwiartki[i].zajmij(false); cwiartki[i].zwolnij end;
                n: begin
                        cwiartki[i].zajmij(false);
                        cwiartki[i+].zajmij(true); cwiartki[i].zwolnij;
                        cwiartki[i+].zwolnij
                   end;
                l: begin
                        cwiartki[i].zajmij(false);
                        cwiartki[i+].zajmij(true); cwiartki[i].zwolnij;
                        tory[i+].zajmij(false); cwiartki[i+].zwolnij;
                        tory[(i+)+].zajmij(false); tory[i+].zwolnij;
                        cwiartki[(i+)+].zajmij(true); tory[(i+)+].zwolnij;
                        cwiartki[(i+)+].zwolnij
                   end;
                z: begin
                        cwiartki[i].zajmij(false);
                        cwiartki[i+].zajmij(true); cwiartki[i].zwolnij;
                        tory[i+].zajmij(false); cwiartki[i+].zwolnij;
                        tory[(i+)+].zajmij(false); tory[i+].zwolnij;
                        cwiartki[(i+)+].zajmij(true); tory[(i+)+].zwolnij;
                        cwiartki[((i+)+)+].zajmij(true); cwiartki[(i+)+].zwolnij;
                        cwiartki[((i+)+)+].zwolnij
                   end;
        end
end;


procedure jedź_w_poprzek_torów(i:0..3; kier:(l,n,p));
begin
        case kier of
                p: begin cwiartki[i].zajmij(false); cwiartki[i].zwolnij end;
                n: begin
                        cwiartki[i].zajmij(false);
                        tory[i].zajmij(false); cwiartki[i].zwolnij;
                        tory[i+].zajmij(false); tory[i].zwolnij;
                        cwiartki[i+].zajmij(true); tory[i+].zwolnij;
                        cwiartki[i+].zwolnij
                   end;
                l: begin
                        cwiartki[i].zajmij(false);
                        tory[i].zajmij(false); cwiartki[i].zwolnij;
                        tory[i+].zajmij(false); tory[i].zwolnij;
                        cwiartki[i+].zajmij(true); tory[i+].zwolnij;
                        cwiartki[(i+)+].zajmij(true); cwiartki[i+].zwolnij;
                        cwiartki[(i+)+].zwolnij
                   end;
                z: begin
                        cwiartki[i].zajmij(false);
                        tory[i].zajmij(false); cwiartki[i].zwolnij;
                        tory[i+].zajmij(false); tory[i].zwolnij;
                        cwiartki[i+].zajmij(true); tory[i+].zwolnij;
                        cwiartki[(i+)+].zajmij(true); cwiartki[i+].zwolnij;
                        tory[(i+)+].zajmij(false); cwiartki[(i+)+].zwolnij;
                        tory[((i+)+)+].zajmij(false); tory[(i+)+].zwolnij;
                        cwiartki[((i+)+)+].zajmij(true); tory[((i+)+)+].zwolnij;
                        cwiartki[((i+)+)+].zwolnij
                   end;
        end
end;

procedure jedź_tramwaj(i:(0,2));
begin
        tory[i].zajmij(true);
        tory[(i+)+].zajmij(false); tory[i].zwolnij;
        tory[(i+)+].zwolnij;
end;


begin
end;