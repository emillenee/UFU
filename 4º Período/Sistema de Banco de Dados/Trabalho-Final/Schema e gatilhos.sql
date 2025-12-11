CREATE SCHEMA TRABFINAL;

SET search_path TO TRABFINAL;

CREATE TABLE CONTA(
	NomeDeUsuario VARCHAR(20) PRIMARY KEY,
	Nome VARCHAR(50) NOT NULL,
	CPF VARCHAR(11) NOT NULL UNIQUE,
	Email VARCHAR(50) NOT NULL UNIQUE,
	Senha VARCHAR(50) NOT NULL CHECK (CHAR_LENGTH(Senha) >= 8),
	DataNascimento timestamp,
	Endereco VARCHAR(100)
);

CREATE TABLE TELEFONES(
	Conta VARCHAR(20) NOT NULL,
	Telefone VARCHAR(11) NOT NULL,
	PRIMARY KEY (Conta, Telefone),
	FOREIGN KEY (Conta) REFERENCES CONTA(NomeDeUsuario) ON DELETE CASCADE
);

CREATE TABLE PACOTE(
	Codigo SERIAL PRIMARY KEY,
    Nome VARCHAR(30) NOT NULL,
    Taxa FLOAT NOT NULL
); 

CREATE TABLE EMPRESARIAL(
	Conta VARCHAR(20),
	CNPJ VARCHAR(14) NOT NULL UNIQUE,
    Codigo INT,
	PRIMARY KEY (Conta),
	FOREIGN KEY (Conta) REFERENCES CONTA(NomeDeUsuario) ON DELETE CASCADE,
    FOREIGN KEY (Codigo) REFERENCES PACOTE(Codigo)
);

CREATE TABLE PESSOAL(
	Conta VARCHAR(20) NOT NULL,
	NumAmigos INT DEFAULT 0 CHECK (NumAmigos >= 0),
	PRIMARY KEY (Conta),
	FOREIGN KEY (Conta) REFERENCES CONTA(NomeDeUsuario) ON DELETE CASCADE
);

CREATE TABLE CONECTA(
	Conta1 VARCHAR(20),
	Conta2 VARCHAR(20),
	Status VARCHAR(20),
	PRIMARY KEY (Conta1, Conta2),
	FOREIGN KEY (Conta1) REFERENCES CONTA(NomeDeUsuario) ON DELETE CASCADE,
	FOREIGN KEY (Conta2) REFERENCES CONTA(NomeDeUsuario) ON DELETE CASCADE
);


CREATE TABLE FUNCIONALIDADES(
	Codigo INT,
    Funcionalidade VARCHAR(50),
   	PRIMARY KEY (Codigo, Funcionalidade),
   	FOREIGN KEY (Codigo) REFERENCES PACOTE(Codigo) ON DELETE CASCADE
);

CREATE TABLE GRUPOS(
	Codigo SERIAL PRIMARY KEY,
    Nome VARCHAR(40) NOT NULL,
   	Categoria VARCHAR(30) NOT NULL,
	Conta_Pessoal VARCHAR(20),
    FOREIGN KEY (Conta_Pessoal) REFERENCES PESSOAL(Conta)
);

CREATE TABLE PARTICIPA(
	Conta_Pessoal VARCHAR(20),
	Grupos INT,
    	PRIMARY KEY (Conta_Pessoal, Grupos),
    	FOREIGN KEY (Conta_Pessoal) REFERENCES PESSOAL(Conta),
    	FOREIGN KEY (Grupos) REFERENCES GRUPOS(Codigo)
);

CREATE TABLE PAGINA(
	Nome VARCHAR(50),
   	Conta VARCHAR(20),
  	Numero_visitas INT DEFAULT 0,
    PRIMARY KEY (Nome, Conta),
    FOREIGN KEY (Conta) REFERENCES CONTA(NomeDeUsuario)
);


CREATE TABLE PPROPAGANDA (
	Pagina_Nome VARCHAR(50),
	Pagina_Conta VARCHAR(20),
	Taxa_conversao FLOAT DEFAULT 0 CHECK (Taxa_conversao >= 0 AND Taxa_conversao <= 1),
	Taxa_cliques FLOAT DEFAULT 0 CHECK (Taxa_cliques >= 0 AND Taxa_cliques <= 1),
	Taxa_rejeicao FLOAT DEFAULT 0 CHECK (Taxa_rejeicao >= 0 AND Taxa_rejeicao <= 1),
	EmpresarialConta VARCHAR(20),
	PRIMARY KEY (Pagina_Nome, Pagina_Conta),
	FOREIGN KEY (Pagina_Nome, Pagina_Conta) REFERENCES PAGINA(Nome, Conta),
	FOREIGN KEY (EmpresarialConta) REFERENCES EMPRESARIAL(Conta)
);

CREATE TABLE FICA_VISIVEL(
	Codigo INT,
    	Nome VARCHAR(30),
	PaginaConta VARCHAR(20),
    	PRIMARY KEY (Codigo, Nome, PaginaConta),
    	FOREIGN KEY (Codigo) REFERENCES GRUPOS(Codigo),
    	FOREIGN KEY (Nome, PaginaConta) REFERENCES PAGINA(Nome, Conta)
);

CREATE TABLE ACAO(
	Codigo SERIAL PRIMARY KEY,
    Descricao VARCHAR(50) NOT NULL
);

CREATE TABLE PRIVILEGIOS (
	Pessoal_conta VARCHAR(20),
	Pagina_Nome VARCHAR(30),
	Pagina_Conta VARCHAR(20),
	Acao INT,
	PRIMARY KEY (Pessoal_conta, Pagina_Nome, Pagina_Conta, Acao),
	FOREIGN KEY (Pessoal_conta) REFERENCES PESSOAL(Conta),
	FOREIGN KEY (Pagina_Nome, Pagina_Conta) REFERENCES PAGINA(Nome, Conta),
	FOREIGN KEY (Acao) REFERENCES ACAO(Codigo)
);

CREATE TABLE POST(
	Id SERIAL,
	Pagina_Nome VARCHAR(50),
   	Pagina_Conta VARCHAR(20),
   	Titulo VARCHAR(70) NOT NULL,
   	Texto VARCHAR(2000) NOT NULL,
   	PRIMARY KEY (Id, Pagina_Nome, Pagina_Conta),
    FOREIGN KEY (Pagina_Nome, Pagina_Conta) REFERENCES PAGINA(Nome, Conta)
);

CREATE TABLE MIDIAS (
	Post_Id INT,
	Pagina_Nome VARCHAR(50),
	Pagina_Conta VARCHAR(20),
	Midia VARCHAR(255),
	PRIMARY KEY (Post_Id, Pagina_Nome, Pagina_Conta),
	FOREIGN KEY (Post_Id, Pagina_Nome, Pagina_Conta) REFERENCES POST(Id, Pagina_Nome, Pagina_Conta)
);

