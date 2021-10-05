#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*Criação de um Struct do tipo aluno e usando o typedef("criando um apelido")
para facilitar nas criações de função e no uso na função main!*/
typedef struct aluno{
    char nome[100];
    int matricula;
    float nota1, nota2, nota3, media;
}aluno;
/*criando os cabeçalhos das funções*/
void calculo_media(aluno *m, int tam);
void ordenar(aluno *aux, int qordem);
void sequencial(aluno *busca, int tambusca);
void aprovado(aluno *dados, int i);
/*criano a função principal(main)*/
int main(){
    char alter[100];
    char contlin ;
    float menorn1, menorn2,menorn3, Maiorn1, Maiorn2, Maiorn3;
    int posin1,posin2,posin3, posi;
    int lim=1, cont, i;
    //criação do ponteiro para abertura do arquivo.
    FILE *Arq;
    //abertura do arquivo e teste se não houve erro na abertura.
    Arq = fopen("alunos.txt", "r");
    if(Arq == NULL){
        printf("\n\tFalha na bertura do arquivo");
        system("pause");
        exit(1);
    }
    /*contagem de quantas linhas é composto o
    arquivo anteriormente aberto e valor dado a variável que irá fazer alocação de memoria*/
    while((contlin = fgetc(Arq)) != EOF){
        if(contlin == '\n'){
            lim++;
        }
        }
    /*fechamento do arquivo e em seguida o arquivo é novamente aberto para que o
    cursor seja alocado novamente no inicio do arquivo*/
    fclose(Arq);
    Arq = fopen("alunos.txt", "r");
    if(Arq == NULL){
        printf("\n\tFalha na bertura do arquivo");
        system("pause");
        exit(1);
    }
    /*criação do vetor do tipo struct por alocação de memoria*/
    aluno *dados = (aluno *)malloc(lim*sizeof (aluno));
    //criação de variável para passar os dados do arquivo para o vetor do tipo struct
    aluno copia;
    /*copia do arquivo para o vetor de struct*/
    for(i=0;i<lim;i++){
        fscanf(Arq,"%d %s %f %f %f", &copia.matricula, copia.nome, &copia.nota1, &copia.nota2, &copia.nota3);
        dados[i].matricula = copia.matricula;
        strcpy(dados[i].nome,copia.nome);
        dados[i].nota1 = copia.nota1;
        dados[i].nota2 = copia.nota2;
        dados[i].nota3 = copia.nota3;
    }
    /*fechamento do arquivo, a partir de agora toda manipulação dos dados se dará no veto struct
    até que salve e crie um novo arquivo com os novos dados*/
    fclose(Arq);
    int menu;
    /*criação do menu com as opções par manipulação dos dados alocados na struct*/
    do{
    printf("\n\tEscolha uma opcao:");
    printf("\n\t[1]Imprimir todos os elementos do arranjo");
    printf("\n\t[2]Imprimir apenas os nomes dos alunos");
    printf("\n\t[3]Imprimir o nome dos alunos e sua respectiva nota");
    printf("\n\t[4]Buscar os dados de um aluno usando a busca sequencial");
    printf("\n\t[5]Imprimir os alunos ordenados de acordo com a sua matricula");
    printf("\n\t[6]Editar as notas de um aluno,para isso e necesario que se busque os dados do aluno");
    printf("\n\t[7]Imprimir a matricula, nome e nota final do aluno que obteve a maior nota de todas");
    printf("\n\t[8]Imprimir a matricula, nome e nota final do aluno que obteve a menor nota de todas");
    printf("\n\t[9]Imprimir quantos alunos foram aprovados e quantos alunos foram reprovados, imprima ainda a media geral");
    printf("\n\t[0]Sair do programa: ");
    scanf("%i", &menu);
    calculo_media(dados,lim);
    /*Para gerenciar o menu, foi usado o switch case*/
    switch(menu){
    case 1:
        for(int i=0;i<lim;i++){
            printf("\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\n", dados[i].matricula, dados[i].nome, dados[i].nota1, dados[i].nota2, dados[i].nota3);
        }
        break;
    case 2:
        for(int i=0;i<lim;i++){
            printf("\n\tNome: %s", dados[i].nome);
        }
        printf("\n\n");
        break;
    case 3:
        for(int i=0;i<lim;i++){
            printf("\n\tNome: %s\n\tNota 1: %.2f\n\tNota 2: %.2f\n\tNota 3: %.2f\n\tMedia: %.2f\n\n", dados[i].nome, dados[i].nota1, dados[i].nota2, dados[i].nota3, dados[i].media);
        }
        break;
    case 4:
        sequencial(dados, lim);
        break;
    case 5:
        ordenar(dados,lim);
        for(i=0;i<lim;i++){
            printf("\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\tMedia %.2f\n\n", dados[i].matricula, dados[i].nome, dados[i].nota1, dados[i].nota2, dados[i].nota3, dados[i].media);
        }
        break;
    case 6:
        posi=-1;
        do{
        printf("\n\tDigite o nome que se busca: ");
        setbuf(stdin,NULL);
        fgets(alter,50, stdin);
        cont= strlen(alter);
        alter[cont-2]='\0';
        for(i=0;i<lim;i++){
            cont= strlen(dados[i].nome);
            dados[i].nome[cont]='\0';
            if(strcmp(alter,dados[i].nome) ==0 ){
                posi=i;
            }
        }
        if(posi>=0){
            printf("\n\tDigite a nova nota 1: ");
            scanf("%f", & dados[posi].nota1);
            printf("\n\tDigite a nova nota 2: ");
            scanf("%f", & dados[posi].nota2);
            printf("\n\tDigite a nova nota 3: ");
            scanf("%f", & dados[posi].nota3);
            printf("\n\t[1]-Alterar mais notas\n\t[0]-Finalizar: ");
            scanf("%i", & i);
        }
            }while(i!=0);
        break;
    case 7:
        Maiorn1=dados[0].nota1;
        posin1=0;
        Maiorn2=dados[0].nota2;
        posin2=0;
        Maiorn3=dados[0].nota3;
        posin3=0;
        for(int i=0;i<lim;i++){
            for(int j=0;j<lim;j++){
                if(Maiorn1<dados[j].nota1){
                    Maiorn1=dados[j].nota1;
                    posin1=j;
                }
                if(Maiorn2<dados[j].nota2){
                    Maiorn2=dados[j].nota2;
                    posin2=j;
                }
                if(Maiorn3<dados[j].nota3){
                    Maiorn3=dados[j].nota3;
                    posin3=j;
                }
            }
        }
        if(Maiorn1>Maiorn2&&Maiorn1>Maiorn3){
                posi=posin1;
        }
        else if(Maiorn2>Maiorn1&&Maiorn2>Maiorn3){
                posi=posin2;
        }
        else{
                posi=posin3;
        }
        printf("\n\tNome %s\n\tMedia %.2f\n\n", dados[posi].nome, dados[posi].media);
        break;
    case 8:
         menorn1=dados[0].nota1;
         posin1=0;
         menorn2=dados[0].nota2;
         posin2=0;
         menorn3=dados[0].nota3;
         posin3=0;
        for(int i=0;i<lim;i++){
            for(int j=0;j<lim;j++){
                if(menorn1>dados[j].nota1){
                    menorn1=dados[j].nota1;
                    posin1=j;
                }
                if(menorn2>dados[j].nota2){
                    menorn2=dados[j].nota2;
                    posin2=j;
                }
                if(menorn3>dados[j].nota3){
                    menorn3=dados[j].nota3;
                    posin3=j;
                }
            }
        }
        if(menorn1<menorn2&&menorn1<menorn3){
                posi=posin1;
        }
        else if(menorn2<menorn1&&menorn2<menorn3){
                posi=posin2;
        }
        else{
                posi=posin3;
        }
        printf("\n\tNome %s\n\tMedia %.2f\n\n", dados[posi].nome, dados[posi].media);
        break;
    case 9:
        aprovado(dados, lim);
        break;
    case 0:
        /*Esta opção ordena, cria e finaliza novo arquivo com os dados atualizados.*/
        ordenar(dados,lim);
        FILE *NovoArq;
        NovoArq = fopen("NovoArq.txt", "w");
        if(NovoArq == NULL){
        printf("\n\tFalha na bertura do arquivo");
        system("pause");
        exit(1);
        }
        for(i=0; i<lim; i++){
            fprintf(NovoArq,"\n\t%i\t%s\t%.2f\t%.2f\t%.2f\t%.2f",dados[i].matricula, dados[i].nome, dados[i].nota1, dados[i].nota2, dados[i].nota3, dados[i].media);
        }
        fclose(NovoArq);
        printf("\n\tObrigado por usar o sistema!\n\n");
        break;
    default:
        printf("\n\tOpcao invalida!\n\n");
    }
    system("pause");
    system("cls");
    }while(menu != 0);
    return 0;
}
/*funcção para calculo da media das notas esta função é
apenas para o calculo das médias que não foram informadas neste caso a função foi passada por parametros de
referencia e não retorna nada*/
void calculo_media(aluno *m, int tam){
    for(int i=0; i<tam; i++){
        m[i].media = (m[i].nota1+ m[i].nota2 +m[i].nota3)/3;
    }
}
/*função que não retorna nada é por parametros de referência
 por isso foi usado o void para a impressão em
ordem de matricula usado no menu principal na opção 5*/
void ordenar(aluno *aux, int qordem){
    aluno ordem;
    for(int i=0;i<qordem;i++){
        for(int j=0;j<qordem;j++){
            if(aux[i].matricula<aux[j].matricula){
                ordem=aux[i];
                aux[i]=aux[j];
                aux[j]=ordem;
            }
        }
    }
}
/*função para busca sequencial que não retorna nada por
isso foi usado o void e foi passado os parametros por referencia
 usada no menu principal na opção 4*/
