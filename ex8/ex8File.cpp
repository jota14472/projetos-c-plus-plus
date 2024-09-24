#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

/** fun��o de inicializa��o do programa **/

const int numRegistos = 26;
int numRegistosExistentes = 0;
bool leuFicheiro = false;

void readfile(string localficheiro, string col1[numRegistos], int col2[numRegistos], string col3[numRegistos]) {

    string myText;
    string txtFinal = "";
    bool comeca = false;
    int comecarVar = 1, posicaoArray=0;
    string idadeAux;

    ifstream MyReadFile(localficheiro);

    while(getline (MyReadFile, myText)) {
        comecarVar = 1;
        idadeAux="";
        //cout << myText;
        if (myText == "<READ>") comeca = true;
        if (myText == "</READ>") comeca = false;

        if (comeca && myText!="<READ>") {
            col1[posicaoArray] = "";
            col3[posicaoArray] = "";
            for (int i=0; i< myText.length(); i++) {
                if (myText[i] == ';') {
                    comecarVar++;
                } else {
                    if (comecarVar == 1) {
                        col1[posicaoArray] = col1[posicaoArray] + myText[i];
                    } else if (comecarVar == 2) {
                        idadeAux = idadeAux + myText[i];
                        //col2[posicaoArray] = col2[posicaoArray] + myText[i];
                    } else if (comecarVar == 3) {
                        col3[posicaoArray] = col3[posicaoArray] + myText[i];
                    }
                }
            }
            col2[posicaoArray] = stoi(idadeAux);
            posicaoArray++;
            txtFinal = txtFinal + myText + "\n";
        }
    }
    MyReadFile.close();
    numRegistosExistentes = posicaoArray;
    leuFicheiro = true;

}

void writefile(string localficheiro, string col1[numRegistos], int col2[numRegistos], string col3[numRegistos]) {

    string txtTotal = "";

    ofstream MyFile(localficheiro);

    txtTotal += "<READ>\n";

    for (int i=0; i<numRegistosExistentes; i++) {
        txtTotal += col1[i]; //Nome
        txtTotal += ";";
        txtTotal += to_string(col2[i]); //Idade
        txtTotal += ";";
        txtTotal += col3[i]; //Localidade
        txtTotal += "\n";
    }

    txtTotal += "</READ>\n";

    MyFile << txtTotal;

    MyFile.close();

}

void mostraDados(string col[numRegistos]) {
    for (int i=0; i<numRegistosExistentes; i++) {
        cout << "#" << i << " - " << col[i] << "\n";
    }
}

void mostraDadosInteiros(int col[numRegistos]) {
    for (int i=0; i<numRegistosExistentes; i++) {
        cout << col[i] << "\n";
    }
}

void popularDadosInteiros(int col[numRegistos]) {
    for (int i=0; i<numRegistos; i++) {
       col[i]=0;
    }
}

void mostraRegistos(string col1[numRegistos], int col2[numRegistos], string col3[numRegistos]) {

    for (int i=0; i<numRegistosExistentes; i++) {
        cout << "#" << i << " - ";
        cout << col1[i];
        cout << " | ";
        cout << to_string(col2[i]) << " anos ";
        cout << " | ";
        cout << col3[i];
        cout << "\n";
    }

}

int mostraMenuPrincipal() {
    system("cls");
    int opx = 0;
    cout << "**** LEITURA / ESCRITA DE FICHEIROS **** \n\n\n";
    cout << "1 - Ler Dados do ficheiro" << endl;
    if (leuFicheiro) {
        cout << "2 - Gravar Dados do ficheiro" << endl;
        cout << "3 - Mostra Nomes Lidos " << endl;
        cout << "4 - Mostra Localidades Lidas " << endl;
        cout << "5 - Mostra Idades Lidas " << endl;
        cout << "6 - Mostra Registos da BD " << endl;
        cout << "11 - Inserir Registo da BD " << endl;
        cout << "12 - Alterar Registo da BD " << endl;
        cout << "13 - Apagar Registo da BD " << endl;
    }
    cout << "0 - Sair do programa" << endl;
    cout << "O que pretende fazer?" << endl;
    cin >> opx;

    return opx;

}

void inserirRegisto(string nomes[numRegistos], int idades[numRegistos], string localidades[numRegistos]) {

    string nome, localidade;
    int idade;

    cout << "Vai inserir um registo" << endl;
    cout << endl << "Diga o nome do novo registo: ";
    cin >> nome;
    cout << endl << "Diga a idade do novo registo: ";
    cin >> idade;
    cout << endl << "Diga a localidade do novo registo: ";
    cin >> localidade;

    nomes[numRegistosExistentes] = nome;
    idades[numRegistosExistentes] = idade;
    localidades[numRegistosExistentes] = localidade;
    numRegistosExistentes++;

}

void alterarRegisto(string nomes[numRegistos], int idades[numRegistos], string localidades[numRegistos]) {


}

void apagarRegisto(string nomes[numRegistos], int idades[numRegistos], string localidades[numRegistos]) {

    int numero;
    int op;

    cout << "Vai apagar um registo" << endl;
    cout << endl << "Diga o numero do registo que deseja eliminar: ";
    cin >> numero;

    if (numero < numRegistosExistentes && numero >= 0) {
        cout << "Tem a certeza que quer eliminar o seguinte registo?: " << endl;
        cout << nomes[numero] << ", " << idades[numero] << ", " << localidades[numero];
        cout << endl << "Resposta(1 - Sim / 0 - N�o): ";
        cin >> op;
        if (op == 1) {
           for (int i=numero; i < (numRegistosExistentes - 1); i++ ) {
                nomes[i] = nomes[i+1];
                idades[i] = idades[i+1];
                localidades[i] = localidades[i+1];
            }
            numRegistosExistentes--;

        } else {
        cout << "Nao temos nenhum registo com esse numero" << endl << "Continua(1-Sim)";
        cin >> op;
        }

    }

}


int main() {

    string nomes[numRegistos], localidades[numRegistos];
    int idades[numRegistos];
    int op = 0;

    do {

      op = mostraMenuPrincipal();

      switch (op) {
      case 1:
        numRegistosExistentes = 0;
        popularDadosInteiros(idades);
        readfile("20240408_angeloferreira.txt", nomes, idades, localidades);
        break;

      case 2:
        writefile("20240408_angeloferreira.txt", nomes, idades, localidades);
        break;

      case 3:
        system("cls");
        mostraDados(nomes);
        cout << endl << "Pretende prosseguir?" << endl;
        getch();
        break;

      case 4:
        system("cls");
        mostraDados(localidades);
        cout << endl << "Pretende prosseguir?" << endl;
        getch();
        break;

      case 5:
        system("cls");
        mostraDadosInteiros(idades);
        cout << endl << "Pretende prosseguir?" << endl;
        getch();
        break;

      case 6:
        system("cls");
        mostraRegistos(nomes, idades, localidades);
        cout << endl << "Pretende prosseguir?" << endl;
        getch();
        break;

      case 11:
        inserirRegisto(nomes, idades, localidades);
        cout << endl << "Pretende prosseguir?" << endl;
        getch();
        break;

      case 12:
        alterarRegisto(nomes, idades, localidades);
        cout << endl << "Pretende prosseguir?" << endl;
        getch();
        break;

      case 13:
        apagarRegisto(nomes, idades, localidades);
        cout << endl << "Pretende prosseguir?" << endl;
        getch();
        break;

      default:
        break;

      }

    } while (op != 0);

    return 0;
}
