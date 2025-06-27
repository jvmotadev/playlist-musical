#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

Playlist *criar_playlist(){
    Playlist *playlist = (Playlist *)malloc(sizeof(Playlist));
    if (playlist == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a playlist.\n");
        return NULL;
    }
    playlist->atual = NULL;
    playlist->tamanho = 0;
    playlist->modo_repeticao = 0; 
    return playlist;
}

void liberar_playlist(Playlist *playlist) {
    if (playlist == NULL) return;

    if (playlist->atual != NULL) {
        Musica *inicio = playlist->atual;
        Musica *musica = inicio->proxima;
        while (musica != inicio) {
            Musica *temp = musica;
            musica = musica->proxima;
            free(temp);
        }
        free(inicio);
    }

    free(playlist);
}


void adicionar_musica(Playlist *playlist, const char *titulo, const char *artista, int duracao) {
    if (playlist == NULL) return;

    Musica *nova_musica = (Musica *) malloc(sizeof(Musica));
    if (nova_musica == NULL) {
        perror("Erro ao alocar memória para a nova música");
        return;
    }

    // Copia os dados para a nova estrutura de música
    strncpy(nova_musica->titulo, titulo, 99);
    nova_musica->titulo[99] = '\0'; // Garante terminação nula
    strncpy(nova_musica->artista, artista, 99);
    nova_musica->artista[99] = '\0'; // Garante terminação nula
    nova_musica->duracao = duracao;

    if (playlist->tamanho == 0) { // A playlist está vazia
        playlist->atual = nova_musica;
        nova_musica->proxima = nova_musica; // A música aponta para si mesma
    } else { // A playlist já tem músicas
        // Insere a nova música logo após a música atual
        nova_musica->proxima = playlist->atual->proxima;
        playlist->atual->proxima = nova_musica;
    }

    playlist->tamanho++;
}

int remover_musica(Playlist *playlist, const char *titulo) {
    if (playlist == NULL || playlist->tamanho == 0) {
        return 0; // Playlist não existe ou está vazia
    }

    Musica *musica_anterior = playlist->atual;
    Musica *musica_a_remover = NULL;

    // Procura pela música a ser removida, mantendo o controle da música anterior
    for (int i = 0; i < playlist->tamanho; i++) {
        if (strcmp(musica_anterior->proxima->titulo, titulo) == 0) {
            musica_a_remover = musica_anterior->proxima;
            break;
        }
        musica_anterior = musica_anterior->proxima;
    }

    if (musica_a_remover == NULL) {
        return 0; // Música não encontrada
    }

    // Caso 1: Removendo a única música da lista
    if (playlist->tamanho == 1) {
        playlist->atual = NULL;
    } else {
        // Remove a música religando os ponteiros
        musica_anterior->proxima = musica_a_remover->proxima;
        
        // Se a música a ser removida for a "atual", avança a "atual"
        if (musica_a_remover == playlist->atual) {
            playlist->atual = musica_a_remover->proxima;
        }
    }
    
    free(musica_a_remover);
    playlist->tamanho--;

    return 1;
}



void proxima_musica(Playlist *playlist) {
    if (playlist != NULL && playlist->atual != NULL) {
        // Simplesmente avança para o próximo nó na lista circular
        playlist->atual = playlist->atual->proxima;
    }
}


void musica_anterior(Playlist *playlist) {
    if (playlist == NULL || playlist->tamanho <= 1) {
        // Não faz nada se a lista for nula, vazia ou tiver apenas uma música
        return;
    }

    Musica *temp = playlist->atual;
    // Percorre a lista até encontrar o nó que aponta para o atual
    while (temp->proxima != playlist->atual) {
        temp = temp->proxima;
    }
    // O nó encontrado (temp) é o anterior
    playlist->atual = temp;
}


void alternar_modo_repeticao(Playlist *playlist) {
    if (playlist != NULL) {
        playlist->modo_repeticao = !playlist->modo_repeticao; // Inverte o valor (0->1, 1->0)
        printf("Modo de repetição %s.\n", playlist->modo_repeticao ? "ativado" : "desativado");
    }
}

void listar_musicas(Playlist *playlist) {
    if (playlist == NULL || playlist->tamanho == 0) {
        printf("A playlist está vazia.\n");
        return;
    }

    printf("---- Playlist (%d músicas) ----\n", playlist->tamanho);
    Musica *temp = playlist->atual;
    for (int i = 0; i < playlist->tamanho; i++) {
        if (temp == playlist->atual) {
            printf("=> "); // Indica a música atual
        } else {
            printf("   ");
        }
        printf("Título: %s, Artista: %s, Duração: %d:%02d\n", 
               temp->titulo, temp->artista, temp->duracao / 60, temp->duracao % 60);
        temp = temp->proxima;
    }
    printf("-----------------------------\n");
}


Musica *buscar_musica(Playlist *playlist, const char *titulo) {
    if (playlist == NULL || playlist->tamanho == 0) {
        return NULL;
    }

    Musica *temp = playlist->atual;
    for (int i = 0; i < playlist->tamanho; i++) {
        if (strcmp(temp->titulo, titulo) == 0) {
            return temp; // Música encontrada
        }
        temp = temp->proxima;
    }

    return NULL; // Música não encontrada
}


void exibir_musica_atual(Playlist *playlist) {
    if (playlist != NULL && playlist->atual != NULL) {
        Musica *atual = playlist->atual;
        printf("\n--> Tocando Agora:\n");
        printf("    Título: %s\n", atual->titulo);
        printf("    Artista: %s\n", atual->artista);
        printf("    Duração: %d:%02d\n", atual->duracao / 60, atual->duracao % 60);
    } else {
        printf("Nenhuma música tocando. A playlist está vazia.\n");
    }
}