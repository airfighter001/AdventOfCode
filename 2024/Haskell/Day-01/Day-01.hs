import Data.List (length, map, sort)

parseInput :: String -> ([Int], [Int])
parseInput= unzip . map ((\[x, y] -> (x, y)) . map read . words) . lines

main :: IO ()
main = do
    content <- readFile "01input.txt"
    let (first, second) = parseInput content
    print (sum $ map (abs . uncurry (-)) $ zip (sort first) (sort second))
    print (sum $ map (\x -> length (filter (x==) second) * x ) first)
