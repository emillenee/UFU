{-Lucas Matos Rodrigues 12311BCC024 e Raquel Emillene Freire Thome 12311DCC026 -}

module Main (main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering), writeFile, readFile)
import System.Directory (doesFileExist)
import Data.Char (toUpper)
import Data.List (sort)

-- | Funcao principal que inicia o programa
main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    initMenu ([],[])


data Estudante = Estudante { nomeEstudante :: String
                           , matricula     :: String
                           , nota1         :: Double
                           , nota2         :: Double
                           , nota3         :: Double
                           , trab1         :: Double
                           , trab2         :: Double
                           , numeroFaltas  :: Int
                           , notaFinal     :: Double
                           , situacaoFinal :: String
                           } deriving (Show)

-- | Inicia o menu principal
initMenu :: (String,[Estudante]) -> IO ()
initMenu xs = do
    op <- menu
    lacoMenu op xs

-- | Exibe um menu de opções e permite que o usuário selecione uma opção.
menu :: IO Int
menu = do
    exibirOpcoes texto
    lerOpcao opMín opMáx
  where
    -- Texto do menu
    texto = [ "=========================================\n*              Menu Principal           *\n=========================================\n"
            , "1 - Ler turma de estudantes do arquivo"
            , "2 - Imprimir turma de estudantes"
            , "3 - Imprimir estatísticas da turma"
            , "4 - Cadastrar novo estudante"
            , "5 - Editar informações de um estudante"
            , "6 - Reler turma de estudantes do arquivo"
            , "7 - Salvar e Sair"
            ]
    -- Opções mínimo e máximo
    opMín = 0
    opMáx = 7

-- | Exibe as opções de um menu.
exibirOpcoes :: [String] -> IO ()
exibirOpcoes opcoes = do
    putStrLn ""
    putStrLn ""
    putStrLn (unlines opcoes)
    putStrLn ""

-- | Lê a opção escolhida pelo usuário.
lerOpcao :: Int -> Int -> IO Int
lerOpcao mínima máxima = do
    putStr "Digite uma opcao: "
    opcao <- readLn
    valida opcao
  where
    -- Valida a opção
    valida opcao 
        | mínima <= opcao && opcao <= máxima = return opcao
        | otherwise = do
            putStrLn "Opcao inválida!"
            putStrLn ""
            putStr "Digite uma opcao: "
            opcao <- readLn
            valida opcao

-- | Laço para redirecionar para as funções correspondentes ao menu selecionado.
lacoMenu :: Int -> (String, [Estudante]) -> IO ()
lacoMenu op xs = do
    case op of
        1 -> do 
           opcao01 xs
        2 -> do 
           opcao02 xs
        3 -> do 
           opcao03 xs 
        4 -> do 
           opcao04 xs       
        5 -> do 
           opcao05 xs   
        6 -> do 
           opcao06 xs
        7 -> do
           opcao07 xs 
        0 -> do 
          return()
        _ -> do 
            putStrLn "Opcao inválida"
            initMenu xs

-- Funcao que pega a string ,que recebeu o conteudo do arquivo, retorna uma lista de contendo os estudantes   
toEst :: [String] -> [Estudante]     
toEst [] = []       
toEst (n:m:n1:n2:n3:t1:t2:f:nf:c:xs) = aluno : (toEst xs)
      where 
        aluno = Estudante n m (read n1 :: Double) (read n2 :: Double) (read n3 :: Double) (read t1 :: Double) (read t2 :: Double) (read f :: Int ) (read nf :: Double) c


-- | Converte uma lista de estudantes em uma string formatada.
toStr :: [Estudante]-> String
toStr (x:xs) = do
    case xs of
        [] -> (nomeEstudante x) ++ "\n" ++ (matricula x) ++ "\n" ++ (show (nota1 x)) ++ "\n" ++ (show (nota2 x)) ++ "\n" ++ (show (nota3 x)) ++ "\n" ++ (show (trab1 x)) ++ "\n" ++ (show (trab2 x)) ++ "\n" ++ (show (numeroFaltas x)) ++ "\n" ++ (show(notaFinal x) ++ "\n" ++ (situacaoFinal x))
        xs -> (nomeEstudante x) ++ "\n" ++ (matricula x) ++ "\n" ++ (show (nota1 x)) ++ "\n" ++ (show (nota2 x)) ++ "\n" ++ (show (nota3 x)) ++ "\n" ++ (show (trab1 x)) ++ "\n" ++ (show (trab2 x)) ++ "\n" ++ (show (numeroFaltas x)) ++ "\n" ++ (show(notaFinal x) ++ "\n" ++ (situacaoFinal x) ++ "\n" ++ (toStr xs))

