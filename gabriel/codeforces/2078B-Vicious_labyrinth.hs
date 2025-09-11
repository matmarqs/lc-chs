import Data.Bool (bool)
import Control.Monad (forM_)

solution :: Int -> Int -> [Int]
solution n k
  | odd k     = [ if i==n   then n-1 else n   | i <- [1..n]]
  | otherwise = [ if i==n-1 then n   else n-1 | i <- [1..n]]

main = do
  n <- read <$> getLine
  forM_ [1..n] $ \_ -> do
    [n,k] <- map read . words <$> getLine
    putStrLn $ unwords . map show $ solution n k
