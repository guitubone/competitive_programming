//peguei no http://blog.forthright48.com/2015/08/prime-factorization-of-factorial.html
void factFactorize ( int n ) {
    for ( int i = 0; i &lt; prime.size() &amp;&amp; prime[i] &lt;= n; i++ ) {
            int x = n;
            int freq = 0;
     
            while ( x / prime[i] ) {
                        freq += x / prime[i];
                        x = x / prime[i];
                    }
     
            printf ( "%d^%d\n", prime[i], freq );
        }
}

