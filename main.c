// main.c
#include <stdio.h>
#include "playlist.h"

int main() {
    printf("Criando a playlist...\n");
    Playlist *minha_playlist = criar_playlist();

    printf("\nAdicionando músicas...\n");
    adicionar_musica(minha_playlist, "Drip", "Raffa Moreira", 355);
    adicionar_musica(minha_playlist, "Nos tempos de Motorola", "Jé Santiago", 482);
    adicionar_musica(minha_playlist, "Smells Like Teen Spirit", "Nirvana", 301);
    adicionar_musica(minha_playlist, "Sozinho no Sukyia", "Raffa Moreira Makalister", 369);

    listar_musicas(minha_playlist);
    exibir_musica_atual(minha_playlist);

    printf("\n>>> Tocando próxima música...\n");
    proxima_musica(minha_playlist);
    exibir_musica_atual(minha_playlist);
    
    printf("\n>>> Tocando próxima música...\n");
    proxima_musica(minha_playlist);
    exibir_musica_atual(minha_playlist);

    printf("\n>>> Voltando para música anterior...\n");
    musica_anterior(minha_playlist);
    exibir_musica_atual(minha_playlist);

    listar_musicas(minha_playlist);

    printf("\nRemovendo 'Stairway to Heaven'...\n");
    if (remover_musica(minha_playlist, "Stairway to Heaven")) {
        printf("Música removida com sucesso.\n");
    } else {
        printf("Música não encontrada.\n");
    }

    listar_musicas(minha_playlist);
    exibir_musica_atual(minha_playlist);

    printf("\nLiberando a memória da playlist...\n");
    liberar_playlist(minha_playlist);
    printf("Programa finalizado.\n");

    return 0;
}