-- | Realiza operações de acordo com a opção escolhida no submenu 1.
opcao01 :: (String, [Estudante]) -> IO ()
opcao01 xs = do
    subopp <- submenu1
    case subopp of
        1 -> do
            abrirArquivo xs
        2 -> do
            criarArquivo xs  
        3 -> do
            initMenu xs       

-- | Abre um arquivo contendo a turma de estudantes.
abrirArquivo :: (String,[Estudante])-> IO()
abrirArquivo xs = do
    putStrLn "Digite o nome do arquivo com a turma: "
    nomeArquivo <- getLine
    existe <- doesFileExist nomeArquivo
    if existe == True
        then do
            informacoes <- readFile nomeArquivo
            putStrLn ("Arquivo " ++ nomeArquivo ++ " lido com sucesso!")
            initMenu (nomeArquivo , toEst (lines informacoes))
        else do
            putStrLn ("O arquivo " ++ nomeArquivo ++ " não existe!")
            initMenu xs  

-- | Cria um novo arquivo para a turma de estudantes.
criarArquivo :: (String,[Estudante])-> IO()
criarArquivo xs = do
    putStrLn "Digite o nome do arquivo para a nova turma: "
    nomeArquivo <- getLine
    existe <- doesFileExist nomeArquivo
    if existe == True
        then do
        putStrLn ("Arquivo" ++ nomeArquivo ++ "já existe. Deseja sobrescrevê-lo? (S/N)")
        opcao <- getLine
        case map toUpper opcao of
            "S" -> do
                let informacoes = ""
                writeFile nomeArquivo informacoes
                putStrLn ("Arquivo" ++ nomeArquivo ++ "sobrescrito com sucesso.")
                initMenu (nomeArquivo, [])
            "N" -> do initMenu xs
            _   -> do 
                putStrLn "Opção inválida."
                initMenu xs
    else do
        let informacoes = ""
        writeFile nomeArquivo informacoes
        putStrLn ("Arquivo" ++ nomeArquivo ++ "criado com sucesso.")
        initMenu (nomeArquivo, [])  

-- | Realiza operações de acordo com a opção escolhida no submenu 2.
opcao02 :: (String,[Estudante])-> IO()
opcao02 xs = do
    case xs of 
        ([] ,_   ) -> do
            putStrLn "Não há turma carregada"
            initMenu xs
        (x  ,xss ) -> do
            imprimeturma xss   
            initMenu xs    

-- | Imprime a turma de estudantes na tela.
imprimeturma :: [Estudante]-> IO ()
imprimeturma xs = do
    putStr   (replicate 40 ' ')
    putStrLn "Estudantes"
    putStrLn (replicate 102 '=')
    putStrLn ("Nome" ++ (replicate 47 ' ') ++ "Matricula" ++ (replicate 4 ' ') ++ "N1   N2   N3   T1   T2   Fal Final Sit") 
    putStrLn (replicate 102 '_')
    uxiprimeturma(lines(toStr xs))
    putStrLn (replicate 90 ' ')

-- | Imprime uma lista formatada de informações de estudantes na tela.
uxiprimeturma :: [String] -> IO ()
uxiprimeturma [] = return ()
uxiprimeturma (n:m:n1:n2:n3:t1:t2:f:nf:c:xs) = do
    putStr n
    putStr (replicate (51 - length n) ' ')
    putStr m
    putStr (replicate (12 - length m) ' ')
    putStr (replicate (5 - length n1) ' ')
    putStr n1
    putStr (replicate (5 - length n2) ' ')
    putStr n2
    putStr (replicate (5 - length n3) ' ')
    putStr n3
    putStr (replicate (5 - length t1) ' ')
    putStr t1
    putStr (replicate (5 - length t2) ' ')
    putStr t2
    putStr (replicate (4 - length f) ' ')
    putStr f
    putStr (replicate (5 - length nf) ' ')
    putStr nf
    putStr "  "
    putStrLn c
    uxiprimeturma xs

