{-Lucas Matos Rodrigues 12311BCC024 Raquel Emillene Freire Thome 12311DCC026 -}


-- | Esse modulo composto por diversas funcoes que trabalham junto com objetivo implementar uma lista de ferramentas para manipulacao de numeros em diversas bases

module Main (main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

-- | Função principal que inicia o programa
main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    initMenu

-- | Inicia o menu principal
initMenu :: IO ()
initMenu = do
    op <- menu
    laçoMenu op

-- | Laço para redirecionar para as funções correspondentes ao menu selecionado
laçoMenu :: Int -> IO ()
laçoMenu op = do
    n <- entrad op
    case op of
        1 -> do 
            imprimirResultado op n (show (deBD n))
            submenu op
        2 -> do 
            imprimirResultado op n (show (deHD n))
            submenu op
        3 -> do 
            imprimirResultado op n (deDB (read n :: Int))
            submenu op
        4 -> do 
            imprimirResultado op n (deDH (read n :: Int))
            submenu op
        5 -> do 
            imprimirResultado op n (deBH n)
            submenu op
        6 -> do 
            imprimirResultado op n (deHB n)
            submenu op
        7 -> do 
            imprimirResultado op n (show (deFbD n))
            submenu op
        8 -> do 
            imprimirResultado op n (deFdB n)
            submenu op
        9 -> do 
            putStrLn "Digite o segundo binário: "
            n1 <- getLine
            imprimirResultado op n (somadois n n1)
            submenu op
        0 -> do 
            imprimirResultado op n ""
            return ()
        _ -> do 
            putStrLn "Opção inválida"
            submenu op

-- | Mostra um texto específico para cada opção do submenu
subtexto:: Int -> IO()
subtexto op = do
    case op of
        1 -> putStrLn "Deseja converter outro binário (s/n)? "
        2 -> putStrLn "Deseja converter outro hexadecimal (s/n)? "
        3 -> putStrLn "Deseja converter outro natural (s/n)? "
        4 -> putStrLn "Deseja converter outro natural (s/n)? "
        5 -> putStrLn "Deseja converter outro binário (s/n)? "
        6 -> putStrLn "Deseja converter outro hexadecimal (s/n)? "
        7 -> putStrLn "Deseja converter outro binário fracionário (s/n)? "
        8 -> putStrLn "Deseja converter outro real (s/n)? "
        9 -> putStrLn "Deseja somar outros binários (s/n)?"
        _ -> return ()

-- | Submenu de opções
submenu:: Int -> IO()
submenu opc = do
    subtexto opc
    op <- getLine 
    veri opc op
    where
        veri opc op 
            | op == "S" || op == "s" = do 
                laçoMenu opc
            | op == "N" || op == "n" = do 
                initMenu
            | otherwise = do 
                putStrLn "Opção inválida!"
                putStrLn ""
                submenu opc

-- | Função que solicita uma entrada conforme a opção escolhida no menu
entrad :: Int -> IO String
entrad op = do
    val <- case op of
        1 -> do
            putStrLn "Digite um binário: "
            getLine
        2 -> do
            putStrLn "Digite um hexadecimal: "
            getLine
        3 -> do
            putStrLn "Digite um natural: "
            getLine
        4 -> do
            putStrLn "Digite um natural: "
            getLine
        5 -> do
            putStrLn "Digite um binário: "
            getLine
        6 -> do
            putStrLn "Digite um hexadecimal: "
            getLine
        7 -> do
            putStrLn "Digite um binário fracionário: "
            getLine
        8 -> do
            putStrLn "Digite um real: "
            getLine
        9 -> do
            putStrLn "Digite o primeiro binário: "
            getLine
        0 -> do return ""
        _ -> do
            putStrLn "Opção inválida"
            return ""
    return val

-- | Exibe o menu principal
menu :: IO Int
menu = do
    exibirOpções texto
    lerOpção opMín opMáx
    where
        texto = [ "****************************************************\n*                    Conversor                     *\n****************************************************\n",
                  "1 - Converter de binário para decimal",
                  "2 - Converter de hexadecimal para decimal",
                  "3 - Converter de decimal para binário",
                  "4 - Converter de decimal para hexadecimal",
                  "5 - Converter de binário para hexadecimal",
                  "6 - Converter de hexadecimal para binário",
                  "7 - Converter de fração binária para decimal",
                  "8 - Converter de fração decimal para binário",
                  "9 - Somar dois binários sem sinal",
                  "0 - sair" ]
        opMín = 0
        opMáx = 9

-- | Exibe as opções de um menu
exibirOpções :: [String] -> IO ()
exibirOpções opções = do
    putStrLn ""
    putStrLn "Opções:"
    putStrLn ""
    putStrLn (unlines opções)
    putStrLn ""

-- | Lê a opção escolhida pelo usuário
lerOpção :: Int -> Int -> IO Int
lerOpção mínima máxima = do
    putStr "Digite uma opção: "
    opção <- readLn
    valida opção
    where
        valida opção 
            | mínima <= opção && opção <= máxima = return opção
            | otherwise = do
                putStrLn "Opção inválida!"
                putStrLn ""
                putStr "Digite uma opção: "
                opção <- readLn
                valida opção

-- | Imprime o resultado das conversões
imprimirResultado :: Int -> String -> String -> IO ()
imprimirResultado op n res = do
    putStrLn ""
    putStrLn "--------------------------------------------------"
    case op of
        1 -> putStrLn converterBD
        2 -> putStrLn converterHD
        3 -> putStrLn converterDB
        4 -> putStrLn converterDH
        5 -> putStrLn converterBH
        6 -> putStrLn converterHB
        7 -> putStrLn converterFD
        8 -> putStrLn converterFB
        9 -> putStrLn somarBis
        _ -> putStrLn "Fim"
    putStrLn "--------------------------------------------------"
    where
        converterBD = n ++ "_(2) = " ++ res ++ "_(10)"
        converterHD = n ++ "_(16) = " ++ res ++ "_(10)"
        converterDB = n ++ "_(10) = " ++ res ++ "_(2)"
        converterDH = n ++ "_(10) = " ++ res ++ "_(16)"
        converterBH = n ++ "_(2) = " ++ res ++ "_(16)"
        converterHB = n ++ "_(16) = " ++ res ++ "_(2)"
        converterFD = n ++ "_(2) = " ++ res ++ "_(10)"
        converterFB = n ++ "_(10) = " ++ res ++ "_(2)"
        somarBis    = "O resultado da soma eh: "++ res
   


-- | Converte uma representação binária em decimal.
deBD :: String    
     -> Int       
deBD [] = 0
deBD (x:xs) = if x == '1'
                then 2^(length xs) + deBD xs
                else deBD xs



-- | Converte uma representação hexadecimal em decimal.
deHD :: String    
     -> Int       
deHD [] = 0
deHD (x:xs) = (v * (16^(length xs))) + deHD xs
    where
        v = numH x

-- | Converte um caractere hexadecimal em decimal.
numH :: Char     
     -> Int      
numH x 
    | '0' <= x && x <= '9' = fromEnum x - fromEnum '0'
    | 'a' <= x && x <= 'f' = fromEnum x - fromEnum 'a' + 10
    | 'A' <= x && x <= 'F' = fromEnum x - fromEnum 'A' + 10

-- | Converte um número decimal em binário.
deDB :: Int      
     -> String   
deDB 0 = "0"
deDB dec
    | ((mod dec 2) == 1) = deDB (div dec 2) ++ "1"
    | otherwise          = deDB (div dec 2) ++ "0"

-- | Converte um número decimal em hexadecimal.
deDH :: Int      
     -> String   
deDH 0 = "0"
deDH dec = deDH (div dec 16) ++ [hexChar (mod dec 16)]
    where
        
hexChar :: Int    
        -> Char   
hexChar x
        | 0 <= x && x <= 9 = toEnum (x + fromEnum '0')
        | 10 <= x && x <= 15 = toEnum (x - 10 + fromEnum 'A')
        | otherwise = error "invalido"

-- | Converte uma representação binária em hexadecimal.
deBH :: String   
     -> String   
deBH [] = "0"
deBH bs = hs 
       where
         hs = deDH dec
         dec = deBD bs

-- | Converte uma representação hexadecimal em binário.
deHB :: String   
     -> String   
deHB [] = "0"
deHB hs = bs
        where
          bs = deDB dec
          dec = deHD hs

-- | Converte uma representação binária fracionária em decimal.
deFbD :: String     
      -> Double    
deFbD [] = 0
deFbD xs = retorno
        where
          (inteiro, frac) = separar xs
          intt            = deBD inteiro
          fracc           = deFrac frac
          retorno         = fromIntegral(intt) + fracc


-- | Separa a parte inteira da parte fracionária de um número binário fracionário.
separar :: String           
        -> (String, String) 
separar [] = ([], [])
separar (x:xs)
    | x == ',' || x == '.' = ([], xs)
    | otherwise             = (x : parteInteira, parteFracionaria)
    where
        (parteInteira, parteFracionaria) = separar xs


-- | Converte uma representação binária fracionária em decimal.
deFrac :: String 
       -> Double 
deFrac [] = 0
deFrac bits = deFrac'  bits 1
  where
    deFrac' [] _ = 0
    deFrac' (x:xs) position
        | x == '1'  = 2 ** fromIntegral (-position) + deFrac' xs (position + 1)
        | otherwise = deFrac' xs (position + 1)

-- | Converte uma representação decimal fracionária em binário.
deFdB :: String   
      -> String   
deFdB "0"  = "0"
deFdB xs = retorno
        where
          (inteiro, frac) = separar xs
          intt = deDB (read (inteiro) :: Int)
          fracc = deDFrac (read("0."++frac):: Double) 0
          retorno = intt ++ "," ++  fracc


-- | Converte um valor decimal fracionário em uma representação binária fracionária.
--
--   Se o valor passado for 0 ou o contador de iteração chegar a 16, a função retorna uma string vazia.
--   Caso contrário, a função continua a iteração, convertendo a parte fracionária do número decimal em binário.
deDFrac :: Double  
        -> Int     
        -> String  
deDFrac x i = 
    if x == 0 || i == 16
        then ""
        else if x*2 >= 1
            then "1" ++ deDFrac (2*x - 1) (i+1) -- Se x for maior ou igual a 1, adiciona "1" à representação binária e continua a iteração
            else "0" ++ deDFrac (2*x) (i+1)    -- Se x for menor que 1, adiciona "0" à representação binária e continua a iteração

-- | Soma dois números binários fracionários representados por strings e retorna a representação binária fracionária do resultado.
-- | O resultado é calculado convertendo os números binários fracionários para valores decimais, somando-os e convertendo o resultado de volta para binário.
somadois :: String    
         -> String    
         -> String    
somadois xs ys = res
    where
        x = deFbD xs  
        y = deFbD ys  
        res = deFdB (show (x + y))  
