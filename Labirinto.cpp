#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

#define linhao "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
#define esp "                               "
#define maxn 110
#define inf 1000000000

void inicio();
void WASD();
void inter();
void imprimematriz(char **m, int l, int c, string dificuldade);
string dificuldadelabirinto();
string dificuldademinotauro();
void ler(char **m, int *a, int *b, string dL);
void tamanho(int *a, int *b, string dL);
void andarP(char **m);
void andarM1(char **m, int v[], int *aux, int *auxOposto);
void OK();
void carregandofase();
void BFS(int l, int c, int x, int y);
void andarM3(char **m);
void perdeu();
void ganhou();

int distancia[maxn][maxn], processado[maxn][maxn];
int iP, jP, iM, jM, iO, jO;

int main () {

    inicio();
    inter();
    WASD();

    char **m;
    string dL, dM, resultado;
    int l, c, v[4], aux=0, auxOposto=5;

    dL=dificuldadelabirinto();
    dM=dificuldademinotauro();
    tamanho(&l, &c, dL);

    m = new char*[l];
    for(int i=0; i<l; i++) m[i] = new char[c];

    ler(m, &l, &c, dL);
    carregandofase();

    while(true){
        cout<<linhao;

        imprimematriz(m, l, c, dL);

        andarP(m);

        if(iP==iM and jP==jM){
            resultado="PERDEU";
            m[iP][jP]='M';
            break;
        }
        if(iP==iO and jP==jO){
            resultado="GANHOU";
            break;
        }

        if(dM=="1")
            andarM1(m, v, &aux, &auxOposto);
        else if(dM=="2"){
            andarM1(m, v, &aux, &auxOposto);
            andarM1(m, v, &aux, &auxOposto);
        }
        else if(dM=="3"){
            BFS(iP, jP, l, c);
            andarM3(m);

            for(int i=0; i<l; i++){
                for(int j=0; j<c; j++){

                    processado[i][j]=0;
                    if(m[i][j]=='|')  processado[i][j]=true;

                }
            }
        }
        if(iP==iM and jP==jM){
            resultado="PERDEU";
            break;
        }
    }
    imprimematriz(m, l, c, dL);
    if(resultado=="PERDEU") perdeu();
    if(resultado=="GANHOU") ganhou();
}

void inicio(){

    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<"          "<<esp
        <<"Aperte qualquer botao para abrir jogo"<<endl;
    getch();

    cout<<linhao<<"                      "<<esp
        <<"Abrindo o jogo."<<linhao;
    Sleep(500);
    cout<<linhao<<"                      "<<esp
        <<"Abrindo o jogo.."<<linhao;
    Sleep(500);
    cout<<linhao<<"                      "<<esp
        <<"Abrindo o jogo..."<<linhao;
    Sleep(500);

    keybd_event(VK_MENU  , 0x36, 0, 0);
    keybd_event(VK_RETURN, 0x1C, 0, 0);
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU  , 0x38, KEYEVENTF_KEYUP, 0);
}

void inter(){

    ifstream arq;
    arq.open("Minotauro.txt");

    string linha;
    cout<<linhao<<linhao<<"\n\n\n";

    if(arq.is_open()){
            while(getline(arq, linha)){
              cout<<esp<<"   "<<linha<<endl;
            }
        arq.close();
    }

    else cout<<"deu ruim";

    cout<<linhao<<"\n"<<"     "<<esp<<esp<<"Aperte qualquer botao para iniciar"<<endl;
    getch();

}

void WASD(){

    cout<<linhao<<linhao<<esp<<esp<<"       Utilize as teclas para escolher"
        <<endl<<endl<<esp<<esp<<"                      "<<"^"<<endl
        <<esp<<esp<<"                      "<<"W"<<endl<<endl
        <<esp<<esp<<"                      "<<"S"<<endl
        <<esp<<esp<<"                      "<<"v"<<endl<<endl
        <<esp<<"                          "<<"Depois de escolhido, aperte qualquer tecla para selecionar";
    cout<<linhao<<"\n"<<"    "<<esp<<esp<<"Aperte qualquer botao para prosseguir"<<endl;
    getch();
}