-- | Imprime informações de estudantes individualmente na tela.
aximprimeturma :: [Estudante] -> IO()
aximprimeturma [] = return ()
aximprimeturma (x:xs) = do
    putStrLn (show x) 
    aximprimeturma xs

opcao03 :: (String,[Estudante])-> IO()
opcao03 xs = do
    case xs of 
        ([]   , _         ) -> do
                    putStrLn "Não há turma carregada!"
                    initMenu xs
        (turma, estudantes) -> do
                    mostrarEstatisticas (turma, estudantes)
                    initMenu xs 

-- | Imprime as estatísticas da turma, incluindo maiores e menores notas, notas médias, medianas e distribuição de aprovação/reprovação.
mostrarEstatisticas :: (String, [Estudante]) -> IO()
mostrarEstatisticas (x, estudantes)  = do
    putStrLn "                      Estatísticas"
    putStrLn (replicate 75 '=')
    putStr (replicate 40 ' ')
    putStrLn "N1    N2    N3    T1    T2    Final"
    putStrLn (replicate 75 '_')
    let maiorNota1 = show(maiorNota estudantes nota1)
    let maiorNota2 = show(maiorNota estudantes nota2)
    let maiorNota3 = show(maiorNota estudantes nota3)
    let maiorTrab1 = show(maiorNota estudantes trab1)
    let maiorTrab2 = show(maiorNota estudantes trab2)
    let maiorNotaFinal = show(maiorNota estudantes notaFinal)
    putStr "Maiores notas da turma      " 
    putStr (replicate 12 ' ')
    putStrLn ( maiorNota1 ++ (replicate (6-(length maiorNota1)) ' ') ++ maiorNota2 ++ (replicate (6-(length maiorNota2)) ' ')  ++  maiorNota3 ++ (replicate (6-(length maiorNota3)) ' ')  ++  maiorTrab1 ++ (replicate (6-(length maiorTrab1)) ' ')  ++  maiorTrab2 ++ (replicate (6-(length maiorTrab2)) ' ')  ++  maiorNotaFinal)

    putStr "Menores notas da turma      "
    let menorNota1 = show(menorNota estudantes nota1)
    let menorNota2 = show(menorNota estudantes nota2)
    let menorNota3 = show(menorNota estudantes nota3)
    let menorTrab1 = show(menorNota estudantes trab1)
    let menorTrab2 = show(menorNota estudantes trab2)
    let menorNotaFinal = show(menorNota estudantes notaFinal)
    putStr (replicate 12 ' ')
    putStrLn ( menorNota1 ++ (replicate (6-(length menorNota1)) ' ') ++ menorNota2 ++ (replicate (6-(length menorNota2)) ' ')  ++  menorNota3 ++ (replicate (6-(length menorNota3)) ' ')  ++  menorTrab1 ++ (replicate (6-(length menorTrab1)) ' ')  ++  menorTrab2 ++ (replicate (6-(length menorTrab2)) ' ')  ++  menorNotaFinal)
    

    putStr "Notas médias da turma       " 
    let mediaNota1 = show(notaMedia estudantes nota1)
    let mediaNota2 = show(notaMedia estudantes nota2)
    let mediaNota3 = show(notaMedia estudantes nota3)
    let mediaTrab1 = show(notaMedia estudantes trab1)
    let mediaTrab2 = show(notaMedia estudantes trab2)
    let mediaNotaFinal = show(notaMedia estudantes notaFinal)
    putStr (replicate 12 ' ')
    putStrLn ( mediaNota1 ++ (replicate (6-(length mediaNota1)) ' ') ++ mediaNota2 ++ (replicate (6-(length mediaNota2)) ' ')  ++  mediaNota3 ++ (replicate (6-(length mediaNota3)) ' ')  ++  mediaTrab1 ++ (replicate (6-(length mediaTrab1)) ' ')  ++  mediaTrab2 ++ (replicate (6-(length mediaTrab2)) ' ')  ++  mediaNotaFinal)
    
    putStr "Medianas das notas da turma " 
    let notas1 = map nota1 estudantes
    let medianaNota1 = show(mediana notas1)
    let notas2 = map nota2 estudantes
    let medianaNota2 = show(mediana notas2)
    let notas3 = map nota3 estudantes
    let medianaNota3 = show(mediana notas3)
    let trab1s = map trab1 estudantes
    let medianaTrab1 = show(mediana trab1s)
    let trab2s = map trab2 estudantes
    let medianaTrab2 = show(mediana trab2s)
    let notasFinais = map notaFinal estudantes
    let medianaNotaFinal = show(mediana notasFinais)
    putStr (replicate 12 ' ')
    putStrLn ( medianaNota1 ++ (replicate (6-(length medianaNota1)) ' ') ++ medianaNota2 ++ (replicate (6-(length medianaNota2)) ' ')  ++  medianaNota3 ++ (replicate (6-(length medianaNota3)) ' ')  ++  medianaTrab1 ++ (replicate (6-(length medianaTrab1)) ' ')  ++  medianaTrab2 ++ (replicate (6-(length medianaTrab2)) ' ')  ++  medianaNotaFinal)


    putStrLn (replicate 75 '_')
    putStrLn ""
    let aprovados = length (filter (\estudante -> situacaoFinal estudante == "A") estudantes)
    let pA = (fromIntegral aprovados / fromIntegral (length estudantes)) * 100 
    putStrLn ("Número de estudantes aprovados:            " ++ show aprovados ++ " (" ++ show pA ++ "%)")
    let reprovados = length (filter (\estudante -> situacaoFinal estudante == "R") estudantes)
    let pR = (fromIntegral reprovados / fromIntegral (length estudantes)) * 100
    putStrLn ("Número de estudantes reprovados:           " ++ show reprovados ++ " (" ++ show pR ++ "%)")
    let reprovadosF = length (filter (\estudante -> situacaoFinal estudante == "F") estudantes)
    let pF = (fromIntegral reprovadosF / fromIntegral (length estudantes)) * 100
    putStrLn ("Número de estudantes reprovados por falta: " ++ show reprovados ++ " (" ++ show pF ++ "%)")
    putStrLn (replicate 75 '_')
    putStrLn ""
    histograma estudantes

