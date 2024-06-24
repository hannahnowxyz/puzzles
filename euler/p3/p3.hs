--https://projecteuler.net/problem=3

main :: IO()
main =
    --construct lazy list of primes by trial division
    --see also https://web.archive.org/web/20240608070230/https://www.cs.hmc.edu/~oneill/papers/Sieve-JFP.pdf
    let primes = 2 : [x | x <- [3..], isPrime x]
        isPrime x = all (\p -> x `mod` p > 0) (takeWhile (\p -> p*p <= x) primes)
        --only need to look for prime factors below sqrt(n),
        --  because any greater factor p would already be implied by its reciprocal factor n/p.
        --  ex. 22: find factor 2 and stop looking after floor(sqrt(22)) = 4, because factor 11 = 22/2 already known
        --775146 = floor(sqrt(600851475143))
        possibleFactors = takeWhile (<= 775146) primes
    in do
        --correct number of possible factors is pi(775146) = 62113
        let l = length possibleFactors
            c = if l == 62113 then "correct" else "incorrect"
            g = head (dropWhile (\p -> 600851475143 `mod` p > 0) (reverse possibleFactors))
        print ("found " ++ show l ++ " primes below 775146 (" ++ c ++ ")")
        print ("greatest prime factor of 600851475143 is: " ++ show g)
