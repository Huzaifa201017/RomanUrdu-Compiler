kaam markazi@khali () karo
	rakho x@adad := 0;
	rakho y@adad := 0;
	rakho z@adad;

	agar (n < 0) to phir karo
		dekhao << `munfi number daal diya\n`;
		dekhao << 0; 
	warna agar (n = 0) to phir
		dekhao << `yar 0 hai!\n`;
		dekhao << 0; 
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
	bas karo
	dekhao << i ;

	rakho num@adad;
	lo << `Enter the number` >> num; input
	wapas bhaijo 0; halt


kaam khatam