histograma :: [Estudante] -> IO()
histograma estudantes = do
    let notasFinais = map notaFinal estudantes
    let zeroA10 = length (filtrarNotas 0 10 notasFinais)
    let onzeA20 = length (filtrarNotas 11 20 notasFinais)
    let vinte1A30 = length (filtrarNotas 21 30 notasFinais)
    let trinta1A40 = length (filtrarNotas 31 40 notasFinais)
    let quarenta1A50 = length (filtrarNotas 41 50 notasFinais)
    let cinco1A60 = length (filtrarNotas 51 60 notasFinais)
    let seis1A70 = length (filtrarNotas 61 70 notasFinais)
    let sete1A80 = length (filtrarNotas 71 80 notasFinais)
    let oito1A90 = length (filtrarNotas 81 90 notasFinais)
    let nove1A100 = length (filtrarNotas 91 100 notasFinais)

    putStrLn ("Histograma de notas finais em grupos de 10 pontos:")
    putStrLn (" 0 - 10:  " ++ show zeroA10 ++ replicate zeroA10 '*')
    putStrLn ("11 - 20:  " ++ show onzeA20 ++ replicate onzeA20 '*')
    putStrLn ("21 - 30:  " ++ show vinte1A30 ++ replicate vinte1A30 '*')
    putStrLn ("31 - 40:  " ++ show trinta1A40 ++ replicate trinta1A40 '*')
    putStrLn ("41 - 50:  " ++ show quarenta1A50 ++ replicate quarenta1A50 '*')
    putStrLn ("51 - 60:  " ++ show cinco1A60 ++ replicate cinco1A60 '*')
    putStrLn ("61 - 70:  " ++ show seis1A70 ++ replicate seis1A70 '*')
    putStrLn ("71 - 80:  " ++ show sete1A80 ++ replicate sete1A80 '*')
    putStrLn ("81 - 90:  " ++ show oito1A90 ++ replicate oito1A90 '*')
    putStrLn ("91 - 100: " ++ show nove1A100 ++ replicate nove1A100 '*')

-- | Opção do menu para cadastrar um novo estudante.
opcao04 :: (String, [Estudante]) -> IO ()
opcao04 xs = do
    case xs of 
        ([]   , _         ) -> do
                    putStrLn "Não há turma carregada!"
                    initMenu xs
        (turma, estudantes) -> do
                    cadastrarEstudante (turma, estudantes)

