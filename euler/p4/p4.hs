--https://projecteuler.net/problem=4

--solution by intelligent search
--there is probably a more efficient criterion to determine if n = r0r1r2*t0t1t2 for some 3-digit r0r1r2, t0t1t2
--  the expansion n = 10^4(r0*t0) + 10^3(r1*t0 + r0*t1) + 10^2(r2*t0 + r1*t1 + r0*t2) + 10(r2*t1 + r1*t2) + r2*t2
--  leads to a system of equations modulo 10, so maybe something from number theory to determine if a solution exists
main :: IO()
main =
    --products range from 100*100 = 10000 to 999*999 = 998001 (but safely assume answer has 6 digits)
    --  largest palindrome in range is 997799, so enumerate: 997xxx, 996xxx, 995xxx, ...
    --  all 6-digit palindromes are divisible by 11, so one 3-digit factor will be too
    --  3-digit multiples of 11 are 11*10 to 11*90, but only some of these products are in the correct range
    --  ex. 573375/11 = 52125, so the other correct minimum factor is ceil(52125/1000) = 53
    --      (sanity check: 52125/52 > 1000 and 52125/53 < 1000)
    let palindromes = [1000*n + 100*(n `mod` 10) + (n `mod` 100) - (n `mod` 10) + (n `quot` 100) | n <- reverse [100..997]]
        doesItFactor n = any (\q -> (n `quot` 11) `mod` q == 0) [((n `quot` 11) `quot` 1000 + 1)..90]
        largest = head (dropWhile (not . doesItFactor) palindromes)
    in do
        print ("largest palindrome that factors: " ++ show largest)
