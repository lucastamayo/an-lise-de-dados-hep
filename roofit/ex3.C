#include <TFile.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooCBShape.h>
#include <RooPolynomial.h>
#include <RooAddPdf.h>
#include <RooPlot.h>
#include <RooFit.h>
#include <TCanvas.h>
#include <TLegend.h>

void ex3() {
    // abre o arquivo ROOT e obtém o RooDataSet
    TFile* file = TFile::Open("DataSet_lowstat.root");
    RooDataSet* data = (RooDataSet*)file->Get("data");

    // define a variável observável
    RooRealVar x("mass", "mass [GeV]", 2, 6); // tomando o conjunto de variáveis mass disponíveis dentro de Data

    // parâmetros do Crystal Ball para J/ψ
    RooRealVar mean_jpsi("mean_jpsi", "Média do J/psi", 3.1, 3.0, 3.2);
    RooRealVar sigma_jpsi("sigma_jpsi", "Desvio padrão do J/psi", 0.03, 0.01, 0.05);
    RooRealVar alpha_jpsi("alpha_jpsi", "Alpha do J/psi", 1, 0.5, 1.5);
    RooRealVar n_jpsi("n_jpsi", "n do J/psi", 5, 1, 10);
    RooCBShape cb_jpsi("cb_jpsi", "Crystal Ball para J/psi", x, mean_jpsi, sigma_jpsi, alpha_jpsi, n_jpsi);

    // parâmetros do Crystal Ball para ψ(2S)
    RooRealVar mean_psi2S("mean_psi2S", "Média do psi(2S)", 3.7, 3.6, 3.8);
    RooRealVar sigma_psi2S("sigma_psi2S", "Desvio padrão do psi(2S)", 0.03, 0.01, 0.05);
    RooRealVar alpha_psi2S("alpha_psi2S", "Alpha do psi(2S)", 1, 0.5, 1.5);
    RooRealVar n_psi2S("n_psi2S", "n do psi(2S)", 5, 1, 10);
    RooCBShape cb_psi2S("cb_psi2S", "Crystal Ball para psi(2S)", x, mean_psi2S, sigma_psi2S, alpha_psi2S, n_psi2S);

    // parâmetros do Background Polinomial
    RooRealVar a0("a0", "coeficiente a0", 0.1, -1, 1);
    RooRealVar a1("a1", "coeficiente a1", 0.1, -1, 1);
    RooPolynomial bkg("bkg", "Background Polinomial", x, RooArgSet(a0, a1));

    // coeficientes para o modelo estendido
    RooRealVar nsig_jpsi("nsig_jpsi", "Número de eventos de sinal J/psi", 500, 0, 10000);
    RooRealVar nsig_psi2S("nsig_psi2S", "Número de eventos de sinal psi(2S)", 100, 0, 5000);
    RooRealVar nbkg("nbkg", "Número de eventos de fundo", 1000, 0, 10000);

    // modelo total (sinal + background)
    RooAddPdf model("model", "Modelo total", RooArgList(cb_jpsi, cb_psi2S, bkg), RooArgList(nsig_jpsi, nsig_psi2S, nbkg));

    // ajusta os dados para o modelo de máxima verossimilhança extendida, conforme proposto no exercício
    RooFitResult* fitResult = model.fitTo(*data, RooFit::Extended(), RooFit::Save());

    // plotagem do resultado do ajuste
    TCanvas* c = new TCanvas("c", "Ajuste de ressonâncias", 800, 600);
    RooPlot* frame = x.frame(RooFit::Title("Fit J/#psi e #psi(2S) com fundos"));
    // plotagem dos dados
    data->plotOn(frame);

    // plotagem do modelo completo
    model.plotOn(frame);

    model.plotOn(frame, RooFit::Components(cb_jpsi), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed), RooFit::Name("JpsiFit"));
    model.plotOn(frame, RooFit::Components(cb_psi2S), RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen), RooFit::Name("Psi2SFit"));

    frame->Draw();



    // adiciona uma caixa de estatística para alguns parâmetros
    RooArgSet params(mean_jpsi, sigma_jpsi, mean_psi2S, sigma_psi2S);
    model.paramOn(frame, RooFit::Parameters(params), RooFit::Layout(0.55, 0.9, 0.9), RooFit::Format("NEAU", RooFit::AutoPrecision(2)));


    gStyle->SetStatFontSize(0.025);
    gStyle->SetStatY(0.9); 
    gStyle->SetStatX(0.9); 

    RooRealVar* mean_jpsi_result = (RooRealVar*)fitResult->floatParsFinal().find("mean_jpsi");
    RooRealVar* sigma_jpsi_result = (RooRealVar*)fitResult->floatParsFinal().find("sigma_jpsi");
    RooRealVar* mean_psi2S_result = (RooRealVar*)fitResult->floatParsFinal().find("mean_psi2S");
    RooRealVar* sigma_psi2S_result = (RooRealVar*)fitResult->floatParsFinal().find("sigma_psi2S");

    // adiciona a legenda
    TLegend* leg = new TLegend(0.55, 0.77, 0.88, 0.87);
    leg->AddEntry((TObject*)0, Form("Chi^2/NDF: %.3f", frame->chiSquare(fitResult->floatParsFinal().getSize())), "");
    leg->SetBorderSize(1);
    leg->SetFillColor(0);
    leg->AddEntry("JpsiFit", Form("J/#psi Fit: Mean = %.3f #pm %.3f GeV", mean_jpsi_result->getVal(), mean_jpsi_result->getError()), "l");
    leg->AddEntry("Psi2SFit", Form("#psi(2S) Fit: Mean = %.3f #pm %.3f GeV", mean_psi2S_result->getVal(), mean_psi2S_result->getError()), "l");
    leg->Draw();

    // salva o gráfico
    c->SaveAs("ex3.png");

    // limpeza da memória
    delete c;
    delete leg;
    file->Close(); // Fecha o arquivo ROOT
}
