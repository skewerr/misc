import System.Environment
import System.IO
import Data.Bits
import Data.Word
import qualified Data.ByteString as BS

hexChars = ['0'..'9'] ++ ['A'..'F']

word82Hex :: Word8 -> String
word82Hex word =
    let fstHalf = shift word (-4)
        sndHalf = word .&. 15
        fstChar = hexChars !! (fromIntegral fstHalf)
        sndChar = hexChars !! (fromIntegral sndHalf)
    in  [fstChar, sndChar]

hexOutput :: Handle -> IO ()
hexOutput fh = do
    word8s <- BS.unpack <$> BS.hGetContents fh
    mapM_ putStr . map word82Hex $ word8s

main :: IO ()
main = do
    fileHandleFs <- map ((flip withBinaryFile) ReadMode) <$> getArgs
    mapM_ ($ hexOutput) fileHandleFs
    putStr "\n"
