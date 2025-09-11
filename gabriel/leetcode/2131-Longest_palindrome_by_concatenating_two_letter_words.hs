import Data.List (mapAccumL)
import qualified Data.Map as M

solution :: [String] -> Int
solution ss = sum vv + (if sobrouPalíndromo then 2 else 0) where
  (mm, vv) = mapAccumL go M.empty ss
  sobrouPalíndromo = any (\[a,b] -> a==b) . M.keys $ mm

  go mm s@[a,b]
    | s' `M.member` mm = (decrease s' mm, 4) -- par-antipar se cancelam
    | otherwise        = (increase s  mm, 0)
    where s' = [b,a]

  increase = M.alter (Just . maybe 1 succ)
  decrease = M.update (\a -> if a==1 then Nothing else Just $ a-1)

main = print . solution . read =<< getLine