CREATE TABLE POSTCOMUM (
	Post_ID INT,
	Pagina_Nome VARCHAR(50),
	Pagina_Conta VARCHAR(20),
	Curtidas INT DEFAULT 0 CHECK (Curtidas >= 0),
	Compartilhamento INT DEFAULT 0 CHECK (Compartilhamento >= 0),
	PRIMARY KEY (Post_ID, Pagina_Nome, Pagina_Conta),
	FOREIGN KEY (Post_ID, Pagina_Nome, Pagina_Conta) REFERENCES POST(Id, Pagina_Nome, Pagina_Conta)
);

CREATE TABLE COMENTARIOS (
	PostComum_ID INT,
	Pagina_Nome VARCHAR(50),
	Pagina_Conta VARCHAR(20),
	Conta_Comentador VARCHAR(20),
	Comentario VARCHAR(200),
	PRIMARY KEY (PostComum_ID, Pagina_Nome, Pagina_Conta, Conta_Comentador, Comentario),
	FOREIGN KEY (PostComum_ID, Pagina_Nome, Pagina_Conta) REFERENCES POSTCOMUM(Post_ID, Pagina_Nome, Pagina_Conta),
	FOREIGN KEY (Conta_Comentador) REFERENCES PESSOAL(Conta)
);

CREATE TABLE POSTPROPAGANDA (
	Post_ID INT,
	Pagina_Nome VARCHAR(50),
	Pagina_Conta VARCHAR(20),
	PRIMARY KEY (Post_ID, Pagina_Nome, Pagina_Conta),
	FOREIGN KEY (Post_ID, Pagina_Nome, Pagina_Conta) REFERENCES POST(Id, Pagina_Nome, Pagina_Conta)
);

CREATE TABLE SERVICO (
	Post_ID INT,
	Pagina_Nome VARCHAR(50),
	Pagina_Conta VARCHAR(20),
	Servico VARCHAR(50),
	PRIMARY KEY (Post_ID, Pagina_Nome, Pagina_Conta, Servico),
	FOREIGN KEY (Post_ID, Pagina_Nome, Pagina_Conta) REFERENCES POSTPROPAGANDA(Post_ID, Pagina_Nome, Pagina_Conta)
);

CREATE TABLE EVENTO (
	Nome VARCHAR(50),
	Data TIMESTAMP,
	Descricao VARCHAR(100) NOT NULL,
	Local VARCHAR(50) NOT NULL,
	Conta VARCHAR(20) NOT NULL,
	PRIMARY KEY (Nome, Data),
	FOREIGN KEY (Conta) REFERENCES CONTA(NomeDeUsuario)
);

CREATE TABLE NEWSLETTER (
	Conta_Pessoal VARCHAR(20),
	Titulo VARCHAR(200),
	Imagem VARCHAR(255),
	Texto VARCHAR(2000) NOT NULL,
	PRIMARY KEY (Conta_Pessoal, Titulo),
	FOREIGN KEY (Conta_Pessoal) REFERENCES PESSOAL(Conta)
);






CREATE OR REPLACE FUNCTION att_num_conexoes_insert() RETURNS TRIGGER AS $$
BEGIN
	UPDATE PESSOAL
	SET NUMAMIGOS = ( SELECT COUNT(*) 
			  FROM CONECTA 
			  WHERE CONTA1 = NEW.CONTA1 OR CONTA2 = NEW.CONTA1)
	WHERE CONTA = NEW.CONTA1;
	
	UPDATE PESSOAL
	SET NUMAMIGOS = ( SELECT COUNT(*)
			  FROM CONECTA
			  WHERE CONTA1 = NEW.CONTA2 OR CONTA2 = NEW.CONTA2 )
	WHERE CONTA = NEW.CONTA2;

	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_num_conexoes_insert
AFTER INSERT ON CONECTA
FOR EACH ROW EXECUTE FUNCTION att_num_conexoes_insert();


CREATE OR REPLACE FUNCTION att_num_conexoes_delete() RETURNS TRIGGER AS $$
BEGIN
	UPDATE PESSOAL
	SET NUMAMIGOS = ( SELECT COUNT(*)
			  FROM CONECTA
			  WHERE CONTA1 = OLD.CONTA1 OR CONTA2 = OLD.CONTA1)
	WHERE CONTA = OLD.CONTA1;

	UPDATE PESSOAL
	SET NUMAMIGOS = ( SELECT COUNT(*)
			  FROM CONECTA
			  WHERE CONTA1 = OLD.CONTA2 OR CONTA2 = OLD.CONTA2 )
	WHERE CONTA = OLD.CONTA2;

	RETURN OLD;
END;
$$ LANGUAGE plpgsql;
	
CREATE TRIGGER trigger_num_conexoes_delete
AFTER DELETE ON CONECTA
FOR EACH ROW EXECUTE FUNCTION att_num_conexoes_delete();






