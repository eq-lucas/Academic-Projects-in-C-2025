
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int h, tamx = 10, tamy = 10;

void inicializar();
void jogando();
void modojogo(int modo);
void sortearbombas(int bombas);
void tabuleiro();
int ehvalido(int posicaox, int posicaoy);
int descobrirvizinhos(int ll, int cc);
int seraqueganhou();
void liberarmemoria();
void marcandopossivelbomba();





int limpezateclado()
{
    int limpeza;
    while ((limpeza = getchar()) != '\n' && limpeza != 'EOF')
        ;
}

// assim funciona tb deve se APOS o scanf pois se n tiver nada no buffer do teclado
// tera que digitar nvoamente antes, o && garante que no proxim ocaractere deve ser um dos 2
// caso nao seja 1 ja invalida a codnica e sai do loop, mas isso nao faz o texto que foi enviado
// apos as obtencao dos %d %d tipo 3 3 22 2 2, fara 3 3 ir pro %d %d e o resto ser apagado

typedef struct
{
    int ehbomba;                      // 0 ou 1
    int posicaovalida;                // 0 ou 1
    int descoberto;                   // 0 ou 1
    int verEmMimVizinhosQueSaoBombas; // 1 a 4
    int mascarar;
    int descobrirbomba;
} box;

box **caixa;

int i, j, l, c;






void criartabuleiro()
{
    caixa = (box **)malloc(tamx * sizeof(box *));
    if (caixa == NULL)
        exit(1);
    for (i = 0; i < tamx; i++)
    {
        caixa[i] = (box *)malloc(tamy * sizeof(box));
        if (caixa[i] == NULL)
            exit(1);
        for (j = 0; j < tamy; j++)
        {
            caixa[i][j].descoberto = 0;
            caixa[i][j].ehbomba = 0;
        }
    }
}






void inicializar()
{
    for (i = 0; i < tamx; i++)
    {
        for (j = 0; j < tamy; j++)
        {
            caixa[i][j].descoberto = 0;
            caixa[i][j].ehbomba = 0;
            caixa[i][j].mascarar = 0;
            caixa[i][j].descobrirbomba = 0;
        }
    }

    tabuleiro();
}






void jogando()
{
    int abc = 1;

    int modoDeJogo = 0;
    printf("\nDefina um modo de jogo:\n(1)Facil\n(2)Medio\n(3)Dificil\nDIGITE AQUI: ");
    do
    {
        scanf("%d", &modoDeJogo);
        limpezateclado();
        if (modoDeJogo > 3 || modoDeJogo < 1)
            printf("\nSelecione um modo valido.\nDIGITE AQUI:");
    } while (modoDeJogo > 3 || modoDeJogo < 1);

    do
    {
        if(!abc)
        marcandopossivelbomba();
        printf("\nDigite uma posicao (x,y): ");
        do
        {

            scanf("%d %d", &l, &c);
            limpezateclado();

            if (!ehvalido(l, c) || caixa[l][c].descoberto == 1)
                printf("\nPosicao ja descoberta ou invalida.\nDigite novamente: ");
        } while (!ehvalido(l, c) || caixa[l][c].descoberto == 1);
        caixa[l][c].descoberto = 1;
        
        if (abc)
            modojogo(modoDeJogo);
        abc = 0;
        descobrirvizinhos(l, c);
        tabuleiro();

    } while (caixa[l][c].ehbomba == 0 && !seraqueganhou());

    if (seraqueganhou() && caixa[l][c].ehbomba == 0)
    {
        printf("Voce gahou!");
        return;
    }

    printf("\nVoce perdeu.");
    for(int i=0;i<tamx;i++){
        for(j=0;j<tamy;j++){
            caixa[i][j].descobrirbomba = 1;
        }
    }
    tabuleiro();
}






int main()
{

    char tamanhodefault;
    printf("\n\tBem-Vindo ao Jogo do Campo Minado!\n\n\nPressione ENTER se quiser o tabuleiro padrao, se nao digite (1) e pressione Enter:");

    if ((tamanhodefault = getchar()) == '1')
    {
        printf("\nDefina o tamanho do tabuleiro que deseja.\n");

        printf("\nTamanho maximo de linhas:");
        scanf("%d", &tamx);
        limpezateclado();

        printf("\nTamanho maximo de colunas: ");
        scanf("%d", &tamy);
        limpezateclado();
    }
    else
    {
        tamx = 10;
        tamy = 10;
    }

    criartabuleiro();

    srand(time(NULL));
    char querContinuarJogando[3];

    do
    {
        inicializar();
        jogando();

        printf("\n\n quer jogar novamente? (s/n): ");
        fgets(querContinuarJogando, sizeof(querContinuarJogando), stdin);

    } while (!(strcmp(querContinuarJogando, "s\n")));

    liberarmemoria();
    return 0;
}






void modojogo(int modo)
{
    switch (modo)
    {
    case 1:
        sortearbombas((tamx * tamy) - ((tamx * tamy * 90) / 100));
        printf("\nModo escolhido: FACIL");
        break;
    case 2:
        sortearbombas((tamx * tamy) - (tamx * tamy * 80) / 100);
        printf("\nModo escolhido: MEDIO");

        break;
    case 3:
        sortearbombas((tamx * tamy) - (tamx * tamy * 70) / 100);
        printf("\nModo escolhido: DIFICIL");

        break;
    }
}






