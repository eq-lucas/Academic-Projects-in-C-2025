#include <stdio.h>
#include <stdlib.h>

#define tam 40

void limparBuffer()
{
    int c;
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
 *@return 1 em caso de tamanho maior q 36 caracteres
 */
int truncarString(char *string, char *truncar)
{
    if (MinhaStrlen(string) > 36)
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

/** Abrir o arquivo com nome desejado
 * @param arquivo variavel q recebe o endereco do arquivo com nome desejavle
 * @return 1 se o arquivo nao for encontrado
 *
 */
int OpenArquivo(FILE *arquivo, char *name)
{
    int qtde = 0;
    char *nomecaminho = (char *)malloc(sizeof(char) * tam);

    do
    {
        do
        {
            do
            {

                printf("\nDigite o nome do arquivo que deseja abrir: ");
                fgets(nomecaminho, (tam - 4), stdin);

                // se for com scanf n da o problema
                // a questao eh q fgets le 36 caracteres indepednentemente, ate encontrar '\n'
                // ou seja, se eu digitar casa, ele vai consumir todo o buffer: 'casa/n'
                // entao colcoar um if para se o strlen de nomecaminho for maior q 35
                // ja q ele le tam-4 = 36 e na vdd ele LE 36-1 caracteres deixando o ultimo (36)
                // para o nulo q ele insere no final da stirng
                // lembrando q o /n ele mantem da string! deve ser retirado ok
                // logo criar uma funcao chamda RetirarCaracter q recebe string e um caracter
                // logo fazer um if seria o ideal aqui
                // --------------------------------------------------------------
                // mas strlen>35 nunca ocorrea pq a string so guarda 35, e tb fazer ==35 n
                // garante q tem coisa no buffer pq posso ter digitado exatamente 35 caracteres
                // oq pode ser feito:
                // tenho q colocar entao uma funcao propria onde ela verifica se tem strlen==35
                // e no seu ultim ocaracter antes do nulo nao ser um /n oq logo signficia
                // q o /n ficou no buffer
                // if (strlen(nomecaminho) == 35 && nomecaminho[34] != '\n')
                // e se atender logo fazer a cahamda da funcao limpar buffer
                //
                // if (strchr(nomecaminho, '\n') == NULL)
                //
                // Este código é mais robusto porque não se importa com o tamanho do buffer.
                // Você pode mudar de 36 para 100 ou para 1000
                //
                // ou: if (strlen(nomecaminho) == VARIAVEL && nomecaminho[34] != '\n')

                if (MinhaStrlen(nomecaminho) == tam - 5 && nomecaminho[tam - 6])
                    limparBuffer();

                if (!(qtde = strHaveCaracter(nomecaminho, ' ')))
                    break;

                printf("O caracter [ %c ] apareceu: %dx\nNao pode haver nenhum\n", ' ', qtde);

            } while (1);

            if (!truncarString(nomecaminho, ".txt"))
                break;

        } while (1);

        arquivo = fopen(nomecaminho, "r");

        if (!(arquivo == NULL))
            break;

        char sair;

        printf("\n\t      -- Arquivo inexistente -- \n\n --Pressione [ENTER] para"
               "voltar ao menu iniciar --\n\n  ");
        do
        {
            if (sair = getchar() == '\n')
                break;
            limparBuffer();

            printf("PRESSIONE [ENTER] ");
        } while (1);

        return 1;

    } while (1);

    return 0;
}

int CreateArquivo(FILE *arquivo, char *nome)
{
    return 1;
}

int OpenLast()
{
    return 1;
}

/**
 * @return 1 sempre pois o objetivo eh listar e voltar pro menu q estava
 */
int listarArquivo(char *caminhoDaLista)
{
    FILE *file = fopen(caminhoDaLista, "a+");
    if (file == NULL)
    {
        printf("Ainda nao foram criados nenhum arquivo!\n\n");
        return 1;
    }
    printf("\n -- Arquivos existentes --\n\n");

    int i = 1;

    char *string = (char *)malloc(sizeof(char) * tam);

    while (fgets(string, tam, file) && string != NULL)
    {
        printf("%d| %s", i, string);
        i++;
    }
    free(string);
    //free dps pq o fgets vai no msm endereco q malloc alocou e SUBSTITUI, E NAO CRIA UM NOVO ENDERECO COM A NOVA STRING
    // E OBVIO se os nomes fossem maiores q 40 caracteres seria um outro for com verificacao se o caacter atual
    // eh um /n e se for, logo ai sim incrementar i e tudo mais... 
    printf("\n\n--------------------------\n");

    return 1;
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
    int retorno = 0;
    char *caminhoDaLista = "ListaDosArquivos.txt";
    // 0: pode progesseguir,
    // se 1: deve repetir o menu pois a condicao n foi atendida da funct
    printf("\n-- Gerenciador de tarefas v1.0 --\n\n");

    char Sair[5] = {0};
    int mode = 0;
    do
    {
        do
        {
            printf("\nSelecione um modo:\n\n"
                   "1) Abrir arquivo existente\n"
                   "2) Criar arquivo novo\n"
                   "3) Abrir Ultimo arquivo\n"
                   "4) Listar Arquivos existentes\n"
                   "4) Sair\n"
                   "\nDigite aqui: ");
            scanf("%d", &mode);
            limparBuffer();

            switch (mode)
            {
            case 1:
                retorno = OpenArquivo(arquivo, nome);
                mode = 0;
                break;
            case 2:
                retorno = CreateArquivo(arquivo, nome);
                mode = 0;
                break;
            case 3:
                retorno = OpenLast(arquivo, nome);
                mode = 0;
                break;
            case 4:
                retorno = listarArquivo(caminhoDaLista);
                mode = 0;
                break;

            default:
                printf("\n -- Numero selecionado invalido. --\n");
                mode = -1;
                break;
            }
        } while (mode == -1 || retorno == 1);

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

            scanf("%d", &mode);
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
