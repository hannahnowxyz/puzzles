main :: IO()
main = do
    -- fibs is the infinite (lazily evaluated) Fibonacci sequence
    -- expression graph reduction?
    let fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
    print (sum [f | f <- (takeWhile (<= 4000000) fibs), f `mod` 2 == 0])
