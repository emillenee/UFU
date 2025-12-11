:- use_module(library(http/thread_httpd)).
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/http_parameters)).
:- use_module(library(http/html_write)).

:- http_handler(root(processa_pedido), cadastra_pedido, []).
:- http_handler(root(processa_cancelamento), cancela_pedido, []).

servidor(Porta) :-
    http_server(http_dispatch, [port(Porta)]).

:- dynamic(pedido/7).

cadastra_pedido(Request) :-
    http_parameters(Request, [
        nomeCliente(C, []),
        telCliente(T, []),
        emailCliente(E, []),
        tamanho(S, []),
        ing(Ingredientes, [optional(true), list(atom)]),
        tempo(H, []),
        obs(O, [])
    ]),
    processa_pedido(C, T, E, S, Ingredientes, H, O),
    ingredientes_para_html(Ingredientes, IngredientesHTML),
    reply_html_page(
        title('Pedido Recebido'),
        [
            h1('Pedido feito com sucesso!'),
            p(['Nome: ', C]),
            p(['Telefone: ', T]),
            p(['Email: ', E]),
            p(['Tamanho da pizza: ', S]),
            div([
                p('Ingredientes:') | IngredientesHTML
            ]),
            p(['Horario: ', H]),
            p(['Observacoes: ', O])
        ]
    ).

processa_pedido(C, T, E, S, Ingredientes, H, O) :-
    open('pedidos.pl', append, Stream),
    writeq(Stream, pedido(C, T, E, S, Ingredientes, H, O)),
    write(Stream, '.'),
    nl(Stream),
    flush_output(Stream),
    close(Stream).

ingredientes_para_html([], []).
ingredientes_para_html([H|T], [H, br([])|Resto]) :-
    ingredientes_para_html(T, Resto).

cancela_pedido(Request) :-
    http_parameters(Request, [telCliente(Tel, [])]),
    consult('pedidos.pl'),
    findall(pedido(N, Tel, E, T, I, H, O),
            pedido(N, Tel, E, T, I, H, O),
            Pedidos),
    Pedidos \= [],
    retractall(pedido(_, Tel, _, _, _, _, _)),
    open('pedidos.pl', write, Stream),
    forall(pedido(N, T2, E, Tam, Ing, Hora, Obs),
           format(Stream, 'pedido(~q,~q,~q,~q,~q,~q,~q).~n',
                  [N, T2, E, Tam, Ing, Hora, Obs])),
    close(Stream),
    reply_html_page(title('Pedido cancelado'),
                    [h1('Seu pedido foi cancelado com sucesso!')]).

cancela_pedido(_) :-
    reply_html_page(title('Erro'),
                    [h1('Nao encontramos nenhum pedido com esse telefone.')]).