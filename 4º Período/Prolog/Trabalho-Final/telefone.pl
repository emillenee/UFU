:- dynamic telefone_de/2.
:- consult('kb.pl').

main :-
    repeat,
    mostra_menu,
    le_op(X),
    executa(X),
    X =:= 8, !.

mostra_menu :-
    write("1-Obter telefone"), nl,
    write("2-Adicionar assinante"), nl,
    write("3-Modificar telefone"), nl,
    write("4-Modificar nome"), nl,
    write("5-Remover assinante"), nl,
    write("6-Remover Telefone"), nl,
    write("7-Listar assinantes com letra inicial"),nl,
    write("8-Finalizar"), nl.

le_op(X) :- get0(Char),
    get0(_),
    X is Char - 48.


cadastra(Nome) :- le_tel(Telefone),
    atom_chars(Telefone, ListaTelefone),
    verifica(ListaTelefone, Tam),
    ( Tam =:= 8 ->
         assertz(telefone_de(Nome, [Telefone])),
         salvar_base
    ;
        write("Telefone invalido. Digite um com 8 digitos"), nl
    ).

mostrar_telefones([], _).

mostrar_telefones([X|Xs], N) :-
    write(N), write(" - "), write(X), nl,
    N1 is N+1, mostrar_telefones(Xs, N1).

executa(1) :-
    le_nome(Nome),
    atom_string(Nomeatom, Nome),
    ( telefone_de(Nomeatom,Telefones) ->
        write("Telefones: "),nl, mostrar_telefones(Telefones, 1), nl
    ;
        write("Usuário não cadastrado."),nl,
        write("Deseja cadastrar? (S/N):"),nl,
        obtemsn(Op),
        (Op = sim -> cadastra(Nome))
    ).


executa(2) :-
    le_nome(Nome),
    (telefone_de(Nome, Telefones) ->
      write("Assinante já cadastrado."),nl,
      write("Deseja adicionar mais um telefone? (S/N):"), nl,
      obtemsn(Op),
      (Op = sim -> nl,
        le_tel(NovoT),
        atom_chars(NovoT, NovoTelefone),
        verifica(NovoTelefone, Tam),
        (Tam =:= 8 ->
          append(Telefones, [NovoT], NovosTelefones),
          retract(telefone_de(Nome, Telefones)),
          assertz(telefone_de(Nome, NovosTelefones)),
          salvar_base,
          write("Número adicionado com sucesso!"),nl
        ;
        write("Telefone inválido. Digite um com 8 digitos."),nl
        )
      ;
      write("Operação cancelada."), nl
      )
    ;
      cadastra(Nome)
    ).

executa(3) :-
    le_nome(Nome),
    atom_string(Nomeatom, Nome),
    modifica_telefone(Nomeatom).

executa(4) :-
    le_nome(Nome),
    atom_string(Nomeatom, Nome),
    modifica_nome(Nomeatom).

executa(5) :-
    le_nome(Nome),
    atom_string(Nomeatom, Nome),
    ( telefone_de(Nomeatom, T) ->
        retract(telefone_de(Nomeatom, T)),
        write("Assinante removido com sucesso!"),nl,
        salvar_base
    ;
        write("Registro nao encontrado."), nl
    ).

executa(6) :-
    le_nome(Nome),
    atom_string(Nomeatom, Nome),
    remove_telefone(Nomeatom).


executa(7) :- write("Por qual inicial deseja buscar?"), nl,
    get0(C), get0(_), char_code(Char,C), listar_inicial(Char).

executa(8) :- write("Finalizando..."), nl.

remove_telefone(Nome) :-
    (telefone_de(Nome, T) ->
     write("Telefones atuais: "),nl, mostrar_telefones(T, 1), nl,
     write("Digite o número do valor que deseja remover:"),nl,
     le_op(P),
     pega_lista(T, P, TelefoneAntigo),
     write("Telefone escolhido: "), write(TelefoneAntigo),nl,
     remove(T, P, NovosTelefones),
     retract(telefone_de(Nome, T)),
     assertz(telefone_de(Nome, NovosTelefones)),
     salvar_base,
     write("Telefone removido com sucesso!"),nl
    ;
        write("Registro nao encontrado."), nl
    ).

