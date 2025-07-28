import Data.Function (on)
import Data.Char (toLower, isAlphaNum)

solution :: String -> Bool
solution = ((==) `on` crivo) <*> reverse
  where crivo = map toLower . filter isAlphaNum
