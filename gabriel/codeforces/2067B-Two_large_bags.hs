{-# Language TupleSections #-}

import Data.Bool (bool)
import Control.Monad (forM_)
import qualified Data.IntMap.Lazy as M

go :: M.IntMap Int -> Bool
go mm = case M.minViewWithKey mm of
  Nothing           -> True
  Just ((_,1), _  ) -> False
  Just ((_,2), mm') -> go mm'
  Just ((k,v), mm') -> go mm'' where
    r    = v-2
    mm'' = M.alter (Just . maybe r (+r)) (k+1) mm'

solution :: [Int] -> Bool
solution = go . M.fromListWith (+) . map (,1)

main = do
  n <- read <$> getLine
  forM_ [1..n] $ \_ -> do
    getLine --descarta
    xx <- map read . words <$> getLine
    putStrLn $ bool "No" "Yes" $ solution xx
