kaam calculateFib@adad (n@adad | c@adad) karo
	rakho x@adad := (23+2)/2;
	dekhao << `Huzaifa` << `Farooqi\n`;
	lo << `Huzaifa` << `Farooqi` << `Kutty Saly` >> temp@adad >> x ;

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
	bas karo

	wapas bhaijo 0;
kaam khatam

;fibonacci series ka hisaab karnay and dekhanay wala program
kaam markazi@khali () karo
	rakho num@adad;
	lo << `Enter the number` >> num; input
	rakho result@adad := chalao calculateFib(num | 0);
	wapas bhaijo 0; halt
kaam khatam
