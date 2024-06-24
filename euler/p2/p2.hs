--https://projecteuler.net/problem=2

{--copypasta solution
--https://wiki.haskell.org/The_Fibonacci_sequence#Canonical_zipWith_implementation
main :: IO()
main = do
    --fibs is the infinite (lazily evaluated) Fibonacci sequence
    let fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
    print (sum [f | f <- (takeWhile (<= 4000000) fibs), f `mod` 2 == 0])
-}

--better solution using even Fibonacci subsequence E(n) = F(3n) = 4E(n - 1) + E(n - 2)
--https://projecteuler.net/overview=0002
main :: IO()
main = do
    --fibs is the infinite (lazily evaluated) even Fibonacci subsequence
    let fibs = 2 : 8 : zipWith (\n0 n1 -> n0 + 4*n1) fibs (tail fibs)
    print (takeWhile (<= 4000000) fibs)
    print (sum (takeWhile (<= 4000000) fibs))

--another solution would be to sum the closed-form expression of the even subsequence