-- | Opção do menu para editar informações de um estudante existente.
opcao05 :: (String, [Estudante]) -> IO ()
opcao05 xs = do
    case xs of
        ([]   , _         ) -> do
                    putStrLn "Não há turma carregada!"
                    initMenu xs
        (turma, estudantes) -> do
                    subOpp <- subEditarInfo
                    case subOpp of
                        1 -> do
                            putStrLn "Digite o número de matrícula:"
                            matriculaE <- getLine
                            estudanteAtualizado <- editarInfo (\e -> matricula e == matriculaE) (turma, estudantes)
                            let estudantesAtualizados = estudanteAtualizado : filter (\e -> matricula e /= matriculaE) estudantes
                            lacoMenu 5 (turma, estudantesAtualizados)
                        2 -> do
                            putStrLn "Digite o nome:"
                            nome <- getLine
                            estudanteAtualizado <- editarInfo (\e -> nomeEstudante e == nome) (turma, estudantes)
                            let estudantesAtualizados = estudanteAtualizado : filter (\e -> nomeEstudante e /= nome) estudantes
                            lacoMenu 5 (turma, estudantesAtualizados)
                        3 -> do
                            initMenu xs 

-- | Opção do menu para reler a turma de estudantes do arquivo.
opcao06 :: (String, [Estudante]) -> IO ()
opcao06 xs = do
    case xs of
        ([]         ,_   ) -> do
            putStrLn "Nenhum arquivo ainda foi carregado!"
            initMenu xs
        (nomeArquivo,cont) -> do
            existe <- doesFileExist nomeArquivo
            if existe == True
                then do
                informacoes <- readFile nomeArquivo
                putStrLn ("Arquivo " ++ nomeArquivo ++ " lido com sucesso!")
                initMenu (nomeArquivo , toEst (lines informacoes))
                else do
                putStrLn ("O arquivo " ++ nomeArquivo ++ " não existe!")
                initMenu xs 

-- | Opção do menu para salvar e sair.
opcao07 :: (String, [Estudante]) -> IO ()
opcao07 xs = do
    case xs of
        ([]         ,_    ) -> do
            putStrLn "Não há turma carregada!"
            initMenu xs
        (turma, estudantes) -> do
            existe <- doesFileExist turma
            if existe
                then do
                    putStrLn "Arquivo já existe. Deseja sobrescrevê-lo? (S/N)"
                    opcao <- getLine
                    case map toUpper opcao of
                        "S" -> do
                            writeFile turma (toStr estudantes)
                            putStrLn "Até a próxima."
                            return () -- Termina o programa pois o loop do main é a "única" coisa que o programa está fazendo
                        "N" -> do
                            putStrLn "Até a próxima."
                            return ()
                        _  -> do
                            putStrLn "Opção inválida."
                            lacoMenu 7 (turma, estudantes)
            else do
                putStrLn "O arquivo não existe. Deseja criar um novo? (S/N)"
                opcao <- getLine
                case map toUpper opcao of
                    "S" -> do
                        writeFile turma (toStr estudantes)
                        putStrLn "Até a próxima."
                        return ()
                    "N" -> do
                        putStrLn "Até a próxima."
                        return ()
                    _  -> do
                        putStrLn "Opção inválida."
                        lacoMenu 7 (turma, estudantes)





--Função para retornar a situação do aluno, dependendo da nota final e das faltas
calcularSituacao :: Double -> Int -> String
calcularSituacao notaFinal faltas
    |notaFinal >= 60 && faltas <= 18 = "A"
    |faltas > 18 = "F" 
    |notaFinal < 60 = "R" 
    |otherwise = "Invalido"




-- | Submenu de opcoes
submenu1 :: IO Int
submenu1 = do
    exibirOpcoes texto
    lerOpcao 1 3  
    where
        texto = [ "=========================================\n                Ler Turma                    \n=========================================",
                "1 - Ler turma existente",
                "2 - Criar nova turma",
                "3 - Voltar ao menu principal"]


subEditarInfo :: IO Int 
subEditarInfo = do
    exibirOpcoes texto
    lerOpcao 1 3
    where
        texto = [ "=========================================\n     Editar Informações do Estudante                  \n=========================================",
                "1 - Selecionar por número de matrícula",
                "2 - Selecionar por nome",
                "3 - Voltar ao menu principal" ]

