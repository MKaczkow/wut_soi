Most extends Monitor {

	boolean statek_przeplywa = false; 
	int ilosc_samochodow_na_moscie; //{0,1,2}
	kierunek {DÓŁ, GÓRA} aktualny_kierunek;
	int ile_jeszcze_przepuścić;
	
	dostep_statek() {
		if(!(ilosc_samochodow_na_moscie == 0 && !statek_przeplywa))  //musimy poczekac aż ostatni samochód przejedzie oraz żaden statek nie będzie przepływał
			condition_przepłyń.wait();
		statek_przeplywa = true;
	}

	zwolnij_statek(){
		statek_przeplywa = false;
		zwolnij_wspolne();
	}
	
	dostep_samochod(kierunek){
		if(!(((ilosc_samochodow_na_moscie < 2 && kierunek == aktualny_kierunek && ile_jeszcze_przepuścić > 0) || ilosc_samochodow_na_moscie == 0) && condition_przepłyń.isEmpty() && !statek_przeplywa)) 
		{
			if(kierunek == DÓŁ)
				conditon_dół.wait();
			else
				conditon_góra.wait();
		}
		if((aktualny_kierunek == DÓŁ && !conditon_gora.isEmpty()) || (aktualny_kierunek == GÓRA && !conditon_dol.isEmpty())) {
			ile_jeszcze_przepuścić--; //uznajemy, że samochód został przepuszczony jeśli wjechal na most
		} 
		ilosc_samochodow_na_moscie++;
		aktualny_kierunek = kierunek;
	}
	
	zwolnij_samochod(){
		ilosc_samochodow_na_moscie--;
		zwolnij_wspolne();
	}
	
	zwolnij_wspolne(){
		if(conditon_przepłyń.isNotEmpty() && ilosc_samochodow_na_moscie == 0 && !statek_przeplywa)
			signal(condition_przepłyń);
		else if (conditon_przepłyń.isEmpty() && ilosc_samochodow_na_moscie < 2){
		
			if(aktualny_kierunek == GÓRA)
				if(conditon_góra.isEmpty() && ilosc_samochodow_na_moscie == 0){
					aktualny_kierunek = DÓŁ;
					ile_jeszcze_przepuścić = 5;
					conditon_dół.signal();
				} else if(condition_dół.isEmpty() && ilosc_samochodow_na_moscie < 2){
					conditon_góra.signal(); //ani statek ani żaden samochod z innego kierunku nie czeka więc nic nie trzeba robić
				} else if (!condition_dół.isEmpty()){ 
					if(ile_jeszcze_przepuścić > 0){
						conditon_góra.signal();
					} else if(ilosc_samochodow_na_moscie == 0){
						aktualny_kierunek = DÓŁ; 
						ile_jeszcze_przepuścić = 5; 
						conditon_dół.signal()
					}
				}
			} else if(aktualny_kierunek == DÓŁ) {
			(...)
			//analogicnzie jak dla warunku  aktualny_kierunek == GÓRA
			}
		
		}
	}
	
}

proces statku:
	dostep_statek();
	przeplyn();
	zwolnij_statek();
	
proces_samochodu: 
	dostep_samochod(kierunek)'
	przejedz();
	zwolnij_samochod();