remove([_|Xs], 1, Xs).
remove([X|Xs], P, [X|Resto]) :-
    P > 1, P1 is P-1, remove(Xs, P1, Resto).

modifica_telefone(Nome) :-
    ( telefone_de(Nome, TelefonesAntigos) ->
        write("Telefones atuais: "),nl, mostrar_telefones(TelefonesAntigos, 1), nl,
        write("Digite o número do valor que deseja alterar:"),nl,
        le_op(P),
        pega_lista(TelefonesAntigos, P, TelefoneAntigo),
        write("Telefone escolhido: "), write(TelefoneAntigo),nl,
        write("Digite o novo número:"), nl,
        le_str(NovoTelefoneC), atom_chars(NovoTelefone, NovoTelefoneC),
        substituir_telefone(TelefonesAntigos, P, NovoTelefone, NovosTelefones),
        retract(telefone_de(Nome, TelefonesAntigos)),
        assertz(telefone_de(Nome, NovosTelefones)),
        salvar_base
    ;
        write("Registro nao encontrado."), nl
    ).

substituir_telefone([_|R], 1, Novo, [Novo|R]).

substituir_telefone([X|Xs], P, Novo, [X|NovoResto]) :-
    P > 1, P1 is P-1, substituir_telefone(Xs, P1, Novo,NovoResto).

pega_lista([E|_], 1, E).

pega_lista([_|R], Pos, E) :-
    Pos > 1, Pos1 is Pos-1, pega_lista(R, Pos1, E).


modifica_nome(Nome) :-
    (telefone_de(Nome, Tel) ->
        write("Digite o novo nome: "),
        le_str(N),
        atom_chars(Atomnome, N),
        retract(telefone_de(Nome, Tel)),
        assertz(telefone_de(Atomnome, Tel)),
        salvar_base
    ;
        write("Registro não encontrado."), nl
    ).

verifica([], 0).

verifica([C|Resto], Tam) :-
    char_code(C, X),
    X >= 48, X =< 57,
    verifica(Resto, TamResto),
    Tam is TamResto + 1.

verifica([C|_], _) :-
    char_code(C, X),
    (X < 48 ; X > 57),
    fail.


salvar_base :-
    tell('kb.pl'),
    listing(telefone_de/2),
    told.

le_str(String) :-
    get0(Char), le_str_aux(Char,String).

le_str_aux(-1, []) :- !.
le_str_aux(10, []) :- !.
le_str_aux(13, []) :- !.
le_str_aux(Char, [Char|Resto]) :- le_str(Resto).


le_nome(Nome) :-
    write("Digite o nome: "),
    le_str(N),
    atom_chars(Nome, N).

le_tel(Telefone) :-
    write("Digite o telefone: "),
    le_str(T),
    atom_chars(Telefone, T).

obtemsn(Resultado) :-
    get(Char),
    get0(_),
    digitado(Char, Resultado), !.
obtemsn(Resultado) :- % se digitado fracassar.
    nl, write('Favor, digitar S ou N: '),
    obtemsn(Resultado).

digitado(83, sim). % ASCII S
digitado(115, sim). % ASCII s
digitado(78, nao). % ASCII N
digitado(110,nao). % ASCII n

listar_inicial(C) :-
    telefone_de(Nome, Telefones),
    atom_chars(Nome, NomeLista),
    NomeLista = [ListaLetra | _],
    atom_chars(Letra, [ListaLetra]),
    ( Letra = C ->
        write("Nome: "),
        write(Nome), nl,
        write("Telefones: "),nl,
        mostrar_telefones(Telefones, 1),nl
        ;
        true
    ),
    fail.

listar_inicial(_).
