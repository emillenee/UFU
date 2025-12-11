SET search_path TO TRABFINAL;

/* Encontrar o post comum mais curtido de cada página */
SELECT pc.Post_ID, pc.Curtidas, pc.Pagina_Nome,P.titulo
FROM POSTCOMUM pc
JOIN POST P ON P.id = pc.post_id 
WHERE pc.Curtidas = (
    SELECT MAX(Curtidas)
    FROM POSTCOMUM
    WHERE Pagina_Nome = pc.Pagina_Nome AND Pagina_Conta = pc.Pagina_Conta)
ORDER BY curtidas DESC;



/* Ranking de contas empresariais com mais páginas e maior taxa de conversão média */
SELECT e.Conta, COUNT(pg.Nome) AS TotalPaginas, AVG(pr.Taxa_conversao) AS MediaConversao
FROM EMPRESARIAL e
JOIN PAGINA pg ON pg.Conta = e.Conta
JOIN PPROPAGANDA pr ON pr.Pagina_Nome = pg.Nome AND pr.Pagina_Conta = pg.Conta
GROUP BY e.Conta
ORDER BY MediaConversao DESC;



/* Encontrar grupos com mais participantes e suas categorias */
SELECT g.Nome, g.Categoria, COUNT(p.Conta_Pessoal) AS TotalParticipantes
FROM GRUPOS g
LEFT JOIN PARTICIPA p ON g.Codigo = p.Grupos
GROUP BY g.Codigo, g.Nome, g.Categoria
ORDER BY TotalParticipantes DESC;




/* MOSTRAR DADOS DE UM USUARIO */
SELECT C.Nome, C.Email, P.NumAmigos, G.Nome AS Grupo, PA.Nome AS Pagina
FROM CONTA C
JOIN PESSOAL P ON C.NomeDeUsuario = P.Conta
LEFT JOIN PARTICIPA PR ON PR.Conta_Pessoal = P.Conta
LEFT JOIN GRUPOS G ON G.Codigo = PR.Grupos
LEFT JOIN PAGINA PA ON PA.Conta = P.Conta
WHERE C.NomeDeUsuario = 'ricardo.ferreira';



/* LISTAR FUNCIONALIDADES DE UM PACOTE */
SELECT p.Codigo, p.Nome AS nome_pacote, p.Taxa,STRING_AGG(f.Funcionalidade, ', ') AS funcionalidades
FROM PACOTE p
JOIN FUNCIONALIDADES f ON p.Codigo = f.Codigo
GROUP BY p.Codigo, p.Nome
ORDER BY P.codigo;



/*Sugerir grupos para usuários com base em grupos visíveis para páginas que eles seguem
Usuários que participam de poucos grupos podem receber sugestões com base em visibilidade de páginas que eles consomem. */

SELECT DISTINCT 
    ps.Conta,
    g.Codigo AS grupo_sugerido,
    g.Nome AS nome_grupo,
    g.Categoria
FROM 
    PESSOAL ps
JOIN PRIVILEGIOS pr ON ps.Conta = pr.Pessoal_conta
JOIN FICA_VISIVEL fv ON pr.Pagina_Nome = fv.Nome AND pr.Pagina_Conta = fv.PaginaConta
JOIN GRUPOS g ON fv.Codigo = g.Codigo
LEFT JOIN PARTICIPA pa ON ps.Conta = pa.Conta_Pessoal AND g.Codigo = pa.Grupos
WHERE pa.Grupos IS NULL;



/* Eventos futuros organizados por contas com maior número de conexões */

SELECT 
    ev.Nome AS nome_evento,
    ev.Data,
    ev.Local,
    ev.Conta,
    COUNT(DISTINCT co.Conta2) AS conexoes
FROM 
    EVENTO ev
JOIN CONECTA co ON ev.Conta = co.Conta1 OR ev.Conta = co.Conta2
WHERE ev.Data > NOW()
GROUP BY ev.Nome, ev.Data, ev.Local, ev.Conta
ORDER BY conexoes DESC;



/* Contas pessoais que mais geram conteúdo (posts, newsletters, comentários) */

SELECT 
    ps.Conta,
    COUNT(DISTINCT po.Id) AS total_posts,
    COUNT(DISTINCT n.Titulo) AS total_newsletters,
    COUNT(DISTINCT c.Comentario) AS total_comentarios,
    (COUNT(DISTINCT po.Id) + COUNT(DISTINCT n.Titulo) + COUNT(DISTINCT c.Comentario)) AS producao_total
FROM 
    PESSOAL ps
LEFT JOIN PAGINA pg ON ps.Conta = pg.Conta
LEFT JOIN POST po ON pg.Nome = po.Pagina_Nome AND pg.Conta = po.Pagina_Conta
LEFT JOIN NEWSLETTER n ON ps.Conta = n.Conta_Pessoal
LEFT JOIN COMENTARIOS c ON ps.Conta = c.Conta_Comentador
GROUP BY ps.Conta
ORDER BY producao_total DESC;




/* pacotes mais contratados pelas empresas */

SELECT P.CODIGO, P.NOME AS Nome_pacote, P.TAXA, COUNT(*) AS Número_contratações
FROM PACOTE P
JOIN EMPRESARIAL E ON E.CODIGO = P.CODIGO
GROUP BY P.CODIGO
ORDER BY COUNT(*) DESC;



/* Serviços mais oferecidos e os posts de cada */
SELECT S.SERVICO, COUNT(*) AS Quantidade_ofertas, STRING_AGG(P.titulo, ' ; ')  AS Títulos
FROM SERVICO S 
JOIN POST P ON S.POST_ID = P.ID 
GROUP BY S.SERVICO 
ORDER BY COUNT(*);



/* STORED PROCEDURE ------------------------------------------------ */
/* Procedimento armazenado para verificar se existe um usuário 
com o nome e senha informados na tabela, simulando uma operação de login em um site. */

CREATE OR REPLACE FUNCTION AutenticarUsuario( usuario_input VARCHAR, senha_input VARCHAR ) RETURNS BOOLEAN AS $$ 
DECLARE 
    existe BOOLEAN; 
BEGIN 
    SELECT EXISTS ( 
        SELECT 1 
        FROM CONTA 
        WHERE NomeDeUsuario = usuario_input 
          AND Senha = senha_input 
    ) INTO existe; 
    RETURN existe; 
END; 
$$ LANGUAGE plpgsql;

Select * from AutenticarUsuario ('carlos_silva', 'Jf8!sG2k');