--Menu com as opções de alteração de estudante
subEditarInfo2 :: IO Int
subEditarInfo2 = do
    exibirOpcoes texto
    lerOpcao 1 9
    where
        texto = ["=========================================\n     Editar Informações do Estudante     \n=========================================", 
                "1 - Alterar nome",
                "2 - Alterar matrícula",
                "3 - Alterar nota da prova 1",
                "4 - Alterar nota da prova 2",
                "5 - Alterar nota da prova 3",
                "6 - Alterar nota do trabalho 1",
                "7 - Alterar nota do trabalho 2",
                "8 - Alterar número de faltas",
                "9 - Voltar ao menu anterior" ]


--Função que trabalha as opções de subEditarInfo2, que edita as informações de algum estudante
editarInfo :: (Estudante -> Bool) -> (String, [Estudante]) -> IO Estudante
editarInfo chave (nomeArquivo, estudantes) = do
    let estudanteFiltrado = filter chave estudantes
    case estudanteFiltrado of
        [] -> do
            putStrLn "Estudante não encontrado!"
            return (head estudantes)
        (e:_) -> do
            subOp <- subEditarInfo2
            case subOp of
                1 -> do
                    putStrLn "Digite o novo nome:"
                    novoNome <- getLine
                    let atualizado = e {nomeEstudante = novoNome}
                    putStrLn ("Nome atualizado:" ++ nomeEstudante atualizado)
                    editarInfo chave (nomeArquivo, atualizado : filter (not . chave) estudantes)
                    return atualizado
                2 -> do
                    putStrLn "Digite a nova matrícula:"
                    novaMatricula <- getLine
                    let atualizado = e {matricula = novaMatricula}
                    putStrLn ("Matrícula atualizada:" ++ matricula atualizado)
                    editarInfo chave (nomeArquivo, atualizado : filter (not . chave) estudantes)
                    return atualizado
                3 -> do
                    putStrLn "Digite a nota da prova 1:"
                    novaNota1 <- readLn
                    let atualizado = e {nota1 = novaNota1}
                    let attNotaFinal = recalcularNotaFinal atualizado
                    let situacao = calcularSituacao (notaFinal attNotaFinal) (numeroFaltas atualizado)
                    let attSituacao = atualizado {situacaoFinal = situacao}
                    putStrLn ("Nota da prova 1 atualizada:" ++ show (nota1 attSituacao))
                    editarInfo chave (nomeArquivo, attSituacao : filter (not . chave) estudantes)
                    return attSituacao
                4 -> do
                    putStrLn "Digite a nota da prova 2:"
                    novaNota2 <- readLn
                    let atualizado = e {nota2 = novaNota2}
                    let attNotaFinal = recalcularNotaFinal atualizado
                    let situacao = calcularSituacao (notaFinal attNotaFinal) (numeroFaltas atualizado)
                    let attSituacao = atualizado {situacaoFinal = situacao}
                    putStrLn ("Nota da prova 2 atualizada:" ++ show (nota2 attSituacao))
                    editarInfo chave (nomeArquivo, attSituacao : filter (not . chave) estudantes)
                    return attSituacao
                5 -> do
                    putStrLn "Digite a nota da prova 3:"
                    novaNota3 <- readLn
                    let atualizado = e {nota3 = novaNota3}
                    let attNotaFinal = recalcularNotaFinal atualizado
                    let situacao = calcularSituacao (notaFinal attNotaFinal) (numeroFaltas atualizado)
                    let attSituacao = atualizado {situacaoFinal = situacao}
                    putStrLn ("Nota da prova 3 atualizada:" ++ show (nota3 attSituacao))
                    editarInfo chave (nomeArquivo, attSituacao : filter (not . chave) estudantes)
                    return attSituacao
                6 -> do
                    putStrLn "Digite a nota do trabalho 1:"
                    novoTrab1 <- readLn
                    let atualizado = e {trab1 = novoTrab1}
                    let attNotaFinal = recalcularNotaFinal atualizado
                    let situacao = calcularSituacao (notaFinal attNotaFinal) (numeroFaltas atualizado)
                    let attSituacao = atualizado {situacaoFinal = situacao}
                    putStrLn ("Nota do trabalho 1 atualizada:" ++ show (trab1 attSituacao))
                    editarInfo chave (nomeArquivo, attSituacao : filter (not . chave) estudantes)
                    return attSituacao
                7 -> do
                    putStrLn "Digite a nota do trabalho 2:"
                    novoTrab2 <- readLn
                    let atualizado = e {trab2 = novoTrab2}
                    let attNotaFinal = recalcularNotaFinal atualizado
                    let situacao = calcularSituacao (notaFinal attNotaFinal) (numeroFaltas atualizado)
                    let attSituacao = atualizado {situacaoFinal = situacao}
                    putStrLn ("Nota do trabalho 2 atualizada:" ++ show (trab2 attSituacao))
                    editarInfo chave (nomeArquivo, attSituacao : filter (not . chave) estudantes)
                    return attSituacao
                8 -> do
                    putStrLn "Digite o número de faltas:"
                    novasFaltas <- readLn
                    let atualizado = e {numeroFaltas = novasFaltas}
                    let situacao = calcularSituacao (notaFinal atualizado) (numeroFaltas atualizado)
                    let attSituacao = atualizado {situacaoFinal = situacao}
                    putStrLn ("Número de faltas atualizado:" ++ show (numeroFaltas attSituacao))
                    editarInfo chave (nomeArquivo, attSituacao : filter (not . chave) estudantes)
                    return attSituacao
                9 -> do
                    return (head estudantes)
                _ -> do
                    putStrLn "Opção Inválida."
                    editarInfo chave (nomeArquivo, [e])



