{-# LANGUAGE TemplateHaskell, BangPatterns #-}
-- | Really simple and inefficient Golomb coding. Technically, this
-- is Rice coding, since it only supports power-of-two divisors. 

import Data.Bits
import Test.QuickCheck
import Test.QuickCheck.All

-- Some sample data.
sampleData :: [Int]
sampleData = [1, 3, 2, 1, 0, 1, 1, 0, 0, 1, 2, 1, 3, 5, 1, 7, 12, 2, 1]

-- | Log base 2, rounded up.
log2 :: Int -> Int
log2 x = ceiling $ logBase 2 (fromIntegral x)

-- | Do Rice encoding for a number.
golombEncodeNum :: Int -> Int -> [Bool]
golombEncodeNum m x = quotCode ++ remCode
    where quotCode = (take (x `div` m) (repeat True)) ++ [False]
          remCode = [x `testBit` b | b <- [0..(log2 m - 1)]]

-- Do Rice decoding of a number.
golombDecodeNum :: Int -> [Bool] -> (Int, [Bool])
golombDecodeNum m xs = (q*m + r, cs)
    where (qs, as) = span id xs
          q = length qs
          bs = tail as
          (r, cs) = readBin 0 0 bs
          readBin !bit !acc ys | bit == (log2 m) = (acc, ys)
                               | otherwise = readBin (bit + 1) (if (head ys) then acc `setBit` bit else acc) (tail ys)

-- | Rice encode a list.
enclist m l = concat $ map (golombEncodeNum m) l

-- | Rice decode a list.
declist _ [] = []
declist m l  = x : declist m rest
    where (x, rest) = golombDecodeNum m l

sdEncoded = enclist 2 sampleData


-- QuickCheck properties

prop_encdec_single x k = x >= 0 && k >= 0 ==> golombDecodeNum m (golombEncodeNum m y) == (y, [])
    where m = 2 ^ (k `mod` 6)
          y = x `mod` 12345

prop_encdec_sample k = k >= 0 ==> declist m (enclist m sampleData) == sampleData
    where m = 2 ^ (k `mod` 6)

runQC = $(quickCheckAll)
main = runQC