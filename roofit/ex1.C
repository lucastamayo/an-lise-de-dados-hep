#include <TFile.h>
#include <TNtuple.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooPolynomial.h>
#include <RooAddPdf.h>
#include <RooFit.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <TLegend.h>

void ex1() {
    // carrega o arquivo ROOT e obtém o TNtuple
    TFile *fin = TFile::Open("example_data.root");
    TNtuple *nt = (TNtuple*)fin->Get("nt");

    // define a variável mass
    RooRealVar mass("mass", "mass [GeV]", 0, 2);

    // cria o RooDataSet com a variável definida e o TNtuple
    RooDataSet data("data", "data", RooArgSet(mass), RooFit::Import(*nt));

    // define os parâmetros do modelo Gaussiano
    RooRealVar mean("mean", "mean", 1.0, 0.8, 1.2);
    RooRealVar sigma("sigma", "sigma", 0.1, 0.05, 0.2);

    // define os parâmetros para a função polinomial de fundo
    RooRealVar a0("a0", "a0", -0.1, -1.0, 1.0);
    RooRealVar a1("a1", "a1", 0.1, -1.0, 1.0);

    // cria as funções para sinal e fundo
    RooGaussian gauss("gauss", "gaussian", mass, mean, sigma);
    RooPolynomial poly("poly", "polynomial", mass, RooArgList(a0, a1));

    // coeficientes para o modelo combinado
    RooRealVar gaussFrac("gaussFrac", "fraction of gaussian", 0.5, 0.0, 1.0);

    // cria o modelo combinado
    RooAddPdf model("model", "gauss+poly", RooArgList(gauss, poly), RooArgList(gaussFrac));

    // ajusta o modelo combinado aos dados
    RooFitResult* r = model.fitTo(data, RooFit::PrintLevel(1), RooFit::Save());

    // cria um frame para o RooDataSet
    RooPlot *frame = mass.frame(RooFit::Title("Imported Unbinned Mass"));
    data.plotOn(frame);

    // plota o modelo combinado ajustado
    model.plotOn(frame, RooFit::LineColor(kBlack));
    model.plotOn(frame, RooFit::Components(poly), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
    model.plotOn(frame, RooFit::Components(gauss), RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));

    // adiciona a legenda e os parâmetros estatísticos
    TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.9);
    leg->SetFillColor(0);
    leg->SetLineColor(0); // Sem borda
    leg->SetTextSize(0.03); // Tamanho do texto
    leg->AddEntry(frame->findObject("model_Norm[mass]"), "Gauss+Poly Model", "l");
    leg->AddEntry(frame->findObject("poly_Norm[mass]"), "Polynomial Background", "l");
    leg->AddEntry(frame->findObject("gauss_Norm[mass]"), "Gaussian Signal", "l");
    // adiciona parâmetros estatísticos
    leg->AddEntry((TObject*)0, Form("Chi^2/NDF = %.2f", frame->chiSquare()), "");
    leg->AddEntry((TObject*)0, Form("Mean = %.4f #pm %.4f", mean.getValV(), mean.getError()), "");
    leg->AddEntry((TObject*)0, Form("Sigma = %.4f #pm %.4f", sigma.getValV(), sigma.getError()), "");
    leg->AddEntry((TObject*)0, Form("Gauss Fraction = %.3f #pm %.3f", gaussFrac.getValV(), gaussFrac.getError()), "");
    frame->addObject(leg); // Adiciona a legenda ao frame

    // desenha o frame
    TCanvas *c = new TCanvas("c", "Fit Example", 800, 600);
    frame->Draw();
    c->SaveAs("ex1.png");

    delete c;
    delete fin;
    delete r; // limpando a memória
}


