import Data.Bool (bool)
import Data.Function (on)
import Control.Monad (replicateM_, liftM2, foldM)
import qualified Data.Map.Strict as M
import qualified Data.Set as S

------------------------------------------------------------------------------
-- Esse código passa no Codeforces, mas talvez requeira sorte (trust me bro).
-- O meu passou com 1562 ms e 194800 KB.
------------------------------------------------------------------------------

zipMaybe :: [a] -> [b] -> Maybe [(a,b)]
zipMaybe []     []     = Just []
zipMaybe (x:xx) (y:yy) = ((x,y) :) <$> zipMaybe xx yy
zipMaybe _      _      = Nothing

isFun :: (Ord a, Eq b) => [(a,b)] -> Maybe (M.Map a b)
isFun = foldM go M.empty where
  go mm (a,b) = case M.lookup a mm of
    Nothing             -> Just $ M.insert a b mm
    Just b' | b==b'     -> Just mm
            | otherwise -> Nothing

isBij :: (Ord a, Ord b) => [(a, b)] -> Bool
isBij xx = case isFun xx of
  Nothing -> False
  Just mm -> let vv = S.fromList . M.elems $ mm
             in length mm == length vv

solution :: [Int] -> String -> Bool
solution a b = maybe False isBij $ zipMaybe b a

forN f = do
  n <- read <$> getLine
  replicateM_ n f

main = forN $ do
    getLine -- descarta
    aa <- map read . words <$> getLine
    forN $ do
      ss <- getLine
      putStrLn . bool "No" "Yes" . solution aa $ ss