INSERT INTO CONTA (NomeDeUsuario, Nome, CPF, Email, Senha, DataNascimento, Endereco) VALUES
('carlos_silva', 'Carlos Silva', '12345678901', 'carlos.silva@email.com', 'Jf8!sG2k', '15-05-1990', 'Rua A, 123, Apto 101, Centro, São Paulo, SP, 01001-000'),
('ana_oliveira95', 'Ana Oliveira', '23456789012', 'ana.oliveira@email.com', 'Xp2#vLm9', '22-08-1995', 'Rua B, 456, Casa 2, Bela Vista, São Paulo, SP, 01321-000'),
('mariana_souza88', 'Mariana Souza', '34567890123', 'mariana.souza@email.com', 'Tq9@pN7z', '10-03-1988', 'Avenida C, 789, Conj. 304, Consolação, São Paulo, SP, 01303-000'),
('bruno_santos92', 'Bruno Santos', '45678901234', 'bruno.santos@email.com', 'Wm6*oRc4', '05-11-1992', 'Travessa D, 101, Sobrado, República, São Paulo, SP, 01042-000'),
('fernanda.lima00', 'Fernanda Lima', '56789012345', 'fernanda.lima@email.com', 'Zy5%gHd8', '19-07-2000', 'Rua E, 202, Bloco B, Apto 502, Higienópolis, São Paulo, SP, 01241-000'),
('rodrigo.alves97', 'Rodrigo Alves', '67890123456', 'rodrigo.alves@email.com', 'Bn3^xQy2', '30-09-1997', 'Avenida F, 303, Sala 1101, Itaim Bibi, São Paulo, SP, 04538-132'),
('juliana.costa94', 'Juliana Costa', '78901234567', 'juliana.costa@email.com', 'Kd7&vMz6', '12-12-1994', 'Rua G, 404, Casa 3, Jardins, São Paulo, SP, 01415-000'),
('felipe_martins85', 'Felipe Martins', '89012345678', 'felipe.martins@email.com', 'Xr4@pLs9', '25-06-1985', 'Praça H, 505, Loja 10, Pinheiros, São Paulo, SP, 05425-070'),
('larissa_pereira91', 'Larissa Pereira', '90123456789', 'larissa.pereira@email.com', 'Vb8*oNy3', '18-04-1991', 'Rua I, 606, Fundos, Vila Madalena, São Paulo, SP, 05416-010'),
('rafael_mendes98', 'Rafael Mendes', '01234567890', 'rafael.mendes@email.com', 'Tz5#qLd7', '07-02-1998', 'Alameda J, 707, Cond. Edifício JK, Apto 801, Morumbi, São Paulo, SP, 05690-000'),
('joao.silva', 'João Silva', '12345678910', 'joao.silva@email.com', 'P@$$wOrd123!', '15-05-1990', 'Rua das Flores, 123, Centro, São Paulo, SP, 01001-001'),
('maria.souza', 'Maria Souza', '98765432109', 'maria.souza@email.com', 'S3gur@nca456#', '20-10-1985', 'Avenida Paulista, 456, Bela Vista, São Paulo, SP, 01310-000'),
('pedro.oliveira', 'Pedro Oliveira', '11223344556', 'pedro.oliveira@email.com', 'C0mpl3x@789$', '08-03-2002', 'Rua Augusta, 789, Consolação, São Paulo, SP, 01305-100'),
('lucas.pereira', 'Lucas Pereira', '66554433221', 'lucas.pereira@email.com', 'Str0ngP@$$wOrd!', '01-12-1998', 'Avenida Ipiranga, 101, República, São Paulo, SP, 01039-000'),
('julia.santos', 'Julia Santos', '44556677889', 'julia.santos@email.com', 'S3cur3P@$$wOrd#', '25-07-1975', 'Rua da Consolação, 222, Higienópolis, São Paulo, SP, 01235-000'),
('ricardo.ferreira', 'Ricardo Ferreira', '77889900112', 'ricardo.ferreira@email.com', 'H@shP@$$wOrd123', '30-09-2005', 'Avenida Brigadeiro Faria Lima, 333, Itaim Bibi, São Paulo, SP, 04538-001'),
('amanda.rodrigues', 'Amanda Rodrigues', '22334455667', 'amanda.rodrigues@email.com', 'S@ltP@$$wOrd456', '10-04-1993', 'Rua Oscar Freire, 444, Jardins, São Paulo, SP, 01426-001'),
('gabriel.almeida', 'Gabriel Almeida', '88990011223', 'gabriel.almeida@email.com', 'Crypt0P@$$wOrd!', '05-01-1980', 'Avenida Rebouças, 555, Pinheiros, São Paulo, SP, 05402-001'),
('fernanda.costa', 'Fernanda Costa', '55667788990', 'fernanda.costa@email.com', 'R@nd0mP@$$wOrd#', '18-06-2000', 'Rua Teodoro Sampaio, 666, Vila Madalena, São Paulo, SP, 05405-050'),
('thiago.gomes', 'Thiago Gomes', '33445566778', 'thiago.gomes@email.com', 'K3yP@$$wOrd123$', '22-11-1988', 'Avenida Morumbi, 777, Morumbi, São Paulo, SP, 05650-001');

INSERT INTO TELEFONES (Conta, Telefone) VALUES
('carlos_silva', '34991234567'),
('carlos_silva', '34997654321'),
('ana_oliveira95', '11998765432'),
('mariana_souza88', '31996543210'),
('bruno_santos92', '21997456321'),
('fernanda.lima00', '41991239876'),
('rodrigo.alves97', '51993456789'),
('rafael_mendes98', '11985625478'),
('juliana.costa94', '62999876543'),
('felipe_martins85', '81992345678');

INSERT INTO PACOTE (Nome, Taxa) VALUES 
('Básico', 29.90),
('Startup', 39.90),
('Premium', 49.90),
('Pro', 69.90),
('Avançado', 109.90),
('Executivo', 179.90),
('Corporativo', 199.90),
('Empresarial', 159.90),
('Corporativo Plus', 249.90),
('Master', 299.90);

INSERT INTO FUNCIONALIDADES (Codigo, Funcionalidade) VALUES
(1, 'Chat ilimitado'),
(2, 'Chat ilimitado'),
(2, 'Compartilhamento de arquivos'),
(3, 'Chat ilimitado'),
(3, 'Compartilhamento de arquivos'),
(3, 'Videoconferência com 100 participantes'),
(4, 'Chat ilimitado'),
(4, 'Compartilhamento de arquivos'),
(4, 'Videoconferência com 100 participantes'),
(4, 'Integração com CRM'),
(5, 'Chat ilimitado'),
(5, 'Compartilhamento de arquivos'),
(5, 'Videoconferência com 100 participantes'),
(5, 'Integração com CRM'),
(5, 'Suporte prioritário 24/7'),
(6, 'Chat ilimitado'),
(6, 'Compartilhamento de arquivos'),
(6, 'Videoconferência com 100 participantes'),
(6, 'Integração com CRM'),
(6, 'Suporte prioritário 24/7'),
(6, 'Gravação de videoconferências'),
(7, 'Chat ilimitado'),
(7, 'Compartilhamento de arquivos'),
(7, 'Videoconferência com 100 participantes'),
(7, 'Integração com CRM'),
(7, 'Suporte prioritário 24/7'),
(7, 'Gravação de videoconferências'),
(7, 'Webinars para até 500 pessoas'),
(8, 'Chat ilimitado'),
(8, 'Compartilhamento de arquivos'),
(8, 'Videoconferência com 100 participantes'),
(8, 'Integração com CRM'),
(8, 'Suporte prioritário 24/7'),
(8, 'Gravação de videoconferências'),
(8, 'Webinars para até 500 pessoas'),
(8, 'Enquetes e pesquisas'),
(9, 'Chat ilimitado'),
(9, 'Compartilhamento de arquivos'),
(9, 'Videoconferência com 100 participantes'),
(9, 'Integração com CRM'),
(9, 'Suporte prioritário 24/7'),
(9, 'Gravação de videoconferências'),
(9, 'Webinars para até 500 pessoas'),
(9, 'Enquetes e pesquisas'),
(9, 'Transmissão ao vivo para redes sociais'),
(10, 'Chat ilimitado'),
(10, 'Compartilhamento de arquivos'),
(10, 'Videoconferência com 100 participantes'),
(10, 'Integração com CRM'),
(10, 'Suporte prioritário 24/7'),
(10, 'Gravação de videoconferências'),
(10, 'Webinars para até 500 pessoas'),
(10, 'Enquetes e pesquisas'),
(10, 'Transmissão ao vivo para redes sociais'),
(10, 'Análise de dados avançada');