void imprimematriz(char **m, int l, int c, string dificuldade){

    system("cls");
    if(dificuldade=="Facil"){
        cout<<linhao;
        for(int i=0; i<l; i++){
            cout<<esp<<esp<<"            ";
            for(int j=0; j<c; j++){
                cout<<m[i][j];
            }
            cout<<endl;
        }
        cout<<"\n\n\n";
    }
    else if(dificuldade=="Medio"){
        cout<<linhao;
        for(int i=0; i<l; i++){
            cout<<esp<<esp<<"       ";
            for(int j=0; j<c; j++){
                cout<<m[i][j];
            }
            cout<<endl;
        }
    }
    else{
        for(int i=0; i<l; i++){
            cout<<esp<<"                            ";
            for(int j=0; j<c; j++){
                cout<<m[i][j];
            }
            cout<<endl;
        }
    }

}

string dificuldadelabirinto(){

    cout<<linhao<<linhao<<"\n\n"<<esp<<esp<<"     "
        <<"Escolha a dificuldade do labirinto:"<<endl<<endl<<esp<<esp
        <<"               "<<"   ->Facil"<<endl<<esp<<esp<<"           "
        <<"       .Medio"<<endl<<esp<<esp<<"           "
        <<"       .Dificil\n\n"<<esp<<esp<<linhao;

    string a="->", b=".", c=".";
    char t;

    if(kbhit){

        t=getch();
        while(t=='s' or t=='w' or t=='S' or t=='W'){

            if(t=='s' or t=='S')
                if(a=="->"){
                    b="->";
                    a=".";
                }
                else if(b=="->"){
                    c="->";
                    b=".";
                }
            if(t=='w' or t=='W'){
                if(c=="->"){
                    b="->";
                    c=".";
                }
                else if(b=="->"){
                    a="->";
                    b=".";
                }
            }

                system("cls");
                cout<<linhao<<linhao<<"\n\n"<<esp<<esp<<"     "
                <<"Escolha a dificuldade do labirinto:"<<endl<<endl<<esp<<esp
                <<"              "<<"    "<<a<<"Facil"<<endl<<esp<<esp<<"           "
                <<"       "<<b<<"Medio"<<endl<<esp<<esp<<"           "
                <<"       "<<c<<"Dificil\n\n"<<esp<<esp<<linhao;
            t=getch();

        }
    }

    string dificuldade;

    if(a=="->") dificuldade="Facil";
    if(b=="->") dificuldade="Medio";
    if(c=="->") dificuldade="Dificil";
    OK();

    if(dificuldade=="Facil" or dificuldade=="Medio" or dificuldade=="Dificil"){

        cout<<linhao<<linhao<<esp<<esp<<"             "
            <<"Dificuldade escolhida"<<endl<<esp<<esp<<"                   "<<"-> "<<dificuldade<<linhao<<"\n\n\n\n";

        Sleep(2000);
        return dificuldade;
    }
    else{
        cout<<linhao<<linhao<<esp<<esp<<"            "
            <<"Dificuldade invalida"<<endl<<linhao<<esp<<esp<<"              "
            <<"Tente novamente\n\n"<<"->";
        Sleep(2000);
        cout<<linhao<<linhao;
        dificuldade=dificuldadelabirinto();
        return dificuldade;
    }

}

