void ex4() {
    // abre o arquivo ROOT e acessa a árvore
    TFile *file = TFile::Open("tree.root");
    TTree *tree = (TTree*)file->Get("tree1");

    // determina a média da energia do feixe
    TH1F *hEnergy = new TH1F("hEnergy", "Beam Energy", 100, 0, 200);
    tree->Draw("ebeam>>hEnergy", "", "goff"); // "goff" para não desenhar o histograma agora
    double meanEnergy = hEnergy->GetMean(); // média da energia
    delete hEnergy;

    // define um TCut para eventos onde a energia do feixe está fora da média por mais de 0.2
    TCut cut = Form("abs(ebeam - %f) > 0.2", meanEnergy);

    // cria um histograma do momento total para eventos que passam pelo corte
    TH1F *hMomentum = new TH1F("hMomentum", "Total Momentum", 100, 135, 150);
    TString totalMomentum = "sqrt(px*px + py*py + pz*pz)";
    tree->Draw(totalMomentum+">>hMomentum", cut); // preenche o histograma com o corte na média de energia previamente definido

    // plota o histograma
    TCanvas *c1 = new TCanvas("c1", "Total Momentum Distribution", 800, 600);
    hMomentum->Draw();

    // salva o histograma em um arquivo
    c1->SaveAs("momentum_distribution.png"); 

    file->Close();
}

