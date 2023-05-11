kaam markazi@khali () karo


	lo << `Enter the number : ` >> n@adad ;input
 

	agar (n = 0) to phir karo
		dekhao << 1;
		wapas bhaijo 0; 
	warna agar (n = 1) to phir
		dekhao << 1;
		wapas bhaijo 0;
    warna phir
        rakho result@adad := 1; 
	    dekhao << `\nfibonacci series: `;
		rakho i@adad := 2;
		jab tak (i-1 >= n) karo
			rakho result := result * i;
			rakho i := i + 1;
		bas karo 
        dekhao << `Result is: ` << result;
	bas karo

   
kaam khatam