void sequencial(aluno *busca, int tambusca){
    int menu, posi, comp, mat;
    char str[100];
    int posin1, posin2, posin3;
    float Maiorn1, Maiorn2, Maiorn3, Maiorm;
    float menorn1, menorn2, menorn3, menorm;
    /*Menu para saber em qual o critério da busca, se por nome, matricula, etc..*/
    printf("\n\tESCOLHA UMA OPCAO PARA BUSCA!");
    printf("\n\t[1]POR NOME");
    printf("\n\t[2]POR MATRICULA");
    printf("\n\t[3]POR MAIOR NOTA");
    printf("\n\t[4]POR MENOR NOTA");
    printf("\n\t[5]POR MAIOR MEDIA");
    printf("\n\t[6]POR MENOR MEDIA: ");
    scanf("%i", &menu);
    /*Para gerenciar o menu foi usado o Switch case*/
    switch(menu){
    case 1:
        printf("\n\tDigite o nome que se busca: ");
        setbuf(stdin,NULL);
        fgets(str,50, stdin);
        int car= strlen(str);
        str[car-1]='\0';
    /*para fazer a comparação e a busca por string é usado o comando strcmp que retorna um valor inteiro e
    se esse valor fo igual a 0 é porque as palavras são iguais entrando na estrutura if e guardondo a posição
    na variavel posi para que no final da busca ela possa imprimir o parametro buscado*/
        for(int i=0;i<tambusca;i++){
            if(strcmp(busca[i].nome,str)==0){
            posi=i;
          }
        }
        printf("\n\tO Aluno buscado e :\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\tMedia %.2f\n\n", busca[posi].matricula, busca[posi].nome, busca[posi].nota1, busca[posi].nota2, busca[posi].nota3, busca[posi].media);
        break;
    case 2:
        printf("\n\tDigite a matricula: ");
        scanf("%i", &mat);
        for(int i=0;i<tambusca;i++){
            if(mat==busca[i].matricula){
                posi=i;
            }
        }
        printf("\n\tO Aluno buscado e :\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\tMedia %.2f\n\n", busca[posi].matricula, busca[posi].nome, busca[posi].nota1, busca[posi].nota2, busca[posi].nota3, busca[posi].media);
        break;
    case 3:
        Maiorn1=busca[0].nota1;
        posin1=0;
        Maiorn2=busca[0].nota2;
        posin2=0;
        Maiorn3=busca[0].nota3;
        posin3=0;
        for(int i=0;i<tambusca;i++){
            for(int j=0;j<tambusca;j++){
                if(Maiorn1<busca[j].nota1){
                    Maiorn1=busca[j].nota1;
                    posin1=j;
                }
                if(Maiorn2<busca[j].nota2){
                    Maiorn2=busca[j].nota2;
                    posin2=j;
                }
                if(Maiorn3<busca[j].nota3){
                    Maiorn3=busca[j].nota3;
                    posin3=j;
                }
            }
        }
        if(Maiorn1>Maiorn2&&Maiorn1>Maiorn3){
                posi=posin1;
        }
        else if(Maiorn2>Maiorn1&&Maiorn2>Maiorn3){
                posi=posin2;
        }
        else{
                posi=posin3;
        }
        printf("\n\tO Aluno buscado e :\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\tMedia %.2f\n\n", busca[posi].matricula, busca[posi].nome, busca[posi].nota1, busca[posi].nota2, busca[posi].nota3, busca[posi].media);
        break;
    case 4:
        menorn1=busca[0].nota1;
        posin1=0;
        menorn2=busca[0].nota2;
        posin2=0;
        menorn3=busca[0].nota3;
        posin3=0;
        for(int i=0;i<tambusca;i++){
            for(int j=0;j<tambusca;j++){
                if(menorn1>busca[j].nota1){
                    menorn1=busca[j].nota1;
                    posin1=j;
                }
                if(menorn2>busca[j].nota2){
                    menorn2=busca[j].nota2;
                    posin2=j;
                }
                if(menorn3>busca[j].nota3){
                    menorn3=busca[j].nota3;
                    posin3=j;
                }
            }
        }
        if(menorn1<menorn2&&menorn1<menorn3){
                posi=posin1;
        }
        else if(menorn2<menorn1&&menorn2<menorn3){
                posi=posin2;
        }
        else{
                posi=posin3;
        }
        printf("\n\tO Aluno buscado e :\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\tMedia %.2f\n\n", busca[posi].matricula, busca[posi].nome, busca[posi].nota1, busca[posi].nota2, busca[posi].nota3, busca[posi].media);
        break;
    case 5:
        Maiorm = busca[0].media;
        posi=0;
        for(int i=0;i<tambusca;i++){
            if(Maiorm<busca[i].media);
            posi=i;
        }
        printf("\n\tO Aluno buscado e :\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\tMedia %.2f\n\n", busca[posi].matricula, busca[posi].nome, busca[posi].nota1, busca[posi].nota2, busca[posi].nota3, busca[posi].media);
        break;
    case 6:
        menorm = busca[0].media;
        posi = 0;
        for( int i=0;i<tambusca;i++){
            if(menorm>busca[i].media){
                posi=i;
            }
        }
        printf("\n\tO Aluno buscado e :\n\tMatricula %i\n\tNome %s\n\tNota 1 %.2f\n\tNota 2 %.2f\n\tNota 3 %.2f\n\tMedia %.2f\n\n", busca[posi].matricula, busca[posi].nome, busca[posi].nota1, busca[posi].nota2, busca[posi].nota3, busca[posi].media);
        break;
    default:
        printf("\n\tOPCAO INVALIDA!");
    }
}
void aprovado(aluno *dados, int i){
    int aprov = 0, reprov = 0;
    float media_geral=0.0;
    for(int j=0;j<i;j++){
        if(dados[j].media>=6.0){
            aprov++;
        }
        if(dados[j].media<6.0){
            reprov++;
        }

        media_geral = media_geral+dados[j].media;
    }
    printf("\n\tA quantidade de alunos aprovados e: %i\n\tA quantidade de alunos reprovados e: %i\n\tA media geral e: %.2f\n\n", aprov, reprov, media_geral/i);
    return 0;
}
