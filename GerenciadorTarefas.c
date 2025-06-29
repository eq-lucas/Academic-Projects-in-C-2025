#include <stdio.h>
#include <stdlib.h>

#define tam 40

void limparBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * Retorna tamanho string
 * @param string a ser retornada
 * @return comprimento da string
 */
int MinhaStrlen(const char *str)
{
    const char *string = str;
    size_t tamanho = 0;
    while (*string != 0)
    {
        tamanho++;
        string++;
    }
    return tamanho;
}

/**
 * Funcao verificar 2 strings sao iguais
 * @param fechar string a ser verificada
 * @param word deve ser igual a esta palavra
 * @return 1 se as strings forem diferentes
 */
int stringequal(const char *fechar, const char *word)
{
    const char *caminharfechar = fechar;
    const char *verificarWord = word;
    const char *verificarfechar = fechar;
    size_t tamanhoFechar = 0;

    while ((*caminharfechar) != 0)
    {
        tamanhoFechar++;
        caminharfechar++;
    }

    for (unsigned int i = 0; i < tamanhoFechar; i++)
    {
        if ((*verificarfechar) != (*verificarWord))
            return 1;

        verificarfechar++;
        verificarWord++;
    }

    if (MinhaStrlen(word) != tamanhoFechar)
        return 1;

    return 0;
}

/* VERSAO 2 DE STRINGEQUAL
int stringsIguais(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (*a != *b)
            return 0;
        a++;
        b++;
    }

    return *a == *b;
}

*/

/**
 * verificar se existe tal caracter na string e a qtdade
 * @param str string a ser verificada
 * @param c caracter a ser insepcionado
 * 
 */
int strHaveCaracter(char *str, char c)
{
    int qtde = 0;

    while ((*str != 0))
    {
        if ((*str) == c)
            qtde++;
        str++;
    }
    return qtde;
}

/**
 * truncar string com ".txt"
 * @param str string a ser truncada
 * @param truncar o ".txt"
 *@return 1 em caso de tamanho mairo q 36 caracteres
 */
int  truncarString(char *string, char *truncar)
{
if(MinhaStrlen(string)>36)
{
    printf("Texto muito longo, deve ter 36 caracteres no maximo!\n\n");
    return 1;
}


    char *str = string;
    int tamanhoTruncar = MinhaStrlen(truncar);

    while ((*str) != 0)
        str++;


    for (int i = 0; i < tamanhoTruncar; i++)
    {
        *str = truncar[i];
        str++;
    }
    *str = 0;

    return 0;
}

void confirmarSaida(char *Sair)
{
    while (1)
    {
        printf("\nDigite 'sim' para sair: ");
        scanf(" %4s", Sair);
        limparBuffer();
        if (!stringequal(Sair, "sim"))
            break;
    }
}

void OpenArquivo(FILE *arquivo, char *name)
{
    int qtde = 0;
    char *nomecaminho = (char *)malloc(sizeof(char) * tam);
    do
    {

        printf("\nDigite o nome do arquivo que deseja abrir: ");

        fgets(nomecaminho, (tam - 4), stdin);

        if (!(qtde = strHaveCaracter(nomecaminho, ' ')))
            break;

        printf("O caracter [ %c ] apareceu: %dx\nNao pode haver nenhum\n", ' ', qtde);

    } while (1);

    truncarString(nomecaminho, ".txt");
    arquivo = fopen(nomecaminho, "r");
    if (arquivo == NULL)
    {
        printf("Arquivo inexistente, tente novamente\n\n");
    }
}

void Visualizar()
{
}

void Inserir()
{
}

void Atualizar()
{
}

void Deletar()
{
}

int main()
{
    FILE *arquivo;
    char *nome;
    printf("-- Gerenciador de tarefas v1.0 --\n\n");

    char Sair[5] = {0};
    int mode = 0;
    do
    {
        do
        {
            printf("\nSelecione um modo:\n\n"
                   "1) Abrir arquivo existente\n"
                   "2) Criar arquivo novo\n"
                   "3) Sair\n"
                   "\nDigite aqui: ");
            scanf(" %d", &mode);
            limparBuffer();

            switch (mode)
            {
            case 1:
                OpenArquivo(arquivo, nome);
                break;
            case 2:
                CreateArquivo(arquivo, nome);
                break;
            case 3:
                confirmarSaida(Sair);
                break;

            default:
                printf("Numero selecionado invalido.\n\n");
                mode = -1;
                break;
            }
        } while (mode == -1);

        if (!stringequal(Sair, "sim"))
            break;

        do
        {
            printf("\nSelecione um modo:\n\n"
                   "1) Visualizar.\n"
                   "2) Inserir.\n"
                   "3) Atualizar.\n"
                   "4) Deletar.\n"
                   "5) sair\n"
                   "\nDigite aqui: ");

            scanf(" %d", &mode);
            limparBuffer();

            do
            {
                switch (mode)
                {
                case 1:
                    Visualizar();
                    break;
                case 2:
                    Inserir();
                    break;
                case 3:
                    Atualizar();
                    break;
                case 4:
                    Deletar();
                    break;
                case 5:
                    printf("saindo deste arquivo...");
                    confirmarSaida(Sair);
                    break;

                    break;

                default:
                    printf("Numero selecionado invalido.\n\n");
                    mode = -1;
                    break;
                }
            } while (mode == -1);

        } while (stringequal(Sair, "sim"));

    } while (1);

    return 0;
}