INSERT INTO EMPRESARIAL (Conta, CNPJ, Codigo) VALUES
('carlos_silva', '12345678000190', 1),
('ana_oliveira95', '23456789000280', 3),
('mariana_souza88', '34567890000370', 3),
('bruno_santos92', '45678901000460', 7),
('fernanda.lima00', '56789012000550', 10),
('rodrigo.alves97', '67890123000640', 7),
('juliana.costa94', '78901234000730', 7),
('felipe_martins85', '89012345000820', 5),
('larissa_pereira91', '90123456000910', 5),
('rafael_mendes98', '01234567001000', 10);

INSERT INTO PESSOAL (Conta) VALUES
('joao.silva'),
('maria.souza'),
('pedro.oliveira'),
('lucas.pereira'),
('julia.santos'),
('ricardo.ferreira'),
('amanda.rodrigues'),
('gabriel.almeida'),
('fernanda.costa'),
('thiago.gomes');

INSERT INTO CONECTA (Conta1, Conta2, Status) VALUES
('joao.silva', 'maria.souza', 'Amigos'),
('joao.silva', 'pedro.oliveira', 'Conhecidos'),
('maria.souza', 'lucas.pereira', 'Amigos'),
('pedro.oliveira', 'julia.santos', 'Colegas'),
('lucas.pereira', 'ricardo.ferreira', 'Amigos'),
('julia.santos', 'amanda.rodrigues', 'Colegas'),
('ricardo.ferreira', 'gabriel.almeida', 'Amigos'),
('amanda.rodrigues', 'fernanda.costa', 'Colegas'),
('gabriel.almeida', 'thiago.gomes', 'Amigos'),
('fernanda.costa', 'joao.silva', 'Conhecidos'),
('lucas.pereira', 'joao.silva', 'Amigos'),
('maria.souza', 'pedro.oliveira', 'Conhecidos'),
('maria.souza', 'julia.santos', 'Amigos'),
('pedro.oliveira', 'lucas.pereira', 'Colegas'),
('ricardo.ferreira', 'maria.souza', 'Amigos'),
('joao.silva', 'ricardo.ferreira', 'Colegas');

INSERT INTO GRUPOS (Nome, Categoria, Conta_Pessoal) VALUES
('Amigos do Parque', 'Lazer', 'joao.silva'),
('Leitura em Dia', 'Hobbies', 'maria.souza'),
('Desenvolvedores Iniciantes', 'Estudo', 'pedro.oliveira'),
('Cozinha Criativa', 'Culinária', 'lucas.pereira'),
('Aventureiros da Montanha', 'Esportes', 'julia.santos'),
('Fotografia Urbana', 'Arte', 'ricardo.ferreira'),
('Amantes de Animais', 'Comunidade', 'amanda.rodrigues'),
('Geek Universe', 'Entretenimento', 'gabriel.almeida'),
('Yoga para Todos', 'Bem-estar', 'fernanda.costa'),
('Música e Poesia', 'Arte', 'thiago.gomes');

INSERT INTO PARTICIPA (Conta_Pessoal, Grupos) VALUES
('joao.silva', 1),
('maria.souza', 1),
('pedro.oliveira', 1),
('gabriel.almeida', 1),
('julia.santos', 1),
('maria.souza', 2),
('lucas.pereira', 2),
('julia.santos', 2),
('pedro.oliveira', 3),
('ricardo.ferreira', 3),
('amanda.rodrigues', 3),
('lucas.pereira', 4),
('thiago.gomes', 4),
('gabriel.almeida', 4),
('fernanda.costa', 4),
('julia.santos', 5),
('ricardo.ferreira', 5),
('thiago.gomes', 5),
('ricardo.ferreira', 6),
('joao.silva', 6),
('gabriel.almeida', 6),
('maria.souza', 6),
('amanda.rodrigues', 7),
('pedro.oliveira', 7),
('lucas.pereira', 7),
('gabriel.almeida', 8),
('julia.santos', 8),
('ricardo.ferreira', 8),
('fernanda.costa', 9),
('amanda.rodrigues', 9),
('gabriel.almeida', 9),
('ricardo.ferreira', 9),
('thiago.gomes', 10),
('gabriel.almeida', 10),
('fernanda.costa', 10);

INSERT INTO PAGINA (Nome, Conta, Numero_visitas) VALUES
('Carlos Silva Consultoria', 'carlos_silva', 500),
('Ana Oliveira Fotografia', 'ana_oliveira95', 800),
('Mariana Souza Confeitaria', 'mariana_souza88', 300),
('Bruno Santos Design', 'bruno_santos92', 600),
('Fernanda Lima Maquiagem', 'fernanda.lima00', 1000),
('Rodrigo Alves Tecnologia', 'rodrigo.alves97', 700),
('Juliana Costa Moda', 'juliana.costa94', 200),
('Felipe Martins Galeria de Arte', 'felipe_martins85', 150),
('Larissa Pereira Agência de Viagens', 'larissa_pereira91', 400),
('Rafael Mendes Artigos Científicos', 'rafael_mendes98', 550),
('Perfil do João', 'joao.silva', 220),
('Página da Maria', 'maria.souza', 190),
('Blog do Pedro', 'pedro.oliveira', 110),
('Portfólio do Lucas', 'lucas.pereira', 160),
('Canal da Julia', 'julia.santos', 280),
('Site do Ricardo', 'ricardo.ferreira', 230),
('Blog da Amanda', 'amanda.rodrigues', 95),
('Galeria do Gabriel', 'gabriel.almeida', 85),
('Página da Fernanda', 'fernanda.costa', 125),
('Artigos do Thiago', 'thiago.gomes', 165);

INSERT INTO PPROPAGANDA (Pagina_Nome, Pagina_Conta, Taxa_conversao, Taxa_cliques, Taxa_rejeicao, EmpresarialConta) VALUES
('Carlos Silva Consultoria', 'carlos_silva', 0.08, 0.15, 0.20, 'carlos_silva'),
('Ana Oliveira Fotografia', 'ana_oliveira95', 0.12, 0.20, 0.15, 'ana_oliveira95'),
('Mariana Souza Confeitaria', 'mariana_souza88', 0.05, 0.10, 0.25, 'mariana_souza88'),
('Bruno Santos Design', 'bruno_santos92', 0.10, 0.18, 0.10, 'bruno_santos92'),
('Fernanda Lima Maquiagem', 'fernanda.lima00', 0.15, 0.25, 0.08, 'fernanda.lima00'),
('Rodrigo Alves Tecnologia', 'rodrigo.alves97', 0.09, 0.16, 0.18, 'rodrigo.alves97'),
('Juliana Costa Moda', 'juliana.costa94', 0.06, 0.12, 0.22, 'juliana.costa94'),
('Felipe Martins Galeria de Arte', 'felipe_martins85', 0.04, 0.08, 0.30, 'felipe_martins85'),
('Larissa Pereira Agência de Viagens', 'larissa_pereira91', 0.07, 0.14, 0.19, 'larissa_pereira91'),
('Rafael Mendes Artigos Científicos', 'rafael_mendes98', 0.11, 0.19, 0.12, 'rafael_mendes98');