void sortearbombas(int qtdebombas)
{
    if ((tamx * tamy) < 2)
        return;

    int lll, ccc;
    for (i = 0; i < qtdebombas; i++)
    {
        lll = rand() % tamx;
        ccc = rand() % tamy;
        if (caixa[lll][ccc].ehbomba == 1 || caixa[lll][ccc].descoberto == 1)
        {
            i--;
            continue;
        }
        

    caixa[lll][ccc].ehbomba = 1;
    }
}






void tabuleiro()
{
    int pontilhado;
    printf("\n\n");

    for (i = -1; i < tamx; i++)
    {

        if (i == -1)
            printf("      ");

        if (i > -1)
            printf(" %2d | ", i);

        for (j = 0; j < tamy; j++)
        {
            if (i == -1)
            {
                printf(" %2d ", j);
                continue;
            }

            if(caixa[i][j].ehbomba == 1 && caixa[i][j].descobrirbomba == 1 && caixa[i][j].descoberto == 0)
            {
              printf("  X ");
              continue;
            }

            if(caixa[i][j].mascarar == 1 && caixa[i][j].descoberto == 0)
            {
              printf("  # ");
              continue;
            }

            if (caixa[i][j].ehbomba && caixa[i][j].descoberto)
            {
                printf("  x ");
              continue;
            }
            if (caixa[i][j].descoberto == 0)
            {
                printf("  . ");
                continue;
            }

            printf(" %2d ", caixa[i][j].verEmMimVizinhosQueSaoBombas);
        }
        if (i == -1)
        {
            printf("\n      ");
            for (pontilhado = 0; pontilhado < tamy; pontilhado++)
                printf("----");
        }
        printf("\n");
    }
}






int ehvalido(int px, int py)
{
    if (px < tamx && px >= 0 && py < tamy && py >= 0)
    return 1;

    return 0;
}






int descobrirvizinhos(int ll, int cc)
{
    caixa[ll][cc].descoberto = 1;

    int qtdedebombavizinha = 0;
    if (ehvalido(ll + 1, cc) && caixa[ll + 1][cc].ehbomba)
        qtdedebombavizinha++;
    if (ehvalido(ll - 1, cc) && caixa[ll - 1][cc].ehbomba)
        qtdedebombavizinha++;
    if (ehvalido(ll, cc + 1) && caixa[ll][cc + 1].ehbomba)
        qtdedebombavizinha++;
    if (ehvalido(ll, cc - 1) && caixa[ll][cc - 1].ehbomba)
        qtdedebombavizinha++;

    caixa[ll][cc].verEmMimVizinhosQueSaoBombas = qtdedebombavizinha;

    if (qtdedebombavizinha)
        return 0;

    if (ehvalido(ll + 1, cc) && !caixa[ll + 1][cc].ehbomba && caixa[ll + 1][cc].descoberto == 0)
        descobrirvizinhos(ll + 1, cc);
    if (ehvalido(ll - 1, cc) && !caixa[ll - 1][cc].ehbomba && caixa[ll - 1][cc].descoberto == 0)
        descobrirvizinhos(ll - 1, cc);
    if (ehvalido(ll, cc + 1) && !caixa[ll][cc + 1].ehbomba && caixa[ll][cc + 1].descoberto == 0)
        descobrirvizinhos(ll, cc + 1);
    if (ehvalido(ll, cc - 1) && !caixa[ll][cc - 1].ehbomba && caixa[ll][cc - 1].descoberto == 0)
        descobrirvizinhos(ll, cc - 1);
}






int seraqueganhou()
{
    int ppx, ppy;

    for (ppx = 0; ppx < tamx; ppx++)
    {
        for (ppy = 0; ppy < tamy; ppy++)
        {
            if (!caixa[ppx][ppy].descoberto && caixa[ppx][ppy].ehbomba)
                continue;
            if (!caixa[ppx][ppy].descoberto)
                return 0;
        }
    }
    return 1;
}





void marcandopossivelbomba()
{
char mask;
    do{
printf("\nMarcar posicoes digite:  (1).\nDesmarcar posicoes digite:  (2).\nEfetuar jogada digite:  (3).\nDigite aqui: ");

scanf("%c",&mask);
limpezateclado();
printf("\n");
if(mask == '3')
return;

if(mask == '1'){

    printf("\nPARA PARAR DE MARCAR BASTA digitar -1.\n\n");
    
int llll,cccc;


    for(;;) {

    printf("Digite uma posicao que deseja marcar:");

    
    scanf("%d",&llll);

    if(llll == -1){
        limpezateclado();
    break;
    }

    scanf("%*c%d",&cccc);
    limpezateclado();




    if(ehvalido(llll,cccc) && caixa[llll][cccc].descoberto == 0)
    caixa[llll][cccc].mascarar = 1;

        }
        tabuleiro();
        continue;
    }

if(mask == '2'){

    printf("\nPARA PARAR DE DESMARCAR BASTA digitar -1.\n\n");
    
int llll,cccc;


    for(;;) {

    printf("Digite uma posicao que deseja desmarcar:");

    
    scanf("%d",&llll);

    if(llll == -1){
        limpezateclado();
    break;
    }

    scanf("%*c%d",&cccc);
    limpezateclado();


    if(ehvalido(llll,cccc) )
    caixa[llll][cccc].mascarar = 0;

        }
        tabuleiro();
        continue;
    }


    } while(mask =='2' || mask == '1');



}







void liberarmemoria()
{
    for (i = 0; i < tamx; i++)
    {
        free(caixa[i]);
    }
    free(caixa);
}