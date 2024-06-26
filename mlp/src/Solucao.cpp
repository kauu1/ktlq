#include "Solucao.h"
#include "Data.h"
#include <algorithm>
#include <vector>

void exibir_solucao(Solucao &s, Data *dados){

    std::cout << "Solução: " << std::endl;
    for(int i = 0; i < s.sequencia.size() - 1; i++){
        std::cout << s.sequencia[i] << " -> ";
    }
    std::cout << s.sequencia.back() << std::endl;

    if(s.custoS != 0){
        std::cout << "CustoS: " << s.custoS << std::endl;
    }else{
        calcula_custoS(s, dados);
        std::cout << "CustoS: " << s.custoS << std::endl;
    }

    if(s.custoA != 0){
        std::cout << "CustoA: " << s.custoA << std::endl;
    }else{
        calcula_custoA(s, dados);
        std::cout << "CustoA: " << s.custoA << std::endl;
    }
}

void calcula_custoS(Solucao &s, Data *dados){
    s.custoS = 0;
    
    for(int i = 0; i < s.sequencia.size() - 1; i++){
        s.custoS += dados->getDistance(s.sequencia[i], s.sequencia[i+1]);
    }

}


void calcula_custoA(Solucao &s, Data *dados){
    s.custoA = 0;
    
    for(int i = 0; i < s.sequencia.size(); i++){
        for(int j = 0; j < i; j++){
            s.custoA += dados->getDistance(s.sequencia[j], s.sequencia[j+1]);
        }
    }

}


Solucao perturbacao(Solucao &s, Data *data){

    Solucao perturbada = s;

    std::vector<int> bloco1, bloco2;
    int size_b1, size_b2;

    size_b1 = rand() % (perturbada.sequencia.size()/10) + 2;
    size_b2 = rand() % (perturbada.sequencia.size()/10) + 2;

    bloco1.reserve(size_b1);
    bloco2.reserve(size_b2);


    int posicao_b1, posicao_b2;

    posicao_b1 = (rand() % (perturbada.sequencia.size() - (size_b1+1))) + 1;

    posicao_b2 = (rand() % (perturbada.sequencia.size() - (size_b2+1))) + 1;

    while(posicao_b2 < posicao_b1+size_b1 && posicao_b1 < posicao_b2+size_b2){
        posicao_b2 = (rand() % (perturbada.sequencia.size() - (size_b2+1))) + 1;
    }

    // std::cout << "[b1] posicao: " << posicao_b1 << ", tamanho: " << size_b1 << std::endl; 
    // std::cout << "[b2] posicao: " << posicao_b2 << ", tamanho: " << size_b2 << std::endl; 
    

    for(int i = 0; i < size_b1; i++){
        bloco1.push_back(perturbada.sequencia[posicao_b1+i]);
    }
    for(int i = 0; i < size_b2; i++){
        bloco2.push_back(perturbada.sequencia[posicao_b2+i]);
    }
    

    if(posicao_b1 > posicao_b2){

        perturbada.sequencia.erase(perturbada.sequencia.begin()+posicao_b1, perturbada.sequencia.begin()+posicao_b1+size_b1);
        perturbada.sequencia.insert(perturbada.sequencia.begin()+posicao_b1, bloco2.begin(), bloco2.end());
        perturbada.sequencia.erase(perturbada.sequencia.begin()+posicao_b2, perturbada.sequencia.begin()+posicao_b2+size_b2);
        perturbada.sequencia.insert(perturbada.sequencia.begin()+posicao_b2, bloco1.begin(), bloco1.end());
    }else{

        perturbada.sequencia.erase(perturbada.sequencia.begin()+posicao_b2, perturbada.sequencia.begin()+posicao_b2+size_b2);
        perturbada.sequencia.insert(perturbada.sequencia.begin()+posicao_b2, bloco1.begin(), bloco1.end());
        perturbada.sequencia.erase(perturbada.sequencia.begin()+posicao_b1, perturbada.sequencia.begin()+posicao_b1+size_b1);
        perturbada.sequencia.insert(perturbada.sequencia.begin()+posicao_b1, bloco2.begin(), bloco2.end());
    }
    
    return perturbada;
}