INSERT INTO FICA_VISIVEL (Codigo, Nome, PaginaConta) VALUES
(1, 'Perfil do João', 'joao.silva'),
(2, 'Página da Maria', 'maria.souza'),
(3, 'Blog do Pedro', 'pedro.oliveira'),
(4, 'Portfólio do Lucas', 'lucas.pereira'),
(5, 'Canal da Julia', 'julia.santos'),
(6, 'Site do Ricardo', 'ricardo.ferreira'),
(7, 'Blog da Amanda', 'amanda.rodrigues'),
(8, 'Galeria do Gabriel', 'gabriel.almeida'),
(9, 'Página da Fernanda', 'fernanda.costa'),
(10, 'Artigos do Thiago', 'thiago.gomes');

INSERT INTO ACAO (Descricao) VALUES
('Editar conteúdo da página'),
('Excluir conteúdo da página'),
('Gerenciar permissões de outros usuários'),
('Exibir curtidas'),
('Acessar dados analíticos da página'),
('Moderar comentários'),
('Criar enquetes e eventos'),
('Adicionar administradores à página'),
('Alterar informações da página'),
('Exibir contas que visualizaram');

INSERT INTO PRIVILEGIOS (Pessoal_conta, Pagina_Nome, Pagina_Conta, Acao) VALUES
('joao.silva', 'Página da Maria', 'maria.souza', 1),
('maria.souza', 'Blog do Pedro', 'pedro.oliveira', 2),
('pedro.oliveira', 'Portfólio do Lucas', 'lucas.pereira', 3),
('lucas.pereira', 'Canal da Julia', 'julia.santos', 4),
('julia.santos', 'Site do Ricardo', 'ricardo.ferreira', 5),
('ricardo.ferreira', 'Blog da Amanda', 'amanda.rodrigues', 6),
('amanda.rodrigues', 'Galeria do Gabriel', 'gabriel.almeida', 7),
('gabriel.almeida', 'Página da Fernanda', 'fernanda.costa', 8),
('fernanda.costa', 'Artigos do Thiago', 'thiago.gomes', 9),
('thiago.gomes', 'Perfil do João', 'joao.silva', 10);

