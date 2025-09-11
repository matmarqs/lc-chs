solution :: Int -> [Int]
solution n = case divMod n 3 of
  (d,0) -> take 3 [pred d..]
  _     -> []

main = print . solution . read =<< getLine
