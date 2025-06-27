#ifndef PLAYLIST_H
#define PLAYLIST_H
typedef struct Musica
{
    char titulo[100];
    char artista[100];
    int duracao; // em segundos
    struct Musica *proxima;
} Musica;
typedef struct
{
    Musica *atual;
    int tamanho;
    int modo_repeticao; // 0 = desativado, 1 = ativado
} Playlist;

// Inicialização e finalização
Playlist *criar_playlist();
void liberar_playlist(Playlist *playlist);

// Gerenciamento de músicas
void adicionar_musica(Playlist *playlist, const char *titulo, const char *artista, int duracao);
int remover_musica(Playlist *playlist, const char *titulo);

// Navegação
void proxima_musica(Playlist *playlist);
void musica_anterior(Playlist *playlist);

// Configuração
void alternar_modo_repeticao(Playlist *playlist);

// Visualização
void listar_musicas(Playlist *playlist);

Musica *buscar_musica(Playlist *playlist, const char *titulo);

void exibir_musica_atual(Playlist *playlist);

#endif