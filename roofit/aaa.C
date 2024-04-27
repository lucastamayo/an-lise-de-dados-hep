#include <Riostream.h>
#include <TFile.h>
#include <RooDataSet.h>
#include <RooRealVar.h>

void aaa() {
    TFile *file = TFile::Open("DataSet_lowstat.root");
    RooDataSet *data = nullptr;
    file->GetObject("data", data);

    if (data) {
        data->Print();   // Informações gerais sobre o RooDataSet

        // Acessar e imprimir a primeira entrada
        const RooArgSet* row = data->get(0);
        if (row) {
            row->Print("v");  // Imprime todas as variáveis na primeira entrada
        }
    } else {
        std::cout << "RooDataSet 'data' não encontrado." << std::endl;
    }

    file->Close();
}