--Função que vai recalcular a nota final caso alguma nota seja alterada
recalcularNotaFinal :: Estudante -> Estudante
recalcularNotaFinal e = e {notaFinal = novaNotaFinal}
    where
      novaNotaFinal = (((nota1 e) + (nota2 e) + (nota3 e) + (trab1 e) + (trab2 e)) / 5.0)





-- Função que calcula a maior nota dentro da lista de estudantes
maiorNota :: [Estudante] -> (Estudante -> Double) -> Double
maiorNota [] _ = error "Lista vazia"
maiorNota [e] nota = nota e
maiorNota (e:es) nota
    | nota e > maiorNota es nota = nota e
    | otherwise = maiorNota es nota


-- Função que calcula a menor nota dentro da lista de estudantes
menorNota :: [Estudante] -> (Estudante -> Double) -> Double
menorNota [] _ = error "Lista vazia"
menorNota [e] nota = nota e
menorNota (e:es) nota
    | nota e < menorNota es nota = nota e
    | otherwise = menorNota es nota

-- Função que calcula a media das notas
notaMedia :: [Estudante] -> (Estudante -> Double) -> Double
notaMedia [] _ = error "Lista vazia"
notaMedia estudantes notas = somaNotas / quantidade
    where
      somaNotas = sum (map notas estudantes)
      quantidade = fromIntegral (length estudantes)
    
-- Função que retorna a mediana
mediana :: [Double] -> Double
mediana notas = if odd (length notas)
                then valorMeio
                else (valorMeio + valorMeio2) / 2
    where
      ordenado = sort notas
      meio = (div ((length notas) + 1) 2) - 1
      valorMeio = ordenado !! meio
      valorMeio2 = ordenado !! (meio + 1)



--Função que retorna só as notas dentro do intervalo
filtrarNotas :: Double -> Double -> [Double] -> [Double]
filtrarNotas min max notas = filter (\nota -> nota >= min && nota <= max) notas

{-
quantidadePorNota :: [Double] -> Int
quantidadePorNota notas = length notas
-}

-- OPÇÃO 4
cadastrarEstudante :: (String, [Estudante]) -> IO()
cadastrarEstudante (turma,estudantes) = do
    putStrLn "========================================="
    putStrLn "        Cadastrar Novo Estudante"
    putStrLn "========================================="
    putStrLn " "
    putStrLn "Digite o nome: "
    nome <- getLine
    putStrLn "Digite a matrícula:"
    matricula <- getLine
    putStrLn "Digite as três notas das provas:"
    nota1 <- readLn
    nota2 <- readLn
    nota3 <- readLn
    putStrLn "Digite as duas notas dos trabalhos:"
    trab1 <- readLn
    trab2 <- readLn
    putStrLn "Digite o número de faltas:"
    faltas <- readLn
    let notafinal = ((nota1 + nota2 + nota3 + trab1 + trab2) / 5.0)
    let situacaoFinal1 = calcularSituacao notafinal faltas
    let novoE = Estudante nome matricula nota1 nota2 nota3 trab1 trab2 faltas notafinal situacaoFinal1
    putStrLn ("Nota final calculada:" ++ show (notaFinal novoE))
    putStrLn ("Situação final:" ++ situacaoFinal1)
    initMenu (turma, estudantes ++ [novoE])