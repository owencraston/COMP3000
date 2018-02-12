/* Inefficiently, compute successive prime numbers.  
   Return the nth prime number.  */
int compute_prime (int n) {
   int factor;
   int candidate = 2;
   while (true) {
      int is_prime = true;
      /* test primality by successive division */
      for (factor = 2; factor < candidate; ++factor)
         if (candidate % factor == 0) {
            is_prime = false;
            break;
         }
      /* is prime number we're looking for?  */
      if (is_prime) {
         if (--n == 0) {
            /* define the result  */
		    return candidate;
         }
      }
      ++candidate;
   }
}  