INSERT INTO POST (Pagina_Nome, Pagina_Conta, Titulo, Texto) VALUES
('Perfil do João', 'joao.silva', 'Leitura do mês', 'Estou lendo "O Senhor dos Anéis" e estou adorando a história. Alguém mais já leu?'),
('Página da Maria', 'maria.souza', 'Série imperdível', 'Comecei a assistir "Stranger Things" e estou curtindo muito! As atuações estão sensacionais.'),
('Blog do Pedro', 'pedro.oliveira', 'Filme impressionante', 'Assisti "Parasita" e achei a direção e o roteiro simplesmente geniais. Super recomendo!'),
('Portfólio do Lucas', 'lucas.pereira', 'Novo som no ar', 'Acabei de lançar uma música nova no YouTube! Me conta o que achou nos comentários.'),
('Canal da Julia', 'julia.santos', 'Look de hoje', 'Esse foi o look que escolhi hoje para dar uma volta no parque. Curtiram?'),
('Site do Ricardo', 'ricardo.ferreira', 'Restaurante que vale a pena', 'Conheci um restaurante novo hoje e a comida estava maravilhosa! Ambiente super agradável.'),
('Blog da Amanda', 'amanda.rodrigues', 'Fofura do dia', 'Olha só meu gato dormindo desse jeitinho! Muita fofura pra um bichinho só!'),
('Galeria do Gabriel', 'gabriel.almeida', 'Nova arte em progresso', 'Estou trabalhando em uma nova pintura abstrata. O que acham das cores até agora?'),
('Página da Fernanda', 'fernanda.costa', 'Make para eventos', 'Usei essa make hoje para um evento. Gostaram do resultado?'),
('Artigos do Thiago', 'thiago.gomes', 'Novo artigo sobre IA', 'Saiu um novo artigo meu sobre IA. Quero saber a opinião de vocês!'),
('Carlos Silva Consultoria', 'carlos_silva', 'Impulsione seus lucros', 'Soluções sob medida para o crescimento do seu negócio. Fale conosco!'),
('Ana Oliveira Fotografia', 'ana_oliveira95', 'Momentos inesquecíveis em fotos', 'Cobertura profissional para eventos e ensaios. Faça seu orçamento!'),
('Mariana Souza Confeitaria', 'mariana_souza88', 'Doces incríveis para sua festa', 'Faça sua encomenda e torne sua comemoração ainda mais especial!'),
('Bruno Santos Design', 'bruno_santos92', 'Identidade visual profissional', 'Serviços de design para destacar sua marca no mercado competitivo.'),
('Fernanda Lima Maquiagem', 'fernanda.lima00', 'Maquiagem que valoriza você', 'Atendimentos com qualidade profissional para diversas ocasiões.'),
('Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Otimização com tecnologia', 'Softwares, apps e sites sob demanda para sua empresa.'),
('Juliana Costa Moda', 'juliana.costa94', 'Moda em destaque', 'Looks exclusivos para arrasar em qualquer lugar. Confira!'),
('Felipe Martins Galeria de Arte', 'felipe_martins85', 'Arte exclusiva para seu espaço', 'Peças autorais e únicas para transformar seus ambientes.'),
('Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Destinos imperdíveis', 'Roteiros planejados com cuidado para uma viagem inesquecível.'),
('Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'Pesquisas de qualidade', 'Conteúdo de excelência revisado por especialistas. Peça um orçamento!'),
('Carlos Silva Consultoria', 'carlos_silva', 'Transforme sua empresa', 'Mapeamos oportunidades e otimizamos seus processos.'),
('Carlos Silva Consultoria', 'carlos_silva', 'Resultados através da consultoria', 'Resultados consistentes com estratégias eficazes.'),
('Ana Oliveira Fotografia', 'ana_oliveira95', 'Fotos com emoção', 'Eventos, ensaios e mais, com um olhar profissional.'),
('Ana Oliveira Fotografia', 'ana_oliveira95', 'Ensaio externo ou em estúdio', 'Registros naturais e criativos em qualquer cenário.'),
('Ana Oliveira Fotografia', 'ana_oliveira95', 'Cada clique, uma história', 'Cada foto é uma história. Agende seu ensaio!'),
('Mariana Souza Confeitaria', 'mariana_souza88', 'Surpreenda com sabor', 'Receitas feitas com dedicação para adoçar seu evento.'),
('Bruno Santos Design', 'bruno_santos92', 'Marca com presença', 'Sua empresa merece uma presença visual marcante.'),
('Bruno Santos Design', 'bruno_santos92', 'Design que transmite valor', 'Comunique-se melhor com um design de alto impacto.'),
('Bruno Santos Design', 'bruno_santos92', 'Visual criativo e funcional', 'Projetos visuais que traduzem a essência da sua marca.'),
('Fernanda Lima Maquiagem', 'fernanda.lima00', 'Especial para noivas e formandas', 'Pacotes completos com direito a teste de maquiagem.'),
('Fernanda Lima Maquiagem', 'fernanda.lima00', 'Beleza com destaque', 'Beleza realçada com técnicas personalizadas.'),
('Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Tecnologia sob medida', 'Serviços digitais feitos para você se destacar.'),
('Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Automatize sua empresa', 'Softwares eficientes para seu dia a dia.'),
('Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Inovação nos processos', 'Modernize sua empresa com nossas soluções tecnológicas.'),
('Juliana Costa Moda', 'juliana.costa94', 'Estilo que combina com você', 'Estilo e conforto para todas as ocasiões.'),
('Felipe Martins Galeria de Arte', 'felipe_martins85', 'Fim de semana com arte', 'Venha conhecer o trabalho de grandes artistas!'),
('Felipe Martins Galeria de Arte', 'felipe_martins85', 'Obras com personalidade', 'Obras com personalidade e expressão autêntica.'),
('Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Explore o mundo com a gente', 'Temos opções para todos os estilos de viajante!'),
('Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Verão com desconto', 'Garanta já sua viagem com condições especiais.'),
('Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Horizontes a explorar', 'Explore o mundo com os melhores roteiros!'),
('Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'Normas e revisão', 'Deixe seu artigo pronto para submissão com qualidade.'),
('Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'Conteúdo que gera impacto', 'Produzimos conteúdo científico com excelência.');



INSERT INTO MIDIAS (Post_Id, Pagina_Nome, Pagina_Conta, Midia) VALUES
(1, 'Perfil do João', 'joao.silva', 'https://images.pexels.com/photos/159711/pexels-photo-159711.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(2, 'Página da Maria', 'maria.souza', 'https://images.pexels.com/photos/1779487/pexels-photo-1779487.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(3, 'Blog do Pedro', 'pedro.oliveira', 'https://images.pexels.com/photos/1260968/pexels-photo-1260968.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(4, 'Portfólio do Lucas', 'lucas.pereira', 'https://images.pexels.com/photos/3861969/pexels-photo-3861969.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(5, 'Canal da Julia', 'julia.santos', 'https://images.pexels.com/photos/38554/girl-people-landscape-sun-38554.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(6, 'Site do Ricardo', 'ricardo.ferreira', 'https://images.pexels.com/photos/712618/pexels-photo-712618.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(7, 'Blog da Amanda', 'amanda.rodrigues', 'https://images.pexels.com/photos/6347891/pexels-photo-6347891.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(8, 'Galeria do Gabriel', 'gabriel.almeida', 'https://images.pexels.com/photos/1001991/pexels-photo-1001991.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(9, 'Página da Fernanda', 'fernanda.costa', 'https://images.pexels.com/photos/602750/pexels-photo-602750.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(10, 'Artigos do Thiago', 'thiago.gomes', 'https://images.pexels.com/photos/1181263/pexels-photo-1181263.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(11, 'Carlos Silva Consultoria', 'carlos_silva', 'https://images.pexels.com/photos/3184423/pexels-photo-3184423.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(12, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'https://images.pexels.com/photos/1194713/pexels-photo-1194713.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(13, 'Mariana Souza Confeitaria', 'mariana_souza88', 'https://images.pexels.com/photos/1260968/pexels-photo-1260968.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(14, 'Bruno Santos Design', 'bruno_santos92', 'https://images.pexels.com/photos/3861969/pexels-photo-3861969.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(15, 'Fernanda Lima Maquiagem', 'fernanda.lima00', 'https://images.pexels.com/photos/38554/girl-people-landscape-sun-38554.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(16, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'https://images.pexels.com/photos/712618/pexels-photo-712618.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(17, 'Juliana Costa Moda', 'juliana.costa94', 'https://images.pexels.com/photos/6347891/pexels-photo-6347891.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(18, 'Felipe Martins Galeria de Arte', 'felipe_martins85', 'https://images.pexels.com/photos/1001991/pexels-photo-1001991.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(19, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'https://images.pexels.com/photos/602750/pexels-photo-602750.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(20, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'https://images.pexels.com/photos/1181263/pexels-photo-1181263.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1'),
(21, 'Carlos Silva Consultoria', 'carlos_silva', 'C:/imagens/consultoria_profissional.jpg'),
(22, 'Carlos Silva Consultoria', 'carlos_silva', 'C:/imagens/resultados_clientes_video.mp4'),
(23, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'https://www.exemplo.com/portfolios/ensaio_fotografico_1.jpg'),
(24, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'C:/imagens/ensaio_externo_foto1.jpg'),
(25, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'C:/imagens/ensaio_estudio_criativo.jpg'),
(26, 'Mariana Souza Confeitaria', 'mariana_souza88', 'https://www.exemplo.com/doces_personalizados/foto_bolo1.jpg'),
(27, 'Bruno Santos Design', 'bruno_santos92', 'C:/imagens/identidade_visual_pro.jpg'),
(28, 'Bruno Santos Design', 'bruno_santos92', 'https://www.exemplo.com/portfolios/design_marcas/portfolio_1.jpg'),
(29, 'Bruno Santos Design', 'bruno_santos92', 'C:/imagens/design_criativo.jpg'),
(30, 'Fernanda Lima Maquiagem', 'fernanda.lima00', 'https://www.exemplo.com/maquiagem_noivas/noiva_1.jpg'),
(31, 'Fernanda Lima Maquiagem', 'fernanda.lima00', 'C:/imagens/maquiagem_eventos.jpg'),
(32, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'https://www.exemplo.com/software_em_acao/software_1.mp4'),
(33, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'C:/imagens/automatizacao_video.mp4'),
(34, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'https://www.exemplo.com/inovacao_tecnologica/infografico_inovacao.png'),
(35, 'Juliana Costa Moda', 'juliana.costa94', 'C:/imagens/look_dia.jpg'),
(36, 'Felipe Martins Galeria de Arte', 'felipe_martins85', 'https://www.exemplo.com/exposicao_arte/expo1.jpg'),
(37, 'Felipe Martins Galeria de Arte', 'felipe_martins85', 'C:/imagens/obra_autoral1.jpg'),
(38, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'https://www.exemplo.com/destinos_turisticos/destino_1.jpg'),
(39, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'C:/imagens/promocao_viagem_verao.jpg'),
(40, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'C:/imagens/roteiro_aventura.jpg'),
(41, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'https://www.exemplo.com/artigo_academico/artigo_1.pdf'),
(42, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'https://www.exemplo.com/pesquisa_cientifica/infografico_pesquisa.png');

INSERT INTO POSTCOMUM (Post_ID, Pagina_Nome, Pagina_Conta, Curtidas, Compartilhamento) VALUES
(1, 'Perfil do João', 'joao.silva', 150, 30),
(2, 'Página da Maria', 'maria.souza', 200, 50),
(3, 'Blog do Pedro', 'pedro.oliveira', 120, 25),
(4, 'Portfólio do Lucas', 'lucas.pereira', 180, 40),
(5, 'Canal da Julia', 'julia.santos', 300, 70),
(6, 'Site do Ricardo', 'ricardo.ferreira', 250, 60),
(7, 'Blog da Amanda', 'amanda.rodrigues', 100, 20),
(8, 'Galeria do Gabriel', 'gabriel.almeida', 90, 15),
(9, 'Página da Fernanda', 'fernanda.costa', 130, 35),
(10, 'Artigos do Thiago', 'thiago.gomes', 170, 45);

INSERT INTO COMENTARIOS (PostComum_ID, Pagina_Nome, Pagina_Conta, Conta_Comentador, Comentario) VALUES
(1, 'Perfil do João', 'joao.silva', 'maria.souza', 'Adoro esse livro!'),
(1, 'Perfil do João', 'joao.silva', 'pedro.oliveira', 'Vou colocar na minha lista de leitura.'),
(2, 'Página da Maria', 'maria.souza', 'joao.silva', 'Essa série é muito boa!'),
(2, 'Página da Maria', 'maria.souza', 'lucas.pereira', 'Já vi todos os episódios.'),
(3, 'Blog do Pedro', 'pedro.oliveira', 'julia.santos', 'Esse filme é incrível!'),
(3, 'Blog do Pedro', 'pedro.oliveira', 'joao.silva', 'Vou assistir hoje mesmo.'),
(4, 'Portfólio do Lucas', 'lucas.pereira', 'maria.souza', 'Parabéns pela música nova!'),
(4, 'Portfólio do Lucas', 'lucas.pereira', 'ricardo.ferreira', 'Adorei a melodia.'),
(5, 'Canal da Julia', 'julia.santos', 'pedro.oliveira', 'Que look lindo!'),
(5, 'Canal da Julia', 'julia.santos', 'amanda.rodrigues', 'Amei a combinação de cores.'),
(6, 'Site do Ricardo', 'ricardo.ferreira', 'lucas.pereira', 'Esse restaurante parece ótimo!'),
(6, 'Site do Ricardo', 'ricardo.ferreira', 'gabriel.almeida', 'Vou esperimentar o prato prinsipal.'),
(7, 'Blog da Amanda', 'amanda.rodrigues', 'julia.santos', 'Que gato fofo!'),
(7, 'Blog da Amanda', 'amanda.rodrigues', 'fernanda.costa', 'Adoro gatos!'),
(8, 'Galeria do Gabriel', 'gabriel.almeida', 'thiago.gomes', 'Essa pintura é linda!'),
(8, 'Galeria do Gabriel', 'gabriel.almeida', 'ricardo.ferreira', 'Parabéns pelo trabalho!'),
(9, 'Página da Fernanda', 'fernanda.costa', 'amanda.rodrigues', 'Que maquiagem incrível!'),
(9, 'Página da Fernanda', 'fernanda.costa', 'joao.silva', 'Vou tentar fazer essa maquiagem.'),
(10, 'Artigos do Thiago', 'thiago.gomes', 'fernanda.costa', 'Artigo muito interessante!'),
(10, 'Artigos do Thiago', 'thiago.gomes', 'gabriel.almeida', 'Parabéns pela pesquisa!');

INSERT INTO POSTPROPAGANDA (Post_ID, Pagina_Nome, Pagina_Conta) VALUES
(11, 'Carlos Silva Consultoria', 'carlos_silva'),
(12, 'Ana Oliveira Fotografia', 'ana_oliveira95'),
(13, 'Mariana Souza Confeitaria', 'mariana_souza88'),
(14, 'Bruno Santos Design', 'bruno_santos92'),
(15, 'Fernanda Lima Maquiagem', 'fernanda.lima00'),
(16, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97'),
(17, 'Juliana Costa Moda', 'juliana.costa94'),
(18, 'Felipe Martins Galeria de Arte', 'felipe_martins85'),
(19, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91'),
(20, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98'),
(21, 'Carlos Silva Consultoria', 'carlos_silva'),
(22, 'Carlos Silva Consultoria', 'carlos_silva'),
(23, 'Ana Oliveira Fotografia', 'ana_oliveira95'),
(24, 'Ana Oliveira Fotografia', 'ana_oliveira95'),
(25, 'Ana Oliveira Fotografia', 'ana_oliveira95'),
(26, 'Mariana Souza Confeitaria', 'mariana_souza88'),
(27, 'Bruno Santos Design', 'bruno_santos92'),
(28, 'Bruno Santos Design', 'bruno_santos92'),
(29, 'Bruno Santos Design', 'bruno_santos92'),
(30, 'Fernanda Lima Maquiagem', 'fernanda.lima00'),
(31, 'Fernanda Lima Maquiagem', 'fernanda.lima00'),
(32, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97'),
(33, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97'),
(34, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97'),
(35, 'Juliana Costa Moda', 'juliana.costa94'),
(36, 'Felipe Martins Galeria de Arte', 'felipe_martins85'),
(37, 'Felipe Martins Galeria de Arte', 'felipe_martins85'),
(38, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91'),
(39, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91'),
(40, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91'),
(41, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98'),
(42, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98');


INSERT INTO SERVICO (Post_ID, Pagina_Nome, Pagina_Conta, Servico) VALUES
(11, 'Carlos Silva Consultoria', 'carlos_silva', 'Consultoria'),
(12, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'Fotografia'),
(13, 'Mariana Souza Confeitaria', 'mariana_souza88', 'Confeitaria'),
(14, 'Bruno Santos Design', 'bruno_santos92', 'Design'),
(15, 'Fernanda Lima Maquiagem', 'fernanda.lima00', 'Maquiagem'),
(16, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Desenvolvimento de software'),
(17, 'Juliana Costa Moda', 'juliana.costa94', 'Venda'),
(18, 'Felipe Martins Galeria de Arte', 'felipe_martins85', 'Venda'),
(19, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Venda'),
(20, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'Artigos'),
(21, 'Carlos Silva Consultoria', 'carlos_silva', 'Consultoria'),
(22, 'Carlos Silva Consultoria', 'carlos_silva', 'Consultoria'),
(23, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'Fotografia'),
(24, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'Fotografia'),
(25, 'Ana Oliveira Fotografia', 'ana_oliveira95', 'Fotografia'),
(26, 'Mariana Souza Confeitaria', 'mariana_souza88', 'Confeitaria'),
(27, 'Bruno Santos Design', 'bruno_santos92', 'Design'),
(28, 'Bruno Santos Design', 'bruno_santos92', 'Design'),
(29, 'Bruno Santos Design', 'bruno_santos92', 'Design'),
(30, 'Fernanda Lima Maquiagem', 'fernanda.lima00', 'Maquiagem'),
(31, 'Fernanda Lima Maquiagem', 'fernanda.lima00', 'Maquiagem'),
(32, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Desenvolvimento de software'),
(33, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Desenvolvimento de software'),
(34, 'Rodrigo Alves Tecnologia', 'rodrigo.alves97', 'Consultoria'),
(35, 'Juliana Costa Moda', 'juliana.costa94', 'Consultoria'),
(36, 'Felipe Martins Galeria de Arte', 'felipe_martins85', 'Curadoria'),
(37, 'Felipe Martins Galeria de Arte', 'felipe_martins85', 'Venda'),
(38, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Viagem'),
(39, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Viagem'),
(40, 'Larissa Pereira Agência de Viagens', 'larissa_pereira91', 'Consultoria'),
(41, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'Artigos'),
(42, 'Rafael Mendes Artigos Científicos', 'rafael_mendes98', 'Artigos');

INSERT INTO EVENTO (Nome, Data, Descricao, Local, Conta) VALUES
('Aniversário João', '15-06-2025 18:00:00', 'Festa de aniversário com amigos e familiares', 'Rua das Flores, 123', 'joao.silva'),
('Clube do Livro', '10-05-2025 19:30:00', 'Encontro do grupo Leitura em Dia', 'Café Literário, Av. Paulista', 'maria.souza'),
('Trilha na Serra', '20-04-2025 07:00:00', 'Caminhada com grupo Aventureiros da Montanha', 'Serra da Cantareira', 'julia.santos'),
('Workshop de Fotografia', '05-05-2025 14:00:00', 'Sessão prática com grupo Fotografia Urbana', 'Parque Ibirapuera', 'ricardo.ferreira'),
('Churrasco de Amigos', '27-04-2025 13:00:00', 'Confraternização com os amigos do parque', 'Casa do João', 'joao.silva'),
('Live de Maquiagem', '25-04-2025 20:00:00', 'Fernanda Lima apresenta dicas ao vivo', 'Instagram - @fernanda.make', 'fernanda.lima00'),
('Exposição de Arte', '12-05-2025 10:00:00', 'Felipe Martins apresenta novas obras', 'Galeria ModernArt, SP', 'felipe_martins85'),
('Webinar sobre Design', '01-05-2025 16:00:00', 'Bruno Santos discute tendências de UX/UI', 'Zoom', 'bruno_santos92'),
('Oficina de Confeitaria', '20-05-2025 15:00:00', 'Mariana Souza ensina bolos decorados', 'Espaço Doce Sabor, SP', 'mariana_souza88'),
('Palestra de Consultoria', '03-06-2025 09:00:00', 'Carlos Silva fala sobre planejamento estratégico', 'Auditório FGV, SP', 'carlos_silva');


INSERT INTO NEWSLETTER (Conta_Pessoal, Titulo, Imagem, Texto) VALUES
('joao.silva', 'Leituras Fantásticas', 'https://images.pexels.com/photos/590493/pexels-photo-590493.jpeg', 'Nesta edição, falo sobre o universo de Tolkien e como "O Senhor dos Anéis" continua encantando gerações.'),
('maria.souza', 'Séries em Alta', 'https://images.pexels.com/photos/799137/pexels-photo-799137.jpeg', 'Destaque para Stranger Things: nostalgia oitentista, suspense e personagens cativantes.'),
('pedro.oliveira', 'Cinema com Propósito', 'https://images.pexels.com/photos/799158/pexels-photo-799158.jpeg', 'Análise completa de "Parasita", vencedor do Oscar. Um filme que é muito mais do que aparenta.'),
('lucas.pereira', 'Meu Novo Som', 'https://images.pexels.com/photos/1647161/pexels-photo-1647161.jpeg', 'Lancei uma faixa nova que mistura lo-fi e indie. Clique para ouvir e me diga o que achou!'),
('julia.santos', 'Look da Semana', 'https://images.pexels.com/photos/2983464/pexels-photo-2983464.jpeg', 'Tendência comfy e casual para dias de parque. Veja fotos e sugestões de peças.'),
('ricardo.ferreira', 'Gastronomia Urbana', 'https://images.pexels.com/photos/262978/pexels-photo-262978.jpeg', 'Fui a um bistrô aconchegante e testei pratos incríveis. Veja minha resenha completa.'),
('amanda.rodrigues', 'Mundo Felino', 'https://images.pexels.com/photos/45201/kitty-cat-kitten-pet-45201.jpeg', 'Fotos e dicas sobre cuidados com gatos. Conheça meu fofo companheiro!'),
('gabriel.almeida', 'Abstrato em Tela', 'https://images.pexels.com/photos/370799/pexels-photo-370799.jpeg', 'Compartilho minha nova pintura e falo sobre o processo criativo e as inspirações.'),
('fernanda.costa', 'Make do Dia', 'https://images.pexels.com/photos/3771837/pexels-photo-3771837.jpeg', 'Tutorial passo-a-passo do look que usei para a festa. Simples e marcante!'),
('thiago.gomes', 'IA e Futuro', 'https://images.pexels.com/photos/3861969/pexels-photo-3861969.jpeg', 'Exploro os impactos da IA na sociedade e tendências para os próximos anos.'),
('joao.silva', 'Ficção é Vida', 'https://images.pexels.com/photos/261909/pexels-photo-261909.jpeg', 'Como as histórias de fantasia podem influenciar nossa visão de mundo.'),
('maria.souza', 'Maratona de Suspense', 'https://images.pexels.com/photos/799137/pexels-photo-799137.jpeg', 'Listo as melhores séries de suspense para assistir nesse mês.'),
('pedro.oliveira', 'Cinema Asiático', 'https://images.pexels.com/photos/799158/pexels-photo-799158.jpeg', 'Trago um especial sobre filmes coreanos que merecem ser vistos.'),
('julia.santos', 'Moda Sustentável', 'https://images.pexels.com/photos/2983464/pexels-photo-2983464.jpeg', 'Como montar looks estilosos com peças recicladas.'),
('gabriel.almeida', 'Inspiração nas Cores', 'https://images.pexels.com/photos/370799/pexels-photo-370799.jpeg', 'A influência da paleta de cores nas emoções que uma arte transmite.');