#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooGaussian.h>
#include <RooCBShape.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <RooFitResult.h>

void ex2() {
    // define a variável observável
    RooRealVar x("x", "Dados", -10, 10);

    // parâmetros do Crystal Ball
    RooRealVar mean("mean", "Média", 0, -10, 10);
    RooRealVar sigma("sigma", "Desvio padrão", 1, 0.1, 10);
    RooRealVar alpha("alpha", "Transição", 1, 0, 5);
    RooRealVar n("n", "Cauda", 5, 0, 10);

    // cria a Crystal Ball p.d.f
    RooCBShape crystalBall("crystalBall", "Função Crystal Ball", x, mean, sigma, alpha, n);

    // gera um conjunto de 10000 dados
    RooDataSet* data = crystalBall.generate(x, 10000); // 10000 eventos

    // ajustar o modelo aos dados
    crystalBall.fitTo(*data);

    // cria um frame de RooPlot para desenhar os dados e o ajuste
    RooPlot* xframe = x.frame(RooFit::Title("Ajuste Crystal Ball"));    data->plotOn(xframe);
    crystalBall.plotOn(xframe);

    // adiciona a caixa de informação estatística ao gráfico
    crystalBall.paramOn(xframe, RooFit::Layout(0.6, 0.9, 0.9));
    // desenha o gráfico em um canvas do ROOT
    TCanvas* c = new TCanvas("c", "Ajuste Crystal Ball", 800, 600);
    xframe->Draw();
    c->SaveAs("ex2.png");
    c->Draw();
}
