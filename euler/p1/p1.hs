--https://projecteuler.net/problem=1

main :: IO ()
main = print (sum [x | x <- [1..999], x `mod` 3 == 0 || x `mod` 5 == 0])
