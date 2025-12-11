SET search_path TO TRABFINAL;

UPDATE CONTA
SET SENHA = 'X8r@fLq92!TmWzD'
WHERE NomeDeUsuario = 'carlos_silva';

select NomeDeUsuario, Senha
from CONTA
where NomeDeUsuario = 'carlos_silva';


UPDATE EMPRESARIAL
SET Codigo = 4
WHERE Conta = 'ana_oliveira95';

select Conta, Codigo
from EMPRESARIAL
where Conta = 'ana_oliveira95';