#include <TFile.h>
#include <TNtuple.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooFit.h>
#include <RooPlot.h>
#include <TCanvas.h>

void ex1b() {
    // carrega o arquivo ROOT e obtém o TNtuple
    TFile *fin = TFile::Open("example_data.root");
    TNtuple *nt = (TNtuple*)fin->Get("nt");

    // define a variável RooRealVar
    RooRealVar mass("mass", "mass [GeV]", 0.8, 1.2); 

    // cria o RooDataSet com a variável definida e o TNtuple
    RooDataSet data("data", "data", RooArgSet(mass), RooFit::Import(*nt));

    // imprime informações sobre o RooDataSet
    data.Print("v");

    // cria um frame para o RooDataSet
    RooPlot *frame3 = mass.frame(RooFit::Title("Imported Unbinned Mass"));
    data.plotOn(frame3);

    // define os parâmetros do modelo Gaussiano
    RooRealVar mean("mean", "mean", 1.0, 0.9, 1.1);
    RooRealVar sigma("sigma", "sigma", 0.1, 0.05, 0.15); 

    RooGaussian gauss("gauss", "gauss", mass, mean, sigma);

    // ajusta o modelo gaussiano aos dados
    gauss.fitTo(data, RooFit::PrintLevel(1), RooFit::Range("fitrange"));

    // plota o modelo gaussiano ajustado
    gauss.plotOn(frame3);
    gauss.paramOn(frame3, RooFit::Format("NEU", RooFit::AutoPrecision(2)), RooFit::Layout(0.6, 0.9, 0.9));
    frame3->Draw();

    // cria um canvas para desenhar o frame
    TCanvas *c3 = new TCanvas("exemplo03", "Gaussian Fit to Unbinned Data", 800, 400);
    frame3->Draw();
    c3->Draw();
    
    // salva o canvas em um arquivo
    c3->SaveAs("ex1b.png");
}
