:- use_module(library(http/thread_httpd)).
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/html_write)).
:- use_module(library(http/http_parameters)).

:- http_handler(root(processa_pedido), mensagem, []).

servidor(Porta) :-
    http_server(http_dispatch, [port(Porta)]).

mensagem(Request) :-
    http_parameters(Request, [
        nomeCliente(Nome, []),
        telCliente(Tel, []),
        emailCliente(Email, []),
        tamanho(Tamanho, []),
        ing(Ingredientes, []),
        tempo(Horario, []),
        obs(Obs, [])
    ]),
    reply_html_page(
        title('Pedido Recebido'),
        [
            h1('Pedido feito com sucesso!'),
            p(['Nome: ', Nome]),
            p(['Telefone: ', Tel]),
            p(['Email: ', Email]),
            p(['Tamanho da pizza: ', Tamanho]),
            p(['Ingredientes: ', Ingredientes]),
            p(['Horário: ', Horario]),
            p(['Observações: ', Obs])
        ]
    ).
