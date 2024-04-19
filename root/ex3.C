void ex3() {
    // define um histograma
    TH1F *h1 = new TH1F("h1", "Histograma Gaussiano", 50, 0, 10);
    
    // define a semente do gerador de números aleatórios
    gRandom->SetSeed(0);
    
    // preenche o histograma com números aleatórios gaussianos
    for (int i = 0; i < 10000; ++i) {
        h1->Fill(gRandom->Gaus(5, 2));
    }
    
TCanvas *c1 = new TCanvas("c1", "Gáfico Gaussiana + Estatísticas", 200, 10, 700, 500);

    // desenha o histograma
    h1->Draw();

    // configura a caixa de estatísticas para mostrar as informações desejadas
    gStyle->SetOptStat(1111111);
    h1->SetStats(kTRUE); 

    // atualiza o canvas (para mostrar as estatísticas)
    gPad->Modified();
    gPad->Update();

    c1->SaveAs("ex3.png");
    
    std::cout << "Entradas: " << h1->GetEntries() << std::endl;
    std::cout << "Média: " << h1->GetMean() << std::endl;
    std::cout << "RMS: " << h1->GetRMS() << std::endl;
    std::cout << "Integral: " << h1->Integral() << std::endl;
    std::cout << "Underflows: " << h1->GetBinContent(0) << std::endl;
    std::cout << "Overflows: " << h1->GetBinContent(h1->GetNbinsX() + 1) << std::endl;
    std::cout << "Assimetria: " << h1->GetSkewness() << std::endl;
    std::cout << "Curtose: " << h1->GetKurtosis() << std::endl;
}
