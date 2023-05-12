kaam calculateFib@adad (n@adad | c@adad | x@adad) karo
	rakho x@adad := 0;
	rakho y@adad := 0;
	rakho z@adad;
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

	wapas bhaijo 0;
kaam khatam


;fibonacci series ka hisaab karnay and dekhanay wala program
kaam markazi@khali (a@adad) karo
	rakho num@adad;
	rakho num@adad := 0;
	lo << `Enter the number` >> num; input
	lo >> x;
	lo >> x@adad;
	lo << `Enter the number` >> num@adad; input

	;lo << >> num;
	;lo >> ;

	rakho result@adad := chalao calculateFib();
	rakho result@adad := chalao calculateFib(arg1 | 5);
	;rakho result@adad := chalao calculateFib(arg1 | );
	;rakho result@adad := chalao calculateFib(| arg1 );
	wapas bhaijo 0; halt
	wapas bhaijo x; halt
	
	chalao calculateFib();
	
	;warna phir
	;bas karo
	
	;warna agar (m>9) to phir
	;	dekhao << x << ` `;
	;bas karo
	
	agar (n<>x) to phir karo
	bas karo
	
	agar (n<>x) to phir karo
		dekhao << x << ` `;
	;warna phir
	;	dekhao << x << ` `;
	warna phir
		dekhao << x << ` `;
	bas karo
	
	
	
	agar (n<>x) to phir karo
		jab tak (i-1 >= n) karo
			dekhao << x << ` `;
		bas karo
	bas karo
	
	
	
	agar (n<>x) to phir karo
	warna agar (m>9) to phir
	bas karo
	
	agar (n<>x) to phir karo
		dekhao << x << ` `;
	warna agar (m>9) to phir
		dekhao << x << ` `;
	bas karo
	
	agar (n<>x) to phir karo
		dekhao << x << ` `;
	warna agar (m>9) to phir
		dekhao << x << ` `;
	warna agar (m>9) to phir
		dekhao << x << ` `;
	warna phir
		dekhao << x << ` `;
	bas karo
kaam khatam