string dificuldademinotauro(){

    string dificuldade;

    system("cls");
    cout<<linhao;
    cout<<esp<<"  "<<"Escolha o nivel de inteligencia do minotauro:\n\n\n\n"<<endl;
    cout<<esp<<"  "<<"->1. O minotauro escolhe aleatoriamente uma direcao valida e da um passo a frente\n"<<endl
        <<esp<<"  "<<"2. O minotauro da 2 passos consecutivos.\n"<<esp<<"     Para cada passo, ele o escolhe aleatoriamente seguindo uma direcao valida como descrito no item acima\n"<<endl
        <<esp<<"  "<<"3. O minotauro escolhe uma direcao valida que mais se aproxima do personagem e da um passo a frente.\n\n";

    string a="->", b="", c="";
    char t;

    if(kbhit){

        t=getch();
        while(t=='s' or t=='w' or t=='S' or t=='W'){

            if(t=='s' or t=='S')
                if(a=="->"){
                    b="->";
                    a="";
                }
                else if(b=="->"){
                    c="->";
                    b="";
                }
            if(t=='w' or t=='W'){
                if(c=="->"){
                    b="->";
                    c="";
                }
                else if(b=="->"){
                    a="->";
                    b="";
                }
            }

            system("cls");
            cout<<linhao;
            cout<<esp<<"  "<<"Escolha o nivel de inteligencia do minotauro:\n\n\n\n"<<endl;
            cout<<esp<<"  "<<a<<"1. O minotauro escolhe aleatoriamente uma direcao valida e da um passo a frente\n"<<endl
                <<esp<<"  "<<b<<"2. O minotauro da 2 passos consecutivos.\n"<<esp<<"     Para cada passo, ele o escolhe aleatoriamente seguindo uma direcao valida como descrito no item acima\n"<<endl
                <<esp<<"  "<<c<<"3. O minotauro escolhe uma direcao valida que mais se aproxima do personagem e da um passo a frente.\n\n";
            t=getch();

        }
    }

    if(a=="->") dificuldade="1";
    if(b=="->") dificuldade="2";
    if(c=="->") dificuldade="3";
    OK();

    if(dificuldade=="1" or dificuldade=="2" or dificuldade=="3"){

        cout<<linhao<<linhao<<esp<<esp<<"            "
            <<"Inteligencia escolhida"
            <<endl<<esp<<esp<<"                    "
            <<"-> "<<dificuldade<<"\n\n\n\n"<<linhao;

        Sleep(2000);
        return dificuldade;
    }
    else{
        cout<<linhao
            <<linhao<<esp<<esp<<"            "<<"Inteligencia invalida"<<endl
            <<linhao<<esp<<esp<<"              "<<"Tente novamente\n\n"<<"->";
        Sleep(2000);
        dificuldade=dificuldademinotauro();
        return dificuldade;
    }

}

void tamanho(int *a, int *b, string dL){

    int l, c;

    ifstream arq;

    if (dL =="Facil" or dL=="facil")
         arq.open("facil.txt");

    else if (dL=="Medio" or dL=="medio")
         arq.open("medio.txt");

    else if(dL=="Dificil" or dL=="dificil")
         arq.open("dificil.txt");


    if(arq.is_open()){
        arq>>l>>c;
        arq.close();
    }

    else cout<<"\n\n\n\nERRO 431";

    *a=l;
    *b=c;

}

void ler(char **m, int *a, int *b, string dL){

    int l, c;

    ifstream arq;

    if (dL=="Facil" or dL=="facil")
         arq.open("facil.txt");

    else if (dL=="Medio" or dL=="medio")
         arq.open("medio.txt");

    else if(dL=="Dificil" or dL=="dificil")
         arq.open("dificil.txt");

    if(arq.is_open()){
        char a;
        int i=0, j=0;

        arq>>l>>c;

        while(arq>>a){

            m[i][j]=a;

            if(a=='|'){
                processado[i][j]=true;
            }
            if(a=='P'){
                iP=i;
                jP=j;
            }
            else if(a=='M'){
                iM=i;
                jM=j;
            }
            else if(a=='O'){
                iO=i;
                jO=j;
            }
            j++;
            if(j==c){
                j=0;
                i++;
            }
        }
        arq.close();
    }
    else cout<<"\n\n\n\nERRO 432";

}

