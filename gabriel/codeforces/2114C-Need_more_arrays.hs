import Control.Monad (forM_)

solution :: [Int] -> Int
solution = length . foldr go [] where
  go x []     = [x]
  go x (y:yy) | succ x < y = x:y:yy
              | otherwise  =   y:yy

main = do
  n <- read <$> getLine
  forM_ [1..n] $ \_ -> do
    getLine -- descarta
    xx <- map read . words <$> getLine
    print $ solution xx
