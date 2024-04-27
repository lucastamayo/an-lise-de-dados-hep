#include <TFile.h>
#include <RooDataSet.h>
#include <RooRealVar.h>
#include <iostream>

void InspectDataSet() {
    // Abre o arquivo ROOT
    TFile *file = TFile::Open("DataSet_lowstat.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Erro ao abrir o arquivo DataSet_lowstat.root" << std::endl;
        return;
    }

    // Carrega o RooDataSet
    RooDataSet *data = nullptr;
    file->GetObject("data", data);
    if (!data) {
        std::cerr << "RooDataSet 'data' não encontrado no arquivo." << std::endl;
        file->Close();
        return;
    }

    // Imprime informações gerais sobre o RooDataSet
    data->Print();

    // Obtém um conjunto de variáveis associadas ao RooDataSet e imprime
    const RooArgSet *vars = data->get();
    vars->Print("v");

    // Imprime os valores para cada entrada no RooDataSet
    for (int i = 0; i < data->numEntries(); ++i) {
        // Acessa a entrada i
        const RooArgSet *entry = data->get(i);
        std::cout << "Entrada " << i << ":" << std::endl;
        // Imprime todas as variáveis para a entrada i
        entry->Print("v");
        std::cout << std::endl;
    }

    // Fecha o arquivo ROOT
    file->Close();
}