void andarP(char **m){

    int contw=0, conts=0, conta=0, contd=0;

    cout<<endl<<esp<<esp<<"         "<<"Escolha um destes caminhos\n"<<endl;
    if(m[iP-1][jP]!='|'){
        cout<<esp<<esp<<"                "<<"W -> cima"<<endl;
        contw=1;
    }

    if(m[iP+1][jP]!='|'){
        cout<<esp<<esp<<"                "<<"S -> baixo"<<endl;
        conts=1;
    }

    if(m[iP][jP-1]!='|'){
        cout<<esp<<esp<<"                "<<"A -> esquerda"<<endl;
        conta=1;
    }

    if(m[iP][jP+1]!='|'){
        cout<<esp<<esp<<"                "<<"D -> direita"<<endl;
        contd=1;
    }

    cout<<"\n\n\n\n\n\n\n";
    string a;
    char t;

    if(kbhit){

        t=getch();
        while(true){
            if(contw==1 and (t=='w' or t=='W')){
                break;
            }
            if(conta==1 and (t=='a' or t=='A')){
                break;
            }
            if(conts==1 and (t=='s' or t=='S')){
                break;
            }
            if(contd==1 and (t=='d' or t=='D')){
                break;
            }
            t=getch();
        }
    }

    cout<<esp<<"                "<<esp<<"Aguarde";

    m[iP][jP]='.';
    a=t;

    if((a=="w" or a=="W") and contw==1){
        m[iP-1][jP]='P';
        iP--;
    }
    else if((a=="s" or a=="S") and conts==1){
        m[iP+1][jP]='P';
        iP++;
    }
    else if((a=="a" or a=="A") and conta==1){
        m[iP][jP-1]='P';
        jP--;
    }
    else if((a=="d" or a=="D") and contd==1){
        m[iP][jP+1]='P';
        jP++;
    }
}

void andarM1(char **m, int v[], int *aux, int *auxOposto){

    int cont=0;

    if(iP==iM and jP==jM){
        return;
    }

    v[0]=0;
    v[1]=0;
    v[2]=0;
    v[3]=0;

    int i;

    if(m[iM-1][jM]!='|' and m[iM-1][jM]!='O'){
        v[0]=1;
        cont++;
        i=0;
    }
    if(m[iM+1][jM]!='|' and m[iM+1][jM]!='O'){
        v[1]=1;
        cont++;
        i=1;
    }
    if(m[iM][jM-1]!='|' and m[iM][jM-1]!='O'){
        v[2]=1;
        cont++;
        i=2;
    }
    if(m[iM][jM+1]!='|' and m[iM][jM+1]!='O'){
        v[3]=1;
        cont++;
        i=3;
    }

    while(true){

        if(cont==1){
            for(int j=0; j<4; j++){
                if(v[j]==1){
                    i=j;
                    break;
                }
            }
            break;
        }

        if(cont==2 and v[*auxOposto]==1){
            v[*auxOposto]=0;
            for(int j=0; j<4; j++){
                if(v[j]==1){
                    i=j;
                    break;
                }
            }
            break;
        }

        if(v[*aux]==0 and cont==1){
            for(int j=0; j<4; j++){
                if(v[j]==1){
                    i=j;
                    break;
                }
            }
            break;
        }

        unsigned seed = time(0);
        srand(seed);
        i=rand()%4;

        if(v[i]==1 and i!=*auxOposto) break;

    }

    m[iM][jM]='.';

    if(i==0){
        m[iM-1][jM]='M';
        iM--;
        *auxOposto=1;
        *aux=i;
    }
    else if(i==1){
        m[iM+1][jM]='M';
        iM++;
        *auxOposto=0;
        *aux=i;
    }
    else if(i==2){
        m[iM][jM-1]='M';
        jM--;
        *auxOposto=3;
        *aux=i;
    }
    else if(i==3){
        m[iM][jM+1]='M';
        jM++;
        *auxOposto=2;
        *aux=i;
    }



}

