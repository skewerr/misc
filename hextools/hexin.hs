import System.Environment
import System.IO
import Data.Bits
import Data.Word
import qualified Data.ByteString as BS

hexChars = ['0'..'9'] ++ ['a'..'f'] ++ ['A'..'F']

chunksOf :: Int -> String -> [String]
chunksOf _ [] = []
chunksOf n xs = (take n xs) : (chunksOf n (drop n xs))

readHexByte :: String -> Word8
readHexByte s = read $ "0x" ++ s

readHexPairs :: String -> [String]
readHexPairs = chunksOf 2 . filter (`elem` hexChars)

readHexBytes :: String -> [Word8]
readHexBytes = map readHexByte . readHexPairs

main :: IO ()
main = do
    destFilePath <- (!! 0) <$> getArgs
    destString <- BS.pack . readHexBytes <$> getContents
    withBinaryFile destFilePath WriteMode $ (flip BS.hPut) destString
