(* https://projecteuler.net/problem=5 *)
(* boring problem 😴zzz go next!! *)
primesCommaMultiplicities := Catenate[FactorInteger[Range[2, 20]]]
maxes := First @/ GatherBy[ReverseSort[primesCommaMultiplicities], First]]
minimalProduct := Times @@ ((Part[#, 1]^Part[#, 2])& /@ maxes)
Print[minimalProduct]
