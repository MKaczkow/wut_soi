Class most extends Monitor{

int ilosc_samochodow_na_skrzyzowaniu;
int ilosc_samochdow_ktore_wjechaly;
bool statek_plytnie = false;
int strona_jazdy = 0;//lewa – 0 , prawa – 1;
Condition statek;
Condition lewa_strona
Condition prawa_strona

statek_wplywa(){
	if(ilosc_samochodow_na_skrzyzowaniu!=0 && statek_plynie = true)
		statek.wait();
	statek_plynie = true;
}

statek_mijal(){
	statek_plynie = false;
	if(!statek.isEmpty())
		statek.signal();
	else{
		if(strona_jazdy==0)
			lewa_strona.singal();
		else
			prawa_strona.singal();
	}
}
	
samochod_wjezdza(int strona){
	if(!statek.isEmpty() || strona_jazdy != strona  || ilosc_samchodow_na_skrzyzowaniu ==2 		||    !statek_plynie)
		if(strona==0)
			lewa_strona.wait();
		else
			prawa_strona.wait();
	ilosc_samochodow_na_skrzyzowaniu++;
	ilosc_samochdow_ktore_wjechaly++;
	if(ilosc_samochdow_ktore_wjechaly ==5){
		ilosc_samochdow_ktore_wjechaly = 0;
		strona=(strona+1)%2;
	}
}

samochod_zjezdza(int strona){
	ilosc_samochodow_na_skrzyzowaniu--;
	if(ilosc_samochodow_na_skrzyzowaniu==0 && !statek.isEmpty())
		statek.signal();
	else{
		if(strona==0)
			lewa_strona.singal();
		else
			prawa_strona.singal();
	}
}
}