void carregandofase(){

    cout<<linhao<<esp<<esp<<"              "<<"Abrindo labirinto.\n\n\n\n"<<linhao;
    Sleep(500);
    cout<<linhao<<esp<<esp<<"              "<<"Abrindo labirinto..\n\n\n\n"<<linhao;
    Sleep(500);
    cout<<linhao<<esp<<esp<<"              "<<"Abrindo labirinto...\n\n\n\n"<<linhao;
    Sleep(500);
    system("cls");

}

void OK(){

    cout<<linhao;
    cout<<linhao<<esp<<esp<<"                 "<<"Carregando.\n\n\n\n"<<linhao;
    Sleep(500);
    cout<<linhao<<esp<<esp<<"                 "<<"Carregando..\n\n\n\n"<<linhao;
    Sleep(500);
    cout<<linhao<<esp<<esp<<"                 "<<"Carregando...\n\n\n\n"<<linhao;
    Sleep(500);
    system("cls");

}

void BFS(int l, int c, int x, int  y){

    typedef pair<int, int> pii;
    typedef pair<int, pii> piii;

    vector <piii> vizinhos[maxn];
    priority_queue<piii, vector<piii>, greater<piii> >fila;

    int mx[]={1,-1,0,0}, my[]={0,0,1,-1};

    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
          distancia[i][j]=inf;
        }
    }

    distancia[l][c]=0;

    fila.push(piii(distancia[l][c], pii(l, c)));

    while(!fila.empty()){
        int l = fila.top().second.first;
        int c = fila.top().second.second;
        fila.pop();

        if(processado[l][c])
          continue;

        processado[l][c] = true;

        for(int i=0; i<4; i++){
            int l2 = l + mx[i], c2 = c + my[i];
            if(l2 < 0 || l2 > x-1 || c2 < 0 || c2 > y-1) continue;

            if(processado[l2][c2]==false){

                distancia[l2][c2] = distancia[l][c] + 1;
                fila.push(piii (distancia[l2][c2], pii(l2, c2)));

            }
        }
    }
}

void andarM3(char **m){

    int menor=inf;
    int lado;

    if(distancia[iM-1][jM]<menor){
        menor=distancia[iM][jM];
        lado=0;
    }
    if(distancia[iM+1][jM]<menor){
        menor=distancia[iM][jM];
        lado=1;
    }
    if(distancia[iM][jM-1]<menor){
        menor=distancia[iM][jM];
        lado=2;
    }
    if(distancia[iM][jM+1]<menor){
        menor=distancia[iM][jM];
        lado=3;
    }

    m[iM][jM]='.';

    if(lado==0){
        m[iM-1][jM]='M';
        iM--;
    }
    else if(lado==1){
        m[iM+1][jM]='M';
        iM++;
    }
    else if(lado==2){
        m[iM][jM-1]='M';
        jM--;
    }
    else if(lado==3){
        m[iM][jM+1]='M';
        jM++;
    }
}

void perdeu(){
    ifstream arq;
    arq.open("perdeu.txt");

    string linha;
    cout<<linhao<<linhao<<"\n\n\n";

    if(arq.is_open()){
            while(getline(arq, linha)){
              cout<<esp<<"                    "<<linha<<endl;
            }
        arq.close();
    }
    else cout<<"deu ruim";
    cout<<linhao;
}

void ganhou(){
    ifstream arq;
    arq.open("ganhou.txt");

    string linha;
    cout<<linhao<<linhao<<"\n\n\n";

    if(arq.is_open()){
            while(getline(arq, linha)){
              cout<<esp<<"                 "<<linha<<endl;
            }
        arq.close();
    }
    else cout<<"deu ruim";
    cout<<linhao;
}
