import Control.Monad (forM_)

solution :: Int -> (Int, Int, Int) -> Int
solution m (a,b,c) = a' + b' + c' where
  a' = min a m
  b' = min b m
  c' = min c (max 0 $ (2*m) - (a'+b'))

main = do
  n <- read <$> getLine
  forM_ [1..n] $ \_ -> do
    [m,a,b,c] <- map read <$> words <$> getLine
    print $ solution m (a,b,c)
