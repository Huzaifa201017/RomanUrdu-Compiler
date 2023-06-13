kaam markazi@khali () karo

    rakho x@adad := 0;
	rakho y@adad := 4;
	rakho z@adad;
	rakho n@adad := 3;
	;rakho g;
    
	rakho z := x + (y + 1) * 8 / 2;
	
	agar (n < 0) to phir karo
		dekhao << `munfi number daal diya\n`;
		wapas bhaijo 0; 
	warna agar (n = 0) to phir
		dekhao << `yar 0 hai!\n`;
		wapas bhaijo 0;
	warna phir
		dekhao << `\nfibonacci series: `;
		rakho i@adad := 1;
		jab tak (i-1 >= n) karo
			dekhao << x << ` `;
			rakho z := x + y;
			rakho x := y;
			rakho y := z;
			rakho i := i + 1;
		bas karo

		jab tak (i-1 >= n) karo
		bas karo

	bas karo

   
kaam khatam
